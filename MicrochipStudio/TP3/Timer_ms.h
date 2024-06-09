#ifndef TIMER_MS_H
#define TIMER_MS_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

ISR(IRQ_request);

// Inicializacion del timer
void TimerInit_ms(uint8_t flag_top);

// Tiempo desde que inicio el programa
uint32_t ActualTime_ms();

// Cronometro
void CronoInit_ms();
uint32_t CronoStop_ms();

// Temporizador
void TempoInit_ms(uint16_t cant);
uint16_t TempoCount_ms();

// Getters y Setters del FLAG
void SetFLAG_ms(uint8_t flag);
uint8_t GetFLAG_ms();

#endif