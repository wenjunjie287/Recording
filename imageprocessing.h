//
// Created by wenjunjie on 2025/11/18.
//

#ifndef RECORDING_IMAGEPROCESSING_H
#define RECORDING_IMAGEPROCESSING_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class ImageProcessing;
}

QT_END_NAMESPACE

class ImageProcessing : public QWidget
{
    Q_OBJECT

public:
    explicit ImageProcessing(QWidget *parent = nullptr);
    ~ImageProcessing() override;

private:
    Ui::ImageProcessing *ui;
};


#endif //RECORDING_IMAGEPROCESSING_H
