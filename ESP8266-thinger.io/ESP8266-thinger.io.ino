#include <ThingerESP8266.h>

#define USERNAME "djo3dyn"
#define DEVICE_ID "esp01"
#define DEVICE_CREDENTIAL "TGYLmiLdXb79"

#define SSID "JUD_CONNECT"
#define SSID_PASSWORD "1sampai100"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);



void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);


  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led_0"] << invertedDigitalPin(0);
  thing["led_1"] << invertedDigitalPin(1);
  thing["led_2"] << invertedDigitalPin(2);
  thing["led_4"] << invertedDigitalPin(3);

  // resource output example (i.e. reading a sensor value)
  // thing["millis"] >> outputValue(millis());

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
}
