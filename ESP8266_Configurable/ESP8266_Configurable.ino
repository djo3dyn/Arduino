#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

// Define konstan variabel
#define TCP_PORT 8871
#define UDP_PORT 8870
#define R_UDP_PORT 18870
#define RESET_PIN 5
#define LED_PIN 2
#define DEV_NAME "espnode00001"

// Default AP ssid & password
String ssid = "ESP_Node12345";    // Nama AP/Hotspot
String password = "node12345";    // Password AP/Hotspot

// Default STA ssid & password
String stassid ;
String stapassword ;  
bool wifi_changed ;

// TCP Variable
const int port = TCP_PORT;
WiFiServer server(port);
WiFiClient client;

// UDP Variabel
WiFiUDP IsUDP;
char packet[15];
const char discoverykey[] = {0xFC,0xA4,0xDD,0xD1,0xA5,0xDC,0xF0,0xB4,0xF2,0x91};

// Json Variable
const char* defapikey = "abcdefghijk";
char rawjson[2048];
StaticJsonDocument<2048> jsondoc;

// pre defined program---------------------------------------------------------------------------------------
void Wifi_AP_Start(bool _hotchange)
{
    // Cek data di eeprom

    delay(1000);
     if (_hotchange)
    {
        client.stop();
        server.close();
        Serial.println("Client terputus karena pergantian mode"); 
    }
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid , password);

    Serial.println();
    Serial.print("Terhubung ke ");
    char buff[50];
    ssid.toCharArray(buff , 50);
    Serial.println(buff);
    // Mulai Server
    server.begin();
    Serial.print("Socket terhubung :");
    Serial.print(WiFi.softAPIP());
    Serial.print(" port ");
    Serial.println(port);
}
void Wifi_STA_Start(bool _hotchange )
{
    delay(1000);
    if (_hotchange)
    {
        client.stop();
        server.close();
        Serial.println("Client terputus karena pergantian mode"); 
    }
    // Cek data di EEPROM
    eeprom_read_str(0 , 50 , stassid);
    eeprom_read_str(50 , 50 , stapassword);
    String ssidprint = stassid;
    // Start wifi station;
    WiFi.mode(WIFI_STA);
    WiFi.begin(stassid , stapassword);
    // Wait for connection 
    int conn_timeout = 30;
    int conn_counter = 0;
    bool sta_fail = false ;
    Serial.print("Menghubungkan to Wifi AP");
    while (WiFi.status() != WL_CONNECTED) {   
        delay(500);
        Serial.print(".");
        delay(500);
        conn_counter++;
        if (conn_counter >= conn_timeout){
            sta_fail = true;
            break;
        }
    }

    if (sta_fail)
    {
        Serial.println();
        Serial.println("Gagal terhubung ke wifi");
        Serial.println("Masuk ke mode Hotspot (AP)...");
        Wifi_AP_Start(false);
    }
    else
    {
        Serial.println("");
        Serial.print("Terhubung ke ");
        Serial.println(ssidprint);
        // Mulai server
        server.begin();
        Serial.print("Server terhubung : ");
        Serial.print(WiFi.localIP());
        Serial.print(" port ");
        Serial.println(port);
        // Check
        wifi_changed = false;
    }
}

void Reset_wifi()
{

}
void blink_led(int _ledPin , int _interval)
{
    unsigned long currentMillis = millis();
    static unsigned long previousMillis;
    static int ledState;
    if (currentMillis - previousMillis >= _interval) 
    {
        // save the last time you blinked the LED
        previousMillis = currentMillis;

        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
        ledState = HIGH;
        } else {
        ledState = LOW;
        }
        // set the LED with the ledState of the variable:
        digitalWrite(_ledPin, ledState);
  }
}
// EEPROM Operation
// write string to eeprom
void eeprom_write_str(uint16_t startAdd , uint16_t lenght , String src)
{
  int i = 0;
  for ( i = 0 ; i<lenght ; i++)
  {
    EEPROM.write(startAdd+i, src[i]);
  }
}

void eeprom_read_str(int startAdd , uint16_t lenght , String dest)
{
  int i = 0;
  for ( i = 0 ; i<lenght ; i++)
  {
    dest[i] = EEPROM.read(startAdd+i);
  }
}

