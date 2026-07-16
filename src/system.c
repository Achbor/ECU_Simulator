#include <time.h>

#include "system.h"

static time_t start_time;

void System_Init(void)
{
    start_time = time(NULL);
}

uint64_t System_GetUptimeSeconds(void)
{
    return (uint64_t)(time(NULL) - start_time);
}