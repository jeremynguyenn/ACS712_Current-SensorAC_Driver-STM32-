


#ifndef __delay__H__
#define __delay__H__


#include <stdint.h>
uint64_t millis(void);
void systick_init_ms(uint32_t freq);
void delay(uint32_t delay);
#endif
