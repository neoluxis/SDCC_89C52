#include "neolib51/time.h"

#if TIME == ENABLE

#include "at89x52.h"

#ifdef DELAY_WITH_TIMER
#include "neolib51/tim.h"
// TODO: Implement delay with timer
#else
void ntime_delay_ms(const uint16_t ms)
{
    uint16_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 114; j++)
            ;
}
#endif
#endif