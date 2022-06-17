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
#include "lcd.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    int fd;
        const char Address = 0x51;
        QTimer *myTimer1;
        int br=0;
        int lcd_h;
        int red=1;
            int format_lcd = 24;
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void rtcReadTimeSlot();
private slots:
    void on_pushButton_clicked();

    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_checkBox_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
