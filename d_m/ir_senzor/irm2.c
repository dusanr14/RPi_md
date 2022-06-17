// gcc -o irm2 irm2.c -l bcm2835 -l lirc_client
// sudo ./irm1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <bcm2835.h>
#include <softPwm.h>
#include <wiringPi.h>
#include <lirc/lirc_client.h>


// LED3 je na DVK512 pločici na P28 što je pin 20 na BCM-u,
// ako se koristi protobord može se
// koristiti isti ovaj pin ili neki drugi


#define PIN 20

///

// koristi PWM kanal 0
#define PWM_CHANNEL 0
// max range PWM signala
#define RANGE 1024
///

int main(int argc, char **argv)
{
	wiringPiSetup();	

	if (softPwmCreate(28,0,100)!=0)
  	printf("doslo je do greske");
	
	int taster_pritisnut = 0;

	struct lirc_config *config;
	char *code;

	

	if(lirc_init("lirc",1)==-1)
		return 1;
	;
	int data = 0;

	
	//procitaj /etc/lirc/lircrc/lircd.conf
	if(lirc_readconfig(NULL, &config,NULL)==0)
	{
	//radimo dok je LIRC soket otvoren 0=otvoren -1=zatvoren
		while (lirc_nextcode(&code)==0)
		{
			// if code=NULL ništa nije primljenopreskoči
		 
			if(code==NULL) continue; 
                        {
		           if( !taster_pritisnut)
			   {
				delay(40);
				taster_pritisnut = 1;

				if (strstr(code,"KEY_UP"))
                                {
					printf("KEY_UP\n");

					// iskljuci
					//bcm2835_gpio_write(PIN, LOW);
					if(data<100)
						data +=20;
					delay(500);
				}
				else if (strstr(code,"KEY_DOWN"))
                                {
					printf("KEY_DOWN\n");

					// ukljuci
					//bcm2835_gpio_write(PIN, HIGH);
					if(data > 0)
						data -= 20;
					delay(500);
				}
				//else
				//{
				//	taster_pritisnut = 0;
				//	printf("Usao je u else \n");
				//}
				softPwmWrite(28,data);
			   }
			  // else
			   //{
				//   taster_pritisnut = 0;
				  // printf("else grana\n");
			   //}
		       	      if(~(strstr(code,"KEY_UP")) &&  ~(strstr(code,"KEY_DOWN"))){
				      taster_pritisnut= 0;
				      printf("ELSE!!!!!!!!\n");
			      }
			}
			free(code);
		    
		}
		lirc_freeconfig(config);
	}
	lirc_deinit();
 	return 0;
}

