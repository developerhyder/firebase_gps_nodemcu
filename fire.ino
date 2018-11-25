#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
void con(float lati,float longi);
TinyGPSPlus gps;
// The TinyGPS++ object
#define FIREBASE_HOST "YOUR-FIREBASE-DETAILS"
#define FIREBASE_AUTH "YOUR-FIREBASE-DETAILS"

float latitude , longitude;

const char* ssid = "YOUR-WIFI-SSID";
const char* password = "PASSWORD-WIFI";
SoftwareSerial ss(4, 5);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ss.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(ss.available()  > 0)
  if(gps.encode(ss.read())){
    if(gps.location.isValid()){
      Serial.println(gps.location.lat());
      latitude = gps.location.lat();
      Serial.println(gps.location.lng());
      longitude = gps.location.lng();
      con(latitude,longitude);
    }
  }
   
}
void con(float lati,float longi){
   Firebase.setFloat("lat",lati);
   Firebase.setFloat("lng",longi);
   delay(4000);
   Firebase.remove("lat");
   Firebase.remove("lng");
}
