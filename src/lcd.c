#include "lcd.h"


// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40

void delay_us(uint16_t);

void LCD_init(void) {
	// esperar 15ms luego de encendar para inicializar el lcd
	delay_us(15000);
	// activa el clock del puerto del lcd
	RCC->APB2ENR |= LCDIOCLK;
	// establece todos los pines del lcd como salida
	LCDPORT->ODR &= ~(1<<LCD_D0 | 1<<LCD_D1 | 1<<LCD_D2 | 1<<LCD_D3 | 1<<LCD_D4 | 1<<LCD_D5 | 1<<LCD_D6 | 1<<LCD_D7 | 1<<LCD_RW | 1<<LCD_RS | 1<<LCD_E);
	LCDPORT->CRL |= 3<<LCD_D0*4 | 3<<LCD_D1*4 | 3<<LCD_D2*4 | 3<<LCD_D3*4 | 3<<LCD_D4*4 | 3<<LCD_D5*4 | 3<<LCD_D6*4 | 3<<LCD_D7*4;
	LCDPORT->CRL &= ~(12<<LCD_D0*4 | 12<<LCD_D1*4 | 12<<LCD_D2*4 | 12<<LCD_D3*4 | 12<<LCD_D4*4 | 12<<LCD_D5*4 | 12<<LCD_D6*4 | 12<<LCD_D7*4);
	LCDPORT->CRH |= 3<<(LCD_RW-8)*4 | 3<<(LCD_RS-8)*4 | 3<<(LCD_E-8)*4;
	LCDPORT->CRH &= ~(12<<(LCD_RW-8)*4 | 12<<(LCD_RS-8)*4 | 12<<(LCD_E-8)*4);
	delay_us(4200);
	LCD_sendCommand(0x38);
	LCD_sendCommand(0x0E);
	LCD_sendCommand(0x01);
	delay_us(2000);
	LCD_sendCommand(0x06);
}

void LCD_sendCommand(uint8_t cmd){
	LCDPORT->ODR &= ~(1<<LCD_RS);
	LCDPORT->ODR |= cmd;
	LCDPORT->ODR &= (0xFFFF&(0xFF00|cmd));
	LCDPORT->ODR |= 1<<LCD_E;
	delay_us(2);
	LCDPORT->ODR &= ~(1<<LCD_E);
	if ((cmd == 1) | (cmd == 2) | (cmd == 3))
		delay_us(2000);
	else
		delay_us(100);
}

void LCD_sendChar(uint8_t c){
	LCDPORT->ODR |= 1<<LCD_RS;
	LCDPORT->ODR |= c;
	LCDPORT->ODR &= (0xFFFF&(0xFF00|c));
	LCDPORT->ODR |= 1<<LCD_E;
	delay_us(2);
	LCDPORT->ODR &= ~(1<<LCD_E | 1<<LCD_RS);
	delay_us(100);
}

void LCD_sendString(uint8_t* string, uint8_t length){
	for (uint8_t i = 0; i < length; i++) {
		LCD_sendChar(string[i]);
	}
}

void LCD_goToXY(uint8_t x, uint8_t y) {
	register uint8_t DDRAMAddr;
	// remap lines into proper order
	switch(y) {
		case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
		case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
		default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
	}
	// set data address
	LCD_sendCommand(1<<7 | DDRAMAddr);
}

void delay_us(uint16_t t) {
	uint16_t l;
	for(uint16_t i = 0; i < t; i++)
		for(l = 0; l < 10; l++){}
}