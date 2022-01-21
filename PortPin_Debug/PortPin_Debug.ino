
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void debug() {
  Serial.print("PINB : ");
  Serial.println(PINB , BIN);
  Serial.print("PORTB : ");
  Serial.println(PORTB , BIN);
  Serial.print("DDRB : ");
  Serial.println(DDRB , BIN);
  Serial.println();
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  debug();
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  debug();
  delay(1000);                       // wait for a second
}
