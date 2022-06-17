
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <math.h>
//#include <lcd.h>


QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    FILE * log;
    int fd, adcVal;
    float voltage;
    int voltage_int;

    const char PCF8591 = 0x48; // adresa
    if (wiringPiSetup () == -1) exit (1);

    fd = wiringPiI2CSetup(PCF8591);
    int fd = -1, ret;
        char *tmp1, tmp2[10], ch='t';
        char devname_head[50] = "/sys/devices/w1_bus_master1/28-00000";

        char devname_end[10] = "/w1_slave";
        char dev_name[100];
        long value;
        int integer, decimal;
        char buffer[100];
        int i,j;
     QTimer *myTimer1;

public slots:
    void ReadTemp();
private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
