#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <wiringPi.h>

//gcc blink.c -o blink -lwiringPi -lwiringPiDev

int main(int argc, char *argv[])
{
	wiringPiSetup();
	pinMode (25,OUTPUT);

	int fd = -1, ret;
	char *tmp1, tmp2[10], ch='t';
	char devname_head[50] =
	"/sys/devices/w1_bus_master1/28-00000";
	
	char devname_end[10] = "/w1_slave";
	char dev_name[100];
	long value;
	float prag;
	int integer, decimal;
	char buffer[100];
	int i,j;
	
	printf("Unesite prag:\n");
	fflush(stdout);
	scanf("%f",&prag);
	
	strcpy(dev_name, devname_head);
	strcat(dev_name, argv[1]);
	strcat(dev_name, devname_end);
	
	while(1)
	{
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
	
	tmp1 = strchr(buffer, ch);
	sscanf(tmp1, "t=%s", tmp2);
	value = atoi(tmp2);
	integer = value / 1000;
	decimal = value % 1000;
	float temp = integer + decimal/1000;
	
	printf("Temperatura je %d.%d\n", integer,decimal);
	close(fd);
	
	if(temp > prag)
	{
		digitalWrite (25, 1);
		delay (200);
		digitalWrite (25, 0);
		delay (200);
	}
	
	}
	return 0;
	
}
