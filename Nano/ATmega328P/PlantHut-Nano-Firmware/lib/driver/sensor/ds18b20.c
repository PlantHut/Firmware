/*
 * PlantHut Nano Firmware - ds18b20.c
 *
 * Created: 08/09/2021 20:02:16
 * Author : M. Jonauskis
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <lib/driver/sensor/ds18b20.h>

/*
 * ds18b20 init
 */
uint8_t ds18b20_reset(int ch) {
	uint8_t i;

	//low for 480us
	DS18B20_PORT &= ~ (1<<ch); //low
	DS18B20_DDR |= (1<<ch); //output
	_delay_us(480);

	//release line and wait for 60uS
	DS18B20_DDR &= ~(1<<ch); //input
	_delay_us(60);

	//get value and wait 420us
	i = (DS18B20_PIN & (1<<ch));
	_delay_us(420);

	//return the read value, 0=ok, 1=error
	return i;
}

/*
 * write one bit
 */
void ds18b20_writebit(uint8_t bit, int ch){
	//low for 1uS
	DS18B20_PORT &= ~ (1<<ch); //low
	DS18B20_DDR |= (1<<ch); //output
	_delay_us(1);

	//if we want to write 1, release the line (if not will keep low)
	if(bit)
		DS18B20_DDR &= ~(1<<ch); //input

	//wait 60uS and release the line
	_delay_us(60);
	DS18B20_DDR &= ~(1<<ch); //input
}

/*
 * read one bit
 */
uint8_t ds18b20_readbit(int ch){
	uint8_t bit=0;

	//low for 1uS
	DS18B20_PORT &= ~ (1<<ch); //low
	DS18B20_DDR |= (1<<ch); //output
	_delay_us(1);

	//release line and wait for 14uS
	DS18B20_DDR &= ~(1<<ch); //input
	_delay_us(14);

	//read the value
	if(DS18B20_PIN & (1<<ch))
		bit=1;

	//wait 45uS and return read value
	_delay_us(45);
	return bit;
}

/*
 * write one byte
 */
void ds18b20_writebyte(uint8_t byte, int ch){
	uint8_t i=8;
	while(i--){
		ds18b20_writebit(byte&1, ch);
		byte >>= 1;
	}
}

/*
 * read one byte
 */
uint8_t ds18b20_readbyte(int ch){
	uint8_t i=8, n=0;
	while(i--){
		n >>= 1;
		n |= (ds18b20_readbit(ch)<<7);
	}
	return n;
}

/*
 * get temperature
 */
double ds18b20_gettemp(int ch) {
	uint8_t temperature_l;
	uint8_t temperature_h;
	double retd = 0;

	#if DS18B20_STOPINTERRUPTONREAD == 1
	cli();
	#endif

	ds18b20_reset(ch); //reset
	ds18b20_writebyte(DS18B20_CMD_SKIPROM, ch); //skip ROM
	ds18b20_writebyte(DS18B20_CMD_CONVERTTEMP, ch); //start temperature conversion

	while(!ds18b20_readbit(ch)); //wait until conversion is complete

	ds18b20_reset(ch); //reset
	ds18b20_writebyte(DS18B20_CMD_SKIPROM, ch); //skip ROM
	ds18b20_writebyte(DS18B20_CMD_RSCRATCHPAD, ch); //read scratchpad

	//read 2 byte from scratchpad
	temperature_l = ds18b20_readbyte(ch);
	temperature_h = ds18b20_readbyte(ch);

	#if DS18B20_STOPINTERRUPTONREAD == 1
	sei();
	#endif

	//convert the 12 bit value obtained
	retd = ( ( temperature_h << 8 ) + temperature_l ) * 0.0625;

	return retd;
}


