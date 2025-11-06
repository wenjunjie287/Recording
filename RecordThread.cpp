//
// Created by wenjunjie on 2025/11/5.
//

#include "RecordThread.h"
#include <QDebug>

RecordThread::RecordThread(QObject *parent) : QObject(parent), m_width(0), m_height(0), m_fps(30)
{
    // 在构造函数或初始化函数中
    qRegisterMetaType<cv::Mat>("cv::Mat");
    setConnections();
    this->moveToThread(&recordThread);
    recordThread.start();
}

RecordThread::~RecordThread()
{
    recordThread.quit();
    recordThread.wait();
}

void RecordThread::startRecord(QString path, QString filename, int width, int height, int fps)
{
    m_path     = path;
    m_filename = filename;
    m_width    = width;
    m_height   = height;
    m_fps      = fps;
    emit sigStartRecord();
}

void RecordThread::stopRecord()
{
    isRecording = false;
}

void RecordThread::appendFrame(const QVariant &frame)
{
    emit sigAppendFrame(frame);
}

void RecordThread::setConnections()
{
    connect(this, &RecordThread::sigStartRecord, this, &RecordThread::slotStartRecord, Qt::QueuedConnection);
    connect(this, &RecordThread::sigAppendFrame, this, &RecordThread::slotAppendFrame, Qt::QueuedConnection);
}

void RecordThread::slotStartThread()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &RecordThread::slotTimerTimeout,Qt::QueuedConnection);
}

void RecordThread::slotTimerTimeout()
{
    qDebug() << "RecordThread Timer Timeout in thread:" << QThread::currentThread();
    if (!frame_list.empty())
    {
        QVariant frame = frame_list.front();
        writer.write(frame.value<cv::Mat>());
        frame_list.pop_front();
    }else
    {
        if (!isRecording)
        {
            timer->stop();
            writer.release();
        }
    }
}

void RecordThread::slotStartRecord()
{
    isRecording          = true;
    std::string fullPath = (m_path + "/" + m_filename).toStdString();
    int         fourcc   = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    writer.open(fullPath, fourcc, m_fps, cv::Size(m_width, m_height));
    if (!writer.isOpened())
    {
        isRecording = false;
    }
}

void RecordThread::slotAppendFrame(const QVariant &frame)
{
    qDebug() << "slotAppendFrame";
    if (isRecording)
    {
        frame_list.push_back(frame);
    }
}
