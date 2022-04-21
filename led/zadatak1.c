// lcd1602.c
// kompajlirati sa -lwiringPi -lwiringPiDev

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <time.h>
#include <lcd.h>

double temperatura(void) //očitavanje temperature
{
	FILE *ft;
	char tekst[100];
	ft=fopen("/sys/bus/w1/devices/28-00000???????/w1_slave","r");
	if(ft==NULL) return 0;
	int i=0;
	for(i=0;i<22;i++) //samo temperatura
		fscanf(ft,"%s", tekst);
	fclose(ft);
	//obrisati „t=”
	for(i=0;i<10;i++) tekst[i]=tekst[i+2];
	
	int temp=atoi(tekst); //prebaci u double
	double tem=(double)temp/1000;

	return tem;
};

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

	FILE * log;
	int cz=0, j=0;
	struct timespec ts1, ts2; //merenje vremena
	long czas;
	log=fopen("log","w");
	if(log==NULL) return 0;
	fprintf(log, "\n\t\t***Temperatura***\n Izmerena temperatura = %.3f \xC2\xB0 C\t C\n",temperatura());
	fclose(log);
	printf("\n\nPočetna Temp = %.3f \xC2\xB0 C", temperatura());
	
	if (wiringPiSetup() < 0){
	fprintf (stderr, "Greška pri inicijalizaciji:
		%s\n", strerror (errno)) ;
	return 1 ;
	}
	
	lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2,
		D3, D0, D1, D2, D3);
	
	while(1)
	{
	j++; //broj iteracija
	clock_gettime(CLOCK_REALTIME, &ts1);
	//printf("\nMerenje br. %d.\tTemp = %.3f\xC2\xB0 C", j, temperatura());
	lcdPosition(lcd_h, 0,0);
	lcdPrintf(lcd_h,temperatura());
	delay(2000);
	lcdClear(lcd_h);
	clock_gettime(CLOCK_REALTIME, &ts2);
	//trajanje pojedinacnog //merenja
	czas = (ts2.tv_nsec - ts1.tv_nsec)/1000000;
	if(czas<=0) czas=czas+999;
	/* Prethodni red koriguje povremenu gresku pri merenju
	kada se dobija rezultat koji je manji za 999ms u odnosu
	na stvarni */
	printf("\tTrajanje merenja: %ld ms.", czas);
	zapis(temperatura()); //upis u datoteku
}	
	


}
