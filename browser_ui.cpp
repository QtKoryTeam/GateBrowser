#include "browser_ui.h"
#include "ui_browser_ui.h"

browser_ui::browser_ui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::browser_ui)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/Fonts/Resources/NanumGothic.otf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont nanumgothic(family);

#ifdef DEBUG
    qDebug() << "Font Loaded : " << nanumgothic;
#endif

    setFont(nanumgothic);
}

browser_ui::~browser_ui()
{
    delete ui;
}

void browser_ui::on_m_DefaultKory_clicked()
{

}
