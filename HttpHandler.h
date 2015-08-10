#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include <QObject>
#include <qhttprequest.h>
#include <qhttpresponse.h>
#include <json/json.h>

class MainWindow;
class HttpHandler : public QObject
{
    Q_OBJECT

public:
    HttpHandler(MainWindow *main_);

    void process(std::string request, Json::Value &parameters, Json::Value &response);

public slots:
    void handle(QHttpRequest *req, QHttpResponse *resp);

protected:
    MainWindow *mainW;
};

#endif // HTTPHANDLER_H
