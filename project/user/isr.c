#include "neolib51/tim.h"
#include "neolib51/exti.h"

#if EXTI == ENABLE

void nexti0_isr(void) interrupt 0
{
    // nexti0->user_callback(ntim0);
}

void nexti1_isr(void) interrupt 2
{
    // nexti1->user_callback(ntim0);
}

#endif

#if TIM == ENABLE
void ntim0_isr(void) interrupt 1
{
    ntim_reload(ntim0);
    ntim0->user_callback(ntim0);
}

void ntim1_isr(void) interrupt 3
{
    ntim_reload(ntim1);
    ntim1->user_callback(ntim1);
}
#endif