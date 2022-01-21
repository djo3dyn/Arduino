#include <avr/io.h>
#include <util/delay.h>
 
#define DELAY_MS 2000

#define MOSI 0
#define SCK 2
#define MISO 1
#define SS 3

void send_data(unsigned char _data)
{
  for (int i = 0 ; i < 8 ; i++)
  {
    PORTB &= ~_BV(SCK);
    ((_data & 0x80) ? PORTB |= _BV(MOSI) : PORTB &= ~_BV(MOSI));
    _data <<= 1 ;
    PORTB |= _BV(SCK);
  }
}
 
int main (void)
{
 /* set pin 5 of PORTB for output*/
 DDRB |= _BV(MOSI) | _BV(SCK) | _BV(SS);
 PORTB |= _BV(SS);
 _delay_ms(DELAY_MS);
 while(1) {
  
  PORTB &= ~_BV(SS);
  send_data(0x56);
  send_data(0x76);
  send_data(0xFF);
  send_data(0x99);
  send_data(0x5A);
  PORTB |= _BV(SS);
  _delay_ms(DELAY_MS);
 }
}
