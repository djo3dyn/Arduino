#include <ArduinoJson.h>

// Json Doc Temp
String jsondoc = R"(
[
  {
    "name": "Angga",
    "age": 26,
    "city": "Bekasi"
  },
  {
    "name": "Edward",
    "age": 29,
    "city": "Jakarta"
  },
  {
    "name": "Raju",
    "age": 21,
    "city": "Tangerang"
  },
  {
    "name": "Salma",
    "age": 19,
    "city": "Bandung"
  },
  {
    "name": "Albert",
    "age": 30,
    "city": "Medan"
  }
]
)";

void setup()
{
    // Initialize serial port
    Serial.begin(9600);
    while (!Serial) continue;

    // Json Doc
    StaticJsonDocument<600> doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, jsondoc);

    // Test if parsing succeeds.
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    // Fetch values.
    //
    // Most of the time, you can rely on the implicit casts.
    // In other case, you can do doc["time"].as<long>();

    
    while (1)
    {
        for (int i = 0 ; i<5 ; i++)
        {
            const char* name = doc[i]["name"];
            int age = doc[i]["age"];
            const char* city = doc[i]["city"];
            Serial.println(name);
            Serial.println(age);
            Serial.println(city);
            Serial.println();
            delay(1000);
        }
    }

}

void loop()
{
    
}

