#include "recording.h"

#include <QApplication>
#include <opencv2/core.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    QApplication a(argc, argv);
    Recording w;
    w.show();
    return a.exec();
}
