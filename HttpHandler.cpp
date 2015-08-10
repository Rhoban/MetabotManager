#include <sstream>
#include <iostream>
#include "HttpHandler.h"
#include "MainWindow.h"

HttpHandler::HttpHandler(MainWindow *main_)
    : mainW(main_)
{
}

void HttpHandler::handle(QHttpRequest *req, QHttpResponse *resp)
{
    // Reading query & callback for JSONp processing
    QString data = req->url().query();
    QString callback = "";
    data = QUrl::fromPercentEncoding(data.toLatin1());
    QStringList parts = data.split("&");
    data = parts[0];
    for (int i=1; i<parts.size(); i++) {
        QString &part = parts[i];
        if (part.startsWith("callback=")) {
            callback = part.mid(9);
        }
    }
    if (data == "") {
        data = "null";
    }

    // Reading the request
    Json::Reader reader;
    Json::Value request;
    Json::Value response(Json::arrayValue);

    if (reader.parse(data.toStdString(), request)) {
        if (request.isArray() && request.size()<=2 && request[0].isString()) {
            try {
                response[0] = 1;
                Json::Value null;
                process(request[0].asString(), request.size()==2 ? request[1] : null, response[1]);
            } catch (std::string error) {
                response[0] = 0;
                response[1] = error;
            }
        } else {
            response[0] = 0;
            response[1] = "Bad request";
        }
    } else {
        response[0] = 0;
        response[1] = "Unable to parse the request";
    }

    Json::FastWriter writer;
    std::stringstream ss;
    if (callback != "") {
        ss << callback.toStdString() << "(";
    }
    ss << writer.write(response);
    if (callback != "") {
        ss << ");";
    }

    std::string responseData = ss.str();
    resp->setHeader("Content-length", QString("%1").arg(responseData.length()));
    resp->setHeader("Content-Type", "application/json; charset=\"utf-8\"");
    resp->writeHead(200);
    resp->write(QByteArray(responseData.c_str(), responseData.length()));
}

void HttpHandler::process(std::string request, Json::Value &parameters, Json::Value &response)
{
    if (request == "version") {
        response = "1.0";
    } else if (request == "command") {
        if (!parameters.isString()) {
            throw std::string("Command should be a string");
        }
        std::string command = parameters.asString()+"\r\n";

        if (!mainW->isConnected()) {
            throw std::string("Port is closed");
        }

        if (mainW->sendData(QString::fromStdString(command))) {
            response = mainW->getResponse().toStdString();
        } else {
            mainW->closeConnection();
            response = false;
        }
    } else if (request == "rhock") {
        response = Json::Value(Json::objectValue);
        response["version"] = "1.0";
        if (mainW->isConnected()) {
            mainW->sendData("rhock\r\nrhock\r\nrhock\r\n");
            response["rhock_ready"] = true;
        } else {
            response["rhock_ready"] = false;
        }
    } else if (request == "get") {
        mainW->checkConnection();
        if (!mainW->isConnected()) {
            throw std::string("Not connected");
        }
        response = Json::Value(Json::arrayValue);

        auto start = QDateTime::currentMSecsSinceEpoch();
        bool hasData = false;
        int timeout = 250;

        while (QDateTime::currentMSecsSinceEpoch()-start < timeout) {
            auto data = mainW->getData();

            if (data.length()) {
                hasData = true;
                for (int k=0; k<data.length(); k++) {
                    response.append((unsigned char)data.at(k));
                }
            } else {
                if (hasData) {
                    break;
                }
            }
            QThread::msleep(3);
        }
        if (hasData) {
            Json::FastWriter writer;
            std::cout << "Receiving:" << std::endl;
            std::cout << writer.write(response) << std::endl;
        }
    } else if (request == "send") {
        if (mainW->isConnected() && parameters.isArray()) {
            Json::FastWriter writer;
            std::cout << "Sending:" << std::endl;
            std::cout << writer.write(parameters) << std::endl;

            QString buffer;
            for (int k=0; k<parameters.size(); k++) {
                if (parameters[k].isInt()) {
                    buffer += (char)(parameters[k].asInt());
                }
            }
            mainW->sendData(buffer);
            response = true;
        } else {
            response = false;
        }
    } else if (request == "connected") {
        response = mainW->isConnected();
    } else {
        throw std::string("Unknown request");
    }
}
