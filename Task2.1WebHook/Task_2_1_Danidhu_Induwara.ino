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

void setup() {
  Serial.begin(9600);
  delay(1500);

  setupSensors();
  connectWiFi();
  ThingSpeak.begin(client);

  Serial.println("System started");
}

void loop() {
  ensureWiFiConnected();

  float temperature = readTemperature();
  float lightLevel = readLightLevel();

  printSensorData(temperature, lightLevel);
  uploadToThingSpeak(temperature, lightLevel);

  Serial.println("Waiting 30 seconds...\n");
  delay(30000);
}

void setupSensors() {
  Wire.begin();
  dht.begin();
  lightMeter.begin();
}

void connectWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, pass);
    delay(5000);
  }
  Serial.println("WiFi connected");
}

void ensureWiFiConnected() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Reconnecting...");
    connectWiFi();
  }
}

float readTemperature() {
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor");
    return 0;
  }

  return temperature;
}

float readLightLevel() {
  float lightLevel = lightMeter.readLightLevel();

  if (lightLevel < 0) {
    Serial.println("Failed to read from BH1750 sensor");
    return 0;
  }

  return lightLevel;
}

void printSensorData(float temperature, float lightLevel) {
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Light: ");
  Serial.print(lightLevel);
  Serial.println(" lx");
}

void uploadToThingSpeak(float temperature, float lightLevel) {
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, lightLevel);

  int statusCode = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (statusCode == 200) {
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    Serial.print("ThingSpeak error code: ");
    Serial.println(statusCode);
  }
}
