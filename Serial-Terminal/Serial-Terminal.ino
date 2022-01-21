#include <stdlib.h> 

char buff;
char cmd_chr[10] , arg1_chr[5] , arg2_chr[5] , arg3_chr[5];
char arg4_chr[5];
char arg5_chr[5];
int i = 0;
int itot = 0;
int input_mode = 0 ;
int size_in[6];

//Awal Mula..
void incmd()
{
    Serial.print("@arduino:~$ ");
}

void decode_char(char _cmd[] , char _arg1[] , char _arg2[] , char _arg3[] , char _arg4[] , char _arg5[])
{
    if (strcmp(_cmd , "help")==0) 
    {
        Serial.println("ver - display the version");
        Serial.println("pmode [pin] [mode] - set arduino pin input or output");
        Serial.println("dwrite [pin] [1/0] - digital write arduino pin");
        Serial.println();
        Serial.println("Other command is comming soon");
    }
    else if (strcmp(_cmd , "ver")==0) 
    {
        Serial.println("Arduino Serial Terminal - compactible with puTTy");
        Serial.println("Version 0.1.0");
        Serial.println("judincahsigerung@gmail.com");
    }
    else if (strcmp(_cmd , "pmode")==0) 
    {
        int pin = atoi(_arg1);
        int mode = atoi(_arg2);
        pinMode(pin, mode);
        Serial.print("Pin ");
        Serial.print(pin);
        Serial.print(" set to : ");
        if (mode==1) Serial.println("OUTPUT");
        else if (mode==0) Serial.println("INPUT");
    }
    else if (strcmp(_cmd , "dwrite")==0) 
    {
        int pin = atoi(_arg1);
        int value = atoi(_arg2);
        digitalWrite(pin, value);
        Serial.print("Pin ");
        Serial.print(pin);
        Serial.print(" write to : ");
        if (value==1) Serial.println("HIGH");
        else if (value==0) Serial.println("LOW");
    }
    else 
    {
        Serial.print("Command '");
        Serial.print(_cmd);
        Serial.println("' not found");

    }   
}

// Reset All saved character , count and buffer 
void reset_char()
{
    memset(cmd_chr, 0, sizeof cmd_chr);
    memset(arg1_chr, 0, sizeof arg1_chr);
    memset(arg2_chr, 0, sizeof arg2_chr);
    memset(arg3_chr, 0, sizeof arg3_chr);
    memset(arg4_chr, 0, sizeof arg4_chr);
    memset(arg5_chr, 0, sizeof arg5_chr);
    i = 0 ;
    itot = 0 ;
    input_mode = 0 ;
}

void setup()
{
    Serial.begin(9600);
    incmd();
}

void loop()
{
    if (Serial.available()>0)
    { 
        buff = Serial.read();

        if (buff >= 33 && buff <= 126) // Input character
        {
            Serial.print(buff); //echo
            switch (input_mode)
            {
            case 0 : cmd_chr[i] = buff;
            break;
            case 1 : arg1_chr[i] = buff;
            break;
            case 2 : arg2_chr[i] = buff;
            break;
            case 3 : arg3_chr[i] = buff;
            break;
            case 4 : arg4_chr[i] = buff;
            break;
            case 5 : arg5_chr[i] = buff;
            break;
            }
            //chr1[i] = buff ;
            i++;
            itot++;
        }
        else if (buff == 32) // Jika spasi ditekan
        {
            size_in[input_mode] = i ;
            input_mode ++ ;
            i = 0;
            itot ++ ;
            Serial.print(buff); //echo
        }
          
        else if (buff == 127 && itot > 0) // Jika tekan backspace
        {
            Serial.print(buff); //echo
            if (i==0)
            {
                input_mode --;
                i = size_in[input_mode];
            } else {
                i--;            
                switch (input_mode)
                {
                case 0 : cmd_chr[i] = 0;
                break;
                case 1 : arg1_chr[i] = 0;
                break;
                case 2 : arg2_chr[i] = 0;
                break;
                case 3 : arg3_chr[i] = 0;
                break;
                case 4 : arg4_chr[i] = 0;
                break;
                case 5 : arg5_chr[i] = 0;
                break;
                }
            }
            itot--;
        }
        else if (buff == 10 || buff == 13) //Ketika tekan enter or LF and CR
        {
            Serial.println();
            decode_char(cmd_chr , arg1_chr , arg2_chr , arg3_chr , arg4_chr , arg5_chr); //Decode command...
            Serial.println();
            reset_char();
            incmd();
        }
    }
/*
    if (strcmp(chr2 , "Hello")==0) Serial.println("equal");
    Serial.println(chr2);
    delay(1000);
    */
    
}
