/*Povezati izlaz DAC-a sa AIN2 (koji je slobodan)
* očitavati trimer potenciometar koji je na AIN3
* upisati tu vrednost u DAC,
* očitati DAC preko AIN2
* DAC izlaz je validan do oko ~220
*/

#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <lcd.h>
#include <softPwm.h>

// dodela vrednosti za konkretne pinove
// prema gornjoj tabeli i semi DVK512
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

const char PCF8591 = 0x48; // adresa
int fd, adcVal;
float voltage;
int voltage_int;

int main() {

	if (wiringPiSetup () == -1) exit (1);

	fd = wiringPiI2CSetup(PCF8591);
	
	
  
	pinMode(25, OUTPUT);
	digitalWrite(25, HIGH);
	
	if (softPwmCreate(28,0,100)!=0)
	printf("doslo je do greske");
	
	while (1) {
		
		
	// procitaj trimer pot sa AIN3 ulaza
	wiringPiI2CReadReg8(fd, PCF8591) ; // dummy
	adcVal = wiringPiI2CReadReg8(fd, PCF8591) ;
	printf("value %d\n", adcVal);
	if((adcVal >=0) && (adcVal < 100))
	{
		//slvetli jako
		softPwmWrite(28, 100);
	}
	else if((adcVal >=100) && (adcVal < 200))
	{	//svetli sednje
		softPwmWrite(28, 60);
	}
	else if((adcVal >=200) && (adcVal <= 255))
	{	//svetli
		softPwmWrite(28, 10);
	}
	else
	{
		printf("NE VALJAAAA!!!@!q!!!#$^&^^$\n");
	}	
	// upisi tu vrednost u DAC reg, 0x04
	wiringPiI2CWriteReg8 (fd, PCF8591 + 4, adcVal) ;
	// procitaj DAC preko AIN2
	wiringPiI2CReadReg8(fd, PCF8591 + 2) ; // dummy
	adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 2);
	//printf("DAC vrednost = %d \n\n" , adcVal);

	delay(500);
	}
	
	return 0;
}
