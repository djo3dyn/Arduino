/*
#ifndef 74hc595expo_h
#define 74hc595expo_h
*/

class expOutput
{
    public :
        // Fungsi-fungsi public
        void begin(int _clockPin , int _dataPin , int _latchPin , int _count );
        void begin(int _clockPin , int _dataPin , int _latchPin );
        void expBitWrite(int _expNo, int _pin , int _stat);
        void expBitWrite(int _pin , int _stat);
        void expByteWrite(int _expNo , unsigned char _data);
        void expByteWrite(unsigned char _data);

    private :
        // Fungsi-fungsi internal
        void shiftByte(unsigned char _data);
        void shiftAllOut(int _count);

        // Variabel-variabel internal
        int clockPin ;
        int dataPin ;
        int latchPin ;
        int count ;

        // Internal main data
        unsigned char shiftData[16];
};