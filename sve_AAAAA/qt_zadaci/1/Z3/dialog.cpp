#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_3_clicked(bool checked)
{
    if (checked)
        digitalWrite(25,1);
    else
        digitalWrite(25,0);
}

void Dialog::on_pushButton_4_clicked(bool checked)
{
    if (checked)
        digitalWrite(26,1);
    else
        digitalWrite(26,0);
}

void Dialog::on_pushButton_2_clicked(bool checked)
{
    if (checked)
        digitalWrite(27,1);
    else
        digitalWrite(27,0);
}

void Dialog::on_pushButton_clicked(bool checked)
{
    if (checked)
        digitalWrite(28,1);
    else
        digitalWrite(28,0);
}
