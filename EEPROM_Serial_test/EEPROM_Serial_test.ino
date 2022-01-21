#include <EEPROM.h>

uint16_t startAddrSet = 0;
uint16_t startAddrTxt1 = 100;
uint16_t startAddrTxt2 = 200;

uint8_t setting[] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
char textBar1[100] ;
char textBar2[100] ;

//milis for delay
unsigned long previousMillis = 0;
const long interval = 3000;

void setup() 
{
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  startup();
}

void loop() {
 if (Serial.available() > 0) // Dilakukan ketika ada data serial masuk...
  {
    String strBuff ;
    char chrBuff[104];
    strBuff = Serial.readStringUntil('\n');
    strBuff.toCharArray(chrBuff, 104 );

    char inCode[4];
    char inData[100];
    int i = 0;
    
    for (i=0; i<4; i++) // Ekstrak kode.....
    {
      inCode[i]=chrBuff[i];
    }
    for (i=0; i<100; i++) // Ekstrak data.....
    {
     inData[i]=chrBuff[i+4];
    }
    encodeData(inCode,inData); // Encode dan Simpan data...
  }

  unsigned long currentMillis = millis(); // CurrentMillis akan bertambah terus
  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;
    Serial.println("-------------------------------------------------------");
    Serial.println(textBar1);
    Serial.println(textBar2);
    Serial.println("-------------------------------------------------------");
    Serial.println();
  }

}

void encodeData(char code[], char data[])
{
  if(strcmp(code, "TX0:") == 0)
  { 
    eepromWriteStr(startAddrTxt1,100,data);
    Serial.print("Diterima Baris 1 : ");
    Serial.println(data);
    eepromReadStr(startAddrTxt1,100,textBar1);
  }
  else if(strcmp(code, "TX1:") == 0)
  { 
    eepromWriteStr(startAddrTxt2,100,data);
    Serial.print("Diterima Baris 2 : ");
    Serial.println(data);
    eepromReadStr(startAddrTxt2,100,textBar2);
  }
  else
  {
    Serial.println("Kode Salah!");
  }
}

void eepromReadStr(uint16_t startAdd , uint16_t lenght , char dest[])
{
  int i = 0;
  for ( i = 0 ; i<lenght ; i++)
  {
    dest[i] = EEPROM.read(startAdd+i);
  }
}

void eepromWriteStr(uint16_t startAdd , uint16_t lenght , char src[])
{
  int i = 0;
  for ( i = 0 ; i<lenght ; i++)
  {
    EEPROM.write(startAdd+i, src[i]);
  }
}

void startup()
{
  eepromReadStr(startAddrTxt1,100,textBar1);
  eepromReadStr(startAddrTxt2,100,textBar2);
}
