#include <Servo.h>

// Servos
#define COM_PIN 7
#define SERVO_PIN 3
#define latchOpenValue 90
#define latchClosedValue 0
Servo latch;
bool latchOpen = true;

void setup() {
  Serial.begin(9600);
  latch.attach(SERVO_PIN);
  pinMode(COM_PIN, INPUT);
}

void loop() {
  if (latchOpen != digitalRead(COM_PIN) == HIGH) {
    latchOpen = digitalRead(COM_PIN) == HIGH;
    updateLatch();
  }
}

void updateLatch() {
  latch.write(latchOpen ? latchOpenValue : latchClosedValue);
}
