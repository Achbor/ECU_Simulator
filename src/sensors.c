#include <stdio.h>

#include "sensors.h"
#include "ecu_manager.h"
#include "scheduler.h"


void* Sensor_Task(void* arg)
{
	(void)arg;
	
	ECU_t state;
	
	
	
	while(1)
	{
		ECU_Read(&state);
		
		if (state.engine.running)
		{
			// Start Raising Coolant Temp
			
			if(state.sensors.coolant_temp < 90.0f) state.sensors.coolant_temp += 0.2f;
			
			// Battery Charging
			state.sensors.battery_voltage = 14.7f;
			
			// Oil Pressure Dependind on RPMm
			state.sensors.oil_pressure = 2.0f + ((float)state.engine.rpm / 4000.0f) * 2.5f;			
			
			
			state.faults.overheat = (state.sensors.coolant_temp > 110.0f); 
					
		
		}
		else 
		{
			// When Engine is off
			
			if(state.sensors.coolant_temp > 25.0f) state.sensors.coolant_temp -= 0.1f;
			
			state.sensors.battery_voltage = 12.1f;
			
			state.sensors.oil_pressure = 0.0f;
		}
		
		ECU_Write(&state);
		
		Scheduler_SleepMs(100); // Task Running Every 100ms
	}
	
	return NULL;
}
