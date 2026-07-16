#ifndef ECU_MANAGER_H
#define ECU_MANAGER_H

#include "ecu.h"


void ECU_Manager_Init(void);

// Read Current ECU Statee
void ECU_Read(ECU_t* dest);

// Update the ECU states
void ECU_Write(const ECU_t* src);


#endif
