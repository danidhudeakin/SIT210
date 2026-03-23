#include <WiFiNINA.h>
#include <Wire.h>
#include <BH1750.h>

char ssid[] = "Saniky_38";
char pass[] = "sanikypisso";

WiFiSSLClient client;
BH1750 lightMeter;

// Change this if needed after testing
const float LIGHT_THRESHOLD = 100.0;

// Keeps track of previous light state
bool sunlightPresent = false;

const char IFTTT_HOST[] = "maker.ifttt.com";
const char IFTTT_KEY[] = "pzAonBUCdvJ9ehc-vOCW8ae-gHYCHhBBiMPt63ZDKQS";

void connectWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, pass);
    delay(5000);
    Serial.println(" retrying");
  }
  Serial.println("WiFi connected");
}

void triggerIFTTT(const char* eventName) {
  Serial.print("Triggering IFTTT event: ");
  Serial.println(eventName);

  if (client.connect(IFTTT_HOST, 443)) {
    client.print("GET /trigger/");
    client.print(eventName);
    client.print("/with/key/");
    client.print(IFTTT_KEY);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(IFTTT_HOST);
    client.println("Connection: close");
    client.println();

    delay(1000);

    while (client.available()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);
    }

    client.stop();
    Serial.println("IFTTT request sent");
  } else {
    Serial.println("Failed to connect to IFTTT");
  }
}

void setup() {
  Serial.begin(9600);
  delay(1500);

  Wire.begin();
  if (!lightMeter.begin()) {
    Serial.println("BH1750 not found");
  } else {
    Serial.println("BH1750 started");
  }

  connectWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  float lux = lightMeter.readLightLevel();

  Serial.print("Light Level: ");
  Serial.print(lux);
  Serial.println(" lx");

  if (lux >= LIGHT_THRESHOLD && !sunlightPresent) {
    sunlightPresent = true;
    Serial.println("Sunlight started");
    triggerIFTTT("sunlight_started");
  }
  else if (lux < LIGHT_THRESHOLD && sunlightPresent) {
    sunlightPresent = false;
    Serial.println("Sunlight stopped");
    triggerIFTTT("sunlight_stopped");
  }

  delay(5000);
}