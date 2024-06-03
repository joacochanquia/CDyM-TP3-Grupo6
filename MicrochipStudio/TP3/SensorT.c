#include "SensorT.h"


uint32_t GetDato(){
	int8_t i=0;
	uint32_t res=0;
	
	DDRC |= (1<<PINC0); // Se establece el PINC0 como salida
 	PORTC |= (1<<PINC0);// Se pone un valor 1
 	_delay_ms(5);
	PORTC &= ~(1<<PINC0);
	_delay_ms(20);      // Se pone un valor 0 por 20 ms
	PORTC |= (1<<PINC0);// Se pone un valor 1
	DDRC &= ~(1<<PINC0);// Se establece el PINC0 como entrada
	
	while (PINC & (1<<PINC0)){// Se espera el pull down del sensor
		
	}
	while (!(PINC & (1<<PINC0))){// Se espera el pull up del sensor
		
	}
	while (PINC & (1<<PINC0)){// Se espera el pull down del sensor
		
	}
	// Comienza la transmision
	
	for(i=0;i<32;i++){
		while (!(PINC & (1<<PINC0))){ // Tiempo de espera inicial a cada bit
			
		}
		_delay_us(30);
		res |= (PINC & (1<<PINC0));
		if(i!=31){
			res <<= 1;
		}
		while (PINC & (1<<PINC0));
//		CronoInit_us(); // Inicio un conteo para ver la duración de la señal
// 		while (PINC0){  // Espero la caida de la señal
// 			
// 		}
// 		if (CronoStop_us() > 40){
// 			res &= (1<<(31-i));
// 		}
		
	}
	
	return res;
}
