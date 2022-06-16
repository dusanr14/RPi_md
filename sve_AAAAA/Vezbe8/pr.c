// primer rada sa PCF8563 koji ispisuje tekuce vreme
// u terminalu svakih 5 sekundi

#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16))

//adrese registara
#define SEK 0x02
#define MIN 0x03
#define SAT 0x04
#define DANI 0x05
#define MESECI 0x07
#define GODINE 0x08



 unsigned char WriteBuf[2];
 unsigned char ReadBuf;
 unsigned char g8563_Store[7];
								// sec,min,sat
 unsigned char init8563_Store[7]={0x00,0x59,0x08, 0x01, 0x04, 0x10, 0x01};
 
 void P8563_settime()
{
	 WriteBuf[0] = SEK;
	 WriteBuf[1] = g8563_Store[0];
	 bcm2835_i2c_write(WriteBuf,2);
	
	 WriteBuf[0] = MIN;
	 WriteBuf[1] = g8563_Store[1];
	 bcm2835_i2c_write(WriteBuf,2);

	 WriteBuf[0] = SAT;
	 WriteBuf[1] = g8563_Store[2];
	 bcm2835_i2c_write(WriteBuf,2);
	 
	 WriteBuf[0] = DANI;
	 WriteBuf[1] = g8563_Store[3];
	 bcm2835_i2c_write(WriteBuf,2);
	
	 WriteBuf[0] = MESECI;
	 WriteBuf[1] = g8563_Store[5];
	 bcm2835_i2c_write(WriteBuf,2);

	 WriteBuf[0] = GODINE;
	 WriteBuf[1] = g8563_Store[6];
	 bcm2835_i2c_write(WriteBuf,2);
}

void P8563_init()
{
	unsigned char i;
	
	for(i=0;i<=6;i++)
		g8563_Store[i]=init8563_Store[i];

	P8563_settime();
	printf("Postavi početno tekuće vreme\n");

	//inicijalizacija RTC-a
	WriteBuf[0] = 0x0;
	WriteBuf[1] = 0x00; //normalni rezim rada
	bcm2835_i2c_write(WriteBuf,2);
}
///usr/local/include/bcm2835.h:587:
void P8563_Readtime()
{
	unsigned char time[7];
	
	WriteBuf[0] = SEK;
	bcm2835_i2c_write_read_rs(WriteBuf, 1, time, 7);

	 g8563_Store[0] = time[0] & 0x7f;
	 g8563_Store[1] = time[1] & 0x7f;
	 g8563_Store[2] = time[2] & 0x3f;
	 g8563_Store[3] = time[3] & 0x3f;
	 g8563_Store[5] = time[5] & 0x1f;
	 g8563_Store[6] = time[6] & 0xff;

	 g8563_Store[0] = changeHexToInt(g8563_Store[0]);
	 g8563_Store[1] = changeHexToInt(g8563_Store[1]);
	 g8563_Store[2] = changeHexToInt(g8563_Store[2]);
	 g8563_Store[3] = changeHexToInt(g8563_Store[3]);
	 g8563_Store[5] = changeHexToInt(g8563_Store[5]);
	 g8563_Store[6] = changeHexToInt(g8563_Store[6]);
}

int main(int argc, char **argv)
{
	if (!bcm2835_init())
		return 1;

	bcm2835_i2c_begin();
	
	// adresa PCF8563 na I2C magistrali
	 bcm2835_i2c_setSlaveAddress(0x51);
	 bcm2835_i2c_set_baudrate(10000);
	 printf("start..........\n");
	 P8563_init();
	 
	while(1)
	{
		P8563_Readtime();
		printf("Sati:%d Minuti:%d Sekunde:%d, Dani:%d MJeseci:%d Godine:%d, \n", g8563_Store[2], g8563_Store[1], g8563_Store[0], g8563_Store[3], g8563_Store[5], g8563_Store[6]);
		bcm2835_delay(5000);
	}

	bcm2835_i2c_end();
	bcm2835_close();

	return 0;
}
