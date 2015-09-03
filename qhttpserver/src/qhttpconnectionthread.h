#ifndef QHTTPCONNECTIONTHREAD_H
#define QHTTPCONNECTIONTHREAD_H

#include <QThread>
#include "qhttphandler.h"

class QHttpConnectionThread : public QThread
{
    Q_OBJECT

public:
    QHttpConnectionThread(qintptr id, QObject *parent, QHttpHandler *handler);
    void run();

    QHttpHandler *handler;
    qintptr socketId;

public slots:
    void disconnected();
};

#endif // QHTTPCONNECTIONTHREAD_H
