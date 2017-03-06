#include "browser_ui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    browser_ui w;
    w.show();

    return a.exec();
}
