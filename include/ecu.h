#ifndef ECU_H
#define ECU_H

#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    bool running;
    uint16_t rpm;
    uint16_t speed;
    uint8_t throttle;

} Engine_t;


typedef struct
{
    float coolant_temp;
    float battery_voltage;
    float oil_pressure;

} Sensor_t;


typedef struct
{
    bool overheat;
    bool battery_fault;

} Fault_t;


typedef struct
{
    Engine_t engine;
    Sensor_t sensors;
    Fault_t faults;

} ECU_t;

	
void ECU_Init(ECU_t *ecu);
void ECU_PrintStatus(ECU_t* ecu);

#endif
