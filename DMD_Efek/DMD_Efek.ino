#include <DMD2.h>
#include <SPI.h>
#include <fonts/Arial_Black_16.h>
#include <fonts/SystemFont5x7Gemuk.h>
#include <fonts/SystemFont5x7Ramping.h>

//defenisi pin
#define pinOE         9
#define pinSCK        8
#define pinA          6
#define pinB          7

#define DISPLAYS_WIDE 3
#define DISPLAYS_HIGH 1

SPIDMD dmd(DISPLAYS_WIDE, DISPLAYS_HIGH, pinOE, pinA, pinB, pinSCK);
DMDFrame dmdEfek(96, 16);

long millisDetik;
long millisEfek;
bool modeInformasi;

int16_t i = 0;

char textBar1[100] = "Pempek Kito";
char textBar2[100] = "Pempek Kito Green Lake - Rukan Fresh Market";

DMD_TextBox boxBaris1(dmd, 0, 0, 96, 7);
DMD_TextBox boxBaris2(dmd, 0, 8, 96, 8);

struct EfekMarqueHorizontalkeKiri
{
  uint8_t sumber;
  uint16_t alamat;
  uint8_t top;
  uint8_t tinggi;
  uint8_t left;
  uint8_t lebar;
  uint8_t step;
  char data;
  uint16_t posisi;
  uint16_t panjang;
};

EfekMarqueHorizontalkeKiri marqueKiri;

void setup() {
  Serial.begin(9600);

  dmd.setBrightness(255);
  dmd.selectFont(SystemFont5x7Ramping);
  dmd.clearScreen();
  dmd.begin();

  boxBaris1.print("Pempek Kito");
  dmd.drawString(0,8,"Green Lake City");

  //Setting Marque


}

void loop() {
  /*
    if (i>-100)
    {
    DMDFrame to_move = dmd.subFrame(i, 8, 96, 8);
    i--;
    dmd.copyFrame(to_move, i, 8);
    } else
    {
      i=0;
      dmd.drawString(8,95,"Green Lake City");
    }
    delay(50);
    */

}
