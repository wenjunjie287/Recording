//
// Created by wenjunjie on 2025/11/5.
//

#include "RecordThread.h"

RecordThread::RecordThread(QObject* parent) : QObject(parent)
{
    setConnections();
        // 将当前对象移动到新的线程中
    this->moveToThread(&recordThread);
    recordThread.start();
}

RecordThread::~RecordThread()
{
    recordThread.quit();
    recordThread.wait();
}

void RecordThread::setConnections()
{
}
