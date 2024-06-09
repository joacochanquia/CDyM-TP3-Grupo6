#include "i2c.h"
#include <avr/io.h>

void I2C_Init(){
    TWSR = 0X00;
    TWBR = 152;
    TWCR = 0X04;
}

void I2C_Start(){
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while((TWCR & (1<<TWINT)) == 0);
}

void I2C_Write(unsigned char data){
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);    
    while((TWCR & (1<<TWINT)) == 0);
}

unsigned char I2C_Read(unsigned char isLast){
    if(isLast == 0)
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    else
        TWCR = (1<<TWINT)|(1<<TWEN);
    while((TWCR & (1<<TWINT)) == 0);
    return TWDR; 
}

void I2C_Stop(){
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}