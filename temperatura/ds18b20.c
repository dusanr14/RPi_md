#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

int main(void)
{
FILE * log;
int cz=0, j=0;
struct timespec ts1, ts2; //merenje vremena
long czas;
log=fopen("log","w");
if(log==NULL) return 0;
fprintf(log, "\n\t\t***Temperatura***\n
Izmerena temperatura = %.3f \xC2\xB0 C\t C\n",
temperatura());
fclose(log);

/*if(value > 25000)
{
	digitalWrite (LED, 1);
	delay (200);
	digitalWrite (LED, 0);
	delay (200);
}
else
{
	digitalWrite (LED, 0);
}
*/
close(fd);
return 0;
}
