#ifndef TIMER_US_H
#define TIMER_US_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

ISR(IRQ_request);

// Inicializacion del timer
void TimerInit_us(uint8_t flag_top);

// Tiempo desde que inicio el programa
uint32_t ActualTime_us();

// Cronometro
void CronoInit_us();
uint32_t CronoStop_us();

// Temporizador
void TempoInit_us(uint16_t cant);
uint16_t TempoCount_us();

// Getters y Setters del FLAG
void SetFLAG_us(uint8_t flag);
uint8_t GetFLAG_us();

#endif