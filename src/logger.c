#include<stdio.h>
// #include <unistd.h>

#include "logger.h"
#include "ecu_manager.h"
#include "scheduler.h"
#include "system.h"

static void ShowUpTime(void)
{
	uint64_t uptime = System_GetUptimeSeconds();

	uint64_t hours = uptime / 3600;  
	uint16_t minutes = (uptime % 3600) / 60; 
	uint16_t seconds = uptime % 60; 

	printf("\nUptime : %02lu:%02lu:%02lu\n", hours, minutes, seconds);
}


static void PrintDashboard(const ECU_t* state)
{
	printf("\n=====================================\n");

    printf("Engine Running : %s\n", state->engine.running ? "YES" : "NO");

    printf("RPM            : %u\n", state->engine.rpm);

    printf("Speed          : %u km/h\n", state->engine.speed);

    printf("Throttle       : %u %%\n", state->engine.throttle);


    printf("****************************************\n");


    printf("Coolant Temp   : %.1f C\n", state->sensors.coolant_temp);

    printf("Battery Volt   : %.2f V\n", state->sensors.battery_voltage);

    printf("Oil Pressure   : %.2f bar\n", state->sensors.oil_pressure);


    printf("****************************************\n");


    printf("Overheat       : %s\n", state->faults.overheat ? "ACTIVE" : "NO");

    printf("Battery Fault  : %s\n", state->faults.battery_fault ? "ACTIVE" : "NO");

    printf("=====================================\n");

	ShowUpTime();
}


void* Logger_Task(void* arg)
{
	(void) arg;

	ECU_t state;
	
	while(1)
	{
		Scheduler_SleepMs(5000);
		
		ECU_Read(&state);
		
		PrintDashboard(&state);

		Scheduler_SleepMs(1000);
		
		
	}
	
	return NULL;
}
