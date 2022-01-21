
const int row_pin[4] = {12,11,10,9};
const int col_pin[4] = {8,7,6,5};


void keypad_setup()
{
    int row_len = 4;
    int col_len = 4;

    //Set pin IO
    for(int i=0; i<4; i++)
    {
        pinMode(row_pin[i],OUTPUT);
        pinMode(col_pin[i],INPUT);
    }

    // Serial.print(row_len);
    // Serial.print(col_len);

}

unsigned int scan_key()
{
    for(int i=0; i<4; i++)
    {
        if (i>0) digitalWrite(row_pin[i-1],LOW);
        //if (i=0) digitalWrite(row_pin[3],LOW);
        digitalWrite(row_pin[i],HIGH);
        delay(500);  
    }
}

void setup()
{
    Serial.begin(9600);

    keypad_setup();

}

void loop()
{
    scan_key();
}