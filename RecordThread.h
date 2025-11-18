//
// Created by wenjunjie on 2025/11/5.
//

#ifndef RECORDING_RECORDTHREAD_H
#define RECORDING_RECORDTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <opencv2/opencv.hpp>

Q_DECLARE_METATYPE(cv::Mat)

class RecordThread : public QObject
{
    Q_OBJECT
signals:
    void sigStartRecord();
    void sigStopRecord();
    void sigAppendFrame(const QVariant& frame);
public:
    explicit RecordThread(QObject *parent = nullptr);
    ~RecordThread() override;
    void startRecord(QString path,QString filename,int width,int height,int fps = 30);
    void stopRecord();
    void appendFrame(const QVariant& frame);


private:
    void    setConnections();
    QThread recordThread;
    bool   isRecording = false;
    cv::VideoWriter writer;

    QString m_path;
    QString m_filename;
    int m_width;
    int m_height;
    int m_fps;
protected:
    void slotStartRecord();
    void slotStopRecord();
    void slotAppendFrame(const QVariant& frame);

};


#endif //RECORDING_RECORDTHREAD_H
