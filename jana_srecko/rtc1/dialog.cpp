#include "dialog.h"
#include "ui_dialog.h"
#define changeHexToInt(hex) ((((hex)>>4)*10)+((hex)%16))
//adrese registara
#define SEK 0x02
#define MINUT 0x03
#define SAT 0x04
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    myTimer1 = new QTimer(this);
        connect(myTimer1, SIGNAL(timeout()), this,
        SLOT(rtcReadTimeSlot()));
        lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::rtcReadTimeSlot()
{
    br++;
    qDebug() << br;
    volatile unsigned char time[7];
    unsigned char sati;
    unsigned char minuti;
    unsigned char sekunde;

    time[0] = wiringPiI2CReadReg8(fd,SEK);
    time[1] = wiringPiI2CReadReg8(fd,MINUT);
    time[2] = wiringPiI2CReadReg8(fd,SAT);
qDebug() << "vreme1 "<<time[0];
    //time[0] = 34;
    //time[1] = 34;
    //time[2] = 34;

    sekunde = time[0] & 0x7f;
    minuti = time[1] & 0x7f;
    sati = time[2] & 0x3f;


    sekunde = changeHexToInt(sekunde);
    minuti = changeHexToInt(minuti);
    sati = changeHexToInt(sati);
    qDebug() << "vreme "<<sati;
    if(format_lcd==12)
           sati=sati-12;
    QTime vreme (sati, minuti, sekunde);
   // QTime vreme2 (QTime::currentTime());
   // qDebug() << "vreme "<<vreme;
   // QString format = "hh:mm:ss";
   // QString str = vreme2.toString(format);
    QString format = "hh:mm:ss";
    QString str = vreme.toString(format);

    ui -> label_3 ->setText(str);

    lcdClear(lcd_h);
        lcdPosition(lcd_h, 0,red);
        lcdPrintf(lcd_h,"%s", str.toStdString().c_str());

       /* if(sati_alarm==vreme.hour() && minuti_alarm==vreme.minute() && sekunde_alarm==vreme.second())
        {
            qDebug() << "alarm ";
           // digitalWrite(25, HIGH);

        }*/
}

unsigned char hex2bcd(unsigned char x)
{
    unsigned char y;
    y = (x / 10) << 4;
    y = y | (x % 10);
    return (y);
}

void Dialog::on_pushButton_clicked()
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





void Dialog::on_checkBox_clicked()
{
    if(red == 1)
           red=0;
       else
           red=1;
       qDebug() <<red;
}

void Dialog::on_radioButton_clicked()
{
    format_lcd = 24;
}

void Dialog::on_radioButton_2_clicked()
{
    format_lcd = 12;
}
