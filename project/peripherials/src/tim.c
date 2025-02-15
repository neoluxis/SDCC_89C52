#include "neolib51/tim.h"

#if TIM == ENABLE

#include "REGX52.H"
#include "MATH.H"

ntim_t nt0, nt1;
ntim_t *ntim0 = &nt0;
ntim_t *ntim1 = &nt1;

static void __ntim_calc_reload_in_13bit(ntim_t *ntimx)
{
    uint16_t count = 0; // 计数次数
    uint16_t reload = 0;
    switch (ntimx->arbeit)
    {
    case TIM_ARB_TIMER:
        count = ntimx->period / PRD_MACHINE_CYCLE;
        break;
    case TIM_ARB_COUNTER:
        count = ntimx->period;
        break;
    default:
        break;
    }
    reload = 0x1FFF - count;
    ntimx->th = (uint8_t)(reload >> 8);
    ntimx->tl = (uint8_t)(reload & 0xFF);
}

static void __ntim_calc_reload_in_16bit(ntim_t *ntimx)
{
    uint16_t count = 0; // 计数次数
    uint16_t reload = 0;
    switch (ntimx->arbeit)
    {
    case TIM_ARB_TIMER:
        count = ntimx->period / PRD_MACHINE_CYCLE;
        break;
    case TIM_ARB_COUNTER:
        count = ntimx->period;
        break;
    default:
        break;
    }
    reload = 0xFFFF - count;
    ntimx->th = (uint8_t)(reload >> 8);
    ntimx->tl = (uint8_t)(reload & 0xFF);
}

static void __ntim_calc_reload_in_8bit(ntim_t *ntimx)
{
    uint8_t count = 0; // 计数次数
    uint8_t reload = 0;
    switch (ntimx->arbeit)
    {
    case TIM_ARB_TIMER:
        count = ntimx->period / PRD_MACHINE_CYCLE;
        break;
    case TIM_ARB_COUNTER:
        count = ntimx->period;
        break;
    default:
        break;
    }
    reload = 0xFF - count;
    ntimx->tl = reload;
    ntimx->th = reload;
}

static void __ntim_calc_reload(ntim_t *ntimx)
{
    uint16_t count = 0; // 计数次数
    switch (ntimx->mode)
    {
    case TIM_MODE_13BIT:
        __ntim_calc_reload_in_13bit(ntimx);
        break;
    case TIM_MODE_16BIT:
        __ntim_calc_reload_in_16bit(ntimx);
        break;
    case TIM_MODE_8BIT:
        __ntim_calc_reload_in_8bit(ntimx);
        break;
    case TIM_MODE_2x8BIT:
        // TODO: Implement this mode
        break;
    case TIM_MODE_AUTO: // 自动选择模式
        count = ntimx->period / PRD_MACHINE_CYCLE;
        if (count < 0xff) // 8bit 255
        {
            ntimx->mode = TIM_MODE_8BIT;
            __ntim_calc_reload_in_8bit(ntimx);
        }
        else if (count < 0x1fff) // 13bit 8191
        {
            ntimx->mode = TIM_MODE_13BIT;
            __ntim_calc_reload_in_13bit(ntimx);
        }
        else // 16bit 65535
        {
            ntimx->mode = TIM_MODE_16BIT;
            __ntim_calc_reload_in_16bit(ntimx);
        }
        break;
    default:
        break;
    }
}

static void __ntim_set_mode(ntim_t *ntimx)
{
    switch (ntimx->tim_id)
    {
    case TIM0:
        TMOD &= 0xF0;
        TMOD |= ntimx->mode;
        break;
    case TIM1:
        TMOD &= 0x0F;
        TMOD |= ntimx->mode << 4;
        break;
    }
}

static void __ntim_set_arbeit(ntim_t *ntimx)
{
    switch (ntimx->tim_id)
    {
    case TIM0:
        if (ntimx->arbeit == TIM_ARB_TIMER)
            TMOD &= ~(0x01 << 2);
        else
            TMOD |= 0x01 << 2;
        break;
    case TIM1:
        if (ntimx->arbeit == TIM_ARB_TIMER)
            TMOD &= ~(0x01 << 6);
        else
            TMOD |= 0x01 << 6;
        break;
    default:
        break;
    }
}

void ntim_init(ntim_t *ntimx)
{
    __ntim_calc_reload(ntimx);
    __ntim_set_mode(ntimx);
    __ntim_set_arbeit(ntimx);
    ntim_reload(ntimx);
    if (ntimx->enable_irq)
    {
        ntim_en_irq(ntimx);
    }
    else
    {
        ntim_dis_irq(ntimx);
    }

    if (ntimx->enable)
    {
        ntim_start(ntimx);
    }
    else
    {
        ntim_stop(ntimx);
    }
}

void ntim_deinit(ntim_t *ntimx)
{
    ntim_stop(ntimx);
    ntim_dis_irq(ntimx);
}

void ntim_reload(ntim_t *ntimx)
{
    if (ntimx->mode == TIM_MODE_8BIT)
        return;
    else
    {
        switch (ntimx->tim_id)
        {
        case TIM0:
            TH0 = ntimx->th;
            TL0 = ntimx->tl;
            break;
        case TIM1:
            TH1 = ntimx->th;
            TL1 = ntimx->tl;
            break;
        default:
            break;
        }
    }
}

void ntim_start(ntim_t *ntimx)
{
    switch (ntimx->tim_id)
    {
    case TIM0:
        TR0 = 1;
        break;
    case TIM1:
        TR1 = 1;
        break;
    default:
        break;
    }
}

void ntim_stop(ntim_t *ntimx)
{
    switch (ntimx->tim_id)
    {
    case TIM0:
        TR0 = 0;
        break;
    case TIM1:
        TR1 = 0;
        break;
    default:
        break;
    }
}

void ntim_en_irq(ntim_t *ntimx)
{
    switch (ntimx->tim_id)
    {
    case TIM0:
        ET0 = 1;
        break;
    case TIM1:
        ET1 = 1;
        break;
    default:
        break;
    }
}

void ntim_dis_irq(ntim_t *ntimx)
{
    switch (ntimx->tim_id)
    {
    case TIM0:
        ET0 = 0;
        break;
    case TIM1:
        ET1 = 0;
        break;
    default:
        break;
    }
}

#endif