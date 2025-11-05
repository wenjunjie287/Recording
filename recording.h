#ifndef RECORDING_H
#define RECORDING_H

#include <QWidget>

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
    Ui::Recording *ui;
};
#endif // RECORDING_H
