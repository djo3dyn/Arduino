#include <ThingerESP8266.h>

#define USERNAME "djo3dyn"
#define DEVICE_ID "esp01"
#define DEVICE_CREDENTIAL "5v2NaUp6dvlp"

#define SSID "JUD_CONNECT"
#define SSID_PASSWORD "1sampai100"

unsigned long myvar ;
//string myStr ;

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);



void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  /*
  thing["led"] << [](pson& in){
  digitalWrite(2, in ? HIGH : LOW);
  };
  */

  thing["led_1"] << digitalPin(2);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());

  thing["test_var_in"] << [](pson& in){
    myvar = in ;
  };

  thing["test_var_out"] >> [](pson& out){
    out = myvar ;
  };



}

void loop() {
  thing.handle();
}
