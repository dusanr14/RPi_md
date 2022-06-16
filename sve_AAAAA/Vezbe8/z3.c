#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <lcd.h>

// dodela vrednosti za konkretne pinove
// prema gornjoj tabeli i semi DVK512
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;


#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16))

//adrese registara
#define SEK 0x02
#define MIN 0x03
#define SAT 0x04
#define DANI 0x05
#define MESECI 0x07
#define GODINE 0x08

const char PCF8591=0X51; //adresa
int fd;

unsigned char WriteBuf[2];
 unsigned char ReadBuf;
 unsigned char g8563_Store[7];
								// sec,min,sat
 unsigned char init8563_Store[7]={0x00,0x59,0x08, 0x01, 0x04, 0x10, 0x01};
 
  void P8563_settime()
{
	
	 wiringPiI2CWriteReg8(fd, SEK, g8563_Store[0]);
	
	 wiringPiI2CWriteReg8(fd, MIN, g8563_Store[1]);

	 WriteBuf[0] = SAT;
	 WriteBuf[1] = g8563_Store[2];
	 wiringPiI2CWriteReg8(fd, SAT, g8563_Store[2]);
	 
	 WriteBuf[0] = DANI;
	 WriteBuf[1] = g8563_Store[3];
	 wiringPiI2CWriteReg8(fd, DANI, g8563_Store[3]);
	 	 	
	 WriteBuf[0] = MESECI;
	 WriteBuf[1] = g8563_Store[5];
	 wiringPiI2CWriteReg8(fd, MESECI, g8563_Store[5]);

	 WriteBuf[0] = GODINE;
	 WriteBuf[1] = g8563_Store[6];
	 wiringPiI2CWriteReg8(fd, GODINE, g8563_Store[6]);
	 
	 
}

void P8563_init()
{
	unsigned char i;
	
	for(i=0;i<=6;i++)
		g8563_Store[i]=init8563_Store[i];

	P8563_settime();
	printf("Postavi početno tekuće vreme\n");

	//inicijalizacija RTC-a
	/*WriteBuf[0] = 0x0;
	WriteBuf[1] = 0x00; //normalni rezim rada*/
	wiringPiI2CWriteReg8(fd, 0 , 0x00);
}

void P8563_Readtime()
{
	unsigned char time[7];
	
	time[0]=wiringPiI2CReadReg8(fd, SEK);
	time[1]=wiringPiI2CReadReg8(fd, MIN);
	time[2]=wiringPiI2CReadReg8(fd, SAT);
	time[3]=wiringPiI2CReadReg8(fd, DANI);
	time[5]=wiringPiI2CReadReg8(fd, MESECI);
	time[6]=wiringPiI2CReadReg8(fd, GODINE);
	
	
	
	 g8563_Store[0] = time[0] & 0x7f;
	 g8563_Store[1] = time[1] & 0x7f;
	 g8563_Store[2] = time[2] & 0x3f;
	 g8563_Store[3] = time[3] & 0x3f;
	 g8563_Store[5] = time[5] & 0x1f;
	 g8563_Store[6] = time[6] & 0xff;

	 g8563_Store[0] = changeHexToInt(g8563_Store[0]);
	 g8563_Store[1] = changeHexToInt(g8563_Store[1]);
	 g8563_Store[2] = changeHexToInt(g8563_Store[2]);
	 g8563_Store[3] = changeHexToInt(g8563_Store[3]);
	 g8563_Store[5] = changeHexToInt(g8563_Store[5]);
	 g8563_Store[6] = changeHexToInt(g8563_Store[6]);
}


int main()
{
	int lcd_h;
	
	int i = 0;
	int taster_pritisnut = 0;
	
	int key0_value;
	int key1_value;
	int key2_value;
	int key3_value;
	
	int x=13; 
	int y=0;
	
	if(wiringPiSetup() == -1)
		exit(1);
		
	fd = wiringPiI2CSetup(PCF8591);
	
	lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2,D3, D0, D1, D2, D3);
					
	pinMode(21, INPUT);
	pinMode(22, INPUT);
	
	lcdPosition(lcd_h, x, y);
	lcdCursor(lcd_h, 1);
	
	printf("start..........\n");
	P8563_init();
	 
	while(1)
	{
		
		key0_value = digitalRead(21); //procitaj key 0;
		key1_value = digitalRead(22); //procitaj key 1;
		/*key2_value = digitalRead(23); //procitaj key 2;
		key3_value = digitalRead(24); //procitaj key 3
		*/
		if(!key0_value && !taster_pritisnut) //DESNO
		{
			taster_pritisnut = 1;
			
			if(x!=15)
				x++;
			else
			{
				x=13;
				
		        if(y==1)
					y=0;
				else
					y=1;
			}
			
	
		}
		if(!key1_value && !taster_pritisnut) // INCREMENT
		{
			taster_pritisnut = 1;
			
			if( x == 13 && y == 0)
			{
					g8563_Store[3]++;
			}
			else if(x == 14 && y == 0)
			{
					g8563_Store[5]++;
			}
			else if(x == 15 && y == 0)
			{
				    g8563_Store[6]++;
			}
			else if(x == 13 && y == 1)
			{
					g8563_Store[2]++;
			}
			else if(x == 14 && y == 1)
			{
					g8563_Store[1]++;
			}
			else if(x == 15 && y == 1)
			{
					g8563_Store[0]++;
			}
			
			
		}
		
		lcdPosition(lcd_h, x, y);
		lcdCursor(lcd_h, 1);
		
		if(key0_value /*&& key3_value  && key2_value*/ && key1_value   && taster_pritisnut == 1)
		{

			taster_pritisnut = 0;
		
		}
		
		P8563_settime();
		P8563_Readtime();
		printf("Sati:%d Minuti:%d Sekunde:%d, Dani:%d MJeseci:%d Godine:%d, \n", g8563_Store[2], g8563_Store[1], g8563_Store[0], g8563_Store[3], g8563_Store[5], g8563_Store[6]);
		lcdPosition(lcd_h, 0,0);
		lcdPrintf(lcd_h,"%d.%d.%d ", g8563_Store[3], g8563_Store[5], g8563_Store[6]);
		lcdPosition(lcd_h, 0,1);
		lcdPrintf(lcd_h,"%d:%d:%d" , g8563_Store[2], g8563_Store[1], g8563_Store[0]);
		lcdPosition(lcd_h, 13,0);
		lcdPrintf(lcd_h,"DMY");
		lcdPosition(lcd_h, 13,1);
		lcdPrintf(lcd_h,"HMS");
	    delay(100);
	    lcdClear(lcd_h);
	}

	
	return 0;
}
