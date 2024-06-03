#ifndef SENSOR_T_H
#define SENSOR_T_H

#include <avr/io.h>
#include <stdint.h>
#define F_CPU 16000000UL // Especifico la frecuencia de reloj del MCU en 16MHz
#include <util/delay.h> // Retardos por software – Macros: depende de F_CPU
#include "Timer_us.h"

uint32_t GetDato();

#endif