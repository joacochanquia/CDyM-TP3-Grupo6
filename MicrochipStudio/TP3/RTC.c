#include "RTC.h"

void RTC_Init(void)
{
		I2C_Init();                             // Inicializar el módulo I2C.
		I2C_Start();                            // Iniciar la comunicación I2C
		
		I2C_Write(C_Ds1307WriteMode_U8);        // Conectarse al DS1307 enviando su ID en el bus I2C
		I2C_Write(C_Ds1307ControlRegAddress_U8);// Seleccionar el registro de control del DS1307 para configurarlo
		
		I2C_Write(0x00);                        // Escribir 0x00 en el registro de control para desactivar SQW-Out
		
		I2C_Stop();                             // Detener la comunicación I2C después de inicializar el DS1307
	}

	void RTC_SetDateTime(rtc_t *rtc)
	{
		I2C_Start();                          // Iniciar la comunicación I2C
		
		I2C_Write(C_Ds1307WriteMode_U8);      // Conectarse al DS1307 enviando su ID en el bus I2C
		I2C_Write(C_Ds1307SecondRegAddress_U8); // Solicitar la dirección de memoria de los segundos en 00H
		
		I2C_Write(rtc->sec);                    // Escribir los segundos en la dirección de memoria 00H
		I2C_Write(rtc->min);                    // Escribir los minutos en la dirección de memoria 01H
		I2C_Write(rtc->hour);                    // Escribir la hora en la dirección de memoria 02H
		I2C_Write(rtc->weekDay);                // Escribir el día de la semana en la dirección de memoria 03H
		I2C_Write(rtc->date);                    // Escribir la fecha en la dirección de memoria 04H
		I2C_Write(rtc->month);                    // Escribir el mes en la dirección de memoria 05H
		I2C_Write(rtc->year);                    // Escribir el año en la dirección de memoria 06h
		
		I2C_Stop();                              // Detener la comunicación I2C después de configurar la fecha
	}

	void RTC_GetDateTime(rtc_t *rtc)
	{
		I2C_Start();                            // Iniciar la comunicación I2C
		
		I2C_Write(C_Ds1307WriteMode_U8);        // Conectarse al DS1307 enviando su ID en el bus I2C
		I2C_Write(C_Ds1307SecondRegAddress_U8); // Solicitar la dirección de memoria de los segundos en 00H
		
		I2C_Stop();                                // Detener la comunicación I2C después de seleccionar el registro de segundos
		
		I2C_Start();                            // Iniciar la comunicación I2C
		I2C_Write(C_Ds1307ReadMode_U8);            // Conectarse al DS1307 (modo de lectura) enviando su ID
		
		rtc->sec = I2C_Read(1);                // Leer los segundos y devolver ACK positivo
		rtc->min = I2C_Read(1);                 // Leer los minutos y devolver ACK positivo
		rtc->hour= I2C_Read(1);               // Leer la hora y devolver ACK negativo/no ACK
		rtc->weekDay = I2C_Read(1);           // Leer el día de la semana y devolver ACK positivo
		rtc->date= I2C_Read(1);              // Leer la fecha y devolver ACK positivo
		rtc->month=I2C_Read(1);            // Leer el mes y devolver ACK positivo
		rtc->year =I2C_Read(0);             // Leer el año y devolver ACK negativo/no ACK
		
		I2C_Stop();                              // Detener la comunicación I2C después de leer la fecha
}