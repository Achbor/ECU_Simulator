#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>

#include <sys/socket.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "can.h"
#include "ecu_manager.h"
#include "scheduler.h"


// Custom Variables for CAN
typedef struct
{
    uint16_t engine_frames;
    uint16_t sensor_frames;
    uint16_t fault_frames;
}CAN_Stats_t;

static CAN_Stats_t can_stats;


// INititalizing the socket
static int can_socket;


// Initialization of CAN Communications
static int CAN_Init(void)
{
    struct sockaddr_can addr;
    struct ifreq ifr;

    can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if(can_socket < 0)
    {
        perror("socket");
        return -1;
    }
    
    strcpy(ifr.ifr_name, "vcan0");

    if(ioctl(can_socket, SIOCGIFINDEX, &ifr) < 0)
    {
        perror("ioctl");
        return -1;
    }

    // ioctl(sock, SIOCGIFINDEX, &ifr);
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    
    if(bind(can_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return -1;
    }
    printf("Socket Initilized Successfully!!\n");

    return 0;
}



// Method to Get CAN_BUS Stats
void CAN_GetStatistics(uint16_t* engine, uint16_t* sensor, uint16_t* fault)
{
    *engine = can_stats.engine_frames;
    *sensor  = can_stats.sensor_frames;
    *fault = can_stats.fault_frames;
}


// SEnding CAN Engine Data Packets. 
static void CAN_sendEngineFrame(const ECU_t* state)
{

    struct can_frame frame;

    memset(&frame, 0, sizeof(frame));

    frame.can_id = 0x100;
    frame.can_dlc = 8;

    // Packing data

    // RPM Data
    frame.data[0] = state->engine.rpm & 0xFF;
    frame.data[1] = (state->engine.rpm >> 8);

    // Paxking Speed data
    frame.data[2] = state->engine.speed & 0xFF;
    frame.data[3] = (state->engine.speed >> 8);

    //Packing throttle
    frame.data[4] = state->engine.throttle ;

    // Packing Running State
    frame.data[5] = state->engine.running ;

    // Reserved
    // frame.data[6] = 0;
    // frame.data[7] = 0;

    write(can_socket, &frame, sizeof(frame));

    can_stats.engine_frames++;
    
}


// Methdo to Send Sensor DAta

static void CAN_sendSensorFrame(ECU_t* state)
{
    struct can_frame frame;

    uint16_t coolant = (uint16_t)(state->sensors.coolant_temp * 10);
    uint16_t battery = (uint16_t)(state->sensors.battery_voltage * 100);
    uint16_t pressure = (uint16_t)(state->sensors.oil_pressure * 100);

    memset(&frame, 0, sizeof(frame));

    frame.can_id = 0x101;
    frame.can_dlc = 8;

    // Packing DAta
    //Coolant Data
    frame.data[0] = coolant & 0xFF;
    frame.data[1] = coolant >> 8;

    // Battery Data
    frame.data[2] = battery & 0xFF;
    frame.data[3] = battery >> 8;

    // Pressure Date
    frame.data[4] = pressure & 0xFF;
    frame.data[5] = pressure >> 8;


    write(can_socket, &frame, sizeof(frame));

    can_stats.sensor_frames++;
}


// Mesthod to Send Faults Frames
static void CAN_sensFaultFrame(const ECU_t* state)
{
    struct can_frame frame;

    memset(&frame, 0, sizeof(frame));

    frame.can_id = 0x102;
    frame.can_dlc = 8;

    // Overheat Data
    frame.data[0] = state->faults.overheat & 0xFF;

    //  Battery Fautl data
    frame.data[1] = state->faults.battery_fault & 0xFF;

    write(can_socket, &frame, sizeof(frame));

    can_stats.fault_frames++;
}

// Implementation of hte CAN_Task Thread
void* CAN_Task(void* arg)
{
    (void)arg;

    ECU_t state;

    if (CAN_Init() < 0) return NULL;

    while(1)
    {
        ECU_Read(&state);

        CAN_sendEngineFrame(&state);

        CAN_sendSensorFrame(&state);

        CAN_sensFaultFrame(&state);

        Scheduler_SleepMs(100);
    }

    return NULL;
}