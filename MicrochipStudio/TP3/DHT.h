#ifndef DHT_H
#define DHT_H

#include <avr/io.h>
#include <stdint.h>
#define F_CPU 16000000UL // Especifico la frecuencia de reloj del MCU en 16MHz
#include <util/delay.h> // Retardos por software � Macros: depende de F_CPU
#include "Timer_ms.h"

typedef	struct {
	uint8_t T;
	uint8_t RH;
} dht_data;


dht_data GetTyRH();

#endif