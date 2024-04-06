//******************************************************************************
// Universidad Del Valle De Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Héctor Alejandro Martínez Guerra - 22369 
// Proyecto: Prelab 4
// Hardware: Atmega238p
//******************************************************************************

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int conteo = 0;

void initADC(void);


int main(void)
{
	DDRB = 0b00011100;	//PB0, PB1 como entrada
	PORTB = 0b00000011;	//Pull Up PB0 y PB1
	
	cli();
	DDRD |= 0xFF
	PORTD = 0;
	UCSR0B = 0;
	initADC();
	sei(); 
	
    while(1)
    {
	ADCSRA |= (1<<ADSC);
	_delay_ms(200);
		
    }
}

void initADC(void){
	ADMUX = 0;
	//referencia AVCC = 5V
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	//Justificación a la izquierda
	ADMUX |= (1<<ADLAR);
	ADCSRA = 0;

	//Habilitando la interrupción del ADC
	ADCSRA |= (1<<ADIE);
	
	//Habilitar prescaler de 16M7128 Fadc = 125kHz
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	// Habilitando el ADC 
	ADCSRA |= (1<<ADEN);	
		
}

ISR(ADC_vect){
	PORTD = ADCH;
	ADCSRA |= (1<<ADIF);
	
}


ISR(PCINT0_vect){
	
	
	if(((PINB) & (1<<0)) == 0){
		conteo ++;
		if(conteo >= 255){
			conteo = 255;
		}
		PORTD = conteo;
	}
	
	if(((PINB) & (1<<1)) == 0){
		conteo --;
		if(conteo <= 0){
			conteo = 0;
		}
		PORTD = conteo;
	}
	
	
	
}
