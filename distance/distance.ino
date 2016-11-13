#include <SimpleDHT.h>
#include <LiquidCrystal.h>

#define trigPin 10
#define echoPin 13
#define dhtPin 0
#define greenLED 8
#define yellowLED 7
#define redLED 6

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

double getTemp(int raw)
{
  double temp;
  temp = log(10000.0*((1024.0/raw-1))); 
  temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp ))* temp );
  temp = temp - 273.15;          
  return temp;
}

void loop()
{
  float duration, distance, spdSnd;
  double temp;
  temp = getTemp(analogRead(5));
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  spdSnd = 331.4 + (0.606 * temp) + 0.62;
  distance = (duration / 2) * (spdSnd / 10000);
  
  printDistance(distance);
  delay(500);
}