// Setup program---------------------------------------------------------------------------------------
void setup()
{
    bool Reset_mode = false;
    Serial.begin(115200);
    // Setup pin rest;
    pinMode(RESET_PIN , INPUT_PULLUP);
    pinMode(LED_PIN , OUTPUT);

    // Loop cek tombol reset selama  5 detik
    int timeout = 5000;
    int counter_main = 0;
    int counter_pressed = 0;
    Serial.println("Cek tombol reset...");
    while (true)
    {
        // Hitung counter ditekan atau tidak ditekan
        if (!digitalRead(RESET_PIN)){
            counter_pressed++;
            counter_main = 0;} 
        else {
            counter_pressed = 0;
            counter_main++; }
        // Cek timeout
        if (counter_main >= timeout){
            Reset_mode = false; // Tombol tidak ditekan
            Serial.println("Tombol reset tidak ditekan.");
            break;
        } 
        else if (counter_pressed >= timeout) {
            Reset_mode = true; // Tombol ditekan
            Serial.println("Tombol reset ditekan.");
            break;
        }
        delay(1); // delay 1 ms
    }

    // Jika tombol ditekan
    if (Reset_mode) {
        Reset_wifi();
        Wifi_AP_Start(false);
    }
    else {
        Wifi_STA_Start(false);
    }

    // Begin listening to UDP port
    IsUDP.begin(UDP_PORT);
    Serial.print("Listening on UDP port ");
    Serial.println(UDP_PORT);
    
}


// Loop program --------------------------------------------------------------------------------------
void loop()
{
    Config_handle();
    UDP_handle();

    // main program
    blink_led(LED_PIN , 100);
}

// UDP Handle...
void UDP_handle()
{
    // If packet received...
    int packetSize = IsUDP.parsePacket();
    if (packetSize)
    {
        //Serial.print("Received packet! Size: ");
        //Serial.println(packetSize); 
        int len = IsUDP.read(packet, 15);
        if (len > 0)
        {
            packet[len] = '\0';
        }
        Serial.println("UDP Diterima.");
        const char *packetcs = packet;
        if(strcmp (packetcs , discoverykey) == 0)
        {
            // Send return packet
            Serial.println("Discovery Key OK");
            IsUDP.beginPacket(IsUDP.remoteIP(), R_UDP_PORT);
            Serial.println(IsUDP.remoteIP()); // Debug Only
            Serial.println(IsUDP.remotePort()); // Debug Only
            IsUDP.write("OK%s%");
            IsUDP.write(DEV_NAME);
            delay(10);
            IsUDP.endPacket();
        }
        
    }
}
//TCP Handle...........
void Config_handle()
{
    client = server.available();
    // Jika client terhubung
    if (client) 
    {
        if(client.connected()) {
            Serial.println("Client Terhubung.");
        }
    
        while(client.connected())
        {
            digitalWrite(LED_PIN , LOW);
            int i = 0;     
            while(client.available()>0)
            {
                // read data from the connected client
                rawjson[i] = client.read();
                i++;
            }
            
            if (rawjson[i-1]!= 0)
            {
                // Deserialize the JSON document
                DeserializationError error = deserializeJson(jsondoc, rawjson);

                // Test if parsing succeeds.
                if (!error) 
                {
                    // TCP key OK
                    Serial.println("TCP Data OK.");
                    // Extract Header from Jsondoc
                    const char* apikey = jsondoc[0]["apikey"];
                    int fcode = jsondoc[0]["fcode"];
                    int length = jsondoc[0]["length"];
                    
                    // Start decoding json
                    decode_jsondoc(apikey , fcode , length);
                    // Clear Buffer-----
                    memset(&rawjson, 0 , i);
                }
                else
                {
                    Serial.print(F("TCP Data Failed : "));
                    Serial.println(error.f_str());
                } 
            }
            
        }
        client.stop();
        Serial.println("Client Terputus.");  
           
    }
}

// Decode json berdasarkan function code dan jumlah data
void decode_jsondoc(const char *key , int _fcode , int _length)
{
    if(strcmp(key , defapikey)==0)
    {
        Serial.println("API Key OK.");
        switch (_fcode)
        {
        case 0 :
            // Cek device aja , kirim respon OK
            send_response(_fcode , 0 , "OK");
            break;
        case 20 :
            {
                // Ekstrak data dari json document
                String r_ssid = jsondoc[1]["ssid"];
                String r_pass = jsondoc[1]["pass"];
                // Simpan ke variabel local
                stassid = r_ssid;
                stapassword = r_pass;
                // Simpan ke eeprom
                eeprom_write_str(0 , 50 , stassid);
                eeprom_write_str(50 , 50 , stapassword);
                // Beritahu bahwa wifi seting berubah
                wifi_changed = true;
                // kirim respon ke wifi client
                send_response(_fcode , 0 , "STA SSID & Pass set OK");
                break;
            }
            
        case 21 :
            if (WiFi.getMode() != WIFI_STA || wifi_changed)
            {
                send_response(_fcode , 2 , "Starting STA Mode...");
                Wifi_STA_Start(true);
            }
            else
            {
                send_response(_fcode , 2 , "Already STA Mode.");
            }
            
            break;
        }

    }
    else
    {
        send_response(_fcode , 1 , "Invalid key");
    }
}

// Buat response OK
void send_response(int _fcode , int _ercode , const char* _message)
{
    StaticJsonDocument<512> resdoc;
    resdoc[0]["fcode"]=_fcode;
    resdoc[1]["stat"] = _ercode ;
    resdoc[1]["message"] = _message;

    serializeJsonPretty(resdoc, client);

}