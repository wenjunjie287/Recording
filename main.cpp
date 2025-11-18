#include "recording.h"

#include <QApplication>
#include <opencv2/core.hpp>
#include <iostream>
#include "imageprocessing.h"

int main(int argc, char *argv[])
{
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    QApplication a(argc, argv);
    ImageProcessing w;
    w.show();
    return a.exec();
}
