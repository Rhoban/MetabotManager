#-------------------------------------------------
#
# Project created by QtCreator 2014-09-12T16:24:56
#
#-------------------------------------------------

include($$PWD/qextserialport/qextserialport.pro)

QT       += core gui network widgets

TARGET = RobotManager
TEMPLATE = app

RC_FILE += App.rc

CONFIG += c++11

SOURCES += main.cpp\
        MainWindow.cpp \
        json/src/lib_json/json_reader.cpp \
        json/src/lib_json/json_writer.cpp \
        json/src/lib_json/json_value.cpp \
        BT.cpp \
        SliderParameter.cpp \
        Sequencer.cpp \
        FileDownloader.cpp \
        FirmwareUploader.cpp \
    HttpHandler.cpp

HEADERS  += MainWindow.h \
            BT.h \
            SliderParameter.h \
            Sequencer.h \
            FileDownloader.h \
            FirmwareUploader.h \
    HttpHandler.h

FORMS    += MainWindow.ui

INCLUDEPATH += $$PWD/json/include

win32: LIBS += -lbthprops
win32: DEFINES += WIN32

RESOURCES += \
    icons.qrc

TRANSLATIONS = fr.ts en.ts

INCLUDEPATH += $$PWD/qhttpserver/src/
LIBS += -L$$PWD/qhttpserver/lib/ -lqhttpserver
