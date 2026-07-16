#ifndef PLATFORM_THREAD_H
#define PLATFORM_THREAD_H

#include <pthread.h>

typedef void* (*ThreadFunction_t)(void*);

int Platform_CreateThread(pthread_t* thread, ThreadFunction_t function, void* arg);

#endif