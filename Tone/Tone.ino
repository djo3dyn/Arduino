#include <avr/io.h>

void adc_setup (void)
{
    // Set the ADC input to PB2/ADC1
    ADMUX |= (1 << MUX0);
    ADMUX |= (1 << ADLAR);

    // Set the prescaler to clock/128 & enable ADC
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
}

int adc_read (void)
{
    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for it to finish
    while (ADCSRA & (1 << ADSC));

    return ADCH;
}

int
main(void)
{

  // Setup Timer
  DDRB = 0b00000001; // set LED pin as OUTPUT
  PORTB = 0b00000000; // set all pins to LOW
  
  TCCR0B |= _BV(CS01); // set prescaler to 8
  TCCR0A |= _BV(WGM01); // set timer mode to CTC
  TCCR0A |= _BV(COM0A0); // connect PWM pin to Channel A of Timer0
  
  //setup ADC
  int adc_in;
  adc_setup();

  /* loop */
  while (1){
    adc_in = adc_read();
    OCR0A = adc_in;
  }
}
