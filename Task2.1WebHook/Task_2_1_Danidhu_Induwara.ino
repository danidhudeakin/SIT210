#include <WiFiNINA.h>
#include <ThingSpeak.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>

#define DHTPIN 2
#define DHTTYPE DHT11

char ssid[] = "Saniky_38";
char pass[] = "sanikypisso";

unsigned long channelID = 3308270;
const char *writeAPIKey = "KT39EC75COJJ3N8W";

WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

void connectWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    delay(5000);
  }
}

void setup() {
  Serial.begin(9600);
  delay(1500);

  Wire.begin();
  dht.begin();
  lightMeter.begin();

  connectWiFi();
  ThingSpeak.begin(client);

  Serial.println("System started");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Reconnecting...");
    connectWiFi();
  }

  float temperature = dht.readTemperature();
  float lightLevel = lightMeter.readLightLevel();

  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  }

  if (lightLevel < 0) {
    Serial.println("Failed to read from BH1750 sensor");
  } else {
    Serial.print("Light: ");
    Serial.print(lightLevel);
    Serial.println(" lx");
  }

  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, lightLevel);

  int statusCode = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (statusCode == 200) {
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    Serial.print("ThingSpeak error code: ");
    Serial.println(statusCode);
  }

  Serial.println("Waiting 30 seconds...\n");
  delay(30000);
}