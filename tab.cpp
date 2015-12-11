#include <unistd.h>
#include "tab.h"
#include <QCoreApplication>
#include <QDebug>
#include <QWebFrame>
#include "dwwebpage.h"
#include <iostream>
#include <QWebElementCollection>
#include <algorithm>
Tab::Tab(QWidget* parent)
    :QWebView(parent)
{
    pBrowser = (Browser*)parent;
    this->setPage(new DwWebPage());

//    QWebSettings *sets = this->settings();
//    sets->setAttribute(QWebSettings::JavascriptEnabled,false);

    defaultGeom = QRect(0, 120, 512, 1300);
    page()->mainFrame()->setScrollBarPolicy(Qt::Vertical,Qt::ScrollBarAlwaysOn);
    page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal,Qt::ScrollBarAlwaysOn);
    setGeometry(defaultGeom);


    capturingTimer.setInterval(2000);
    capturingTimer.setSingleShot(true);
    capturingTimer.setTimerType(Qt::PreciseTimer);

    connect(&capturingTimer, SIGNAL(timeout()), this, SLOT(onCapturingTimer()));

    connect(this->page()->mainFrame(), SIGNAL(loadFinished(bool)), this, SLOT(onMainFrameLoadFinished(bool)));
    connect(this->page()->mainFrame(), SIGNAL(loadStarted()), this, SLOT(onMainFrameLoadStart()));
    connect(this->page()->mainFrame(), SIGNAL(urlChanged(QUrl)), this, SLOT(onMainFrameUrlChanged(QUrl)));
//    connect(this->page()->mainFrame(), SIGNAL(contentsSizeChanged(QSize)), this, SLOT(onContentSizeChanged(QSize)));
//    connect(this, SIGNAL(askRealClick(int,int)), this, SLOT(doRealClick(int,int)));
}

void Tab::printInfo(){
    qDebug()<< "\n\ntab geometory:"<<this->geometry();
    qDebug()<< "page()->viewportSize:"<<page()->viewportSize();
    //    qDebug()<< "page()->preferredContentsSize:"<<page()->preferredContentsSize();
    qDebug()<< "page()->mainFrame()->contentsSize:"<<page()->mainFrame()->contentsSize();
//    qDebug()<< "page()->mainFrame()->scrollBarGeometry(Qt::Vertical).width():"<<page()->mainFrame()->scrollBarGeometry(Qt::Vertical).width();
//    qDebug()<< "page()->mainFrame()->scrollBarMaximum(Qt::Vertical):"<<page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
//    qDebug()<< "page()->mainFrame()->scrollBarMinimum(Qt::Vertical):"<<page()->mainFrame()->scrollBarMinimum(Qt::Vertical);
    qDebug()<<"isScrollable:" << isScrollable();
    qDebug() << "scrollPosition():" << page()->mainFrame()->scrollPosition();
}


void Tab::setViewPortSize(){
    QSize size = page()->viewportSize();
    size.setWidth(pBrowser->width->text().toInt());
    size.setHeight(pBrowser->height->text().toInt());
    this->page()->setViewportSize(size);
}

void Tab::setTabGeometory(){
    QSize size;
    size.setWidth(pBrowser->width->text().toInt());
    size.setHeight(pBrowser->height->text().toInt());
    QRect rect = defaultGeom;
    rect.setSize(size);
    setGeometry(rect);
    this->page()->setPreferredContentsSize(rect.size());
}

void Tab::onMainFrameLoadStart(){
    qDebug()<<QTime::currentTime() << "\tOnloadStart";
//    setGeometry(defaultGeom);
//    qDebug()<<"OnloadStart set tab geometry to:" << defaultGeom;
}

void Tab::onMainFrameUrlChanged(QUrl url){
    qDebug()<< QTime::currentTime() << "\tOnUrlChanged " << url;
}

void Tab::onContentSizeChanged(QSize size){
    qDebug() << "onContentSizeChanged():"<< size;
}

void Tab::onMainFrameLoadFinished(bool){
    qDebug()<<QTime::currentTime() << "\tonMainFrameLoadFinished";
//    qDebug()<<"isScrollable:" << isScrollable();

    qDebug() << QTime::currentTime() << "\tstart capturingTimer";
    capturingTimer.start();
//    if(isScrollable()){

//    }

}

void Tab::capture(){

    qDebug() << QTime::currentTime() << "\tcapture() begin";
    QSize oldsize = page()->viewportSize();
    QSize snapshotSize = page()->mainFrame()->contentsSize();
    page()->setViewportSize(snapshotSize);

    QImage snapshotImg(snapshotSize, QImage::Format_ARGB32);
    snapshotImg.fill(Qt::white);
    if(snapshotImg.isNull())// TODO, AS WE FAILED TO CAPTURE SCREEN, SHALL WE SEND A CLEAR SCREEN AND A MESSAGE TO DEVICE
    {
    }
    else
    {
        QPainter painter;
        if(!painter.begin((QPaintDevice*)(&snapshotImg)))// TODO, AS WE FAILED TO CAPTURE SCREEN, SHALL WE SEND A CLEAR SCREEN AND A MESSAGE TO DEVICE
        {
        }
        else
        {
            page()->mainFrame()->render(&painter);

            painter.end();

            std::string snapshotName = "/tmp/_snapshot.bmp";
            snapshotImg.save(snapshotName.c_str(), "BMP");

        }
    }
    page()->setViewportSize(oldsize);
    qDebug() << QTime::currentTime() << "\tcapture() done";
}


bool Tab::isScrollable(){

    if(page()->mainFrame()->contentsSize().height() > page()->viewportSize().height()){
        return true;
    }
    return false;
}

void Tab::doScrollV(int y){
    page()->mainFrame()->scroll(0, y);
}

void Tab::doClick(){
    QSize oldSize = page()->viewportSize();
    QSize contentSize = page()->mainFrame()->contentsSize();

    page()->setViewportSize(contentSize);
//    qDebug() << "enlarged viewport";

    int x = 100, y = 100;
    qDebug() << "doclick:" << x << "," << y;
    this->event(new QMouseEvent(
                    QEvent::MouseButtonPress,
                    QPoint(x, y),
                    Qt::LeftButton,
                    Qt::LeftButton,
                    Qt::NoModifier));
    this->event(new QMouseEvent(
                    QEvent::MouseButtonRelease,
                    QPoint(x, y),
                    Qt::LeftButton,
                    Qt::LeftButton,
                    Qt::NoModifier));
    page()->setViewportSize(oldSize);
//    qDebug() << "shirinked viewport";
}



void Tab::doRealClick(int x, int y){

}

void Tab::onCapturingTimer(){
    qDebug() << QTime::currentTime() << "\tonCapturingTimer() calling capture()...";
    capture();
}
