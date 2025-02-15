#include "neolib51/led.h"

#include "at89x52.h"

#define LED_Port P1

void nled_biton(const nled_bitord LEDx) { LED_Port &= ~LEDx; }
void nled_bitoff(const nled_bitord LEDx) { LED_Port |= LEDx; }

void nled_allon(void) { LED_Port = 0x00; }

void nled_alloff(void) { LED_Port = 0xff; }

void nled_alltoggle(void)
{
  LED_Port = ~LED_Port;
}

void nled_set(uint8_t status)
{
  LED_Port = status;
}

uint8_t nled_get(void)
{
  return LED_Port;
}

void nled_bittoggle(const nled_bitord LEDx)
{
  LED_Port ^= LEDx;
}

void nled_set_bitstate(nled_bitord LEDx, nled_state state)
{
  switch (state)
  {
  case LED_State_ON:
    nled_biton(LEDx);
    break;
  case LED_State_OFF:
    nled_bitoff(LEDx);
    break;
  }
}

nled_state nled_get_bitstate(nled_bitord LEDx)
{
  return (LED_Port & LEDx) >> (LEDx >> 1);
}
