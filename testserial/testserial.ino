/*
 */

#define PIN_DEBUG 2
#define PIN_INPUT 3
#define BUFFER 10

byte data[5] ;
bool dbit[5] ;

char receive_bytes[10] ;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_DEBUG,INPUT_PULLUP);
  pinMode(PIN_INPUT,INPUT_PULLUP);

}

void loop() {

  if (!digitalRead(PIN_DEBUG))
  {
    protocol_update(data,dbit);
    Serial.println(data[0]);
    delay(1000);
  }
  int i = 0 ;
  while (Serial.available()>0)
  {
    if (i>=BUFFER)
    {
      Serial.read();
    }
    else
    {
      receive_bytes[i] = Serial.read();
      i++;
    }
    delay(10);
  }
   
}

/*----- Protocol Class -------*/
unsigned int protocol_update(byte data_byte[5], bool data_bit[5])
{
  data_byte[0] += 1;
  return 1 ;
}
  
