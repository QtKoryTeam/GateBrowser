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
}

browser_ui::~browser_ui()
{
    delete ui;
}

void browser_ui::on_m_DefaultKory_clicked()
{

}

void browser_ui::createNewTab(QUrl url)
{
    QWebEngineView *view = new QWebEngineView();

    ui->m_Tab->setCurrentIndex(ui->m_Tab->addWidget(view));

    view->resize(ui->m_Tab->size());

    view->show();

    view->load(url);

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
