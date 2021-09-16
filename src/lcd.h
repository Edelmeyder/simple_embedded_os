#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define LCDPORT GPIOA //puerto al que se conecta el lcd
#define LCDIOCLK RCC_APB2ENR_IOPAEN

#define LCD_D0	0	//pin conectado a LCD D0
#define LCD_D1	1	//pin conectado a LCD D1
#define LCD_D2	2	//pin conectado a LCD D2
#define LCD_D3	3	//pin conectado a LCD D3
#define LCD_D4	4	//pin conectado a LCD D4
#define LCD_D5	5	//pin conectado a LCD D5
#define LCD_D6	6	//pin conectado a LCD D6
#define LCD_D7	7	//pin conectado a LCD D7
#define LCD_RW	8 //pin conectado a LCD R/W
#define LCD_RS	9 //pin conectado a LCD RS
#define LCD_E	10	//pin conectado a LCD E

void LCD_init(void);
void LCD_sendCommand(uint8_t);
void LCD_goToXY(uint8_t, uint8_t);
void LCD_sendChar(uint8_t);
void LCD_sendString(uint8_t*, uint8_t);
void LCD_clear(void);

#endif