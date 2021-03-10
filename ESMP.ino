volatile int flow_frequency; // Measures flow sensor pulses
// Calculated litres/hour
 float vol = 0.0,l_minute;
unsigned char flowsensor = 2; // Water Flow Sensor Input( connect to Digital 2 pin)
unsigned long currentTime;
unsigned long cloopTime;

#include <LiquidCrystal.h> //library for LCD
#include <Wire.h> //library for MPU6050
#include <MPU6050.h> //library for MPU6050

MPU6050 mpu; //declaring MPU6050 as mpu

LiquidCrystal lcd(12, 11, 5, 4, 3, 9); //LCD pin declaration

void flow () // Interrupt function for water flow
{
   flow_frequency++;
}

void setup()
{
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
   lcd.begin(16, 2);
   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("ESMP PROJECT");
   lcd.setCursor(0,1);
   lcd.print("By BUZEE");
   currentTime = millis();
   cloopTime = currentTime;
}

void loop ()
{
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
    cloopTime = currentTime; // Updates cloopTime
    if(flow_frequency != 0){
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      lcd.clear();
      l_minute = l_minute/60;
      lcd.setCursor(0,0);
      vol = vol +l_minute;
      lcd.print("Vol:");
      lcd.print(vol);
      lcd.print(" L");
      flow_frequency = 0; // Reset Counter
      Serial.print(l_minute, DEC); // Print litres/hour
      Serial.println(" L/Sec");
      
      float temp = mpu.readTemperature(); //reading temperature data
      float temp_c = ((temp)/340 + 36.53); //converting to celsius
      Serial.print(" Temp = ");
      Serial.print(temp_c);
      Serial.println(" *C"); //code segment to display on serial monitor

      lcd.setCursor(0,1);
      lcd.print("Temp:");
      lcd.print(temp_c);
      lcd.print(" *C"); //printing on LCD
  
      delay(500);
    }
    else {
      Serial.println(" flow rate = 0 ");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("No Flow Detected");
      lcd.setCursor(0,1);
      lcd.print("Please Try Again");
    }
   }
}
