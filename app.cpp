#include <browser.h>
#include <QApplication>

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    Browser browser;
    browser.setGeometry(0, 0, 620, 900);
    browser.show();
    app.exec();
    return 0;
}
