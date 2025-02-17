#include <LiquidCrystal.h>  
//#include <SoftwareSerial.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);   //LCD :  (rs, enable, d4, d5, d6, d7)
//SoftwareSerial mySerial(2, 3); // RX, TX

const int trigPin = 12; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 11; // Echo Pin of Ultrasonic Sensor

void setup() 
{
Serial.begin(9600); // Starting Serial Terminal
//mySerial.begin(9600);

lcd.begin(16,2);                                                   
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
lcd.setCursor(0,0);
lcd.print("  Fuel    ");
Serial.print("  Fuel    ");
lcd.setCursor(0,1);
lcd.print("  Level  ");
Serial.print("  Level  ");
delay(1000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Made By : ");
delay(1000);
Serial.print("Made By :");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("BUZEE");

Serial.print(" BUZEE  ");
delay(2000);
lcd.clear();

}

void loop()
{
  long duration, inches, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
//  Serial.print(inches);
//  Serial.print("in, ");

unsigned int fuel0, fuel1, distance_km;
fuel0 = cm / 8.57;
fuel1 = 34 - fuel0;
distance_km = fuel0 * 14;

Serial.print("Litre:");
  Serial.print(fuel0);
  Serial.print("LTR");
  delay(100);
  Serial.println();
 
lcd.setCursor(0,0);
lcd.print("Litre:");
lcd.print(fuel0);
lcd.print("LTR");
delay(10);
lcd.setCursor(0,1);
lcd.print("KM:");
lcd.print(distance_km);
lcd.print(" km");
delay(100);
}

long microsecondsToInches(long microseconds)
{
 return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
   return microseconds / 29 / 2;
}
