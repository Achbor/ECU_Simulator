#ifndef ENGINE_H
#define ENGINE_H

#include "ecu.h"

typedef enum{
	ENGINE_OFF,
	ENGINE_STARTING,
	ENGINE_RUNNING,
	ENGINE_SHUTDOWN
}EngineState_t;

void* Engine_Task(void* arg);

// void Engine_Init(void);

// void Engine_Start(ECU_t *ecu);

// void Engine_Stop(ECU_t *ecu);

// void Engine_Update(ECU_t *ecu);

// EngineState_t Engine_GetState(void);

#endif
