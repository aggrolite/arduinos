#include <SimpleDHT.h>
#include <LiquidCrystal.h>

#define trigPin 10
#define echoPin 13
#define dhtPin 9
#define greenLED 8
#define yellowLED 7
#define redLED 6
#define offset 3

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

SimpleDHT11 dht;

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Setting up...");
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

void lightRedLED()
{
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
}

void lightYellowLED()
{
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
}

void lightGreenLED()
{
  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
}

void printDistance(float distance)
{
  lcd.clear();
  lcd.print("Distance");
  lcd.setCursor(0,1);

  if (distance >= 400 || distance <= 2) {
    lcd.print("Out of range");
    lightRedLED();
  } else if (distance > 100) {
    lightYellowLED();
    lcd.print(distance);
    lcd.print("cm");
  } else {
    lightGreenLED();
    lcd.print(distance);
    lcd.print("cm");
  }
}

void printDHTResults(int t, int h)
{
  Serial.print("Sample OK: ");
  Serial.print(t);
  Serial.print(" *C, ");
  Serial.print(h);
  Serial.println(" %");
}

void loop()
{
  byte temperature = 0;
  byte humidity = 0;
  if (dht.read(dhtPin, &temperature, &humidity, NULL)) {
    Serial.println("Read DHT11 failed.");
    return;
  }
  printDHTResults((int)temperature, (int)humidity);

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  float duration = pulseIn(echoPin, HIGH);
  float spdSnd = 331.4 + (0.606 * (int)temperature) + 0.0124 * (int)humidity;
  float distance = (duration / 2) * (spdSnd / 10000);

  distance += offset;
  
  printDistance(distance);
  delay(500);
}
