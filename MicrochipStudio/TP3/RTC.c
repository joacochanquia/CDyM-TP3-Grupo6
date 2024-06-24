#include "RTC.h"

#include "Timer_ms.h"

void RTC_Init(){
	I2C_Init(); // Inicializar el módulo I2C.
}

void RTC_SetDateTime(rtc_data *data){
	Timer_Stop(); // Detener la interrupcion del timer para evitar errores en la escritura de la fecha
	I2C_Start(); // Iniciar la comunicación I2C

	I2C_Write(DS3231WriteMode); // Conectarse al DS3231 enviando su ID en el bus I2C en modo escritura
	I2C_Write(DS3231SecReg);    // Solicitar la dirección de memoria de los segundos en 00H
		
	// Se debe convertir el dato a DCB antes de ser enviado
	I2C_Write(((data->sec / 10) << 4) + (data->sec % 10)); // Escribir los segundos en la dirección de memoria 00H
	I2C_Write(((data->min / 10) << 4) + (data->min % 10)); // Escribir los minutos en la dirección de memoria 01H
	I2C_Write(((data->hour / 10) << 4) + (data->hour % 10)); // Escribir la hora en la dirección de memoria 02H
	I2C_Write(0);                							// Escribir el día de la semana en la dirección de memoria 03H
	I2C_Write(((data->date / 10) << 4) + (data->date % 10)); // Escribir la fecha en la dirección de memoria 04H
	I2C_Write(((data->month / 10) << 4) + (data->month % 10)); // Escribir el mes en la dirección de memoria 05H
	I2C_Write(((data->year / 10) << 4) + (data->year % 10)); // Escribir el año en la dirección de memoria 06h
		
	I2C_Stop(); // Detener la comunicación I2C después de configurar la fecha
	Timer_Start(); // Habilitar la interrupcion del timer  después de configurar la fecha
}

void RTC_GetDateTime(rtc_data *data){
	Timer_Stop(); // Detener la interrupcion del timer para evitar errores en la lectura de la fecha
	I2C_Start(); // Iniciar la comunicación I2C
		
	I2C_Write(DS3231WriteMode); // Conectarse al DS3231 enviando su ID en el bus I2C en modo escritura
	I2C_Write(DS3231SecReg); // Solicitar la dirección de memoria de los segundos en 00H
		
	I2C_Stop(); // Detener la comunicación I2C después de seleccionar el registro de segundos
		
	I2C_Start(); // Iniciar la comunicación I2C
	I2C_Write(DS3231ReadMode); // Conectarse al DS3231 enviando su ID en modo lectura
		
	data->sec = I2C_Read(0); // Leer los segundos
	data->min = I2C_Read(0); // Leer los minutos
	data->hour = I2C_Read(0); // Leer la hora
	data->weekDay = I2C_Read(0); // Leer el día de la semana
	data->date = I2C_Read(0); // Leer la fecha
	data->month = I2C_Read(0); // Leer el mes
	data->year = I2C_Read(1); // Leer el año y enviar un 1 ya que es el ultimo byte a leer
		
	//Conversiones de DCB a binario
 	data->sec = ((((data->sec) & 0x70) >> 4) * 10) + ((data->sec) & 0x0F);
 	data->min = ((((data->min) & 0x70) >> 4) * 10) + ((data->min) & 0x0F);
 	data->hour = ((((data->hour) & 0x30) >> 4) * 10) + ((data->hour) & 0x0F);
 	data->date = ((((data->date) & 0x30) >> 4) * 10) + ((data->date) & 0x0F);
 	data->month = ((((data->month) & 0x10) >> 4) * 10) + ((data->month) & 0x0F);
 	data->year = ((((data->year) & 0xF0) >> 4) * 10) + ((data->year) & 0x0F);

		
	I2C_Stop(); // Detener la comunicación I2C después de leer la fecha
	Timer_Start(); // Habilitar la interrupcion del timer después de leer la fecha
}