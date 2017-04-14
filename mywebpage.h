#ifndef MYWEBPAGE_H
#define MYWEBPAGE_H

#include <QWebEnginePage>

#include "browser_ui.h"

class MyWebPage : public QWebEnginePage
{
    Q_OBJECT
public:
    MyWebPage(QObject* parent = 0) : QWebEnginePage(parent){}

    QWebEnginePage *createWindow(QWebEnginePage::WebWindowType type)
    {
        emit requestNewTab(type, requestedUrl());
    }

    bool acceptNavigationRequest(const QUrl & url, QWebEnginePage::NavigationType type, bool isMainFrame)
    {
        switch( type )
        {
            case QWebEnginePage::NavigationTypeLinkClicked:
            {
                return true;
            }
            default:
                return QWebEnginePage::acceptNavigationRequest( url, type, isMainFrame);
        }
    }

signals:
    void requestNewTab(QWebEnginePage::WebWindowType type, const QUrl & url);
};

#endif // MYWEBPAGE_H
