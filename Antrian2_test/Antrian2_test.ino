class Func {
  public : 
  static void sayhelo()
  {
    Serial.println("Heloo...");
  }
};

Func test;
void setup() {
  Serial.begin(9600);

}

void loop() {
 test.sayhelo();
 delay(1000);
  

}
