#include "neolib51/pwm.h"
#include "neolib51/neolib51.h"
#include "REGX52.H"

#if PWM == ENABLE

#if TIM != ENABLE
#error "TIM must be enabled to use PWM"
#endif

void npwm_init(npwm_t *npwmx)
{
}

void npwm_set_duty(npwm_t *npwmx, uint8_t duty)
{
}

uint8_t npwm_get_duty(npwm_t *npwmx)
{
}

#endif