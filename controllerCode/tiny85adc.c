/*
 * tiny85adc.c
 *
 * Created: 10/28/2014 11:31:07 PM
 *  Author: psaux0
 */ 


#include <avr/io.h>

int main(void)
{
	int adc_value = 0;
	int temp = 0;
	DDRB = (1<<PB0);
	
	ADCSRA = (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //Set Clock
	ADMUX = (0<<REFS1) | (0 << REFS0) | (0<<MUX1) | (1<<MUX0); //Set Reference Voltage and AC negative input
	//ADCSRB = (0<<ADTS2) | (0<<ADTS1) | (0<ADTS0) set Free running mode
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (0<<ADSC);
	
	
    while(1)
    {
        //TODO:: Please write your application code
		ADCSRA |= (1<<ADSC);
		temp = ADCL; //When ADCL is read, the ADC Data Register is not updated until ADCH is read. ADCL and ADCH cannot be read together
		adc_value = (ADCH << 0x8) | temp; //10bit
		if(adc_value > 512)
		{
			PORTB = 1 << PB0;
		}
		else
		{
			PORTB &= ~(1 << PB0); 
		}
    }
}