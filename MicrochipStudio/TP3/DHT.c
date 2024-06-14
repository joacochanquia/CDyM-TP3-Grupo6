#include "DHT.h"


dht_data GetTyRH(){
	int8_t i=0;
	uint32_t res=0;
	dht_data A;
	
	DDRC |= (1<<PINC0); // Se establece el PINC0 como salida
 	PORTC |= (1<<PINC0);// Se pone un valor 1
 	_delay_ms(5);
	PORTC &= ~(1<<PINC0);
	_delay_ms(20);      // Se pone un valor 0 por 20 ms
	PORTC |= (1<<PINC0);// Se pone un valor 1
	DDRC &= ~(1<<PINC0);// Se establece el PINC0 como entrada
	
	TempoInit_ms(2000);
	while (PINC & (1<<PINC0)){// Se espera el pull down del sensor
		if (!TempoCount_ms()){
			A.T = 0xFF;
			A.RH = 1;
			return A;
		}
	}
	while (!(PINC & (1<<PINC0))){// Se espera el pull up del sensor
		if (!TempoCount_ms()){
			A.T = 0xFF;
			A.RH = 2;
			return A;
		}
	}
	while (PINC & (1<<PINC0)){// Se espera el pull down del sensor
		if (!TempoCount_ms()){
			A.T = 0xFF;
			A.RH = 3;
			return A;
		}
	}
	// Comienza la transmision
	
	for(i=0;i<32;i++){
		while (!(PINC & (1<<PINC0))){ // Tiempo de espera inicial a cada bit
			if (!TempoCount_ms()){
				A.T = 0xFF;
				A.RH = 4;
				return A;
			}
		}
		_delay_us(30);
		res |= (PINC & (1<<PINC0));
		if(i!=31){
			res <<= 1;
		}
		while (PINC & (1<<PINC0)){
			if (!TempoCount_ms()){
				A.T = 0xFF;
				A.RH = 5;
				return A;
			}
		}
		
	}
	
			
	A.T = (res >> 8) & 0xFF;
	A.RH = (res >> 24) & 0xFF;

	return A;
}
