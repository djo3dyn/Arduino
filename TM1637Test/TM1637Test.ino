#include <TM1637Display.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;

// Module connection pins (Digital Pins)
#define CLK 17
#define DIO 16

TM1637Display display(CLK, DIO);

int run_mode = 1 ;
uint16_t jam ;
uint16_t menit ;
uint8_t colon ;

void setup()
{
  //Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  display.setBrightness(0xff);
  if (! RTC.isrunning()) {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop()
{
  if (run_mode)
  {
    DateTime now = RTC.now();
    jam = now.hour();
    menit = now.minute();
    colon ^= 0b01000000 ; //display.showNumberDecEx(menit, 0b01000000, true , 2, 2); 
    display.showNumberDecEx(menit, colon, true , 2, 2); 
    display.showNumberDecEx(jam, colon, true , 2, 0 ); 
    delay(500);
  }
  



}
