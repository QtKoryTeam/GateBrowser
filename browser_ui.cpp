#include "browser_ui.h"
#include "ui_browser_ui.h"

browser_ui::browser_ui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::browser_ui)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    int id = QFontDatabase::addApplicationFont(":/Fonts/Resources/NanumGothic.otf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont nanumgothic(family);

#ifdef DEBUG
    qDebug() << "Font Loaded : " << nanumgothic;
#endif

    setFont(nanumgothic);

    createNewTab(QUrl("qrc:/StartPage/Resources/StartPage/StartPage.html"));

    createNewTab(QUrl("http://naver.com"));

    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 80));
    setAutoFillBackground(true);
    setGraphicsEffect(bodyShadow);

#ifdef Q_OS_ANDROID
    ui->m_CloseButton->hide();
    ui->m_FullButton->hide();
    ui->m_MinButton->hide();
    showMaximized();
#endif
}

browser_ui::~browser_ui()
{
    delete ui;
}

void browser_ui::resizeEvent(QResizeEvent* event)
{
    if(!event->oldSize().isEmpty())
    {
    /* 크기도 같이 줄어들거나 커진다 */
        ui->m_Bar->resize(ui->m_Bar->width() + (event->size().width() - event->oldSize().width()), ui->m_Bar->height());
        ui->m_BrowserBar->resize(ui->m_BrowserBar->width() + (event->size().width() - event->oldSize().width()), ui->m_BrowserBar->height());

        ui->m_LoadBar->resize(ui->m_LoadBar->width() + (event->size().width() - event->oldSize().width()), ui->m_LoadBar->height());
        ui->m_UrlBar->resize(ui->m_UrlBar->width() + (event->size().width() - event->oldSize().width()), ui->m_UrlBar->height());

        ui->m_Design_Tab->resize(ui->m_Design_Tab->width() + (event->size().width() - event->oldSize().width()), ui->m_Design_Tab->height());
        ui->m_Tab->resize(ui->m_Tab->width() + (event->size().width() - event->oldSize().width()), ui->m_Tab->height() + (event->size().height() - event->oldSize().height()));

        if(isCenterShow)
            center->resize(size().width() / 3, size().height() - (ui->m_GateBrowserIcon->height() + ui->m_Design_Tab->height()) + 5);

    /* 위치만 이동한다 */

        ui->m_CloseButton->move(event->size().width() - ui->m_CloseButton->width(), 0);
        ui->m_MinButton->move(ui->m_CloseButton->x() - ui->m_MinButton->width(), 0);
        ui->m_FullButton->move(ui->m_MinButton->x() - ui->m_FullButton->width(), 0);

        ui->m_TabForward->move(event->size().width() - ui->m_TabForward->width() - ui->m_GateBrowserIcon->width(), ui->m_TabForward->y());
        ui->m_TabButton->move(ui->m_TabForward->x() - ui->m_TabButton->width(), ui->m_TabButton->y());
        ui->m_TabBack->move(ui->m_TabButton->x() - ui->m_TabBack->width(), ui->m_TabBack->y());
    }
}

void browser_ui::on_m_DefaultKory_clicked()
{
    if(!isKoryEnabled)
    {
        ui->m_DefaultKory->setStyleSheet("image: url(:/Images/Resources/Kory_Pressed.png);"
                                        "background-color: rgb(255, 255, 255);"
                                        "border:0px solid;");
        isKoryEnabled = true;
    }else{
        ui->m_DefaultKory->setStyleSheet("image: url(:/Images/Resources/Kory.png);"
                                        "background-color: rgb(255, 255, 255);"
                                        "border:0px solid;");
        isKoryEnabled = false;
    }
}

void browser_ui::createNewTab(QUrl url)
{
    #ifdef Q_OS_ANDROID
        QWebView *view = new QWebView(); // Android
    #else
        QWebEngineView *view = new QWebEngineView(); // PC
    #endif

    ui->m_Tab->setCurrentIndex(ui->m_Tab->addWidget(view));

    view->resize(ui->m_Tab->size());

    view->show();

    view->load(url);

    view->settings()->setAttribute(view->settings()->WebGLEnabled, true);
    view->settings()->setAttribute(view->settings()->PluginsEnabled, true);
    view->settings()->setAttribute(view->settings()->LocalStorageEnabled, true);
    view->settings()->setAttribute(view->settings()->ErrorPageEnabled, false);
    view->settings()->setAttribute(view->settings()->TouchIconsEnabled, true);

    //view->page()->profile()->setHttpUserAgent("AppleWebKit/537.36 (KHTML, like Gecko) GateBrowser/1.0.0 Chrome/53.0.2785.148 Safari/537.36");

    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
    connect(view, SIGNAL(loadProgress(int)), this, SLOT(loadProgress(int)));
    m_BrowserTabs.append(view);

    tabButtonManager();
}

/* From https://forum.qt.io/topic/34354/solved-frameless-window-dragging-issue/2 */

void browser_ui::mousePressEvent(QMouseEvent *event) {
m_nMouseClick_X_Coordinate = event->x();
m_nMouseClick_Y_Coordinate = event->y();
}

