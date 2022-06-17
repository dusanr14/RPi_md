#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <wiringPi.h>
#include <lcd.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    int lcd_h;
    ~Dialog();

private slots:
    void on_pushButton_clicked(bool checked);

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
