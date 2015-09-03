#ifndef QHTTPHANDLER_H
#define QHTTPHANDLER_H

#include <qhttprequest.h>
#include <qhttpresponse.h>

class QHttpHandler
{
public:
    QHttpHandler();

    virtual void handle(QHttpRequest *req, QHttpResponse *resp)=0;
};

#endif // QHTTPHANDLER_H
