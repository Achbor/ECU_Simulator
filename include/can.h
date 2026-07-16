#ifndef CAN_H
#define CAN_H

void* CAN_Task(void* arg);

void CAN_GetStatistics(uint16_t *engine, uint16_t *sensor, uint16_t* fault);



#endif