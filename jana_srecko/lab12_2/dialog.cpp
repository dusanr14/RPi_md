#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    myTimer1 = new QTimer(this);
        connect(myTimer1, SIGNAL(timeout()), this,
        SLOT(Read()));
        myTimer1->start(1000);
}

void Dialog::Read()
{
    wiringPiI2CReadReg8(fd, PCF8591) ; // dummy
    adcVal = wiringPiI2CReadReg8(fd, PCF8591);
    wiringPiI2CReadReg8(fd, PCF8591 + 3) ; // dummy
    adcVal_2 = wiringPiI2CReadReg8(fd, PCF8591 + 3) ;
    ui->verticalSlider->setDisabled(true);
    ui->dial->setDisabled(true);
    ui->verticalSlider->setSliderPosition(adcVal);
    ui->dial->setSliderPosition(adcVal_2);
    //ui->lcdNumber->display(value);

}

Dialog::~Dialog()
{
    delete ui;
}

