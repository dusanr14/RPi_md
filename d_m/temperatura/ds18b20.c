#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include<unistd.h>

#include <wiringPi.h>

char LED = 25;
int broj = 0;
double temperatura(void) //očitavanje temperature
{
	
	FILE *ft;
	char tekst[100];
	ft=fopen("/sys/bus/w1/devices/28-000008832b6c/w1_slave","r");

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

int main(void)
{
	wiringPiSetup();
	pinMode(LED, OUTPUT);
FILE * log;

int cz=0, j=0;
struct timespec ts1, ts2; //merenje vremena
long czas;
int unesena_temp;

log=fopen("log","w");

if(log==NULL) return 0;

fprintf(log, "\n\t\t***Temperatura***\nIzmerena temperatura = %.3f \xC2\xB0 C\t C\n",temperatura());

fclose(log);

	printf("Unesi temperaturu praga: ");
	scanf("%d" , &unesena_temp);
	printf("\n");
	
printf("\n\nPočetna Temp = %.3f \xC2\xB0 C", temperatura());
	if(fork() == 0);
	while(1)
	{

	j++; //broj iteracija
	
	clock_gettime(CLOCK_REALTIME, &ts1);
	
	printf("\nMerenje br. %d.\tTemp = %.3f\xC2\xB0 C", j, temperatura());
	
	clock_gettime(CLOCK_REALTIME, &ts2);
	
	//trajanje pojedinacnog //merenja
	czas = (ts2.tv_nsec - ts1.tv_nsec)/1000000;
	
	if(czas<=0) czas=czas+999;
	
	/* Prethodni red koriguje povremenu gresku pri merenju
	kada se dobija rezultat koji je manji za 999ms u odnosu
	na stvarni */
	printf("\tTrajanje merenja: %ld ms.", czas);
	
	
	
		if(temperatura() > unesena_temp)
		{
			broj = ~broj;
			digitalWrite (LED, broj);
		}
		else
		{
			digitalWrite (LED, 0);
		}
	}
return 0;
}


