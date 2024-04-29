/*
 * UART.c
 *
 *  Created on: Apr 28, 2024
 *      Author: mrbaytar
 */

#include "UART.h"

/*
 * PA2 -> USART2_TX
 * PA3 -> USART2_RX
 */

/*
 * Procedure:
 *	1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
 *	2. Program the M bit in USART_CR1 to define the word length.
 *	3. Program the number of stop bits in USART_CR2.
 *	4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
 *	   place. Configure the DMA register as explained in multibuffer communication.
 *	5. Select the desired baud rate using the USART_BRR register.
 *	6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
 *	7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
 *	   for each data to be transmitted in case of single buffer.
 *	8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
 *	   that the transmission of the last frame is complete. This is required for instance when
 *	   the USART is disabled or enters the Halt mode to avoid corrupting the last
 *	   transmission.
 */


void USART2_Init(void)
{
	RCC->APB1ENR |= (1 << 17);  // USART2 clock enable
	RCC->AHB1ENR |= (1 << 0);	// GPIO port A clock enable

	GPIOA->MODER |= (2 << 4); 	// GPIOA 2 Alternate function mode (usart tx)

	GPIOA->OSPEEDR |= (3 << 4); // Very high speed PA2

	GPIOA->AFR[0] |= (7 << 8);  // Bites (11:10:9:8) = 0:1:1:1  --> AF7 Alternate function for USART2 at Pin PA2

	USART2->CR1 = 0x00; // Clear ALL
	USART2->CR1 |= (1 << 13);   // USART enabled

	USART2->CR1 &= ~(1 << 12);   // M bit is 0 . ( 1 Start bit, 8 Data bits, n Stop bit)

	//USART2->CR2 &= ~(1 << 12);   // 1 Stop bit
	USART2->BRR |= (13 << 0) | (22 << 4);  // Baud rate of 115200, PCLK1 at 42MHz (22 Mantissa , 13 Fraction)
	USART2->CR1 |= (1 << 3);	// Transmitter is enabled
}

void UART2_SendChar(char c)
{
	USART2->DR = c;  // Load data to Data register

	while(!(USART2->SR & (1 << 6)));
}


















