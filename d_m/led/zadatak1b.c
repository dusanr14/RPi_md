// lcd1602.c
// kompajlirati sa -lwiringPi -lwiringPiDev

#include <stdio.h>
#include <errno.h>
#include <wiringPi.h>
#include <lcd.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>

// dodela vrednosti za konkretne pinove
// prema gornjoj tabeli i semi DVK512
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int main(int argc, char *argv[]){

int lcd_h;

	int fd = -1, ret;
	char *tmp1, tmp2[10], ch='t';
	char devname_head[50] ="/sys/devices/w1_bus_master1/28-00000";
	
	char devname_end[10] = "/w1_slave";
	char dev_name[100];
	long value;
	int integer, decimal;
	char buffer[100];
	int i,j;
	
while(1)
{
	strcpy(dev_name, devname_head);
	strcat(dev_name, argv[1]);
	strcat(dev_name, devname_end);

	if ((fd = open(dev_name, O_RDONLY)) < 0)
	{
		perror("Greška pri otvaranju!");
		exit(1);
	}

	ret = read(fd, buffer, sizeof(buffer));
	
	if (ret < 0)
	{
		perror("Greška pri čitanju!");
		exit(1);
	}
	
	tmp1=strchr(buffer,ch);
	sscanf(tmp1, "t=%s", tmp2);
	value = atoi(tmp2);
	integer=value/1000;
	decimal= value % 1000;


	if (wiringPiSetup() < 0){
	fprintf (stderr, "Greška pri inicijalizaciji: %s\n", strerror (errno)) ;
	return 1 ;
	}

	lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2,
		D3, D0, D1, D2, D3);
	
	lcdPosition(lcd_h, 0,0);
	lcdPrintf(lcd_h,"temp: %d.%d", integer, decimal);

	delay(2000);
    close (fd);
	//lcdClear(lcd_h);
}
}
