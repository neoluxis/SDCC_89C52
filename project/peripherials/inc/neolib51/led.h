#ifndef __NEOLIB51_LED_H
#define __NEOLIB51_LED_H

#include "types.h"
#include "neolib51/led.h"
#include "neolib51/neolib51.h"
typedef enum
{
	LED0 = (0x01 << 0),
	LED1 = (0x01 << 1),
	LED2 = (0x01 << 2),
	LED3 = (0x01 << 3),
	LED4 = (0x01 << 4),
	LED5 = (0x01 << 5),
	LED6 = (0x01 << 6),
	LED7 = (0x01 << 7),
} nled_bitord;

typedef enum
{
	LED_State_ON = 0,
	LED_State_OFF,
	LED_State_Err,
} nled_state;

extern void nled_allon(void);
extern void nled_alloff(void);
extern void nled_alltoggle(void);
extern void nled_set(uint8_t n, uint8_t status);
extern uint8_t nled_get(uint8_t n);

extern void nled_biton(const nled_bitord LEDx);
extern void nled_bitoff(const nled_bitord LEDx);
extern void nled_bittoggle(const nled_bitord LEDx);
extern void nled_set_bitstate(nled_bitord LEDx, nled_state status);
extern nled_state nled_get_bitstate(nled_bitord LEDx);

#endif
