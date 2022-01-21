#include <SPI.h>

#define SS_1 7
#define SS_2 8

unsigned int data_to_send = 0 ;
unsigned int received_data = 0 ;

void setup()
{
    pinMode(SS_1 , OUTPUT);
    pinMode(SS_2 , OUTPUT);
    Serial.begin(9600);
    SPI.begin();
}

void loop()
{
    digitalWrite(SS_2 , LOW);
    data_to_send = SPI.transfer(0x00);
    digitalWrite(SS_2 , HIGH);
    

    digitalWrite(SS_1 , LOW);
    SPI.transfer(data_to_send);
    digitalWrite(SS_1 , HIGH);
    
    Serial.println(data_to_send);
    delay(1000);
}