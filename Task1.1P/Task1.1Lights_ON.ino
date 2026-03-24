const int porchLight = 13;    // built-in LED
const int hallwayLight = 12;  // external LED
const int buttonPin = 4;      // switch

void setup() {
  setupPins();
}

void loop() { //I have seperated my code into different modules
  if (isButtonPressed()) {
    runLightingSequence();
    waitForButtonRelease();
  }
}

void setupPins() {
  pinMode(porchLight, OUTPUT);
  pinMode(hallwayLight, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

bool isButtonPressed() {
  return digitalRead(buttonPin) == LOW;
}

void turnLightsOn() {
  digitalWrite(porchLight, HIGH);
  digitalWrite(hallwayLight, HIGH);
}

void turnPorchLightOff() {
  digitalWrite(porchLight, LOW);
}

void turnHallwayLightOff() {
  digitalWrite(hallwayLight, LOW);
}

void waitForThirtySeconds() {
  delay(30000);
}

void waitForButtonRelease() {
  while (digitalRead(buttonPin) == LOW) {
    delay(10);
  }
}

void runLightingSequence() {
  turnLightsOn();
  waitForThirtySeconds();
  turnPorchLightOff();
  waitForThirtySeconds();
  turnHallwayLightOff();
}
