
#include "lcd_74hc595.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

lcd_74hc595::lcd_74hc595(int _clockPin , int _dataPin , int _latchPin , int _count )
{
    clockPin = _clockPin ;
    dataPin = _dataPin ;
    latchPin = _latchPin ;

    count = _count - 1 ;

    // Semua pin dijadikan Output
    pinMode(_clockPin , OUTPUT);
    pinMode(_dataPin , OUTPUT);
    pinMode(_latchPin , OUTPUT);
}

void lcd_74hc595::init()
{
    command(BIT_MODE);
    command(DISPLAY_ON);
    command(CLEAR);
    command(RETURN_HOME);
    
}

void lcd_74hc595::setCurrent(uint8_t _num)
{
    currentLCD = _num ;
}

// Send Command 
inline void lcd_74hc595::command(uint8_t value)
{
    write4bit(value , LOW);
}

// Write data , send character , ( Replace write on print.h) 
inline size_t lcd_74hc595::write(uint8_t value)
{
    write4bit(value , HIGH);
    return 1;
}

void lcd_74hc595::write4bit(uint8_t _cmd , uint8_t _RS)
{
  uint8_t dH , dL , temp , RS ; //Init variable

  dL = _cmd & 0x0F ;        //Extract Lower nibble
  dH = (_cmd >> 4) & 0x0F ; //Extract High nibble
  RS = (_RS << 5) & 0x20 ;  //Shift RS pin

  temp = 0x10 | RS | dH ;       //add E-High to dH ;
  registerData[currentLCD] = temp ;   // shiftOut to Register
  shiftAllOut();
  temp = 0x00 | RS | dH ;       //add E-LOW to dH ;
  registerData[currentLCD] = temp ;
  shiftAllOut();
  delayMicroseconds(10);

  temp = 0x10 | RS | dL ;       //add E-High to dL ;
  registerData[currentLCD] = temp ;   // shiftOut to Register
  shiftAllOut();
  temp = 0x00 | RS | dL ;       //add E-LOW to dL ;
  registerData[currentLCD] = temp ;   // shiftOut to Register
  shiftAllOut();
  delayMicroseconds(10);
}

/* LOW Level Code for Sending to Shift Register */

// Shift data per 8 bit
inline void lcd_74hc595::shiftByte(uint8_t _data)
{
    for (int i = 0 ; i < 8 ; i++)  
    {
        digitalWrite(clockPin, LOW);
        if (_data & (0x01 << i ) ) digitalWrite(dataPin , HIGH);
        else digitalWrite(dataPin, LOW);
        digitalWrite(clockPin, HIGH);
    }

}

// Shift All data max 64 byte 
inline void lcd_74hc595::shiftAllOut()
{
    digitalWrite(latchPin , HIGH);
    for (int i = count ; i >= 0 ; i-- )
    {
        shiftByte(registerData[i]);
    }
    digitalWrite(latchPin , LOW);
}

void lcd_74hc595::shiftTest(uint8_t _data_1)
{
    digitalWrite(latchPin , HIGH);
    shiftByte(_data_1);
    digitalWrite(latchPin , LOW);

}

