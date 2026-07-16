#include <pthread.h>
#include <string.h>

#include "ecu_manager.h"

static ECU_t ecu;

static pthread_mutex_t ecuLock;

ECU_t* ECU_GetHandle(void){

	return &ecu;
}

void ECU_Manager_Init(void)
{

	pthread_mutex_init(&ecuLock, NULL);
	
	ECU_Init(&ecu);
}

// Copying the ECU state
void ECU_Read(ECU_t* dest)
{
	pthread_mutex_lock(&ecuLock);
	
	
	memcpy(dest, &ecu, sizeof(ECU_t));
	
	pthread_mutex_unlock(&ecuLock);
}


// Updatting ECU STATEs
void ECU_Write(const ECU_t* src)
{
	pthread_mutex_lock(&ecuLock);
	
	//pthread_mutex_t lock = ecu.lock;
	
	memcpy(&ecu, src, sizeof(ECU_t));
	
	//ecu.lock = lock;
	
	pthread_mutex_unlock(&ecuLock);
}


// Printing Method
void ECU_Print(void){
	pthread_mutex_lock(&ecuLock);
	
	ECU_PrintStatus(&ecu);
	
	pthread_mutex_unlock(&ecuLock);
}


































