#include "dialog.h"
#include "ui_dialog.h"
#include <QTime>
#include <QMessageBox>
#include <QDebug>

#define changeHexToInt(hex) ((((hex)>>4)*10)+((hex)%16))
//adrese registara
#define SEK 0x02
#define MINUT 0x03
#define SAT 0x04
const char Address = 0x51;
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    myTimer1 = new QTimer(this);
    connect(myTimer1, SIGNAL(timeout()), this,
    SLOT(rtcReadTimeSlot()));



}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::rtcReadTimeSlot()
{
    br++;
    qDebug() << br;unsigned char time[7];
    unsigned char sati;
    unsigned char minuti;
    unsigned char sekunde;

    time[0] = wiringPiI2CReadReg8(fd,SEK);
    time[1] = wiringPiI2CReadReg8(fd,MINUT);
    time[2] = wiringPiI2CReadReg8(fd,SAT);

    //time[0] = 34;
    //time[1] = 34;
    //time[2] = 34;

    sekunde = time[0] & 0x7f;
    minuti = time[1] & 0x7f;
    sati = time[2] & 0x3f;


    sekunde = changeHexToInt(sekunde);
    minuti = changeHexToInt(minuti);
    sati = changeHexToInt(sati);
    QTime vreme (sati, minuti, sekunde);
    QTime vreme2 (QTime::currentTime());
    qDebug() << "vreme "<<vreme;
    QString format = "hh:mm:ss";
    QString str = vreme2.toString(format);
    ui -> label_3 ->setText(str);
}

unsigned char  Dialog::hex2bcd(unsigned char x)
{
    unsigned char y;
    y = (x / 10) << 4;
    y = y | (x % 10);
    return (y);
}

void Dialog::on_pushButton_clicked(bool checked)
{if(checked)
    {
        unsigned char WriteBuf[2];
        QString text = ui ->lineEdit->text();
        QTime vreme = QTime::fromString(text,"hh:mm:ss");
        if(!vreme.isValid())
            QMessageBox::warning(this, "Upozorenje!","Pogresan format!\nMora da bude hh:mm:ss");
        unsigned char sati = vreme.hour();
        unsigned char minuti = vreme.minute();
        unsigned char sekunde = vreme.second();
        qDebug() << sati;
        qDebug() << minuti;
        qDebug() << sekunde;

        WriteBuf[0] = SEK;
        WriteBuf[1] = hex2bcd(sekunde);
        qDebug() << "sek "<<WriteBuf[1];
        wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);

        WriteBuf[0] = MINUT;
        WriteBuf[1] = hex2bcd(minuti);
        qDebug() << "min "<<WriteBuf[1];
        wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);

        WriteBuf[0] = SAT;
        WriteBuf[1] = hex2bcd(sati);
        qDebug() << "sat "<<WriteBuf[1];
        wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);

        //inicijalizacija RTC-a
        WriteBuf[0] = 0x0;
        WriteBuf[1] = 0x00; //normalni rezim rada
        wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);
        myTimer1->start(1000);
    }
}
