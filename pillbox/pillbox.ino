
#include <Dhcp.h>
#include <Dns.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <Time.h>


/**
Code for the hackathon IoT Pill box
By Nazim Amin and Matthew Del Signore
**/

int resistorValue; //the value we get from the photoresistor
int currentLED=0; //the led that should be blinking for the current day
int threshold = 300; //the threshold of whether or not a pill box is filled
int openedThreshold  = 80; //threshold for if the box is opened
boolean filled[7]; //and array of which compartment is filled and which isn't
boolean boxopened = false;  //whether or not the box is open

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
  // put your main code here, to run repeatedly
  
  boxopened = false;
  //start the client 

    
  /*resistorValue = analogRead(0); //read in analog input at point 0
  Serial.print(resistorValue);
  Serial.print(" "); */
  
  Serial.print("the current date is");
  Serial.print(day(now()));
  Serial.print("\n");
  
  currentLED = day(now()) +1; //get the current day and subtract one to get the right pwm slot
  
  Serial.print(currentLED);
  
  //check to see if the box is opened
  for(int k=0; k<7;k++){
    if(analogRead(k)>openedThreshold){
      //boxopened == true;
    }
  }
  
  if(boxopened == false){
  for(int k=2;k<9 ;k++){ //turn on all the leds 
    digitalWrite(k,HIGH);
  }
  
  //now check to see which compartments are filled
  for(int k=0; k<6;k++){
    if(analogRead(k)<threshold){
      filled[k] = true;
    }
  }
  /**
  if(client){ //if there is a client
    Serial.println("new client connected");
    
    String clientMessage = "";
    
    while(client.connected()){
      boolean newLine = true;
      if(client.available()){ //if the client is sending data
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && newLine) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json"); //send a json file
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          

          client.println("{");
          
          //loop through and print out the status of each compartment
          for(int k = 0; k<7;k++){
             client.print("\" ");
            client.print(k);
            client.print("\" ");
            client.print(" : ");
            if(filled[k]){
              client.print(" \"true\"");
            }else{
              client.print(" \"false\"");
            }
            
            client.println("}");
          }
          
         
           break;
        }
        
        if (c == '\n') {
          // you're starting a new line
          newLine = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          newLine = false;
        }
      }
    }
    
    delay(1);
    client.stop(); //disconnect the client
    Serial.println("client disconnected");
  }**/
  
  //wait 5 s
  delay(5);
  }else{
    //if the box is opened then only turn on the light of the current day
    currentLED = day(now())+1;  //TODO: check that this value is correct
    digitalWrite(currentLED, HIGH);
  }
}

