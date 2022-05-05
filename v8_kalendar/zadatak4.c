// primer rada sa PCF8563 koji ispisuje tekuce vreme
// u terminalu svakih 5 sekundi

#include <wiringPiI2C.h>///
#include <wiringPi.h>///
#include <stdlib.h>///

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <errno.h>
#include <lcd.h>

const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16) )

//adrese registara
#define SEK 0x02
#define MIN 0x03
#define SAT 0x04
#define DAN 0x05
#define MESEC 0x07
#define GODINA 0x08

	int fd;///
	const char PCF8591 = 0x48;///
	
	
	unsigned char WriteBuf[2];
	unsigned char ReadBuf;
	unsigned char g8563_Store[7];
				// sec,min,sat
	unsigned char init8563_Store[7]={0x00,0x59,0x08,0x05,0x03,0x10};
	
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
	
		WriteBuf[0] = DAN;
	WriteBuf[1] = g8563_Store[3];
	wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);
	
	WriteBuf[0] = MESEC;
	WriteBuf[1] = g8563_Store[4];
	wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);
	
	WriteBuf[0] = GODINA;
	WriteBuf[1] = g8563_Store[5];
	wiringPiI2CWriteReg8(fd,WriteBuf[0],WriteBuf[1]);
}

void P8563_init()
{
	unsigned char i;

	for(i=0;i<=5;i++)
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
	time[3] = wiringPiI2CReadReg8(fd,DAN);
	time[5] = wiringPiI2CReadReg8(fd,MESEC);
	time[6] = wiringPiI2CReadReg8(fd,GODINA);

	g8563_Store[0] = time[0] & 0x7f;
	g8563_Store[1] = time[1] & 0x7f;
	g8563_Store[2] = time[2] & 0x3f;
	g8563_Store[3] = time[3] & 0x3f;
	g8563_Store[4] = time[5] & 0x1f;
	g8563_Store[5] = time[6];

	g8563_Store[0] = changeHexToInt(g8563_Store[0]);
	g8563_Store[1] = changeHexToInt(g8563_Store[1]);
	g8563_Store[2] = changeHexToInt(g8563_Store[2]);
	g8563_Store[3] = changeHexToInt(g8563_Store[3]);
	g8563_Store[4] = changeHexToInt(g8563_Store[4]);
	g8563_Store[5] = changeHexToInt(g8563_Store[5]);
}


int main(int argc, char **argv)
{
	wiringPiSetup();
	if (wiringPiSetup () == -1) exit (1);
	
	fd = wiringPiI2CSetup(0x51);
	///bcm2835_i2c_begin();
	// adresa PCF8563 na I2C magistrali
	//bcm2835_i2c_setSlaveAddress(0x51);
	//bcm2835_i2c_set_baudrate(10000);
	printf("start..........\n");
	P8563_init() ;
	
	int lcd_h;
	//za tastere
	int i=0, taster_pritisnut=0;
	int j = 0;
	int r_value, r2_value, r3_value, r4_value;
	//
	
	lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2,D3, D0, D1, D2, D3);
	
	int godina, mesec, dan, sat, minut, sekund;
	
	//za tastere
	pinMode(21, INPUT);
	pinMode(22,INPUT); //ZA SMANJENJE 
	pinMode(23,INPUT);
	pinMode(24,INPUT);
	//
	taster_pritisnut = 0;
	
	while(1)
	{
		
		if( !taster_pritisnut)
		{
			delay(20);
			taster_pritisnut = 1;
			
			if(!r_value)
			{
				if(i = 0)
					i = 1;
				else
					i = 0;
				printf("jedan");
			}

			if(!r2_value)
			{
				if(i = 0)
					dan++;
			    else
					sekund++;
				printf("drugi");
			}
		}

		if(r_value && r2_value /*&& r3_value && r4_value*/) taster_pritisnut = 0;
		
		
		
	}
	while(1)
	{
		P8563_Readtime();
		//za tastere
		r_value = digitalRead(21);
		r2_value = digitalRead(22);
		r3_value = digitalRead(23);
		r4_value = digitalRead(24);
		//
		
	godina = g8563_Store[5];
	mesec = g8563_Store[4];
	dan = g8563_Store[3];
	sat = g8563_Store[2];
	minut = g8563_Store[1];
	sekund = g8563_Store[0];
	
		if( !taster_pritisnut)
		{
			delay(20);
			taster_pritisnut = 1;
			
			if(!r_value)
			{
				if(i = 0)
					i = 1;
				else
					i = 0;
				printf("jedan");
			}

			if(!r2_value)
			{
				if(i = 0)
					dan++;
			    else
					sekund++;
				printf("drugi");
			}
		}

		if(r_value && r2_value /*&& r3_value && r4_value*/) taster_pritisnut = 0;
		
		//printf("Godina:%d Mesec:%d Dan:%d Sati: %d  Minuti:%d Sekunde:%d\n",g8563_Store[5],g8563_Store[4],g8563_Store[3],g8563_Store[2], g8563_Store[1],g8563_Store[0]);
	
	
	lcdPosition(lcd_h, 0,0);
	lcdPrintf(lcd_h,"Datum:%d. %d. %d.",dan,mesec,godina );
	lcdPosition(lcd_h, 0,1);
	lcdPrintf(lcd_h, "%d:%d",minut,sekund);

	delay(500);
	}
	lcdClear(lcd_h);
	//bcm2835_i2c_end();
	//bcm2835_close();

	return 0;
}
