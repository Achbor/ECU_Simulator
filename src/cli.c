#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "can.h"
#include "cli.h"
#include "system.h"
#include "engine.h"
#include "ecu_manager.h"


static void PrintHelp(void);

static void ShowEngine(void);

static void ShowSensors(void);

static void ShowFaults(void);

static void StartEngine(void);

static void StopEngine(void);

static void SetThrottle(int value);

static void InjectOverheat(void);

static void InjectBatteryFault (void);

static void ClearFaults(void);

static void ShowStatistics(void);

static void ShowUpTime(void);



void CLI_Run(void){

	char command[100];
	
	// ECU_t state;

	
	while (1){
	
		// ECU_Read(&state);
	
		printf("\nECU> ");		
		
		if (fgets(command, sizeof(command), stdin) == NULL) continue;
		
		command[strcspn(command, "\n")] = '\0';
		
		if(strcmp(command, "start") == 0)
		{
			StartEngine();
		}
		else if(strcmp(command, "stop") == 0)
		{
			StopEngine();
		}
		else if(strcmp(command, "status") == 0)
		{
			ShowEngine();
		}
		else if(strcmp(command, "faults") == 0)
		{
			ShowFaults();
		}
		else if(strcmp(command, "status") == 0)
		{
			ShowEngine();
		}
		else if(strcmp(command, "help") == 0)
		{
			PrintHelp();
		}
		else if(strcmp(command, "exit") == 0)
		{
			printf("Exiting...\n");
			break;
		}
		else if(strncmp(command, "throttle ", 9) == 0)
		{
			int value = atoi(command+9);
			SetThrottle(value);
		}
		else
		{
			printf("INVALID COMMAND\n");
		}
	}
}

static void StartEngine(void)
{
	ECU_t state;
	
	ECU_Read(&state);
	state.engine.running  = true;

	ECU_Write(&state);

	printf("\nEngine Started.\n");
}

// MEthod to stop the ENgine
static void StopEngine(void)
{
	ECU_t state;
	
	ECU_Read(&state);
	state.engine.running  = false;
	state.engine.throttle = 0; // rpm & speed are nnot touched as the Enigne & sensors thread will update them/.

	ECU_Write(&state);

	printf("\nEngine Stopped.\n");
}

// Method to set throttle
static void SetThrottle(int value)
{
	ECU_t state;

	if(value < 0) value = 0;

	if(value > 100) value = 100;

	ECU_Read(&state);

	state.engine.throttle = value;

	ECU_Write(&state);

	printf("\nThrottle Set To %d%%.\n", value);  // passing the Throttle value in Percentage
}

// Method to Show the Engine
static void ShowEngine(void)
{
	ECU_t state;

	ECU_Read(&state);

	printf("\n");

	printf("======== ENGINE DATA =========\n");

	printf("Running   : %s\n", state.engine.running ? "YES" : "NO");

    printf("RPM       : %u\n", state.engine.rpm);

    printf("Speed     : %u km/h\n", state.engine.speed);

    printf("Throttle  : %u%%\n", state.engine.throttle);

    printf("===========================\n");
}


// Method to SHow the Sensors
static void ShowSensors(void)
{
	ECU_t state;

	ECU_Read(&state);

	printf("\n");

    printf("======= SENSORS =======\n");

    printf("Coolant   : %.1f C\n", state.sensors.coolant_temp);

    printf("Battery   : %.2f V\n", state.sensors.battery_voltage);

    printf("Oil       : %.2f bar\n", state.sensors.oil_pressure);

	printf("============================\n");
}


// Method to show Faults
static void ShowFaults(void)
{
    ECU_t state;

    ECU_Read(&state);

    printf("\n");

    printf("========= FAULTS =========\n");

    printf("Overheat        : %s\n", state.faults.overheat ? "ACTIVE" : "NONE");

    printf("Battery Fault   : %s\n", state.faults.battery_fault ? "ACTIVE" : "NONE");

    printf("============================\n");
}

// Help Method
static void PrintHelp(void)
{
    printf("\n");

    printf("Available Commands\n\n");

    printf("start                -- Engine Start\n");
    printf("stop                 -- Engine Stop\n");
    printf("status               -- To Check the system status\n");
    printf("throttle <0-100> -- To set the Desired Throttle value\n");
    printf("engine          -- To Check the Engine State\n");
    printf("sensors         -- To show the current state of Sensors\n");
    printf("faults          -- Check any Faults in the System\n");
    printf("help                 -- Help with all available Commands and functions\n");
    printf("exit                 -- Exit and Shutdown the system.\n");
}


// Fault INjexctions
static void InjectOverheat(void)
{
	ECU_t state;
	ECU_Read(&state);

	state.faults.overheat = true;

	ECU_Write(&state);

	printf("\nOverheat fault injected.\n");
}

static void InjectBatteryFault(void)
{
	ECU_t state;

	ECU_Read(&state);

	state.faults.battery_fault = true;

	ECU_Write(&state);

	printf("\nBattery Fault Injected.\n");
}

static void ClearFaults(void)
{
	ECU_t state;

	ECU_Read(&state);

	state.faults.overheat = false;
	state.faults.battery_fault = false;

	ECU_Write(&state);

	printf("\nAll Faults Cleared!!\n");
}

static void ShowStatistics(void)
{
	uint16_t engine;
	uint16_t sensor;
	uint16_t fault;

	CAN_GetStatistics(&engine, &sensor, &fault);

	printf("\n");

    printf("CAN Statistics\n");
    printf("-----------------------\n");

    printf("Engine Frames : %lu\n", engine);

    printf("Sensor Frames : %lu\n", sensor);

    printf("Fault Frames  : %lu\n", fault);

    printf("Total Frames  : %lu\n", engine + sensor + fault);

    printf("\n");
}

