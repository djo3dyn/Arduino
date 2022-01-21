//**************************************************************//
//  Name    : shiftOutCode, Dual Binary Counters                 //
//  Author  : Carlyn Maw, Tom Igoe                               //
//  Date    : 25 Oct, 2006                                       //
//  Version : 1.0                                                //
//  Notes   : Code for using a 74HC595 Shift Register            //
//          : to count from 0 to 255                             //
//**************************************************************//

#define NONE    0b00000000
#define ZERO    0b00111111
#define ONE     0b00000110
#define TWO     0b01011011 
#define THREE   0b01001111
#define FOUR    0b01100110
#define FIVE    0b01101101
#define SIX     0b01111101
#define SEVEN   0b00000111
#define EIGHT   0b01111111
#define NINE    0b01101111
#define CHR_A   0b01110111
#define CHR_B   0b01111100
#define CHR_C   0b00111001
#define CHR_D   0b01011110
#define CHR_E   0b01111001
#define CHR_F   0b01110001

#define COM_CATHODE  0
#define COM_ANODE   1



const int latchPin = 8; //Pin connected to ST_CP of 74HC595
const int clockPin = 12; //Pin connected to SH_CP of 74HC595
const int dataPin = 11; //Pin connected to DS of 74HC595

int number[6] ;
int segment[6][4];

byte seg_decode(byte input)
{
  switch (input)
  {
    case 0 : return ZERO ;
    break ;
    case 1 : return ONE ;
    break ;
    case 2 : return TWO ;
    break ;
    case 3 : return THREE ;
    break ;
    case 4 : return FOUR ;
    break ;
    case 5 : return FIVE ;
    break ;
    case 6 : return SIX ;
    break ;
    case 7 : return SEVEN ;
    break ;
    case 8 : return EIGHT ;
    break ;
    case 9 : return NINE ;
    break ;
    case 10 : return CHR_A ;
    break ;
    case 11 : return CHR_B ;
    break ;
    case 12 : return CHR_C ;
    break ;
    case 13 : return CHR_D ;
    break ;
    case 14 : return CHR_E ;
    break ;
    case 15 : return CHR_F ;
    break ;
    default : return NONE ;
    break ;
  }
}

unsigned int dec2bcd(unsigned int number)
{
  
    unsigned char i=0;
    unsigned int k = 0;
    while(number)
    {
        k = ( k ) | ((number%10) << i*4);
        number = number / 10;
        i++;
    }
    return(k);
 
}

void decto7seg(unsigned int input , int _seg[4] , bool compin)
{
  int digit[4];
  for (int i = 0 ; i < 4 ; i++)
  {
    digit[i] = (dec2bcd(input) >> (i * 4) ) & 0x0F ;
    if (compin) _seg[i] = ~ seg_decode(digit[i]);
    else _seg[i] = seg_decode(digit[i]);
  }
}

void hexto7seg(unsigned int input , int _seg[4] , bool compin )
{
  int digit[4];
  for (int i = 0 ; i < 4 ; i++)
  {
    digit[i] = (input >> (i * 4) ) & 0x0F ;
    if (compin) _seg[i] = ~ seg_decode(digit[i]);
    else _seg[i] = seg_decode(digit[i]);
  }
}


void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {

  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  for (int i = 7 ; i >= 0 ; i-- )  
  {
    digitalWrite(myClockPin, 0);
    if ( myDataOut & (1 << i ) ) digitalWrite(myDataPin, HIGH);  //Data out 0000 0000 , Q7-Q6-Q5-Q4 Q3-Q2-Q1-Q0 
    else digitalWrite(myDataPin, LOW);
    digitalWrite(myClockPin, 1);
  }
  digitalWrite(myClockPin, 0);
}

void setup() {
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT); //set pins to output because they are addressed in the main loop

}

void loop() {

    for (int i = 0 ; i < 6 ; i++)
    {
      number[i] = random(0,9999);
      Serial.println(number[i]);
      decto7seg(number[i] , segment[i] , COM_ANODE);
    }
    
    digitalWrite(latchPin, 0);
    for (int i = 0 ; i < 6 ; i++)
    {
      shiftOut(dataPin, clockPin, segment[i][0]); 
      shiftOut(dataPin, clockPin, segment[i][1]);
      shiftOut(dataPin, clockPin, segment[i][2]);
      shiftOut(dataPin, clockPin, segment[i][3]);
    } 
    digitalWrite(latchPin, 1);
    delay(1000);
}
