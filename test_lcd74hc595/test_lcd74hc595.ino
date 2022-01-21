#include "lcd_74hc595.h"

lcd_74hc595 lcd(9 , 8 , 7);

void setup()
{
    delay(1000);
    lcd.init();
    delay(1000);

    lcd.print("Judin");

}

void loop()
{
    

    
}