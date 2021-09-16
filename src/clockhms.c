#include "clockhms.h"

static int16_t hours = 19;
static int16_t minutes = 10;
static int16_t seconds = 22;

static int8_t tempValue[] = {0, 0}; // valor que se va almacenando cuando se quiere cambiar la hora
static int8_t index = 0;            // posición en tempValue donde se está escribiendo

static int8_t digits[] = {1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0, 0, 0}; 

/*
	Guarda la hora con lo que se cargó hasta el momento
*/
void Clockhms_Set_Hours(void)
{
    hours = tempValue[0] * 10 + tempValue[1];
}

/*
	Guarda los minutos con lo que se cargó hasta el momento
*/
void Clockhms_Set_Minutes(void)
{
    minutes = tempValue[0] * 10 + tempValue[1];
}

/*
	Guarda los segundos con lo que se cargó hasta el momento
*/
void Clockhms_Set_Seconds(void)
{
    seconds = tempValue[0] * 10 + tempValue[1];
}

/*
	Devuelve la hora actual
*/
int16_t Clockhms_Get_Hours(void)
{
    return hours;
}

/*
	Devuelve los minutos actuales
*/
int16_t Clockhms_Get_Minutes(void)
{
    return minutes;
}

/*
	Devuelve los segundos actuales
*/
int16_t Clockhms_Get_Seconds(void)
{
    return seconds;
}

/*
	Indica al Clock que se tiene que incrementar en 1s
*/
void Clockhms_Tick(void)
{
    int16_t secondOverflow = (seconds == 59);
    int16_t minuteOverflow = (minutes == 59);

    seconds = (seconds + 1) % 60;
    minutes = (minutes + secondOverflow) % 60;
    hours = (hours + minuteOverflow) % 24;
	
		printf("\n%d : %d : %d", hours, minutes, seconds);
		LCD_goToXY(OFFSET_X, OFFSET_Y);
		LCD_sendString((uint8_t *)"holamundo",9);
}

/*
    Devuelve si se termino de ingresar la hora o no
*/
int8_t Clockhms_End(void)
{
    return index == 2;
}

/*
    Limpia todas las variables internas devolviendo al reloj a un estado por defecto
*/
void Clockhms_Clean(void)
{
    tempValue[0] = 0;
    tempValue[1] = 0;
    index = 0;
}

/*
  Almacena temporalmente el dígito que se envía.
	Devuelve 1 si el valor ingresado es correcto
*/
uint8_t Clockhms_SendHour(int16_t key)
{
	int8_t digit = digits[key];
	if ((index == 0 && digit < 3) || (index == 1 && (tempValue[0] < 2 || (tempValue[0] == 2 && digit < 4)))) { // Hora de 0-23
		tempValue[index++] = digit;
		
		return 1;
	}
	return 0;
}

/*
    Almacena temporalmente el dígito que se envía.
	Devuelve 1 si el valor ingresado es correcto
*/
uint8_t Clockhms_SendMinutesOrSeconds(int16_t key)
{
	int8_t digit = digits[key];
	if ((index == 0 && digit < 6) || index == 1) { // Minutos y Segundos de 0-59
		tempValue[index++] = digit;
		
		return 1;
	}
	return 0;
}