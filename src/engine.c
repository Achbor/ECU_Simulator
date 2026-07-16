#include <stdio.h>
#include <unistd.h>

#include "engine.h"
#include "ecu_manager.h"

static EngineState_t state =  ENGINE_OFF;

void Engine_Init(void){

	state = ENGINE_OFF;
}

EngineState_t Enigne_GetState(void){
	return state;
}


// Enigne Multi-Thread Task
void* Engine_Task(void* arg){

	(void)arg;
	
	ECU_t snapshot;
	
	while(1)
	{
		
		ECU_Read(&snapshot);
		
		if(snapshot.engine.running)
		{
			snapshot.engine.rpm = 800 + snapshot.engine.throttle * 50;
			
			snapshot.engine.speed = snapshot.engine.throttle;			
		}
		
		ECU_Write(&snapshot);
		
		usleep(10000); // To run every 10Miliseconds
	}
	
	return NULL;
}


// void Engine_Start(ECU_t *ecu){
	
// 	if (state == ENGINE_OFF){
// 		printf("Starting Enigne...\n");
		
// 		state = ENGINE_RUNNING;
		
// 		ecu->engine.running = true;
// 		ecu->engine.rpm = 850;
// 		ecu->sensors.oil_pressure = 2.5f;
// 	}
// }

// void Engine_Stop(ECU_t *ecu){
	
// 	if (state == ENGINE_RUNNING){
		
// 		printf ("Stopping Engine...\n");
		
// 		state = ENGINE_OFF;
		
// 		ecu->engine.running = false;
// 		ecu->engine.rpm = 0;
// 		ecu->engine.speed = 0;
// 		ecu->sensors.oil_pressure = 0.0f;
// 		ecu->engine.throttle = 0;
// 	}
// }

// void Engine_Update(ECU_t* ecu){
	
// 	if (state != ENGINE_RUNNING){
// 		return ;
// 	}
// 	ecu->engine.rpm = 800 + ecu->engine.throttle * 50;
// 	ecu->engine.speed = ecu->engine.throttle;
// 	ecu->sensors.coolant_temp += 0.05f;
	
// 	if (ecu->sensors.coolant_temp > 110.0f) ecu->faults.overheat= true;
	
// }



























