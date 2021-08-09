/*
 * PlantHut Nano Firmware - main.c
 *
 * Created: 08/09/2021 20:02:16
 * Author : M. Jonauskis
 *
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include <lib/driver/bus/i2c.h>
#include <lib/driver/display/ssd1306.h>
#include <lib/driver/sensor/dht.h>
#include <lib/driver/sensor/ds18b20.h>

#include <main.h>


int main(void)
{

	char printbuff[100];
	double Peltier_T1, Peltier_T2;

	i2c_init();
	oled_init();
	
	while(1)
	{
		
		/*								 /
		/	Printing PlantHut Version	 /
		/								*/
		
		oled_font_size(0);
		oled_gotoxy(0,7);
		oled_write("PlantHut V%i.%i.%i", version_major, version_minor, version_build);
		


		Peltier_T1 = ds18b20_gettemp(PD7);
		dtostrf(Peltier_T1, 3, 3, printbuff);
		oled_gotoxy(0,3);
		oled_write("T1: ");  oled_write("%s",printbuff); oled_write("C");
		
		Peltier_T2 = ds18b20_gettemp(PD6);
		dtostrf(Peltier_T2, 3, 3, printbuff);
		oled_gotoxy(0,4);
		oled_write("T2: ");  oled_write("%s",printbuff); oled_write("C");
		

		if(dht_gettemperaturehumidity(&temperature, &humidity) != -1) {

			oled_font_size(0);
	
			dtostrf(temperature, 3, 3, printbuff);
			oled_gotoxy(0,1);
			oled_write("T: "); 	oled_write("%s",printbuff); oled_write("C");
	
			dtostrf(humidity, 3, 3, printbuff);
			oled_gotoxy(0,2);
			oled_write("H: "); 	oled_write("%s",printbuff); oled_write("H");

			} else {
	
			//oled_clear_screen();
			oled_font_size(0);
			oled_gotoxy(0,1);
			oled_write("Error");
			oled_gotoxy(0,2);
			oled_write("Error");
	
		}
		
		_delay_ms(1500);
		

	}

}
