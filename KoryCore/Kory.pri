QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

macx{
    LIBS += -L/usr/local/opt/openssl/lib -lssl -lcrypto
    INCLUDEPATH += /usr/local/opt/openssl/include
}

TARGET = Kory
TEMPLATE = app

CONFIG += c++14

SOURCES +=\
    settings.cpp \
    learn_manager.cpp

HEADERS  += \
    ui_script.h \
    settings.h \
    config.h \
    learn_manager.h

FORMS    +=

INCLUDEPATH += $$PWD/Weather
INCLUDEPATH += $$PWD/Core
INCLUDEPATH += $$PWD/DataBase
INCLUDEPATH += $$PWD/GoogleAPI
INCLUDEPATH += $$PWD/Calendar

include($$PWD/Weather/Weather.pri)
include($$PWD/Core/Core.pri)
include($$PWD/DataBase/DataBase.pri)
include($$PWD/GoogleAPI/GoogleAPI.pri)
include($$PWD/Calendar/Calendar.pri)

RESOURCES += \
    testresources.qrc

