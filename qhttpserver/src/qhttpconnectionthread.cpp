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
    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketId))
    {
        // something's wrong, we just emit a signal
        /// emit error(socket->error());
        return;
    }

    QHttpConnection *connection = new QHttpConnection
            (socket, NULL, handler);
    QObject::connect(socket, SIGNAL(disconnected()),
                     this, SLOT(disconnected()));

    exec();
    connection->deleteLater();
    qDebug() << "End of exec()";
}

void QHttpConnectionThread::disconnected()
{
    qDebug() << "Disconnected";
    socket->deleteLater();
    QThread::quit();
}

