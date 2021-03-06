#-------------------------------------------------
#
# Project created by QtCreator 2017-03-05T11:43:28
#
#-------------------------------------------------

QT       += core gui texttospeech

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GateBrowser
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        browser_ui.cpp \
    settings.cpp \
    customshadoweffect.cpp

HEADERS  += browser_ui.h \
    config.h \
    settings.h \
    customshadoweffect.h \
    mywebpage.h

FORMS    += browser_ui.ui

RESOURCES += \
    gatebrowser_ui.qrc

DISTFILES += \
    Resources/GateBrowser.ico \
    Resources/GateBrowser.icns

win32 {
    RC_ICONS = Resources/GateBrowser.ico
}

macx {
    ICON = Resources/GateBrowser.icns
}

!android {
QT += webengine webenginewidgets
}

android {
QT += webview
}
