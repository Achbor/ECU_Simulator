#include <stdio.h>

#include "fault_manager.h"
#include "ecu_manager.h"
#include "scheduler.h"

void* Fault_Manager_Task(void* arg)
{
    (void) arg;

    ECU_t state;

    while(1)
    {
        ECU_Read(&state);

        state.faults.overheat = false;

        if (state.sensors.coolant_temp > 110.0f) state.faults.overheat = true;

        ECU_Write(&state);

        Scheduler_SleepMs(100);
    }

    return NULL;
}