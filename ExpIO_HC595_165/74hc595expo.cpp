#include "Arduino.h"
#include "74hc595expo.h"

void expOutput::begin(int _clockPin , int _dataPin , int _latchPin , int _count )
{
    // Variabel pin Ic 74HC595
    clockPin = _clockPin ;
    dataPin = _dataPin ;
    latchPin = _latchPin ;
    // Jumlah IC
    count = _count - 1 ;

    // Semua pin dijadikan Output
    pinMode(_clockPin , OUTPUT);
    pinMode(_dataPin , OUTPUT);
    pinMode(_latchPin , OUTPUT);
}

void expOutput::begin(int _clockPin , int _dataPin , int _latchPin)
{
    clockPin = _clockPin ;
    dataPin = _dataPin ;
    latchPin = _latchPin ;
    count = 0 ;

    pinMode(_clockPin , OUTPUT);
    pinMode(_dataPin , OUTPUT);
    pinMode(_latchPin , OUTPUT);
}

void expOutput::shiftByte(unsigned char _data)
{
    for (int i = 0 ; i < 8 ; i++)  
    {
        digitalWrite(clockPin, LOW);
        if (_data & (0x80 >> i ) ) digitalWrite(dataPin , HIGH);
        else digitalWrite(dataPin, LOW);
        digitalWrite(clockPin, HIGH);
    }

}

void expOutput::shiftAllOut(int _count)
{
    digitalWrite(latchPin , HIGH);
    
    for (int i = _count ; i >= 0 ; i-- )
    {
        shiftByte(shiftData[i]);
    }
    
    digitalWrite(latchPin , LOW);
}

void expOutput::expBitWrite(int _expNo , int _pin , int _stat)
{
    unsigned char temp;
    temp = ((temp | 1) << _pin);
    if (_stat) shiftData[_expNo] |= temp ;
    else shiftData[_expNo] &= ~temp ;

    shiftAllOut(count);
}

void expOutput::expBitWrite(int _pin , int _stat)
{
    unsigned char temp;
    temp = ((temp | 1) << _pin);
    if (_stat) shiftData[0] |= temp ;
    else shiftData[0] &= ~temp ;

    shiftAllOut(0);
}

void expOutput::expByteWrite(int _expNo , unsigned char _data)
{
    shiftData[_expNo] = _data ;
    shiftAllOut(count);
}

void expOutput::expByteWrite(unsigned char _data)
{
    shiftData[0] = _data ;
    shiftAllOut(0);
}