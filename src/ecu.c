#include <stdio.h>
#include "ecu.h"

void ECU_Init(ECU_t* ecu){

//	pthread_mutex_init(&ecu->lock, NULL);
	
	ecu->engine.running = false;
	
	ecu->engine.rpm = 0;
	ecu->engine.speed = 0;
	
	ecu->engine.throttle = 0;
	
	ecu->sensors.coolant_temp = 25.0f;
	ecu->sensors.battery_voltage = 12.6f;
	ecu->sensors.oil_pressure = 0.0f;
	
	ecu->faults.overheat = false;
	ecu->faults.battery_fault = false;
	
}

void ECU_PrintStatus(ECU_t* ecu){
	
	
	
	printf("\n");
	printf("====================================");
	printf("------AUTOMOTIVE ECU SIMULATOR------");
	printf("====================================\n");
	
	printf("Engine     : %s\n", ecu->engine.running ? "RUNNING" : "OFF");

	printf("RPM        : %u\n", ecu->engine.rpm);
	printf("Speed      : %u km/h\n", ecu->engine.speed);
	printf("Throttle   : %u %%\n", ecu->engine.throttle);

	printf("Coolant    : %.1f C\n", ecu->sensors.coolant_temp);
	printf("Battery    : %.1f V\n", ecu->sensors.battery_voltage);
	printf("Oil        : %.1f bar\n", ecu->sensors.oil_pressure);
	
	printf("Overheat   : %s\n", ecu->faults.overheat ? "YES" : "NO");

	printf("Battery FL : %s\n", ecu->faults.battery_fault ? "YES" : "NO");
	
	
}
