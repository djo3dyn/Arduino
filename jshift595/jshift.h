/* ============================================================================
 * jShift - General Library untuk IC 74HC595
 * 
 * Tujuan : 
 * - Meringkaskan Fungsi-fungsi shift data apabila menggunakan IC 74HC595
 * - Menambah Output digital pada Arduino
 * - Diperuntukan untuk output kecil seperti LED
 * 
 * Hanya menggunakan 3 pin Arduino
 * Dapat dipasang hingga 64 buah IC 74HC595
 * Koneksi IC Daisy Chain
 * 
 * (c) 2020 - judincahsigerung@gmail.com
 * ==============================================================================*/

/*
#ifndef 74hc595expo_h
#define 74hc595expo_h
*/

#include "Arduino.h"

class jshift
{
    public :

        // Inisiasi Pin dan jumlah IC yg terpasang
        jshift(int _clockPin , int _dataPin , int _latchPin , int _count );
        // Inisiasi Pin dengan jumlah terpasang hanya 1
        jshift(int _clockPin , int _dataPin , int _latchPin );

        // Fungsi-fungsi public
        void writeBit(int _expNo, int _pin , int _stat);
        void writeBit(int _pin , int _stat);
        void writeByte(int _expNo , unsigned char _data);
        void writeByte(unsigned char _data);

        // Fungsi batch
        void batchBegin();
        void batchWrite();

    private :
        // Fungsi-fungsi internal
        void shiftByte(unsigned char _data);
        void shiftAllOut(int _count);

        // Variabel-variabel internal
        int clockPin ; // Pin Clock/SH_CP pada IC 74HC595 
        int dataPin ; // Pin Data/DS pada IC 74HC595 
        int latchPin ; // Pin Latch/ST_CP pada IC 74HC595 
        int count ; // Jumlah IC yg terpasang Daisy Chain

        int batchMode ; // Batch mode untuk write beberapa perintah

        // Internal main register data
        unsigned char registerData[64];

};

//#endif