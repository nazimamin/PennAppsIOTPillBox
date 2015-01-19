
#include <Dhcp.h>
#include <Dns.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <SPI.h>
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

char ssid[] = "pennpillbox";      // SSID (name) 
char pass[] = "12345678";   // network password
int keyIndex = 0;                 // network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
//WiFiServer server("http://pillbox.ngrok.com/api/updateStatus", 80);

char server[] = "http://pillbox.ngrok.com/api/updateStatus"; //the server we will connect to
WiFiClient client;

void setup() {
  //start reading serial data
  Serial.begin(9600);
  
  //load all the pin for led's as output
   for(int k=2;k<9;k++){ //turn off all the 
    pinMode(k,OUTPUT);
  }
  
   // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    while(true);        // don't continue
  } 

  String fv = WiFi.firmwareVersion();
  if( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  } 
 // server.begin();                           // start the web server on port 80


  printWifiStatus();                        // you're connected now, so print out the status

}
void loop() {
  // put your main code here, to run repeatedly: 
  
  boxopened = false;
  
  /*resistorValue = analogRead(0); //read in analog input at point 0
  Serial.print(resistorValue);
  Serial.print(" "); */
  
  Serial.print("the current date is: ");
  Serial.print(day(now()));
  Serial.print(". Current LED Is: ");
  
  currentLED = day(now()) +1; //get the current day and subtract one to get the right pwm slot
  
  Serial.print(currentLED);
  Serial.print('\n');
  
  //check to see if the box is opened
  for(int k=0; k<7;k++){
    if(analogRead(k)>openedThreshold){
      boxopened == true;
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
  
  if(client.connect(server, 80)){ //if there is a client
    Serial.println("client server connected");
    
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
          client.println("POST /api/updateStatus HTTP/1.1");
          client.println("Host: pillbox.ngrok.com"); 
          client.println("Cache-control: no-cache");
          client.println("Content-Type: application/x-www-form-urlencoded"); //send a json file

          String message = "email=erickim213%40gmail.com&pillbox=%5B+";
          for (int i = 0; i < 6; i++) {
            message += filled[i] + "%2C+";
          }
          message += filled[6] + "+%5D";

          client.println(message);  // the connection will be closed after completion of the response
        
      }
    }
    
    delay(1);
    client.stop(); //disconnect the client
    Serial.println("client disconnected");
  }
  //wait 5 s
  delay(5);
  }else{
    //if the box is opened then only turn on the light of the current day
    currentLED = day(now())+1;  //TODO: check that this value is correct
    digitalWrite(currentLED, HIGH);
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
