#ifndef BROWSER_UI_H
#define BROWSER_UI_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QList>
#include <QtWebEngineWidgets>
#include <QFontDatabase>
#include <QDebug>
#include <QTextToSpeech>

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

    void deleteTab(int m_TabNum); // 탭을 삭제

    void tabButtonManager(); // 탭 버튼 활성화 / 비활성화 여부를 결정

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

    void on_m_CloseButton_clicked();

    void on_m_MinButton_clicked();

    void on_m_FullButton_clicked();

    void loadFinished(bool ok); // 로딩이 완료되면
    void loadProgress(int progress); // 프로그래스바
    bool checkUrl(const QUrl &url);

    void reloadUI(); // UI 를 새로고침

    void tabGoBack(); // Tab 뒤로 이동
    void tabGoForward(); // Tab 뒤로 이동
    void setTabIndex(int index); // Tab Index 를 설정
    void createNewTab(QString url = QString()); // 새로운 탭을 생성

    void on_m_TabBack_clicked();

    void on_m_TabForward_clicked();

    void on_m_UrlBar_returnPressed();

    void on_m_GoBack_clicked();

    void on_m_GoForward_clicked();

private:
    Ui::browser_ui *ui;
    QList<QWebEngineView*> m_BrowserTabs; // 탭 구성에 필요한 WebView

    /* From https://forum.qt.io/topic/34354/solved-frameless-window-dragging-issue/2 */

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent* event);

    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

    /* End */
};

#endif // BROWSER_UI_H
