/*
 - Online Temperature dan Humidity Monitor
 - Dengan Sensor DTH11
 - Koneksi internet dengan WiFi
 - Menggunakan Protocol HTTP POST request
 - Script Server dengan PHP
 - Database mySQL

*/

//Include WiFi
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
//Define Sensor
#include <dht11.h>

//Define
#define DHT11PIN 4


String apiKey = "fdbclkmdcv"; 
String sensorName = "DTH11";
String sensorLocation = "Kontrakan";
float temp ;
float humd ;

dht11 DHT11;
 
void setup() {
 
  Serial.begin(115200);                         //Serial connection
  WiFi.begin("JUD_CONNECT", "1sampai100");      //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED)         //Wait for the WiFI connection completion
  {  
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
 
}
 
void loop() {

  int chk = DHT11.read(DHT11PIN);
  temp = DHT11.temperature;
  humd = DHT11.humidity;
 
 if(WiFi.status()== WL_CONNECTED){                                       //Check WiFi connection status
 
   HTTPClient http;                                                      //Declare object of class HTTPClient
   http.begin("http://judin.000webhostapp.com/iot/dth_post.php");    //Specify request destination
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header

   String postdata =  "key=" + apiKey +
                      "&sensname=" + sensorName +
                      "&loc=" + sensorLocation +
                      "&tem=" + String(temp) +
                      "&hum=" + String(humd);

   int httpCode = http.POST(postdata);                            //Send the request
   String payload = http.getString();                                     //Get the response payload
 
   Serial.println(httpCode);                                              //Print HTTP return code
   Serial.println(payload);                                               //Print request response payload
 
   http.end();                                                            //Close connection
 
 }
 else
 {
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(60000);   //Send a request every 30 seconds
 
}
