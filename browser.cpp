#include "browser.h"
#include <tab.h>
Browser::Browser(QWidget *parent) : QMainWindow(parent)
{
    pTab = new Tab(this);

    pTab->show();
//    pTab->load(QUrl("http://www.yahoo.com"));

    toolBar1 = addToolBar(tr("Navigation"));

    locationEdit = new QLineEdit(this);
    locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());

    toolBar1->addWidget(locationEdit);
    goButton = new QPushButton("GO");
    toolBar1->addWidget(goButton);
    this->addToolBarBreak();

    toolBar2 = addToolBar(tr("functions"));
    toolBar2->addAction(pTab->pageAction(QWebPage::Back));
    toolBar2->addAction(pTab->pageAction(QWebPage::Forward));
    toolBar2->addAction(pTab->pageAction(QWebPage::Reload));
    toolBar2->addAction(pTab->pageAction(QWebPage::Stop));

    printInfo = new QPushButton("PrintInfo");
    toolBar2->addWidget(printInfo);
    snapshot = new QPushButton("snapshot");
    toolBar2->addWidget(snapshot);
    scrollUp = new QPushButton("scrollUp");
    toolBar2->addWidget(scrollUp);
    scrollDown = new QPushButton("scrollDown");
    toolBar2->addWidget(scrollDown);
    click = new QPushButton("click");
    toolBar2->addWidget(click);




    this->addToolBarBreak();

    toolBar3 = addToolBar(tr("RectTest"));
    width = new QLineEdit(this);
    width->setSizePolicy(QSizePolicy::Expanding, width->sizePolicy().verticalPolicy());
    toolBar3->addWidget(width);

    height = new QLineEdit(this);
    height->setSizePolicy(QSizePolicy::Expanding, width->sizePolicy().verticalPolicy());
    toolBar3->addWidget(height);

    changeViewportSize = new QPushButton("setViewportSize");
    toolBar3->addWidget(changeViewportSize);

    setTabGeom = new QPushButton("setTabGeom");
    toolBar3->addWidget(setTabGeom);

    toolBar4 = addToolBar(tr("timer"));
    interval = new QLineEdit(this);
    toolBar4->addWidget(interval);
    startTimer = new QPushButton("StartTimer");
    toolBar4->addWidget(startTimer);

    timerStatus = new QPushButton("timerStatus");
    toolBar4->addWidget(timerStatus);


    connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));
    connect(pTab, SIGNAL(urlChanged(QUrl)), SLOT(adjustLocation(QUrl)));

    connect(changeViewportSize, SIGNAL(clicked()), pTab, SLOT(setViewPortSize()));
    connect(setTabGeom, SIGNAL(clicked()), pTab, SLOT(setTabGeometory()));
    connect(printInfo, SIGNAL(clicked()), pTab, SLOT(printInfo()));
    connect(snapshot, SIGNAL(clicked()), this, SLOT(capture()));
    connect(scrollUp, SIGNAL(clicked()), this, SLOT(doScrollUp()));
    connect(scrollDown, SIGNAL(clicked()), this, SLOT(doScrollDown()));
    connect(click, SIGNAL(clicked()), this, SLOT(doClick()));
    connect(startTimer, SIGNAL(clicked()), this, SLOT(doStartTimer()));
    connect(timerStatus, SIGNAL(clicked()), this, SLOT(onTimerStatusClicked()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimerout()));
}


void Browser::changeLocation()
{
    QUrl uri = QUrl(locationEdit->text());
    QUrl url = validateUri(uri);
    pTab->setUrl(url);
    pTab->setFocus();
}

QUrl Browser::validateUri(QUrl uri)
{
    QString urlStr = uri.toString();

    if(!urlStr.startsWith("http://")
            && !urlStr.startsWith("https://")
            && !urlStr.startsWith("file://")
            && !urlStr.startsWith("ftp://"))
    {
        urlStr.prepend("http://");
    }
    if(!urlStr.contains("."))
    {
        urlStr.append(".com");
    }
    return QUrl(urlStr);
}


void Browser::adjustLocation(QUrl url)
{
    locationEdit->setText(url.toString());
}

void Browser::capture(){
    pTab->capture();
}


void Browser::doScrollUp(){
    pTab->doScrollV(-100);
}

void Browser::doScrollDown(){
    pTab->doScrollV(100);
}


void Browser::doClick(){
    pTab->doClick();
}

void Browser::doStartTimer(){
    qDebug() << "Browser::doStartTimer is called.";
    timer.set("testTimer", interval->text().toInt());
//    timer.start();
    timer.start();
}

void Browser::onTimerout(){
    qDebug() << "timeout will capture";
}

void Browser::onTimerStatusClicked(){
    qDebug() << "currentThreadId():" <<timer.currentThreadId();
    qDebug() << "isRunning():"<< timer.isRunning();
    qDebug() << "isFinished():"<< timer.isFinished();
}
