
#include <Servo.h>

Servo myServo;

const int SERVO_PIN = 9;
const int BUTTON_PIN = 7;

bool servoState = false;             // false = 0°, true = 180°
bool lastButtonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  myServo.attach(SERVO_PIN);
  myServo.write(0);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  bool reading = digitalRead(BUTTON_PIN);

  // If state changed, reset debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Check if stable for debounceDelay
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (lastButtonState == HIGH && reading == LOW) {
      servoState = !servoState;
      myServo.write(servoState ? 180 : 0);
    }
  }

  lastButtonState = reading;
}
