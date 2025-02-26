#include <Arduino.h>
#include <WiFi.h>               // We are using the ESP32
//#include <ESP8266WiFi.h>      // Uncomment this line if you are using ESP8266 and comment the line above
#include <Firebase_ESP_Client.h>
#include <DHT.h>                // Install DHT library by Adafruit 1.3.8

#define DHT_SENSOR_PIN 4
#define DHT_SENSOR_TYPE DHT11

// To provide the ESP32 / ESP8266 with the connection and the sensor type
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Samsung A50"
#define WIFI_PASSWORD "00000000"

// Insert Firebase project API Key
#define API_KEY "AIzaSyAWoAHak0JPslTkonXGu8OsMZWNiwpjOYo"

// Insert RTDB URL
#define DATABASE_URL "https://dht11-realtime-data-default-rtdb.asia-southeast1.firebasedatabase.app/" 

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;  // Since we are doing an anonymous sign-in

void setup() {
  dht_sensor.begin();
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the API key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase signup successful.");
    signupOK = true;
  } else {
    Serial.printf("Firebase signup failed: %s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long-running token generation task */
  config.token_status_callback = tokenStatusCallback; // See addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  // Read temperature and humidity from the sensor
  float temperature = dht_sensor.readTemperature();
  float humidity = dht_sensor.readHumidity();
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    // Update data every second
    sendDataPrevMillis = millis();

    // Send Temperature data to Firebase
    if (Firebase.RTDB.setInt(&fbdo, "DHT_11/Temperature", temperature)) {
      Serial.print("Temperature: ");
      Serial.println(temperature);
    } else {
      Serial.println("Failed to send Temperature data.");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    // Send Humidity data to Firebase
    if (Firebase.RTDB.setFloat(&fbdo, "DHT_11/Humidity", humidity)) {
      Serial.print("Humidity: ");
      Serial.println(humidity);
    } else {
      Serial.println("Failed to send Humidity data.");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}
