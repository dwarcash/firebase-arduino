
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "test.firebaseio.com" //Replace with your firebase realtime db host
#define FIREBASE_AUTH "REALTIME DB SECRET"  //Replace with your firebase realtime db secret key
#define WIFI_SSID "SSID"                    //Replace with your wifi name
#define WIFI_PASSWORD "PASS"                //Replace with your wifi password
const int trigger = 16;
const int echo = 5;
long T;
float distanceCM;

void setup() 
{
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  WiFi.mode(WIFI_STA);                                                  
               
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
 }
  
Serial.println();
Serial.print("Connected");
Serial.print("IP Address: ");
Serial.println(WiFi.localIP());                               //prints local IP address
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                 // connect to the firebase
 
}

void loop() 
{
  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  T = pulseIn(echo, HIGH);
  distanceCM = T * 0.034;
  distanceCM = distanceCM / 2;
  Serial.print("Distance in cm: ");
  Serial.println(distanceCM);
 
 
  Firebase.pushFloat("/", distanceCM);  

    if (Firebase.failed()) 
    {
 
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 
      return;
  }
}
