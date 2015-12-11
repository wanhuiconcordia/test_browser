#include "dwwebpage.h"
#include <tab.h>
#include <browser.h>
#include <iostream>


DwWebPage::DwWebPage() /*:
    QWebPage(static_cast<QObject*>(parent))*/
{
//    pTab = parent;
//    this->setNetworkAccessManager((QNetworkAccessManager*)pTab->pBrowser->pNetworkAccessManager);
//    this->setNetworkAccessManager(nullptr);
}



QString DwWebPage::userAgentForUrl(const QUrl & url) const
{

    QString mobileAgentStr = "Mozilla/5.0 (Linux; Android 4.4.2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.59 Mobile Safari/537.36";
    QString FbAgentStr = "Mozilla/5.0 (iPhone) AppleWebKit/537.36 (KHTML, like Gecko) Version/8.0 Mobile/12F70 Safari/600.1.4";

//	if(url.host().contains("facebook.com"))
		return FbAgentStr;
        return  mobileAgentStr;

}


