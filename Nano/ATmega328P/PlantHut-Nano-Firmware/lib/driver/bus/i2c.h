/*
 * PlantHut Nano Firmware - i2c.h
 *
 * Created: 08/09/2021 20:02:16
 * Author : M. Jonauskis
 *
 */ 


#ifndef I2C_H_
#define I2C_H_

	#include <avr/io.h>
	#include <util/delay.h>

	#define SDA_PIN			PC4
	#define SCL_PIN			PC5
	#define I2C_PORT		PORTC

	#define OLED_I2C_ADDR	0x78
	#define SCL_CLOCK		400000UL

	void i2c_init(void);
	uint8_t i2c_start (void);
	uint8_t i2c_byte (uint8_t byte);
	void i2c_stop (void);

#endif /* I2C_H_ */