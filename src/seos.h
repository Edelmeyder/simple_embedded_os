#ifndef _SEOS_H
#define _SEOS_H

#include <stm32f10x.h>
#include <inttypes.h>
#include <stdio.h>

#include "clockhms.h"

#define FLAG_RAISE 1
#define FLAG_LOWER 0

/* Overflow */
/* nro de tick del sistema en el que se debe ejecutar la tarea y reiniciar el contador */
#define OVERF_CLOCKTICK 1000  //  1s
#define OVERF_KEYPOLLING 10  // 100 ms

/* Out of Phase */
/* Configuracion para evitar que las tareas se deban ejecutar en el mismo tick del sistema */
#define OOPH_CLOCKTICK 1
#define OOPH_CLOCKTICK 1 

/* Public Functions */
int SEOS_Init(void);

int SEOS_Schedule(void);

int SEOS_Dispatch(void);

int SEOS_Sleep(void);

#endif


