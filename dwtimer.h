#pragma once
#include <QThread>
#include <QTime>
class DwTimer: public QThread
{
    Q_OBJECT
public:
    DwTimer();
    DwTimer(const QString& name, int msecDuration);
    void set(const QString& name, int msecDuration);
    ~DwTimer();

    void start();
    void stop();
private:
    void run();

signals:
    void timeout();
private:
    std::string className;
    QString name;
    int sleepTime;
    volatile bool stoppedByUser;
    volatile bool isThreadRunning;
    volatile bool needToAckRestart;
    int msecDuration;
    QTime startTime;
};
