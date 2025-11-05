#include "recording.h"
#include "./ui_recording.h"
#include <opencv2/core.hpp>
#include <QMessageBox>

Recording::Recording(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Recording)
{
    ui->setupUi(this);
    // 设置窗口标题显示 OpenCV 版本
    this->setWindowTitle(QString("Recording - OpenCV ") + CV_VERSION);
    // 可选弹出一次提示（如不需要可删除）
    QMessageBox::information(this, "OpenCV", QString("当前 OpenCV 版本: ") + CV_VERSION);
}

Recording::~Recording()
{
    delete ui;
}
