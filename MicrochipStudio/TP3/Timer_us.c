#include "Timer_us.h"

static uint8_t FLAG_F=0, FLAG_COUNTING=0;
static uint8_t cuentaF=0, flag_top=0;
static uint16_t cuentaT=0;
static uint32_t cuentaC=0, init_count=0;

ISR(TIMER0_COMPA_vect) { // Rutina de servicio a interrupcion
	init_count++; // Se incrementa el tiempo global
	cuentaF++; //Se incrementa el contador para el flag F
	if (cuentaF == flag_top){ // Si se llego al limite para el flag F
		FLAG_F = 1; // Se indica que ya se llego al limite
		cuentaF = 0; // Se reinicia la cuenta para el flag F
	}
	if (FLAG_COUNTING){ // Si se esta contando
		cuentaC++; // Se aumenta el cronometro
	}
	if (cuentaT){ // Si todavia no termino el temporizador
		cuentaT--; // Se decrementa el contador
	}
}

// Inicializacion del timer
void TimerInit_us(uint8_t top){
	cli();
	
	//Se inicializa el tiempo de cuenta global
	init_count = 0;
	
	//Se establece el tiempo para el flag
	flag_top = top;
	
	// Modo CTC TOP: OCRA
	TCCR0A |= (1<<WGM01);
	TCCR0A &= ~(1<<WGM00);
	TCCR0B &= ~(1<<WGM02);
	
	// Prescaler clk/8
	TCCR0B |= (1<<CS01);
	TCCR0B &= (~(1<<CS02))&(~(1<<CS00));
	
	// Comparador en el valor para la cuenta cada 1 us
	OCR0A = 2;
	
	// Se habilita la interrupcion COMP A
	TIMSK0 |= (1<<OCIE0A);
	
	sei();
}
// Tiempo desde que inicio el programa
uint32_t ActualTime_us(){
	return init_count;
}

// Cronometro
void CronoInit_us(){ 
	cuentaC = 0; // Se reinicia el contador
	FLAG_COUNTING = 1; // Se indica que se esta contando
}
uint32_t CronoStop_us(){
	FLAG_COUNTING = 0; // Se indica que no se debe contar más
	return cuentaC; // Se devuelve el tiempo transcurrido
}

// Temporizador
void TempoInit_us(uint16_t cant){
	cuentaT = cant; // Se inicializa el temporizador
}
uint16_t TempoCount_us(){
	return cuentaT; // Se devuelve el tiempo restante
}

// Getters y Setters del FLAG_F
void SetFLAG_us(uint8_t flag){
	FLAG_F = flag;
}
uint8_t GetFLAG_us(){
	return FLAG_F;
}
