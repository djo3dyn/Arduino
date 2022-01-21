/* 
 Experiment bikin protokol sendiri
 Nama : proto-J Protokol
 Versi : 0.1.0
 Tahun : 2019
 Start : Oct 2019
 Status : on progress - belum bisa di aplikasikan

*/

unsigned char myData[255];
bool myBit[255];

void setup() 
{

  protocol_configure(38400,0xff,0xfe,200 );
  Serial.println("Protocol Terkonfigurasi...");

}

void loop() 
{
  
  unsigned int test = protocol_update(myData,myBit);
        
}


/* -----------------------------Protocol Variable and function -------------------------- */

/*
Log :

00/10/2019 -- Start Coding
00/11/2019 -- Test serial receive
08/11/2019 -- Review add some comment


*/

//Inisialisasi variabel protocol default

unsigned char start_char = 0xff;
unsigned char end_char = 0xfe;

unsigned char data_bytes[255];
bool data_bit [255];
bool loop_ = 0 ;


unsigned int count = 0 ; //jumlah data terkirim

// Variable milis for interval kirim data
unsigned long previousMillis = 0;
unsigned int interval = 100;
unsigned int t_1 = 1000 ; // delay antar karakter frame dala micro second


// Frame data ketika diterima
unsigned char frame_bytes[8]; // Frame byte = [start_char] [function_code] [address] [data_1] [data_2] [data_3] [data_4] [end_char]


// Fungsi konfigurasi protokol
void protocol_configure(unsigned int Baud_rate, unsigned char Start_char, unsigned char End_char,  unsigned int Interval )
{
  Serial.begin(Baud_rate);
  start_char = Start_char;
  end_char = End_char ;
  interval = Interval;
}

unsigned int protocol_update(unsigned char Data_bytes[255], bool Data_bit [255])
{
  // Code jika ada data serial yang masuk
  if (Serial.available()>0)
  { 
      int i = 0 ;
      // Memasukan data masuk kedalam frame
      while (Serial.available()>0)
      {
        if (i<8) frame_bytes[i] = Serial.read(); // Frame byte = [start_char] [function_code] [address] [data_1] [data_2] [data_3] [data_4] [end_char]
        else { Serial.read();}
        i++;
        delayMicroseconds(t_1);
      }

    if (frame_bytes[0]==start_char && frame_bytes[7]==end_char)
    {
      //Encode....
      Serial.println("Data Frame diterima...");

      switch (frame_bytes[1])
      {
        case 0 :
          
          loop_ = 0 ;

        break;
        case 1 :
          
          write_bit(frame_bytes[2],frame_bytes[3]);

        break;
        case 2 :

        break;
        case 3 :
          read_byte(frame_bytes[2],frame_bytes[3]);
        break;
        case 4 :
          
        break;
      }

    }
  }

  if (loop_)
  {
    unsigned long currentMillis = millis(); // CurrentMillis akan bertambah terus
    if (currentMillis - previousMillis >= interval) 
    {
      previousMillis = currentMillis;
      //Kode untuk kirim data dalam rentang waktu interval


    }

  }
  

  return count ; // return data
}


void write_bit( byte _address , bool _value ) //function code 1
{
  if (_value == 0)
  {
    data_bit[_address] = 0 ;
  } else if (_value == 1)
  {
    data_bit[_address] = 1 ;
  }
  
}

void write_byte( byte _address , byte _value ) //function code 2
{
  data_bytes[_address] = _value ;
}

void read_byte(byte _address, byte _length) //function code 3-4
{
  //if (255 - _address -  _length )
  Serial.write(start_char);
  Serial.write(data_bytes[_address]);
  Serial.write(end_char);
 
  count++;
}



/*---------------------------------------------------------------------------------------*/