

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

#include "stm32f4xx.h"

void uart2_tx_init(uint32_t baud,uint32_t freq);
char uart2_read(void);
void uart2_rxtx_init(uint32_t baud,uint32_t freq);


#endif /* UART_H_ */