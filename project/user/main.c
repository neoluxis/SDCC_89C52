#include "regx52.h"

#include "neolib51/neolib51.h"

void sys_init(void);

void main(void)
{
    // sys_init();
    for (;;)
    {
        uint8_t kv = nbtn_scan_matrix(BTN_Scan_NonContinuous);
        if (kv == MATBTN_11)
        {
            nled_biton(LED1);
        }
        else if (kv == MATBTN_12)
        {
            nled_bitoff(LED1);
        }
        else if (kv == MATBTN_21)
        {
            nled_bittoggle(LED1);
        }
    }
}

void sys_init(void)
{
}
