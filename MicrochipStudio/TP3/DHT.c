#include "DHT.h"


dht_data GetTyRH(){
	int8_t i=0;
	uint32_t res=0;
	dht_data A;
	
	// Mensaje del programa
	DDRC |= (1<<PINC0); // Se establece el PINC0 como salida
 	PORTC |= (1<<PINC0);// Se pone un valor 1
 	_delay_ms(2);
	PORTC &= ~(1<<PINC0);
	_delay_ms(20);      // Se pone un valor 0 por 20 ms
	PORTC |= (1<<PINC0);// Se pone un valor 1
	DDRC &= ~(1<<PINC0);// Se establece el PINC0 como entrada
	
	// Respuesta del sensor
	TempoInit_ms(2000);
	while (PINC & (1<<PINC0)){// Se espera el pull down del sensor
		if (!TempoCount_ms()){
			A.T = 0xFF;
			A.RH = 1;
			return A; // Si pasaron 2 segundos se devuelve un codigo de error
		}
	}
	while (!(PINC & (1<<PINC0))){// Se espera el pull up del sensor
		if (!TempoCount_ms()){
			A.T = 0xFF;
			A.RH = 2;
			return A; // Si pasaron 2 segundos se devuelve un codigo de error
		}
	}
	while (PINC & (1<<PINC0)){// Se espera el pull down del sensor
		if (!TempoCount_ms()){
			A.T = 0xFF;
			A.RH = 3;
			return A; // Si pasaron 2 segundos se devuelve un codigo de error
		}
	}
	
	// Comienza la transmision
	for(i=0;i<32;i++){
		while (!(PINC & (1<<PINC0))){ // Tiempo de espera inicial a cada bit
			if (!TempoCount_ms()){
				A.T = 0xFF;
				A.RH = 4;
				return A; // Si pasaron 2 segundos se devuelve un codigo de error
			}
		}
		_delay_us(30); // Se esperan 30 us
		res |= (PINC & (1<<PINC0)); // se guarda el bit recibido al final de la respuesta
		if(i!=31){ // El ultimo bit recibido no necesita un corrimiento
			res <<= 1; // se realiza un corrimiento de bits
		}
		while (PINC & (1<<PINC0)){ // Se espera a que haya un 0 en PINC0
			if (!TempoCount_ms()){
				A.T = 0xFF;
				A.RH = 5;
				return A; // Si pasaron 2 segundos se devuelve un codigo de error
			}
		}
		
	}
	
			
	A.T = (res >> 8) & 0xFF; // Se guarda el valor de la temperatura de la respuesta leida
	A.RH = (res >> 24) & 0xFF; // Se guarda el valor de la humedad de la respuesta leida

	return A;
}
