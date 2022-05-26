#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <wiringPi.h>
#include <lcd.h>
#include <QString>
#include <stdio.h>
#include <string.h>
#include <wiringPiI2C.h>///
#include <stdlib.h>///
#include <unistd.h>


QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
