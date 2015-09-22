#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <http/HttpDaemon.h>
#include <qextserialport.h>
#include <qextserialenumerator.h>
#include <QComboBox>
#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>
#include "BT.h"
#include "SliderParameter.h"
#include "Sequencer.h"
#include "FileDownloader.h"
#include "FirmwareUploader.h"
#include "HttpHandler.h"

class SliderParameter;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void goToConnected();
    void goToDisconnected();
    void populatePorts();
    void setMessage(QString message, bool error=false);

    void checkConnection();
    void closeConnection();
    bool isConnected();
    bool sendData(QString data);
    QByteArray getData();
    QString getResponse();

    Sequencer sequencer;

private slots:
    void on_refresh_clicked();
    void on_connect_clicked();
    void on_port_close();
    void on_disconnect_clicked();
    void on_reconnect_clicked();

    void on_actionQuitter_triggered();

    void on_checkVersion_clicked();
    void on_updateFimwarePorts_clicked();
    void on_updateFirmware_clicked();

    void on_firmwareUploadStep(float alpha);
    void on_firmwareStatusChange(QString status);
    void on_firmwareUploaded();

    void on_tabWidget_tabBarClicked(int index);

    void on_robotChoice_currentIndexChanged(int index);

public:
    QString sendCommand(QString command, bool waitAnswer=false);
    void setValue(QString name, float value);
    bool getValue(QString name, float &output);

    void setEnable(bool enabled);
    void addParameter(SliderParameter *parameter);

protected slots:
    void dowloadedVersion(const QByteArray &data);
    void dowloadedFirmware(const QByteArray &data);

private:
    int gait;
    QString robotModel;
    std::vector<SliderParameter*> parameters;

    FirmwareUploader firmwareUploader;
    FileDownloader versionDownloader;
    FileDownloader firmwareDownloader;
    QString version;
    QByteArray firmware;
    QString currentPort;

    BT bluetooth;
    Ui::MainWindow *ui;
    QMutex mutex;
    QextSerialPort port;

    QHttpServer *server;
    HttpHandler httpHandler;

    bool connected = true;
};

#endif // MAINWINDOW_H
