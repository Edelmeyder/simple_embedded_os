#include "seos.h"

/* PUBLIC FLAGS */
volatile uint16_t Flag_Clocktick;
volatile uint16_t Flag_Keypolling;

/* PRIVATE */
static uint16_t counter_clockhms;
static uint16_t counter_keypolling;

int SEOS_Init(void)
{
	printf("\nINICIANDO OS...\n");
	
	Flag_Clocktick  = FLAG_LOWER;
	Flag_Keypolling = FLAG_LOWER;
	counter_clockhms = OVERF_CLOCKTICK - OOPH_CLOCKTICK;
	counter_keypolling = OVERF_KEYPOLLING - OOPH_CLOCKTICK;
	
	return 0;
}

int SEOS_Schedule(void)
{
	if(++counter_clockhms == OVERF_CLOCKTICK)
	{
		Flag_Clocktick   = FLAG_RAISE; 
		counter_clockhms = 0; 
	}
	if(++counter_keypolling == OVERF_KEYPOLLING)
	{
		Flag_Keypolling    = FLAG_RAISE;
		counter_keypolling = 0; 
	}
	return 0;
}

int SEOS_Dispatch(void)
{
	if(Flag_Keypolling)
	{
		//leer teclado
		Flag_Keypolling = FLAG_LOWER;
	}
	if(Flag_Clocktick)
	{
		Clockhms_Tick();
		Flag_Clocktick = FLAG_LOWER;
	}
	return 0;
}

int SEOS_Sleep(void)
{
	
	return 0;
}
