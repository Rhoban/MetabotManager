#include <QTcpSocket>
#include "qhttpconnection.h"
#include "qhttpconnectionthread.h"

QHttpConnectionThread::QHttpConnectionThread(qintptr id, QObject *parent, QHttpHandler *handler_)
    : QThread(parent), handler(handler_)
{
    this->socketId = id;
}

void QHttpConnectionThread::run()
{
    auto socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketId))
    {
        // something's wrong, we just emit a signal
        /// emit error(socket->error());
        return;
    }

    QHttpConnection connection(socket, NULL, handler);
    QObject::connect(socket, SIGNAL(disconnected()),
                     this, SLOT(disconnected()));

    exec();
}

void QHttpConnectionThread::disconnected()
{
    deleteLater();
    exit(0);
}

