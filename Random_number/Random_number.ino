long randNumber;
int upcase;
char mychr[5];

void setup() {
  Serial.begin(9600);

}

void loop() {
  int i = 0;
   while (i<10)
   {
    upcase = random(0,2);
    if (upcase) {
      mychr[i] = (char) random(65,90);
    } else {
      mychr[i] = (char) random(97,122);
    }
    i++;
   }
   Serial.println(mychr);
  // print a random number from 0 to 299
   //= random(300);
 // Serial.println(randNumber);

  // print a random number from 10 to 19
  //randNumber = random(10, 20);
 // Serial.println(randNumber);

  delay(1000);
}
