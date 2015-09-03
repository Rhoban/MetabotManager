/*
 * Copyright 2011-2014 Nikhil Marathe <nsm.nikhil@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef Q_HTTP_SERVER
#define Q_HTTP_SERVER

#define QHTTPSERVER_VERSION_MAJOR 0
#define QHTTPSERVER_VERSION_MINOR 1
#define QHTTPSERVER_VERSION_PATCH 0

#include "qhttpserverapi.h"
#include "qhttpserverfwd.h"
#include "qhttphandler.h"
#include "qhttpconnectionthread.h"

#include <QTcpServer>
#include <QObject>
#include <QHostAddress>

/// Maps status codes to string reason phrases
extern QHash<int, QString> STATUS_CODES;

/// The QHttpServer class forms the basis of the %QHttpServer
/// project. It is a fast, non-blocking HTTP server.
/** These are the steps to create a server, handle and respond to requests:
    <ol>
        <li>Create an instance of QHttpServer.</li>
        <li>Connect a slot to the newRequest() signal.</li>
        <li>Create a QCoreApplication to drive the server event loop.</li>
        <li>Respond to clients by writing out to the QHttpResponse object.</li>
    </ol>

    <b>Here is a simple sample application on how to use this library</b>

    helloworld.cpp
    @include helloworld/helloworld.cpp

    helloworld.h
    @include helloworld/helloworld.h */
class QHTTPSERVER_API QHttpServer : public QTcpServer
{
    Q_OBJECT

public:
    /// Construct a new HTTP Server.
    /** @param parent Parent QObject for the server. */
    QHttpServer(QObject *parent = 0);
    QHttpHandler *handler;

    virtual ~QHttpServer();

    /// Starts the server on @c port listening on all interfaces.
    /** @param port Port number on which the server should run.
        @return True if the server was started successfully, false otherwise.
        @sa listen(const QHostAddress&, quint16) */
    bool listen(quint16 port);

    /// Stop the server and listening for new connections.
    void close();

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif
