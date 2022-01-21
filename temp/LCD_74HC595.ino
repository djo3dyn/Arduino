#define ST_CP 8
#define SH_CP 12
#define DS 11

#define RETURN_HOME 0x02
#define CLEAR 0x01
#define BIT_MODE 0x28
#define DISPLAY_ON 0x0C
#define CURSOR_ON 0x0A
#define BLINK_ON 0x09

int currLcd = 0 ;
byte dataLCD[8] = {0,0,0,0,0,0,0,0};

void setCurrLcd(int _loc)
{
  currLcd = _loc ;
}

void shiftInit()
{
  pinMode(ST_CP,OUTPUT);
  pinMode(SH_CP,OUTPUT);
  pinMode(DS,OUTPUT);

  pinMode(13,OUTPUT);

  digitalWrite(ST_CP , HIGH);
}

void shiftByte(byte _data) 
{
  digitalWrite(ST_CP , HIGH); //Latch HIGH - Start Shifting
  for (int i = 7 ; i >= 0 ; i-- )  
  {
    digitalWrite(SH_CP, LOW);
    if (_data & (1 << i ) ) digitalWrite(DS , HIGH);  //Data out 0000 0000 , Q7-Q6-Q5-Q4 Q3-Q2-Q1-Q0 // bit Order x-x-RS-E D4-D5-D6-D7
    else digitalWrite(DS, LOW);
    digitalWrite(SH_CP, HIGH);
  }
  digitalWrite(ST_CP , LOW); //Latch LOW - Store to Output
  
}

void shiftByte(byte _data , int _loc) 
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
    if (tempH & ((uint32_t)1 << i ) ) digitalWrite(DS , HIGH);  //Data out
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

void writeByte(byte _cmd , byte _RS)
{
  byte dH , dL , temp , RS ; //Init variable

  dL = _cmd & 0x0F ; //Extract Lower nibble
  dH = (_cmd >> 4) & 0x0F ; //Extract High nibble
  RS = (_RS << 5) & 0x20 ; //Shift RS pin

  temp = 0x10 | RS | dH ; //add E-High to dH ;
  shift8Byte(temp , currLcd);// shiftOut to Register
  temp = 0x00 | RS | dH ; //add E-LOW to dH ;
  shift8Byte(temp , currLcd); // shiftOut to Register
  delayMicroseconds(10);

  temp = 0x10 | RS | dL ; //add E-High to dL ;
  shift8Byte(temp , currLcd);// shiftOut to Register
  temp = 0x00 | RS | dL ; //add E-LOW to dL ;
  shift8Byte(temp , currLcd); // shiftOut to Register
  delayMicroseconds(10);
}

void lcdInit()
{
  writeByte(CLEAR , 0);
  writeByte(RETURN_HOME , 0);
  writeByte(DISPLAY_ON ,0);
  writeByte(BIT_MODE ,0);

}

void lcdClear()
{
  writeByte(CLEAR , 0);
  writeByte(RETURN_HOME , 0);
}

void lcdSetCursor(byte _row , byte _col)
{
  byte temp ;

  if (_row) temp=0x80 | ( _col + 0x40);
  else temp = 0x80 | _col ;

  writeByte(temp , 0 );
}

void writeStr(char _string[])
{
  int len ;
  len = strlen(_string);
  for (int i = 0 ; i <=len ; i++)
  {
    writeByte(_string[i] , 1);
  }
}

void setup() 
{

  shiftInit();
  for (int i = 0 ; i < 8 ; i++)
  {
    setCurrLcd(i);
    lcdInit();
    lcdClear();
    delay(100);
  }

  for (int i = 0 ; i < 8 ; i++)
  {
    setCurrLcd(i);
    String str = String(i+1);
    char num[2];
    str.toCharArray(num , 2);
    writeStr("Hello World!");
    delay(500);
    lcdSetCursor(1,0);
    writeStr("LCD ");
    writeStr(num);
    delay(500);
  }

  
}
void loop() 
{

  for (int i = 0 ; i < 8 ; i++)
  {
    setCurrLcd(i);
    String str = String(i+1);
    char num[2];
    str.toCharArray(num , 2);
    lcdClear();
    writeStr("Selamat Datang");
    lcdSetCursor(1,0);
    writeStr("LCD ");
    writeStr(num);
    delay(500);
  }
  for (int i = 0 ; i < 8 ; i++)
  {
    setCurrLcd(i);
    lcdClear();
    delay(500);
  }
    

}