#ifndef __NEOLIB51_TIM_H
#define __NEOLIB51_TIM_H

#include "neolib51/neolib51.h"

#if TIM == ENABLE

#include "types.h"
#include "exti.h"

#define OSC_FREQ 11059200
#define PRD_OSC 1 / OSC_FREQ
#define PRD_MACHINE_CYCLE PRD_OSC * 12

typedef enum
{
    TIM0 = 0,
    TIM1,
} ntim_id_e;

typedef enum
{
    TIM_ARB_TIMER = 0,
    TIM_ARB_COUNTER,
} ntim_arbeit_e;

typedef enum
{
    TIM_MODE_13BIT = 0,
    TIM_MODE_16BIT,
    TIM_MODE_8BIT,
    TIM_MODE_2x8BIT,
    TIM_MODE_AUTO, // 自动选择计数模式
} ntim_mode_e;

typedef struct _ntim_t ntim_t;
struct _ntim_t
{
    /* 必须配置 */
    ntim_id_e tim_id;
    ntim_arbeit_e arbeit;
    ntim_mode_e mode;
    uint8_t enable;     // 使能标志
    uint8_t enable_irq; // 使能中断
    uint16_t period;    // 计时时间(us)/计数次数
    void (*user_callback)(ntim_t *);

    /* 可选配置 */
    uint8_t th;
    uint8_t tl;
};

extern ntim_t *ntim0;
extern ntim_t *ntim1;

extern void ntim_init(ntim_t *ntimx);

extern void ntim_deinit(ntim_t *ntimx);

extern void ntim_reload(ntim_t *ntimx);

extern void ntim_start(ntim_t *ntimx);

extern void ntim_stop(ntim_t *ntimx);

extern void ntim_en_irq(ntim_t *ntimx);

extern void ntim_dis_irq(ntim_t *ntimx);

#endif
#endif