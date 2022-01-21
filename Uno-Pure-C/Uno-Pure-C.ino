#include <avr/io.h>
#include <util/delay.h>
 
#define BLINK_DELAY_MS 1000
#define PIN_SS 4

void spi_begin(void)
{
  DDRD |= _BV(DDD5) | _BV(DDD6);
  PORTD |= _BV(PORTD5); 
}

void spi_stop(void)
{
  PORTD &= ~_BV(PORTD5); 
}

void send_data(unsigned char _data)
{
  for (int i = 7 ; i >= 0 ; i--)
  {
    PORTD &= ~_BV(PORTD5);
    if ((_data >> i)&0x01) PORTD |= _BV(PORTD6);
    else PORTD &= ~_BV(PORTD6);
    PORTD |= _BV(PORTD5);
    _delay_us(10);
  }
  _delay_us(30);
}
 
int main (void)
{
 /* set pin 5 of PORTB for output*/
 DDRB |= _BV(DDB5);
 spi_begin();
 
 while(1) {
  
  PORTB &= ~_BV(PORTB5);
  send_data(0x56);
  send_data(0x76);
  send_data(0xFF);
  send_data(0x99);
  send_data(0x5A);
  PORTB |= _BV(PORTB5);
  _delay_ms(BLINK_DELAY_MS);
 }
}
