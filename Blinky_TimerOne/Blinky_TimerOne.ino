#include <TimerOne.h>

int _led_1 ;
int _led_2 ;

unsigned long time_off ;
unsigned long time_on ;
unsigned long curr_time ;

void blinky_init()
{
  Timer1.initialize(1000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( blinkIsr ); // attach the service routine here 
}

void blinkIsr()
{
  curr_time++;
  if (curr_time >= time_off)
  {
    
  }
}
 
void setup() 
{
  // Initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards
  pinMode(13, OUTPUT);    
  
  
}
 
void loop()
{
  // Main code loop
  // TODO: Put your regular (non-ISR) logic here
}
 
/// --------------------------
/// Custom ISR Timer Routine
/// --------------------------
void timerIsr()
{
    // Toggle LED
    digitalWrite( 13, digitalRead( 13 ) ^ 1 );
}
