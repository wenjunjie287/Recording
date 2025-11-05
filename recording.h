#ifndef RECORDING_H
#define RECORDING_H

#include <QWidget>
#include <QTimer>
#include "RecordThread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Recording;
}
QT_END_NAMESPACE

class Recording : public QWidget
{
    Q_OBJECT

public:
    Recording(QWidget *parent = nullptr);
    ~Recording();

private:
    void imgTimerTimeout();


    Ui::Recording *ui;
    QTimer imgTimer;

    RecordThread *recordThread;
};
#endif // RECORDING_H
