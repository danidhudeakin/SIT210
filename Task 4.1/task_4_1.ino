#include <Wire.h>
#include <BH1750.h>

#define PIR_PIN 2
#define SWITCH_PIN 3
#define LED1_PIN 11
#define LED2_PIN 12

BH1750 lightMeter;

volatile bool motionInterruptFlag = false;
volatile bool switchInterruptFlag = false;

const float LIGHT_THRESHOLD = 50.0;   // adjust if needed
unsigned long lastSwitchInterrupt = 0;
unsigned long lastMotionInterrupt = 0;

void motionISR() {
  unsigned long currentTime = millis();
  if (currentTime - lastMotionInterrupt > 1000) {   // simple cooldown
    motionInterruptFlag = true;
    lastMotionInterrupt = currentTime;
  }
}

void switchISR() {
  unsigned long currentTime = millis();
  if (currentTime - lastSwitchInterrupt > 300) {    // debounce
    switchInterruptFlag = true;
    lastSwitchInterrupt = currentTime;
  }
}

void setup() {
  Serial.begin(9600);
  delay(1500);

  setupPins();
  setupLightSensor();
  setupInterrupts();

  Serial.println("System ready...");
}

void loop() {
  float lux = readLightLevel();
  printLightLevel(lux);

  handleMotionInterrupt(lux);
  handleSwitchInterrupt();

  delay(200);
}

void setupPins() {
  pinMode(PIR_PIN, INPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void setupLightSensor() {
  Wire.begin();
  if (lightMeter.begin()) {
    Serial.println("BH1750 started successfully");
  } else {
    Serial.println("BH1750 not found");
  }
}

void setupInterrupts() {
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), motionISR, RISING);
  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), switchISR, FALLING);
}

float readLightLevel() {
  float lux = lightMeter.readLightLevel();

  if (lux < 0) {
    Serial.println("Failed to read BH1750");
    return 0;
  }

  return lux;
}

void printLightLevel(float lux) {
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
}

void handleMotionInterrupt(float lux) {
  if (motionInterruptFlag) {
    motionInterruptFlag = false;

    Serial.println("Motion detected!");

    if (lux < LIGHT_THRESHOLD) {
      Serial.println("It is dark. Toggling LED1 and LED2.");
      toggleLights();
    } else {
      Serial.println("It is bright. Lights remain unchanged.");
    }
  }
}

void handleSwitchInterrupt() {
  if (switchInterruptFlag) {
    switchInterruptFlag = false;

    Serial.println("Slider switch activated. Toggling LED1 and LED2.");
    toggleLights();
  }
}

void toggleLights() {
  digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));
  digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));
}