void browser_ui::mouseMoveEvent(QMouseEvent *event) {
move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

/* End */

void browser_ui::on_m_CloseButton_clicked()
{
    close();
}

void browser_ui::on_m_MinButton_clicked()
{
    showMinimized();
}

void browser_ui::on_m_FullButton_clicked()
{
    if(!isMaximized())
    {
        showMaximized();
    }else{
        showNormal();
    }
}

void browser_ui::loadFinished(bool ok)
{
   if(ok)
   {
       reloadUI();
   }else{
       QFile file(":/ErrorPage/Resources/ErrorPage/CanNotLoaded.html");
       file.open(QIODevice::ReadOnly | QIODevice::Text);

       m_BrowserTabs.at(ui->m_Tab->currentIndex() - 2)->setHtml(file.readAll());
       ui->m_TabButton->setText(tr("Can not Loaded"));
   }
}

void browser_ui::loadProgress(int progress)
{
    ui->m_LoadBar->setValue(progress);

    if(progress == 100)
        ui->m_LoadBar->setValue(0);
}

void browser_ui::tabButtonManager()
{
    ui->m_TabBack->setEnabled(true);
    ui->m_TabForward->setEnabled(true);

    if(ui->m_Tab->currentIndex() - 2 == 0) // 만약 첫번째 탭이라면
    {
        ui->m_TabBack->setEnabled(false);
    }

    if(ui->m_Tab->currentIndex() - 2 == m_BrowserTabs.size() - 1) // 만약 마지막 탭이라면
    {
        ui->m_TabForward->setEnabled(false);
    }
}

void browser_ui::on_m_TabBack_clicked()
{
    tabGoBack();
}

void browser_ui::on_m_TabForward_clicked()
{
    tabGoForward();
}

void browser_ui::on_m_UrlBar_returnPressed()
{
    if(checkUrl(QUrl(ui->m_UrlBar->text())))
    {
        m_BrowserTabs.at(ui->m_Tab->currentIndex() - 2)->load(QUrl(ui->m_UrlBar->text()));
    }else if(strstr(ui->m_UrlBar->text().toStdString().c_str(), ".") != NULL){
        m_BrowserTabs.at(ui->m_Tab->currentIndex() - 2)->load(QUrl("http://" + ui->m_UrlBar->text()));
    }else{
        m_BrowserTabs.at(ui->m_Tab->currentIndex() - 2)->load(QUrl("https://www.google.co.uk/?gws_rd=ssl#q=" + ui->m_UrlBar->text()));
    }
}

bool browser_ui::checkUrl(const QUrl &url) {
    if (strstr(url.toString().toStdString().c_str(), "://") != NULL) {
        return true;
    }
    return false;
}

void browser_ui::reloadUI()
{
    ui->m_TabButton->setText(m_BrowserTabs.at(ui->m_Tab->currentIndex() - 2)->title());
    ui->m_TabButton->setIcon(m_BrowserTabs.at(ui->m_Tab->currentIndex() - 2)->icon());
    ui->m_UrlBar->setText(m_BrowserTabs.at(ui->m_Tab->currentIndex() - 2)->url().toString());

    ui->m_GoBack->setEnabled(m_BrowserTabs.at(ui->m_Tab->currentIndex() - 2)->history()->canGoBack());
    ui->m_GoForward->setEnabled(m_BrowserTabs.at(ui->m_Tab->currentIndex() - 2)->history()->canGoForward());\

}

void browser_ui::tabGoBack()
{
    setTabIndex(ui->m_Tab->currentIndex() - 1);
}

void browser_ui::tabGoForward()
{
    setTabIndex(ui->m_Tab->currentIndex() + 1);
}

void browser_ui::setTabIndex(int index)
{
    ui->m_Tab->setCurrentIndex(index);
    reloadUI();
    tabButtonManager();
}

void browser_ui::on_m_GoBack_clicked()
{
    m_BrowserTabs.at(ui->m_Tab->currentIndex() - 2)->back();
}

void browser_ui::on_m_GoForward_clicked()
{
    m_BrowserTabs.at(ui->m_Tab->currentIndex() - 2)->forward();
}

void browser_ui::on_m_AddTab_clicked()
{
    createNewTab(QUrl("http://google.com"));
}

void browser_ui::showCenter()
{
     center = new QWidget(this);

     if(!isCenterShow)
     {

     center->move(0, ui->m_GateBrowserIcon->height() + ui->m_Design_Tab->height() - 5);
     center->resize(size().width() / 3, size().height() - (ui->m_GateBrowserIcon->height() + ui->m_Design_Tab->height()) + 5);
     center->setStyleSheet("background-color: rgb(120, 144, 156);");
     center->show();

     QPropertyAnimation *animation = new QPropertyAnimation(center, "size");

     animation->setDuration(300);
     animation->setStartValue(QSize(0,0));
     animation->setEndValue(center->size());

     animation->start();

     isCenterShow = true;

     }else{
         QPropertyAnimation *animation = new QPropertyAnimation(center, "size");

         animation->setDuration(300);
         animation->setStartValue(center->size());
         animation->setEndValue(QSize(0,0));

         animation->start();
         center->hide();

         isCenterShow = false;
     }
}

void browser_ui::on_m_GateBrowserIcon_clicked()
{
    showCenter();
}
