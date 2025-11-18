//
// Created by wenjunjie on 2025/11/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ImageProcessing.h" resolved

#include "imageprocessing.h"
#include "ui_ImageProcessing.h"

ImageProcessing::ImageProcessing(QWidget *parent) : QWidget(parent), ui(new Ui::ImageProcessing)
{
    ui->setupUi(this);
}

ImageProcessing::~ImageProcessing()
{
    delete ui;
}
