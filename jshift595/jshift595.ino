#include "jshift.h"

#define SH_CP 9
#define DS 8
#define ST_CP 7

jshift sr(SH_CP , DS , ST_CP , 4);

void setup()
{

}

void loop()
{
    sr.writeBit(1,HIGH);
    delay(1000);
    sr.writeBit(1,LOW);
    delay(1000);

    sr.batchBegin();
    sr.writeByte(0,0b10101010);
    sr.writeByte(1,0b10101111);
    sr.writeByte(2,0b11111010);
    sr.writeByte(3,0b11000011);
    sr.batchWrite();
    delay(1000);

    sr.batchBegin();
    sr.writeByte(0,0xFF);
    sr.writeByte(1,0xFF);
    sr.writeByte(2,0xFF);
    sr.writeByte(3,0xFF);
    sr.batchWrite();
    delay(1000);

    sr.batchBegin();
    sr.writeByte(0,0);
    sr.writeByte(1,0);
    sr.writeByte(2,0);
    sr.writeByte(3,0);
    sr.batchWrite();
    delay(1000);
   
}