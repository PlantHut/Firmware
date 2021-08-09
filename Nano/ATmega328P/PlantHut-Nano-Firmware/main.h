/*
 * PlantHut Nano Firmware - main.h
 *
 * Created: 08/09/2021 20:02:16
 * Author : M. Jonauskis
 *
 */ 

#ifndef MAIN_H_
#define MAIN_H_

	// Firmware Version - format V(Major).(Minor).(Build)
	#define version_major	0
	#define version_minor	3
	#define version_build	6

	// Main global variables for Environment Control
	#if DHT_FLOAT == 0
		int8_t temperature = 0;
		int8_t humidity = 0;
	#elif DHT_FLOAT == 1
		float temperature = 0;
		float humidity = 0;
	#endif

#endif /* MAIN_H_ */