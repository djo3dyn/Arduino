
#include <inttypes.h>
#include "Print.h"

#define RETURN_HOME 0x02
#define CLEAR 0x01
#define BIT_MODE 0x28
#define DISPLAY_ON 0x0C
#define CURSOR_ON 0x0A
#define BLINK_ON 0x09

class lcd_74hc595 : public Print
{
    public :

        // Inisiasi Pin dan jumlah IC yg terpasang
        lcd_74hc595(int _clockPin , int _dataPin , int _latchPin , int _count = 1 );

        // Fungsi-fungsi public
        void init();
        void clear();
        void setCursor(uint8_t _col , uint8_t _row);
        void setCurrent(uint8_t _num);

        virtual size_t write(uint8_t);
        void command(uint8_t _cmd);

        void shiftTest(uint8_t _data); // For test only

        void write4bit(uint8_t _cmd , uint8_t _RS);

        using Print::write;
    private :
        // Fungsi-fungsi internal
        void shiftByte(uint8_t _data);
        void shiftAllOut();

       

        // Variabel-variabel internal
        uint8_t clockPin ; // Pin Clock/SH_CP pada IC 74HC595 
        uint8_t dataPin ; // Pin Data/DS pada IC 74HC595 
        uint8_t latchPin ; // Pin Latch/ST_CP pada IC 74HC595 
        uint8_t count ; // Jumlah IC yg terpasang Daisy Chain

        uint8_t currentLCD ;

        uint8_t batchMode ; // Batch mode untuk write beberapa perintah

        // Internal main register data
        uint8_t registerData[64];

};