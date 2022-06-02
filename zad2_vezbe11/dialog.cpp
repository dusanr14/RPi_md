#include "dialog.h"
#include "ui_dialog.h"


const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int lcd_h;
#define SEK 0x02
#define MIN 0x03
#define SAT 0x04

#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16) )
int fd;///
    const char PCF8591 = 0x48;///


    unsigned char WriteBuf[2];
    unsigned char ReadBuf;
    unsigned char g8563_Store[3];
                // sec,min,sat
    unsigned char init8563_Store[3]={0x00,0x59,0x08};


void P8563_settime()
{
    WriteBuf[0] = SEK;
    WriteBuf[1] = g8563_Store[0];
    ///bcm2835_i2c_write(WriteBuf,2);
    wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);

    WriteBuf[0] = MIN;
    WriteBuf[1] = g8563_Store[1];
    wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);

    WriteBuf[0] = SAT;
    WriteBuf[1] = g8563_Store[2];
    wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);
}

void P8563_init()
{
    unsigned char i;

    for(i=0;i<=3;i++)
        g8563_Store[i]=init8563_Store[i];

    P8563_settime();
    printf("Postavi početno tekuće vreme\n");

    //inicijalizacija RTC-a
    WriteBuf[0] = 0x0;
    WriteBuf[1] = 0x00; //normalni rezim rada
    wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);
}

void P8563_Readtime()
{
    unsigned char time[7];

    time[0] = wiringPiI2CReadReg8(fd,SEK);
    time[1] = wiringPiI2CReadReg8(fd,MIN);
    time[2] = wiringPiI2CReadReg8(fd,SAT);
    ///bcm2835_i2c_write_read_rs(WriteBuf, 1, time, 7);
    ///wiringPiI2CWriteReg8 (WriteBuf, 1, time, 7 );
    g8563_Store[0] = time[0] & 0x7f;
    g8563_Store[1] = time[1] & 0x7f;
    g8563_Store[2] = time[2] & 0x3f;

    g8563_Store[0] = changeHexToInt(g8563_Store[0]);
    g8563_Store[1] = changeHexToInt(g8563_Store[1]);
    g8563_Store[2] = changeHexToInt(g8563_Store[2]);
}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
   lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);

}

/*void Dialog:: showTime()
{
   QTime time = QTime::currentTime();
   QString time_text= time.toString("hh : mm : ss");
   if ((time.second()%2) == 0)
   {
       time_text[2]= ' ';
       time_text[5]= ' ';
   }
   ui-> Digital_clock->setText(time_text);


}*/


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{

}
