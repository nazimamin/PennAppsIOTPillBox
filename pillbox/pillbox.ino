#include <Time.h>

#include <Time.h>

/**
Code for the hackathon IoT Pill box
By Nazim Amin and Matthew Del Signore
**/

int resistorValue; //the value we get from the photoresistor

int SUNDAY = 0; //PWM slot for the LED for sunday
int MONDAY = 1;
int TUESDAY = 2;
int WEDNESDAY = 3;
int THURSDAY = 4;
int FRIDAY =  5;
int SATURDAY = 6;

void setup() {
  //start reading serial data
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly: 
  
  /*resistorValue = analogRead(0); //read in analog input at point 0
  Serial.print(resistorValue);
  Serial.print(" "); */
  
  Serial.print("the current date is");
  Serial.print(day(now()));
  Serial.print("\n");
  
  //wait 100ms
  delay(100);
}
