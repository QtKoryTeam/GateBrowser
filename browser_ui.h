#ifndef BROWSER_UI_H
#define BROWSER_UI_H

#include <QMainWindow>
#include <QList>
#include <QtWebEngineWidgets>
#include <QFontDatabase>
#include <QDebug>

namespace Ui {
class browser_ui;
}

class browser_ui : public QMainWindow
{
    Q_OBJECT

public:
    explicit browser_ui(QWidget *parent = 0);
    ~browser_ui();

    /* UI 처리 */

    void createNewTab(); // 새로운 탭을 생성
    void deleteTab(int m_TabNum); // 탭을 삭제

    void showSettingPage(); // 설정창을 나오게 한다

    enum MessageType
    {
        ACTIVE_MESSAGE, // 기능을 활성화 할것이냐고 묻는다.
        WARN, // 경고 메시지
        INFO // 정보 메시지
    };

    void showMessage(int msg_type, QString Message, bool is_download_file = false, QString download_url = QString());

    /* Kory 관련 처리 */



private slots:
    void on_m_DefaultKory_clicked();

private:
    Ui::browser_ui *ui;
    QList<QWebEngineView*> m_BrowserTabs; // 탭 구성에 필요한 WebView
};

#endif // BROWSER_UI_H
