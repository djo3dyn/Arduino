
int count;
void setup() {
  Serial.begin(9600);

}

void loop() {
  count++;
  Serial.println(count);
  delay(1000);

}
