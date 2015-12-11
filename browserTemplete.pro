QT += webkitwidgets

CONFIG += C++11
CONFIG += warn_off


DESTDIR = $$PWD/bin

HEADERS += \
    tab.h \
    browser.h \
    dwwebpage.h \
    dwtimer.h

SOURCES += \
    tab.cpp \
    browser.cpp \
    app.cpp \
    dwwebpage.cpp \
    dwtimer.cpp
