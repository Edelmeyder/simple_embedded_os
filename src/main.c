#include "main.h"

void SysTick_Handler(void);

int main(void)
 {
	SEOS_Init(); 
	
	RCC_Init();
	Timer_Init();
	Gpio_Init();
	
	/* LOOP */
	while(1)
	{
		SEOS_Dispatch();
		SEOS_Sleep();
	}
	

}

void SysTick_Handler(void)
{
	SEOS_Schedule();
}
