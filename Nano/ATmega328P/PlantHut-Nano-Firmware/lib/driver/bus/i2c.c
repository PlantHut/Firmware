/*
 * PlantHut Nano Firmware - i2c.c
 *
 * Created: 08/09/2021 20:02:16
 * Author : M. Jonauskis
 *
 */ 

	#include <lib/driver/bus/i2c.h>


	//***************************************************************************************
	void i2c_init(void){
		I2C_PORT |= (1 << SDA_PIN | 1 << SCL_PIN);			//Port Pullup
		TWCR = 0;
		TWSR = 0;
		TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
		_delay_ms(50);
	}

	//***************************************************************************************
	uint8_t i2c_start (void){
		uint8_t timeout = 0;
		TWCR = (1 << TWINT | 1 << TWSTA | 1 << TWEN);
		while(!(TWCR & (1<<TWINT))){
			if((timeout++) > 100) return 1;
		}
		TWDR = OLED_I2C_ADDR;
		TWCR = (1 << TWINT | 1 << TWEN);
		timeout = 0;
		while(!(TWCR & (1<<TWINT))){
			if((timeout++) > 100) return 1;
		}
		return 0;
	}

	//***************************************************************************************
	uint8_t i2c_byte (uint8_t byte){  
		uint8_t timeout = 0;
		TWDR = byte;
		TWCR = (1 << TWINT | 1 << TWEN);
		while(!(TWCR & (1<<TWINT))){
			if((timeout++) > 100) return 1;
		}
		return 0;
	}

	//***************************************************************************************
	void i2c_stop (void){
		TWCR = (1 << TWINT | 1 << TWSTO | 1 << TWEN);
		TWCR = 0;
	}
