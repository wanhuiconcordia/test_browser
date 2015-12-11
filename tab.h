#ifndef TAB_H
#define TAB_H

#include <QWebView>
#include <browser.h>
#include <QTimer>

class Browser;

class Tab : public QWebView
{
     Q_OBJECT
public:
    Tab(QWidget* parent = 0);
    Browser* pBrowser;
    QRect defaultGeom;
    bool isScrollable();
    QTimer capturingTimer;

signals:
    void askRealClick(int x, int y);
public slots:
    void printInfo();
    void setViewPortSize();
    void setTabGeometory();
    void capture();
    void doClick();
    void onMainFrameLoadFinished(bool);
    void onMainFrameLoadStart();
    void onMainFrameUrlChanged(QUrl);
    void onContentSizeChanged(QSize);
    void doRealClick(int x, int y);
    void doScrollV(int);
    void onCapturingTimer();
private:
};

#endif // TAB_H
