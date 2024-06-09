#ifndef DHT_H
#define DHT_H

typedef	struct {
	uint8_t T;
	uint8_t RH;
} dht_data;

#include <avr/io.h>
#include <stdint.h>
#define F_CPU 16000000UL // Especifico la frecuencia de reloj del MCU en 16MHz
#include <util/delay.h> // Retardos por software � Macros: depende de F_CPU
#include "Timer_ms.h"

dht_data GetTyRH();

#endif