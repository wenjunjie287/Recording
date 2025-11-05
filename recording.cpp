#include "recording.h"
#include "./ui_recording.h"
#include <opencv2/core.hpp>

Recording::Recording(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Recording)
{
    ui->setupUi(this);
    // 设置窗口标题显示 OpenCV 版本
    this->setWindowTitle(QString("Recording - OpenCV ") + CV_VERSION);

    connect(&imgTimer, &QTimer::timeout, this, &Recording::imgTimerTimeout);
    imgTimer.start(100); // 每30毫秒触发一次

    recordThread = new RecordThread(this);

    connect(ui->startButton, &QPushButton::clicked, [this]() {
        recordThread->startRecord("./", "output.avi", 1024, 1024, 30);
    });
    connect(ui->stopButton, &QPushButton::clicked, [this]() {
        recordThread->stopRecord();
    });

}

Recording::~Recording()
{
    delete ui;
}

void Recording::imgTimerTimeout()
{
    cv::Scalar color(std::rand()%256, std::rand()%256, std::rand()%256); // 随机颜色
    cv::Mat frame(1024, 1024, CV_8UC3, color);
    recordThread->appendFrame(QVariant::fromValue(frame));
}
