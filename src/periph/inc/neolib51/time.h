#ifndef __NEOLIB51_TIME_H
#define __NEOLIB51_TIME_H

#include "neolib51/neolib51.h"

#if TIME == ENABLE

#include "types.h"

#ifdef DELAY_WITH_TIMER
extern void ntime_delay_init(void);
extern void ntime_delay_us(const uint16_t us);
extern void ntime_delay_ms(const float32_t ms);
#else
extern void ntime_delay_ms(const uint16_t ms);
#endif

#endif

#endif