#pragma once
#include <QNetworkAccessManager>
#include <QWebPage>

class Tab;

class DwWebPage : public QWebPage
{
    Q_OBJECT
public:
//    Tab* pTab;
    explicit DwWebPage();
protected:
    QString userAgentForUrl(const QUrl & url) const;
signals:

public slots:

};
