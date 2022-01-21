#define ST_CP 8
#define SH_CP 12
#define DS 11

void shiftInit()
{
  pinMode(ST_CP,OUTPUT);
  pinMode(SH_CP,OUTPUT);
  pinMode(DS,OUTPUT);

  pinMode(13,OUTPUT);

  digitalWrite(ST_CP , HIGH);
}

void shift8Byte(byte _data , int _loc) 
{
  uint32_t tempL = 0 ; //32-bit temp data Low
  uint32_t tempH = 0 ; //32-bit temp data High
  
  if (_loc <= 3)
  {
    tempH = 0 ;
    tempL |= _data ;
    tempL <<= (8 * _loc) ;
  } 
  else
  {
    tempL = 0 ;
    tempH |= _data ;
    tempH <<= (8 * (_loc-4));
  }
  digitalWrite(ST_CP , HIGH); //Latch HIGH - Start Shifting
  for (int i = 31 ; i >= 0 ; i-- )  
  {
    digitalWrite(SH_CP, LOW);
    if (tempH & ((uint32_t)1 << i ) ) digitalWrite(DS , HIGH);  //Data out 0000 0000 , Q7-Q6-Q5-Q4 Q3-Q2-Q1-Q0 // bit Order x-x-RS-E D4-D5-D6-D7
    else digitalWrite(DS, LOW);
    digitalWrite(SH_CP, HIGH);
  }
  for (int i = 31 ; i >= 0 ; i-- )  
  {
    digitalWrite(SH_CP, LOW);
    if (tempL & ((uint32_t)1 << i ) ) digitalWrite(DS , HIGH);  //Data out 0000 0000 , Q7-Q6-Q5-Q4 Q3-Q2-Q1-Q0 // bit Order x-x-RS-E D4-D5-D6-D7
    else digitalWrite(DS, LOW);
    digitalWrite(SH_CP, HIGH);
  }
 /*
 
  */
  digitalWrite(ST_CP , LOW); //Latch LOW - Store to Output
  
}

void setup() 
{
  shiftInit();

}

void loop()
{
    shift8Byte(0b10010011 , 0);
    delay(1000);
    shift8Byte(0b10010011 , 1);
    delay(1000);
    shift8Byte(0b10010011 , 2);
    delay(1000);
    shift8Byte(0b10010011 , 3);
    delay(1000);
    shift8Byte(0b10010011 , 4);
    delay(1000);
    shift8Byte(0b10010011 , 5);
    delay(1000);
    shift8Byte(0b10010011 , 6);
    delay(1000);
    shift8Byte(0b10010011 , 7);
    delay(1000);
}