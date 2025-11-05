//
// Created by wenjunjie on 2025/11/5.
//

#ifndef RECORDING_RECORDTHREAD_H
#define RECORDING_RECORDTHREAD_H

#include <QObject>
#include <QThread>

class RecordThread : public QObject
{
    Q_OBJECT
public:
    explicit RecordThread(QObject *parent = nullptr);
    ~RecordThread() override;
private:
    void setConnections();


    QThread recordThread;
};


#endif //RECORDING_RECORDTHREAD_H
