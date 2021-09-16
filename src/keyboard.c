#include "keyboard.h"

char Keyboard_Scan(void);

volatile uint8_t dato;

void delay_app(uint16_t time){
   uint16_t i;
   volatile unsigned long l = 0;
   for (i=0; i<time ; i++)
      for(l=0; l<730; l++);
}

int Keyboard_Init(void)
{	
	GPIOB->CRL = 0x88883333; // PUERTO B primeros 4 bits como salida, los 4 bits siguientes como entrada
	GPIOB->ODR = 0xFF; // 
	
	return 0;
}
char Keyboard_Scan(void)
	{  
    GPIOB->ODR = ~(1<<0);
    delay_app(1);
    dato=GPIOB->IDR;
    if(!(dato&0x0010))
       return '7';
    if(!(dato&0x0020))
       return '8';
    if(!(dato&0x0040))
       return '9';
    if(!(dato&0x0080))
       return '%';
    
    GPIOB->ODR = ~(1<<1);
    delay_app(1);
    dato = GPIOB->IDR;
    if(!(dato&0x0010))
       return '4';
    if(!(dato&0x0020))
       return '5';
    if(!(dato&0x0040))
       return '6';
    if(!(dato&0x0080))
       return '*';
    
    GPIOB->ODR = ~(1<<2);
    delay_app(1);
    dato=GPIOB->IDR;
    if(!(dato&0x0010))
       return '1';
    if(!(dato&0x0020))
       return '2';
    if(!(dato&0x0040))
       return '3';
    if(!(dato&0x0080))
       return '-';
    
    GPIOB->ODR = ~(1<<3);
    delay_app(1);
    dato=GPIOB->IDR;
    if(!(dato&0x0010))
       return 'x';
    if(!(dato&0x0020))
       return '0';
    if(!(dato&0x0040))
       return '=';
    if(!(dato&0x0080))
       return '+';
    
    return 0xFF;
    }
    
char Keyboard_Update(char *pkey) 
{
 static char Old_key;
 static char Last_valid_key=0xFF;
 char Key;        
 
 Key = Keyboard_Scan();

 if(Key==0xFF) {   //NO_DATA
 	Old_key=0xFF;
	Last_valid_key=0xFF;
	return 0;
	}
 if(Key==Old_key) { //2da verificacin
 	if(Key!=Last_valid_key){ //evita mltiple deteccin
		*pkey=Key;
		Last_valid_key=Key;
		return 1;
	}
 }
 Old_key=Key; //1era verificacin
 return 0;
}