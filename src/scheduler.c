#include <time.h>

#include "scheduler.h"

void Scheduler_SleepMs(long milliseconds)
{
    struct timespec ts;
    
    ts.tv_sec = milliseconds / 1000;

    ts.tv_nsec = (milliseconds % 1000) * 1000000;

    clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);
}