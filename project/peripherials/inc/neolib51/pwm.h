#ifndef __NEOLIB51_PWM_H
#define __NEOLIB51_PWM_H

#include "neolib51/neolib51.h"

#if PWM == ENABLE

#if TIM == DISABLE
#error "TIM must be enabled to use PWM"
#endif

#include "neolib51/tim.h"
#include "neolib51/led.h"

typedef struct
{
    ntim_t *ntimx;   // 使用的定时器
    uint16_t disol;  // 分辨率
    uint16_t period; // 波周期(us)
    nled_bitord nledx;
} npwm_t;

extern void npwm_init(npwm_t *npwmx);
extern void npwm_set_duty(npwm_t *npwmx, uint8_t duty);
extern uint8_t npwm_get_duty(npwm_t *npwmx);

#endif
#endif