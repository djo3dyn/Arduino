/*
 *==========================================================================
 * Serial LCD 16x2 
 * LCD 16x2 dengan Driver IC 74HC595 - 8bit Shift Register
 * Hanya menggunakan 3 pin dari Arduino 
 * Dapat di Expansi menjadi 8 atau lebih
 * 
 * Demo 8 LCD 16x2
 * Fungsi tersedia : write string , set cursor , clear  
 * Fungsi lainnya dalam pengembagan
 * Fungsi diambil dari Datasheet IC HD44780U
 * 
 * (c) 2020 : judincahsigerung@gmail.com
 *============================================================================
*/

//================================CLASS Print================================

#include "Print.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

class lcd_str : public Print {
  
  public :

   virtual size_t write(uint8_t);
   using Print::write;
};

//================================CLASS Print================================

// Inisiasi pin arduino yang terhubung ke Serial IC 74HC595
#define ST_CP 8   // Pin untuk LATCH 
#define SH_CP 12  // Pin untuk CLOCK Data 
#define DS 11     // Pin untuk Serial Data

// Definisi kodecommand untuk LCD 16x2 berdasarkan Datasheet
#define RETURN_HOME 0x02
#define CLEAR 0x01
#define BIT_MODE 0x28
#define DISPLAY_ON 0x0C
#define CURSOR_ON 0x0A
#define BLINK_ON 0x09

int currLcd = 0 ; // Variabel lokasi LCD
// Funsi untuk memilih LCD yg akan di write fungsi atau write data
void setCurrLcd(int _loc)
{
  currLcd = _loc ;
}

// Inisiasi shift register 
void shiftInit()
{
  // Semua pin di setting sebagai output
  pinMode(ST_CP,OUTPUT);
  pinMode(SH_CP,OUTPUT);
  pinMode(DS,OUTPUT);

  digitalWrite(ST_CP , HIGH);
}

/*
 * Fungsi Shift data 8 byte atau 64 bit 
 * @param _data --> 8bit data yang akan di transfer , 
 * @param _loc --> lokasi IC shift register, atau urutan dimulai dari 0
*/
void shift8Byte(byte _data , int _loc)
{
  // Karena bit shifting pada C++ / Arduino terbatas hanya 32 makan data dipecah jadi 2
  uint32_t tempL = 0 ; // 32-bit temp data Low 
  uint32_t tempH = 0 ; // 32-bit temp data High 
  
  if (_loc <= 3) // Jika lokasi pada 4 IC pertama maka _data disimpan di tempL
  {
    tempH = 0 ;
    tempL |= _data ;
    tempL <<= (8 * _loc) ;
  } 
  else // Jika lokasi pada 4 IC berikutnya maka _data disimpan di tempH
  {
    tempL = 0 ;
    tempH |= _data ;
    tempH <<= (8 * (_loc-4));
  }
  // Shifting TempH
  digitalWrite(ST_CP , HIGH); //Latch HIGH - Start Shifting
  for (int i = 31 ; i >= 0 ; i-- )  
  {
    digitalWrite(SH_CP, LOW); // Start Send Bit
    if (tempH & ((uint32_t)1 << i ) ) digitalWrite(DS , HIGH);  //Send per bit
    else digitalWrite(DS, LOW);
    digitalWrite(SH_CP, HIGH); // End Send Bit
  }
  // Shifting TempL
  for (int i = 31 ; i >= 0 ; i-- )  
  {
    digitalWrite(SH_CP, LOW);
    if (tempL & ((uint32_t)1 << i ) ) digitalWrite(DS , HIGH);
    else digitalWrite(DS, LOW);
    digitalWrite(SH_CP, HIGH);
  }
  digitalWrite(ST_CP , LOW); //Latch LOW - Store to Output
  
}
/*
 * Fungsi untuk mengirim data ke lcd,
 * _cmd -> 8 bit data yg akan dikirm, 
 * _RS = 0 -> Mengirim command
 * _RS = 1 -> Mengirim data character 
*/
void lcdWriteByte(byte _cmd , byte _RS)
{
  byte dH , dL , temp , RS ; //Init variable

  dL = _cmd & 0x0F ;          //Extract Lower nibble
  dH = (_cmd >> 4) & 0x0F ;   //Extract High nibble
  RS = (_RS << 5) & 0x20 ;    //Shift RS pin

  temp = 0x10 | RS | dH ;     //add E-High to dH ;
  shift8Byte(temp , currLcd); // shiftOut to Register
  temp = 0x00 | RS | dH ;     //add E-LOW to dH ;
  shift8Byte(temp , currLcd); // shiftOut to Register
  delayMicroseconds(10);

  temp = 0x10 | RS | dL ;     //add E-High to dL ;
  shift8Byte(temp , currLcd); // shiftOut to Register
  temp = 0x00 | RS | dL ;     //add E-LOW to dL ;
  shift8Byte(temp , currLcd); // shiftOut to Register
  delayMicroseconds(10);
}

