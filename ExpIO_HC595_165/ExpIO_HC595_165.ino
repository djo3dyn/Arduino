#include "74hc595expo.h"

#define SH_CP 9
#define DS 8
#define ST_CP 7

expOutput exp1 ;

void setup()
{
    exp1.begin(SH_CP , DS , ST_CP , 2);   
}

void loop()
{
    exp1.expBitWrite(0 , 0 , HIGH);
    delay(1000);
    exp1.expBitWrite(0 , 1 , HIGH);
    delay(1000);
    exp1.expBitWrite(1 , 0 , HIGH);
    delay(1000);
    exp1.expBitWrite(1 , 1 , HIGH);
    delay(1000);
    exp1.expBitWrite(0 , 0 , LOW);
    delay(1000);
    exp1.expBitWrite(0 , 1 , LOW);
    delay(1000);
    exp1.expBitWrite(1 , 0 , LOW);
    delay(1000);
    exp1.expBitWrite(1 , 1 , LOW);
    delay(1000);
    exp1.expByteWrite(0 , 0xF0);
    delay(1000);
    exp1.expByteWrite(1 , 0x0F);
    delay(1000);
    exp1.expByteWrite(0 , 0xFF);
    delay(1000);
    exp1.expByteWrite(1 , 0xFF);
    delay(1000);
    exp1.expByteWrite(0 , 0x00);
    delay(1000);
    exp1.expByteWrite(1 , 0x00);
    delay(1000);
}