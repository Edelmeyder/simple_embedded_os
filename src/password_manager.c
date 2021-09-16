#include "password_manager.h"

typedef enum {
	CERRADO, ABRIENDO, ABIERTO, DENEGADO
} state;
typedef enum {
	PRIMERO, SEGUNDO, TERCERO, CUARTO
} state_a;

static state estado; //estado macro de la mef
static state_a estado_a; 
static uint8_t buffer_c[4];
static uint32_t tiempo = 0; //tiempo en estado, se usa para saber la primera vez que se entra a un estado y para algunas temporizaciones
uint8_t key;

uint8_t autenticar(void); //esta función compara la contraseña ingresada con la contraseña actual, retorna 1 si son iguales, 0 cc

void PASSWORD_MANAGER_init(void){
	estado = CERRADO;
}

void PASSWORD_MANAGER_Update(void){
	switch (estado) {
		case CERRADO:
			if (tiempo == 0) {
				LCD_goToXY(4, 1);
				LCD_sendString((uint8_t*) "CERRADO ", 8);
				//solo la primera vez en el estado escribe el display
				tiempo = 1;
			}
			if (Keyboard_Update(&key)) {
				//si se detecta un número se pasa a abriendo
				if (key >= '0' && key <= '9') {
					buffer_c[0] = key;
					estado = ABRIENDO;
					estado_a = PRIMERO;
				}
			}
			break;
		case ABRIENDO:
			switch (estado_a) {
				case PRIMERO:
					//el primer estado de abriendo solo bora el diplay y escribe un * ya que la tecla ya se guardó
					LCD_goToXY(4, 1);
					LCD_sendString((uint8_t*) "       ", 7);
					LCD_goToXY(6, 1);
					LCD_sendChar('*');
					estado_a = SEGUNDO;
					break;
				case SEGUNDO:
					//en los estados segundo y tercero se espera la tecla, se la guarda y se avanza
					if (Keyboard_Update(&key)) {
						buffer_c[1] = key;
						LCD_goToXY(7, 1);
						LCD_sendChar('*');
						estado_a = TERCERO;
					}
					break;
				case TERCERO:
					if (Keyboard_Update(&key)) {
						buffer_c[2] = key;
						LCD_goToXY(8, 1);
						LCD_sendChar('*');
						estado_a = CUARTO;
					}
					break;
				case CUARTO:
					if (Keyboard_Update(&key)) {
						buffer_c[3] = key;
						LCD_goToXY(9, 1);
						LCD_sendChar('*');
						//al recibir la cuarta tecla se autentica
						if (autenticar()) {
							estado = ABIERTO;
						} else {
							estado = DENEGADO;
						}
						tiempo = 0;
					}
					break;
			}
			break;
		case ABIERTO:
			if (tiempo++ == 0) {
				LCD_goToXY(4, 1);
				LCD_sendString((uint8_t*) "ABIERTO ", 8);
			}
			if (tiempo == 24) { //24 iteraciones en el estado son 3 segundos
				estado = CERRADO;
				tiempo = 0;
			}
			break;
		case DENEGADO:
			if (tiempo++ == 0) {
				LCD_goToXY(4, 1);
				LCD_sendString((uint8_t*) "DENEGADO", 8);
			}
			if (tiempo == 16) { //16 iteraciones en el estado son 2 segundos
				estado = CERRADO;
				tiempo = 0;
			}
			break;
	}
}

uint8_t autenticar(void) {
	for (uint8_t i = 0; i < 4; i++){
		if (PASS[i] != buffer_c[i]) return 0;
	}
	return 1;
}
