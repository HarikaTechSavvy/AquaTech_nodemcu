#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "arduino-5aec2.firebaseio.com"
#define FIREBASE_AUTH "MqS4DKcNfMnY77JLiyxihAZRmmRU3L3I9rVR6oCX"
#define WIFI_SSID "R"
#define WIFI_PASSWORD "riddu1234"

void setup() {
  Serial.begin(9600);// put your setup code here, to run once:
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {
  int value = analogRead(A0);
  float voltage =  value * (3.3 / 1023.0);
  Serial.println("Analog reading is :");
  Serial.println(value);
  Serial.println("Conductivity is : ");
  Serial.println(voltage);
  Firebase.setInt("analog", value);
   if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Firebase.setFloat("voltage", voltage);
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
}
