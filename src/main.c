#include<stdio.h>
#include<pthread.h>

#include "ecu.h"
#include "can.h"
#include "engine.h"
#include "cli.h"
#include "logger.h"
#include "sensors.h"
#include "system.h"
#include "ecu_manager.h"
#include "fault_manager.h"

// static time_t start_time;

int main(){

	// API for Accessing Time Elapsed
	System_Init();

	// ECU Manager INitialization
	ECU_Manager_Init();
	
	// Multi threading Handlers initialization
	pthread_t loggerThread;
	pthread_t engineThread;
	pthread_t sensorThread;
	pthread_t faultThread;
	pthread_t canThread;

	// Initializiig the ECU
	ECU_t ecu;
	
	ECU_Init(&ecu);
	
	// Initializing the Engine
	
	// Engine_Init();
	
	// printf("\n");
	// printf("=====================================\n");
	// printf(" Automotive ECU Simulator\n");
	// printf("=====================================\n");

	// printf("Type 'status' to view ECU state.\n");
	// printf("Type 'exit' to quit.\n");
	
	// // Initializing Logger Thread
	pthread_create(&loggerThread, NULL, Logger_Task, &ecu);
	
	// Initilaizing Engine Threas
	pthread_create(&engineThread, NULL, Engine_Task, NULL);
	
	// Creating Sensor Thread
	pthread_create(&sensorThread, NULL, Sensor_Task, NULL);

	// crreating Fault Managing Thread
	pthread_create(&faultThread, NULL, Fault_Manager_Task, NULL);

	// creating CAN Thread
	pthread_create(&canThread, NULL, CAN_Task, NULL);

	CLI_Run();

	pthread_join(engineThread, NULL);
	pthread_join(sensorThread, NULL);
	pthread_join(faultThread, NULL);
	pthread_join(canThread, NULL);
	
		
	
	return 0;
}
