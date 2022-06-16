// gcc -o irm1 irm1.c -l bcm2835 -l lirc_client
// sudo ./irm1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <bcm2835.h>
#include <lirc/lirc_client.h>
#include <wiringPi.h>
#include <softPwm.h>

// LED3 je na DVK512 pločici na P28 što je pin 20 na BCM-u,
// ako se koristi protobord može se
// koristiti isti ovaj pin ili neki drugi
	#define PIN 20


int main(int argc, char **argv)
{
	struct lirc_config *config;
	char *code;
	char *code_hex;
	char code_name[100];
	//startuj lirc
	
	if(lirc_init("lirc",1)==-1)
		return 1;
 
		
		if (wiringPiSetup() == -1)
			exit(1);
			
			pinMode(27,OUTPUT);
			digitalWrite(27, HIGH);
			
			if(softPwmCreate(28,0,100) != 0)
			exit(2);
	
			int i =0; 
			int taster_pritisnut=1;
	
	
	if(lirc_readconfig(NULL, &config,NULL)==0)
		{
		//radimo dok je LIRC soket otvoren 0=otvoren -1=zatvoren

			while (lirc_nextcode(&code)==0)
			{
				// if code=NULL ništa nije primljeno-preskoči
				if(code==NULL) continue; 
				{
					
					
					
					code_hex = "0x";
					char *hex_part = code;
					char pom1[25], pom2[25], pom3[25], pom4[25];
					hex_part+=10;
				
					sscanf(hex_part, "%s %s %s %s", pom1, pom2, pom3, pom4); 
					
					printf("0x%s %s\n", pom1, pom3);
					
				   
					if (strstr(pom3,"KEY_VOLUMEUP") && taster_pritisnut)
					{
						taster_pritisnut = 0;
						
						i+=20;
						if(i>100)
							i=0;
						softPwmWrite(28, i);
					
					}
				    if (strstr(code,"KEY_VOLUMEDOWN")&& taster_pritisnut)
					{
						
						taster_pritisnut = 0;
						
						i-=20;
						if(i<0)
							i=100;
						softPwmWrite(28, i);
						
					}
					if(!strstr(code,"KEY_VOLUMEDOWN") || !strstr(code,"KEY_VOLUMEUP")) {taster_pritisnut=1;}
				}
				free(code);
				
			
			}
			lirc_freeconfig(config);
		}
		lirc_deinit();
		
	return 0;
	}
