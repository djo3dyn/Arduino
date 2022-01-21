#include <EEPROM.h>

uint8_t startAddr = 100;
char textBar1[26]= "abcdefghijklmnopqrstuvwxyz";
int i = 0;

void setup() {
  
  // write textbar1
  for ( i = 0 ; i<26 ; i++){
  EEPROM.write(startAddr+i, textBar1[i]);
  }
}

void loop() {
 
  
}
