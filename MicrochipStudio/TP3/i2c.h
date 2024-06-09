#ifndef I2C_H
#define I2C_H

void I2C_Init();

void I2C_Start();

void I2C_Write(unsigned char);

unsigned char I2C_Read(unsigned char isLast);

void I2C_Stop();

#endif