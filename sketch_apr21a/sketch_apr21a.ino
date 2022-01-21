unsigned long trig_millis;
bool stat = false;
bool stat2 = false;
void setup() {

  pinMode(2, INPUT);
  Serial.begin(9600);
}
void loop() {

  unsigned long curr_millis=millis();
  Serial.print("Time: ");
  if (digitalRead(2) == LOW)
  {
    if (stat == false)
    {
      trig_millis = millis();
      stat = true;
    }
    if ((curr_millis-trig_millis)>=5000 && stat2 == false)
    {
    Serial.println("yeeeesssssssssssssssssss");
    stat2 = true;
    }
  }
  else if (digitalRead(2)==HIGH)
  {
     stat = false;
     stat2 = false;
  }
 
  Serial.println(trig_millis); //prints time since program started
  delay(1000);          // wait a second so as not to send massive amounts of data
}
