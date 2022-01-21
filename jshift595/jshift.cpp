/* ==========================================================================
 * jShift - General Library untuk IC 74HC595
 * 
 * Tujuan : 
 * - Meringkaskan Fungsi-fungsi shift data apabila menggunakan IC 74HC595
 * - Menambah Output digital pada Arduino
 * - Diperuntukan untuk output kecil seperti LED
 * 
 * Hanya menggunakan 3 pin Arduino
 * Dapat dipasang hingga 64 buah IC 74HC595
 * Koneksi IC Daisy Chain
 * 
 * (c) 2020 - judincahsigerung@gmail.com
 * ==============================================================================*/

#include "Arduino.h"
#include "jshift.h"
/*
 * Inisiasi Shift Register
 * _clockPin = Pin yg terpasang pada IC 74HC595  


*/
jshift::jshift(int _clockPin , int _dataPin , int _latchPin , int _count )
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

jshift::jshift(int _clockPin , int _dataPin , int _latchPin)
{
    clockPin = _clockPin ;
    dataPin = _dataPin ;
    latchPin = _latchPin ;
    count = 0 ;

    pinMode(_clockPin , OUTPUT);
    pinMode(_dataPin , OUTPUT);
    pinMode(_latchPin , OUTPUT);
}

void jshift::shiftByte(unsigned char _data)
{
    for (int i = 0 ; i < 8 ; i++)  
    {
        digitalWrite(clockPin, LOW);
        if (_data & (0x80 >> i ) ) digitalWrite(dataPin , HIGH);
        else digitalWrite(dataPin, LOW);
        digitalWrite(clockPin, HIGH);
    }

}

void jshift::shiftAllOut(int _count)
{
    digitalWrite(latchPin , HIGH);
    
    for (int i = _count ; i >= 0 ; i-- )
    {
        shiftByte(registerData[i]);
    }
    
    digitalWrite(latchPin , LOW);
}

void jshift::writeBit(int _expNo , int _pin , int _stat)
{
    unsigned char temp;
    temp = ((temp | 1) << _pin);
    if (_stat) registerData[_expNo] |= temp ;
    else registerData[_expNo] &= ~temp ;

    if(!batchMode)  shiftAllOut(count);
}

void jshift::writeBit(int _pin , int _stat)
{
    unsigned char temp;
    temp = ((temp | 1) << _pin);
    if (_stat) registerData[0] |= temp ;
    else registerData[0] &= ~temp ;

    if(!batchMode) shiftAllOut(count);
}

void jshift::writeByte(int _expNo , unsigned char _data)
{
    registerData[_expNo] = _data ;
    if(!batchMode) shiftAllOut(count);
}

void jshift::writeByte(unsigned char _data)
{
    registerData[0] = _data ;
    if(!batchMode) shiftAllOut(count);
}

void jshift::batchBegin()
{
    batchMode = 1 ;
}

void jshift::batchWrite()
{
    if (batchMode) shiftAllOut(count);
    batchMode = 0 ;
}