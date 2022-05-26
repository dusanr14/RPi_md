#include "dialog.h"
#include "ui_dialog.h"


const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int lcd_h;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
}

Dialog::~Dialog()
{
    delete ui;
}


QString Qstring1;
QString Qstring2;

void Dialog::on_Text2CD_clicked()
{
         QString text =ui-> lineEdit ->text();
         QString text2 =ui-> lineEdit_2 ->text();

         lcdClear(lcd_h);

         lcdPosition(lcd_h, 0,0);
         lcdPrintf(lcd_h,"%s" ,text.toStdString().c_str());
         lcdPosition(lcd_h, 0,1);
         lcdPrintf(lcd_h,"%s" ,text2.toStdString().c_str());
}
