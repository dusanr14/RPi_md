// NA DVK512 ploči se koristi KEY0 i LED3,
// a LED0 svetli dok taster nije pritisnut

#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int i=0, taster_pritisnut=0;
	int r1_value, r2_value;
	
	if (wiringPiSetup() == -1)
		exit(1);
	
	pinMode(21, INPUT);
	pinMode(22, INPUT);
	
	
	if (softPwmCreate(28, 0, 100) != 0)
		exit (2);
	
	i = 0;
	taster_pritisnut = 0;
	
	while (1) {
		r1_value = digitalRead(21); // procitaj KEY0
		r2_value = digitalRead(22); // procitaj KEY1
		
		
		//cekamo na pritisak tastera
		if (!r1_value && !taster_pritisnut) {
			taster_pritisnut = 1;
			delay(50);
			if (i < 100) i += 20;
			printf("i = %d\n", i);
			fflush(stdout);
			softPwmWrite(28, i);
		}
		if (!r2_value && !taster_pritisnut) {
			taster_pritisnut = 1;
			delay(50);
			if (i > 0) i -= 20;
			printf("i = %d\n", i);
			fflush(stdout);
			softPwmWrite(28, i);
		}
		
		// cekamo da se taster otpusti
		if (r1_value && r2_value) 
		{	delay(50);
			taster_pritisnut = 0;
	}
	}
	
	return 0;
}
