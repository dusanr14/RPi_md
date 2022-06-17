//
// lcd1602.c
// kompajlirati sa -lwiringPi -lwiringPiDev

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <lcd.h>

// dodela vrednosti za konkretne pinove
// prema gornjoj tabeli i semi DVK512
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int main(){

int lcd_h;

	int i=0, taster_pritisnut=0;
	int j = 0;
	int r_value, r2_value, r3_value, r4_value;
	
	if (wiringPiSetup() < 0){
	fprintf (stderr, "Greška pri inicijalizaciji:%s\n", strerror (errno)) ;
	return 1 ;
	}

	lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2,
		D3, D0, D1, D2, D3);
		
	
	pinMode(21, INPUT);
	pinMode(22,INPUT); //ZA SMANJENJE 
	pinMode(23,INPUT);
	pinMode(24,INPUT);
	
	taster_pritisnut = 0;
	
	while(1)
	{
		r_value = digitalRead(21);
		r2_value = digitalRead(22);
		r3_value = digitalRead(23);
		r4_value = digitalRead(24);
		
		digitalWrite(25, r_value);//upise na diodu

		if( !taster_pritisnut)
		{
			delay(20);
			taster_pritisnut = 1;
			
			if(!r_value)
			{
				lcdClear(lcd_h);
				if(i < 15)
					i++;
				else
					i = 0;
				printf("jedan\n");
				fflush(stdout);
			}

			if(!r2_value)
			{
				lcdClear(lcd_h);
				if( i > 0)
					i--;
				else
					i = 15;
				printf("drugi\n");
				fflush(stdout);
			}
		/*	if(!r3_value)
			{
			    lcdClear(lcd_h);
				if(j = 0)
					j = 1;
			    else
					j = 0;
				printf("treci\n");
				fflush(stdout);
			}
			if(!r4_value)
			{
			    lcdClear(lcd_h);
				if(j = 0)
					j = 1;
			    else
					j = 0;
				printf("cetvrti\n");
				fflush(stdout);
			}
	    */
		}

		if(r_value && r2_value /*&& r3_value && r4_value*/) taster_pritisnut = 0;
		
		lcdPosition(lcd_h, i,0); //lcdPosition(lcd_h,i,j);
		lcdPrintf(lcd_h,"N");
		delay(20);
	}

	/*lcdPosition(lcd_h, 0,0);
	lcdPrintf(lcd_h,"Displej sa 16 ch");
	lcdPosition(lcd_h, 0,1);
	lcdPrintf(lcd_h, "u 2 reda");
*/

	lcdClear(lcd_h);
	return 0;
}
