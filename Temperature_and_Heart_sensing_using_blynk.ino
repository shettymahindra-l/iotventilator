/***************************************************
 * IoT Health Monitor: ESP8266 + Blynk + DHT + MAX30100
 * Sensors:
 *   - DHT11/22 → Temperature & Humidity
 *   - MAX30100 → Heart Rate & SpO2
 * 
 * Mobile App:
 *   - Blynk app (virtual pins for data display)
 ***************************************************/

// Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include "MAX30100_PulseOximeter.h"

// WiFi & Blynk auth
char auth[] = "Your_Blynk_Auth_Token";   // Enter Blynk Auth Token
char ssid[] = "Your_WiFi_SSID";          // Enter WiFi SSID
char pass[] = "Your_WiFi_Password";      // Enter WiFi Password

// DHT setup
#define DHTPIN D4       // DHT sensor connected to GPIO D4
#define DHTTYPE DHT11   // or DHT22
DHT dht(DHTPIN, DHTTYPE);

// MAX30100 setup
PulseOximeter pox;
uint32_t tsLastReport = 0;

// Variables
float temperature, humidity, heartRate, spo2;

#define REPORTING_PERIOD_MS 1000

// Callback for heartbeat detection
void onBeatDetected() {
  Serial.println("Beat detected!");
}

void setup() {
  Serial.begin(115200);

  // Blynk + WiFi setup
  Blynk.begin(auth, ssid, pass);

  // DHT sensor init
  dht.begin();

  // MAX30100 init
  if (!pox.begin()) {
    Serial.println("FAILED to initialize MAX30100. Check wiring!");
    for(;;);
  } else {
    Serial.println("MAX30100 Initialized.");
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  Blynk.run();
  pox.update(); // Update MAX30100 readings

  // Every 1 second, read and send data
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    tsLastReport = millis();

    // DHT sensor readings
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    // MAX30100 readings
    heartRate = pox.getHeartRate();
    spo2 = pox.getSpO2();

    // Print to Serial Monitor
    Serial.print("Temp: "); Serial.print(temperature);
    Serial.print(" *C | Hum: "); Serial.print(humidity);
    Serial.print(" % | HR: "); Serial.print(heartRate);
    Serial.print(" bpm | SpO2: "); Serial.print(spo2);
    Serial.println(" %");

    // Send to Blynk app
    Blynk.virtualWrite(V1, temperature); // Virtual Pin V1 → Temperature
    Blynk.virtualWrite(V2, humidity);    // Virtual Pin V2 → Humidity
    Blynk.virtualWrite(V3, heartRate);   // Virtual Pin V3 → Heart Rate
    Blynk.virtualWrite(V4, spo2);        // Virtual Pin V4 → SpO2
  }
}
