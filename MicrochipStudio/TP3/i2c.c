#include "i2c.h"
#include <avr/io.h>

void I2C_Init(){
    TWSR = 0X00; // Establece los bits del prescaler en 0
    TWBR = 255; // Establece la frecuencia de SCL
    TWCR = 0X44; // Habilita el modulo TWI
}

void I2C_Start(){
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // Inicia la condición de start
    while((TWCR & (1<<TWINT)) == 0); // Espera hasta que se complete la condición de start
}

void I2C_Write(unsigned char data){
    TWDR = data; // Carga el dato a enviar en el registro de datos
    TWCR = (1<<TWINT)|(1<<TWEN); // Inicia la transferencia de datos
    while((TWCR & (1<<TWINT)) == 0); // Espera hasta que se complete la transferencia
}

unsigned char I2C_Read(unsigned char isLast){
    if(isLast == 0)
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA); // Acknowledge después de la lectura
    else
        TWCR = (1<<TWINT)|(1<<TWEN); // No Acknowledge después de la lectura
    while((TWCR & (1<<TWINT)) == 0); // Espera hasta que se complete la lectura
    return TWDR; // Retorna el dato leído
}

void I2C_Stop(){
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN); // Genera la condición de stop
}