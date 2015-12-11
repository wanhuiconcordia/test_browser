#include "dwtimer.h"
//#include <logmanager.h>
#include <QTime>
#include <iostream>
#include <pthread.h>
DwTimer::DwTimer()
:name(), msecDuration(0), className("DwTimer"), isThreadRunning(false){
    sleepTime = 100;
}

DwTimer::DwTimer(const QString& name, int msecDuration)
    :name(name), msecDuration(msecDuration), className("DwTimer"), isThreadRunning(false){
    sleepTime = 100;
}

void DwTimer::set(const QString& name, int msecDuration){
    this->name = name;
    this->msecDuration = msecDuration;
    //std::cout <<"msecDuration:" << this->msecDuration <<std::endl;
}

void DwTimer::start(){
    startTime = QTime::currentTime();
    if(isThreadRunning){
        needToAckRestart = true;
        std::cout << "thread is running, will not restart it" << std::endl;
        // do for loop looper = sleepTime / 10

        for(int i = 0; i< 7; i++){
            this->msleep(sleepTime/5);
            if(!needToAckRestart){  // RESTART HAD BEEN ACKNOWLEDGED, ALL GOOD
                return;
            } else if(!isThreadRunning){// FAILED TO RESTART, THREAD EXITED BEFORE
                goto START_TIMER_THREAD;
            }
        }
        // NOT SUPPOSE TO HAPPEN, SHOW ERROR
        std::cout << "Failed to restart normally, will start again." << std::endl;
        goto START_TIMER_THREAD;
    }else{
START_TIMER_THREAD:
        QThread::start();
    }
}

DwTimer::~DwTimer(){
//    LogManager::print(DW_TRACE, className, __func__, " is called.");
}

void DwTimer::stop(){
    stoppedByUser = true;
}

void DwTimer::run(){
    isThreadRunning = true;
    stoppedByUser = false;
    while(!stoppedByUser){
        if(needToAckRestart){
            needToAckRestart = false;
        }
        std::cout << startTime.msecsTo(QTime::currentTime()) << std::endl;
        if(startTime.msecsTo(QTime::currentTime()) > msecDuration){
            break;
        }
        this->msleep(sleepTime);
    }
    isThreadRunning = false;

    if(!stoppedByUser){//timeout
        emit timeout();
        stoppedByUser = false;
    }
}
