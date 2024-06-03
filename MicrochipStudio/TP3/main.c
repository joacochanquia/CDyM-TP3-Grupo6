// Inclusión de cabeceras de bibliotecas de código
#include <avr/io.h> // Librería para control de entradas y salidas del microcontrolador AVR
#include <avr/interrupt.h> // Librería para el manejo de interrupciones en AVR
#define F_CPU 16000000UL // Definición de la frecuencia del CPU (16 MHz)
#include <util/delay.h> // Retardos por software – Macros: depende de F_CPU
#include "lcd.h" // Librería para el control del LCD
#include <stdlib.h> // Librería estándar de C para funciones generales
#include <stdint.h>

// Archivos creados para este programa
#include "SensorT.h"

int main(void)
{
	LCD_Init();
	
    uint32_t TyRH;
	uint8_t T, RH, i;
    while (1) 
    {
		TyRH = GetDato();
		//TyRH = 0b00110011100101100111111010000001;
		
		T = (TyRH >> 8) & 0xFF;
		RH = (TyRH >> 24) & 0xFF;
		
//  	  	LCDclr();
//   		LCDGotoXY(0,0);
// 		for (i=32;i>16;i--){
// 			LCDescribeDato((TyRH>>(i-1))&1,1);
// 		}
// 		LCDGotoXY(0,1);
// 		for (i=16;i>0;i--){
// 			LCDescribeDato((TyRH>>(i-1))&1,1);
// 		}
		
		LCDclr();
		LCDGotoXY(0,0);
 		LCDstring("TEMP: ",6);
 		LCDescribeDato(T,3);
 		LCDstring(" C",2);
 		LCDGotoXY(0,1);
 		LCDstring("HUM: ",5);
 		LCDescribeDato(RH,3);
 		LCDstring("%",1);
		
		_delay_ms(1000);
    }

}

