#ifndef __NEOLIB51_H
#define __NEOLIB51_H

#define ENABLE 1
#define DISABLE 0

#define LED ENABLE
#define BTN ENABLE
#define TIM ENABLE
#define EXTI DISABLE
#define TIME ENABLE
#define PWM ENABLE

#include "types.h"
#include "REGX52.h"

#if LED == ENABLE
#include "neolib51/led.h"
#endif
#if BTN == ENABLE
#include "neolib51/btn.h"
#endif
#if TIM == ENABLE
#include "neolib51/tim.h"
#endif
#if EXTI == ENABLE
#include "neolib51/exti.h"
#endif
#if TIME == ENABLE
#include "neolib51/time.h"
#endif

#endif