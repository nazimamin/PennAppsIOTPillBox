#include <Time.h>

#include <Time.h>

/**
Code for the hackathon IoT Pill box
By Nazim Amin and Matthew Del Signore
**/

int resistorValue; //the value we get from the photoresistor
int currentLED; //the led that should be blinking for the current day

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
  
  //load all the pin for led's as output
   for(int k=2;k<9;k++){ //turn off all the 
    pinMode(k,OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly: 
  
  /*resistorValue = analogRead(0); //read in analog input at point 0
  Serial.print(resistorValue);
  Serial.print(" "); */
  
  Serial.print("the current date is");
  Serial.print(day(now()));
  Serial.print("\n");
  
  currentLED = day(now()) +1; //get the current day and subtract one to get the right pwm slot
  
  for(int k=2;k<9 ;k++){ //turn off all the 
  if(k!=currentLED)
    digitalWrite(k,LOW);
  }
  
  //turn on only the led for the current day
  digitalWrite(currentLED,HIGH);
  
  //wait 5 s
  delay(5000);
}
