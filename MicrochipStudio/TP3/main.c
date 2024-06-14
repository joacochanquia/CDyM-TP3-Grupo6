// Inclusi�n de cabeceras de bibliotecas de c�digo
#include <avr/io.h> // Librer�a para control de entradas y salidas del microcontrolador AVR
#include <avr/interrupt.h> // Librer�a para el manejo de interrupciones en AVR
#define F_CPU 16000000UL // Definici�n de la frecuencia del CPU (16 MHz)
#include <util/delay.h> // Retardos por software � Macros: depende de F_CPU
#include <stdlib.h> // Librer�a est�ndar de C para funciones generales
#include <stdint.h>
#include <string.h>

// Archivos creados para este programa
#include "DHT.h"
#include "Timer_ms.h"
#include "RTC.h"
#include "serialPort.h"

#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz

char msg1[] = "Registro de temperatura y humedad medidas por fecha\r\n";

uint8_t active = 1;

int main(void)
{
	dht_data TyRH;
	rtc_t Time;
	
	TimerInit_ms(2000);
	
	SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();			// Activo el Transmisor del Puerto Serie
	SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
	SerialPort_Send_String(msg1);   // Envío el mensaje de Bienvenida
	SerialPort_RX_Interrupt_Enable();	// Activo Interrupción de recepcion.
	sei();
	
	RTC_Init();
	
	Time.hour = 14;
	Time.min = 15;
	Time.sec = 0;
	Time.date = 10;
	Time.month = 06;
	Time.year = 24;
	RTC_SetDateTime(&Time);
	
	while (1) 
	{
		if(GetFLAG_ms() && active){
			SetFLAG_ms(0);
			
			TyRH = GetTyRH();
			
			if (!(TyRH.T == 0xFF)){
				SerialPort_Send_String("TEMP: ");
				SerialPort_Send_uint8_t(TyRH.T);
				SerialPort_Send_String(" C HUM: ");
				SerialPort_Send_uint8_t(TyRH.RH);
				SerialPort_Send_String("% ");
			}else{
				SerialPort_Send_String("Problema en modulo DHT (");
				SerialPort_Send_uint8_t(TyRH.RH);
				SerialPort_Send_String(")\r\n");
			}
			RTC_GetDateTime(&Time);
			SerialPort_Send_String("FECHA: ");
			SerialPort_Send_uint8_t(Time.date);
			SerialPort_Send_String("/");
			SerialPort_Send_uint8_t(Time.month);
			SerialPort_Send_String("/");
			SerialPort_Send_uint8_t(Time.year);
			SerialPort_Send_String(" HORA: ");
			SerialPort_Send_uint8_t(Time.hour);
			SerialPort_Send_String(":");
			SerialPort_Send_uint8_t(Time.min);
			SerialPort_Send_String(":");
			SerialPort_Send_uint8_t(Time.sec);
			SerialPort_Send_String("\n\r");
		}
	}

}

// Rutina de Servicio de Interrupción de Byte Recibido
ISR(USART_RX_vect){
	char RX_Buffer = UDR0; //la lectura del UDR borra flag RXC
	// Si se presiona 's' se alterna la transmision de datos
	if((RX_Buffer == 's')||(RX_Buffer == 'S')){
		active ^= 1;
	}
	RX_Buffer=0;
}