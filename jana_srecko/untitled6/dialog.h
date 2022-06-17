#ifndef DIALOG_H
#define DIALOG_H


#include <QDialog>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    unsigned char hex2bcd(unsigned char x);
    int fd;
    const char Address = 0x51;
    QTimer *myTimer1;
    int br=0;
    ~Dialog();

private slots:
    void on_pushButton_clicked(bool checked);

public slots:
    void rtcReadTimeSlot();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
