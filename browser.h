#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QToolBar>
#include <dwtimer.h>


class Tab;
class DwTimer;
class Browser : public QMainWindow
{
    Q_OBJECT
public:
    explicit Browser(QWidget *parent = 0);
    QToolBar *toolBar1;
    QLineEdit *locationEdit;
    QPushButton *goButton;

    QToolBar *toolBar2;
    QPushButton *printInfo;
    QPushButton *snapshot;
    QPushButton *scrollUp;
    QPushButton *scrollDown;
    QPushButton *click;


    QToolBar *toolBar3;
    QLineEdit *width;
    QLineEdit *height;
    QPushButton *changeViewportSize;
    QPushButton *setTabGeom;

    QToolBar *toolBar4;
    QLineEdit *interval;
    QPushButton *startTimer;
    QPushButton *timerStatus;

    Tab* pTab;

    DwTimer timer;

    QUrl validateUri(QUrl uri);

signals:

public slots:
    void changeLocation();
    void adjustLocation(QUrl url);
    void capture();
    void doScrollUp();
    void doScrollDown();
    void doClick();
    void doStartTimer();
    void onTimerout();
    void onTimerStatusClicked();
};

#endif // BROWSER_H
