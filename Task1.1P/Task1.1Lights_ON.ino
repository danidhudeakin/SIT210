const int porchLight = 13;    // built-in LED
const int hallwayLight = 12;  // external LED
const int buttonPin = 4;      // switch

void setup() {
  pinMode(porchLight, OUTPUT);
  pinMode(hallwayLight, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(porchLight, HIGH);
    digitalWrite(hallwayLight, HIGH);

    delay(30000);
    digitalWrite(porchLight, LOW);

    delay(30000);
    digitalWrite(hallwayLight, LOW);

    while (digitalRead(buttonPin) == LOW) {
      delay(10);
    }
  }
}
