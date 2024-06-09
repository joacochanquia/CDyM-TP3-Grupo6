// Inclusi�n de cabeceras de bibliotecas de c�digo
#include <avr/io.h> // Librer�a para control de entradas y salidas del microcontrolador AVR
#include <avr/interrupt.h> // Librer�a para el manejo de interrupciones en AVR
#define F_CPU 16000000UL // Definici�n de la frecuencia del CPU (16 MHz)
#include <util/delay.h> // Retardos por software � Macros: depende de F_CPU
#include "lcd.h" // Librer�a para el control del LCD
#include <stdlib.h> // Librer�a est�ndar de C para funciones generales
#include <stdint.h>

// Archivos creados para este programa
#include "DHT.h"
#include "Timer_ms.h"
#include "RTC.h"
#include "serialPort.h"

int main(void)
{
	LCD_Init();
	
    uint32_t TyRH;
	dht_data A;
    while (1) 
    {
		while(!GetFlag_ms()){
			SetFlag_ms(0);

			A = GetTyRH();
			
			
		}
		
		
		
		
// LCDclr();
// LCDGotoXY(0,0);
// LCDstring("TEMP: ",6);
// LCDescribeDato(T,3);
// LCDstring(" C",2);
// LCDGotoXY(0,1);
// LCDstring("HUM: ",5);
// LCDescribeDato(RH,3);
// LCDstring("%",1);
		
		_delay_ms(1000);
    }

}