// Fungsi inisiasi lcd
void lcdInit()
{
  lcdWriteByte(CLEAR , 0);        // LCD Clear
  lcdWriteByte(RETURN_HOME , 0);  // LCD kembali ke awal cursor
  lcdWriteByte(DISPLAY_ON ,0);    // LCD Display ON
  lcdWriteByte(BIT_MODE ,0);      // LCD 4bit mode data, 2 line display

}
// Fungsi clear LCD dan kembali ke awal kursor
void lcdClear()
{
  lcdWriteByte(CLEAR , 0);
  lcdWriteByte(RETURN_HOME , 0);
}
/*
 * Fungsi set cursor 
 * Fungsi berdasarkan set DDRAM address , 
 * Code : 0b1xxxxxxx , x = posisi cursor
 */
void lcdSetCursor(byte _row , byte _col)
{
  byte temp ;

  if (_row) temp=0x80 | ( _col + 0x40);
  else temp = 0x80 | _col ;

  lcdWriteByte(temp , 0 );
}

/* 
 * Fungsi mengirim text ke LCD, 
 * Fungsi ini masih terbatas hanya untuk tydata char, 
 * Data type lain harus diconvert terlebih dahulu
 */
void lcdWriteStr(char _string[])
{
  int len ;
  len = strlen(_string);
  for (int i = 0 ; i <=len ; i++)
  {
    lcdWriteByte(_string[i] , 1);
  }
}

// Class inisiasi

inline size_t lcd_str::write(uint8_t value) 
{
  lcdWriteByte(value, HIGH);
  return 1; // assume sucess
}

lcd_str lcd;

void setup() 
{

  shiftInit(); // Inisiasi Shift Register

  // Inisiasi 8 LCD dengan for loop
  for (int i = 0 ; i < 8 ; i++)
  {
    setCurrLcd(i);
    lcdInit();
    lcdClear();
    delay(100);
  }

  // Menampilkan "Hello World!" pada masing2 LCD
  for (int i = 0 ; i < 8 ; i++)
  {
    setCurrLcd(i);
    lcd.print("Hello World!");
    lcdSetCursor(1,0);
    lcd.print("LCD ");
    lcd.print(i+1);
    delay(500);
    /*
    String str = String(i+1);
    char num[2];
    str.toCharArray(num , 2);
    lcdWriteStr("Hello World!");
    delay(500);
    lcdSetCursor(1,0);
    lcdWriteStr("LCD ");
    lcdWriteStr(num);
    delay(500);
    */
  }
}
void loop() 
{

  // Menampilkan "Selamat Datang" pada masing2 LCD Berurutan
  for (int i = 0 ; i < 8 ; i++)
  {
    setCurrLcd(i);
    String str = String(i+1);
    char num[2];
    str.toCharArray(num , 2);
    lcdClear();
    lcdWriteStr("Selamat Datang");
    lcdSetCursor(1,0);
    lcdWriteStr("LCD ");
    lcdWriteStr(num);
    delay(500);
  }

  // Clear LCD secara berurutan
  for (int i = 0 ; i < 8 ; i++)
  {
    setCurrLcd(i);
    lcdClear();
    delay(500);
  }
    
}