#include <Wire.h>
#include "RTClib.h"
#include <TimerOne.h>

#define NONE    0b00000000
#define ZERO    0b00111111
#define ONE     0b00000110
#define TWO     0b01011011 
#define THREE   0b01001111
#define FOUR    0b01100110
#define FIVE    0b01101101
#define SIX     0b01111101
#define SEVEN   0b00000111
#define EIGHT   0b01111111
#define NINE    0b01101111
#define CHR_A   0b01110111
#define CHR_B   0b01111100
#define CHR_C   0b00111001
#define CHR_D   0b01011110
#define CHR_E   0b01111001
#define CHR_F   0b01110001

#define COM_CATHODE  0
#define COM_ANODE   1


RTC_DS1307 RTC;
const int latchPin = 10; //Pin connected to ST_CP of 74HC595
const int clockPin = 12; //Pin connected to SH_CP of 74HC595
const int dataPin = 11; //Pin connected to DS of 74HC595

const int d_latchPin = 7; //Pin connected to ST_CP of 74HC595
const int d_clockPin = 9; //Pin connected to SH_CP of 74HC595
const int d_dataPin = 8; //Pin connected to DS of 74HC595

const int ledPin = 13;

int number[6] ;
int segment[7][4];

byte seg_decode(byte input)
{
  switch (input)
  {
    case 0 : return ZERO ;
    break ;
    case 1 : return ONE ;
    break ;
    case 2 : return TWO ;
    break ;
    case 3 : return THREE ;
    break ;
    case 4 : return FOUR ;
    break ;
    case 5 : return FIVE ;
    break ;
    case 6 : return SIX ;
    break ;
    case 7 : return SEVEN ;
    break ;
    case 8 : return EIGHT ;
    break ;
    case 9 : return NINE ;
    break ;
    case 10 : return CHR_A ;
    break ;
    case 11 : return CHR_B ;
    break ;
    case 12 : return CHR_C ;
    break ;
    case 13 : return CHR_D ;
    break ;
    case 14 : return CHR_E ;
    break ;
    case 15 : return CHR_F ;
    break ;
    default : return NONE ;
    break ;
  }
}

unsigned int dec2bcd(unsigned int number)
{
  
    unsigned char i=0;
    unsigned int k = 0;
    while(number)
    {
        k = ( k ) | ((number%10) << i*4);
        number = number / 10;
        i++;
    }
    return(k);
 
}

void decto7seg(unsigned int input , int _seg[4] , bool compin)
{
  int digit[4];
  for (int i = 0 ; i < 4 ; i++)
  {
     digit[i] = (dec2bcd(input) >> (i * 4) ) & 0x0F ;
     if (compin) _seg[i] = ~ seg_decode(digit[i]);
     else _seg[i] = seg_decode(digit[i]);
  }
}

void hexto7seg(unsigned int input , int _seg[4] , bool compin )
{
  int digit[4];
  for (int i = 0 ; i < 4 ; i++)
  {
     digit[i] = (input >> (i * 4) ) & 0x0F ;
    if (compin) _seg[i] = ~ seg_decode(digit[i]);
     else _seg[i] = seg_decode(digit[i]);
  }
}


void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {

  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  for (int i = 7 ; i >= 0 ; i-- )  
  {
    digitalWrite(myClockPin, 0);
    if ( myDataOut & (1 << i ) ) digitalWrite(myDataPin, HIGH);  //Data out 0000 0000 , Q7-Q6-Q5-Q4 Q3-Q2-Q1-Q0 
    else digitalWrite(myDataPin, LOW);
    digitalWrite(myClockPin, 1);
  }
  digitalWrite(myClockPin, 0);
}

void update_date()
{
  DateTime now = RTC.now();
  decto7seg(20 , segment[4] , COM_ANODE); 
  decto7seg(now.year() , segment[3] , COM_ANODE);
  decto7seg(now.month() , segment[5] , COM_ANODE);
  decto7seg(now.day() , segment[6] , COM_ANODE);
  digitalWrite(d_latchPin, 0);
    for (int i = 3 ; i < 7 ; i++)
    {
      shiftOut(d_dataPin, d_clockPin, segment[i][0]); 
      shiftOut(d_dataPin, d_clockPin, segment[i][1]);
    } 
  digitalWrite(d_latchPin, 1);
  
}

void setup() {
  pinMode(latchPin, OUTPUT); //set pins to output because they are addressed in the main loop
  pinMode(d_latchPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) 
  {
    RTC.adjust(DateTime(__DATE__, __TIME__)); // following line sets the RTC to the date & time this sketch was compiled
  }
  update_date();

  Timer1.initialize(500000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timeIsr ); // attach the service routine here

}

void loop() {
   
   
}

void timeIsr()
{
    DateTime now = RTC.now(); 
    decto7seg(now.hour() , segment[2] , COM_ANODE);
    decto7seg(now.minute() , segment[1] , COM_ANODE);
    decto7seg(now.second() , segment[0] , COM_ANODE);
    
    digitalWrite(latchPin, 0);
    for (int i = 0 ; i < 3 ; i++)
    {
      shiftOut(dataPin, clockPin, segment[i][0]); 
      shiftOut(dataPin, clockPin, segment[i][1]);
    } 
    digitalWrite(latchPin, 1);
    digitalWrite(ledPin, digitalRead(ledPin)^1);
}
