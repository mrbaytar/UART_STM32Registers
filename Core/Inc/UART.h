/*
 * UART.h
 *
 *  Created on: Apr 28, 2024
 *      Author: mrbaytar
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32f4xx_hal.h"

void USART2_Init(void);
void UART2_SendChar(char c);

#endif /* INC_UART_H_ */
