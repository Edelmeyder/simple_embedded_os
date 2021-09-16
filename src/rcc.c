#include "rcc.h"

int RCC_Init(void)
{
	RCC->APB2ENR |= 0xFC; //Enable GPIO ports clocks
	
	return 0;
}