#include "timer.h"

int Timer_Init(void)
{
	uint32_t returnCode;
	
  returnCode = SysTick_Config(SystemCoreClock / 1000);

	return (int)returnCode;
}
