/*

Makes noise on the buzzer.

*/

#define buzzPin 8

void setup()
{
  Serial.begin(9600);
  pinMode(buzzPin, OUTPUT);
}

void loop()
{
  tone(buzzPin, 400, 25);
  delay(50);
  tone(buzzPin, 300, 25);
  delay(50);
  tone(buzzPin, 400, 25);
  delay(50);
  tone(buzzPin, 300, 25);
  delay(50);
  tone(buzzPin, 500, 25);
  delay(50);
  tone(buzzPin, 400, 25);
  delay(50);
  tone(buzzPin, 500, 25);
  delay(50);
  tone(buzzPin, 400, 25);
  delay(50);
  tone(buzzPin, 600, 25);
  delay(50);
  tone(buzzPin, 500, 25);
  delay(50);
  tone(buzzPin, 600, 25);
  delay(50);
  tone(buzzPin, 500, 25);
  delay(50);
  tone(buzzPin, 700, 25);
  delay(50);
  tone(buzzPin, 600, 25);
  delay(50);
  tone(buzzPin, 700, 25);
  delay(50);
  tone(buzzPin, 600, 25);
  delay(50);
}
