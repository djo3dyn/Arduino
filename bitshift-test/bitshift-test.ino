uint8_t bit = 0b01010101;
int i = 0 ;
bool readBit(uint8_t _val , int _pos)
{
    return (_val >> _pos) & 0x01 ; 
}
void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available()>0)
    {
        bit = Serial.read();
        Serial.print("Received : ");
        Serial.println(bit, BIN);
        i = 0 ;
    }
    bool mybit = readBit(bit , i);
    Serial.print("Bit Number ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(mybit, BIN);
    i ++ ;
    if ( i > 7 ) i = 0 ;
    delay(1000);
    
}