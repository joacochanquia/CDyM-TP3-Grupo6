#include "i2c.h"
#include <avr/io.h>

#include "serialPort.h"
#include "Timer_ms.h"

void I2C_Init(){
    TWSR = 0X00;
    TWBR = 255;
    TWCR = 0X44;
}

void I2C_Start(){
	/*CronoInit_ms();*/
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while((TWCR & (1<<TWINT)) == 0){
// 		if (CronoCount_ms() == 2000){
// 			SerialPort_Send_String("ERROR I2C START - ");
// 			return;
// 		}
	}
}

void I2C_Write(unsigned char data){
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    /*CronoInit_ms();*/ 
    while((TWCR & (1<<TWINT)) == 0){
// 		if (CronoCount_ms() == 2000){
// 			SerialPort_Send_String("ERROR I2C WRITE - ");
// 			return;
// 		}
	}
}

unsigned char I2C_Read(unsigned char isLast){
    if(isLast == 0)
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    else
        TWCR = (1<<TWINT)|(1<<TWEN);
    /*CronoInit_ms();*/
    while((TWCR & (1<<TWINT)) == 0){
// 		if (CronoCount_ms() == 2000){
// 			SerialPort_Send_String("ERROR I2C READ - ");
// 			return 0xFF;
// 		}
	}
    return TWDR; 
}

void I2C_Stop(){
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}