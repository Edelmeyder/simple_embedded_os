#ifndef CLOCKHMS_H_
#define CLOCKHMS_H_

#include <inttypes.h>
#include <stdio.h>

/*
	hours - Valor de la hora a establecer
*/
void Clockhms_Set_Hours(void);

/*
	minutes - Valor de los minutos a establecer
*/
void Clockhms_Set_Minutes(void);

/*
	seconds - Valor de la seconds a establecer
*/
void Clockhms_Set_Seconds(void);

/*
	Devuelve la hora actual
*/
int16_t Clockhms_Get_Hours(void);

/*
	Devuelve los minutos actuales
*/
int16_t Clockhms_Get_Minutes(void);

/*
	Devuelve los segundos actuales
*/
int16_t Clockhms_Get_Seconds(void);

/*
	Indica al Clock que se tiene que incrementar en 1s
*/
void Clockhms_Tick(void);

/*
    Devuelve si se termino de ingresar la hora o no
*/
int8_t Clockhms_End(void);

/*
    Limpia todas las variables internas devolviendo al reloj a un estado por defecto
*/
void Clockhms_Clean(void);

/*
    Almacena temporalmente el dígito que se envía
*/
uint8_t Clockhms_SendHour(int16_t digit);

/*
    Almacena temporalmente el dígito que se envía
*/
uint8_t Clockhms_SendMinutesOrSeconds(int16_t digit);

#endif /* CLOCK_H_ */