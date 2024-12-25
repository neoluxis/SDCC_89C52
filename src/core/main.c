#include "at89x52.h"

void delay_ms(unsigned int ms) {
	for(;--ms;)
		for(unsigned int t=114;--t;)
			;
}

void main(void) {
	
	for(;;) {
		P1 = 0x00;
		delay_ms(500);
		P1 = 0xff;
		delay_ms(500);
	}
}
