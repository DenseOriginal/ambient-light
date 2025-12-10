
// Servos
#define COM_PIN 5
bool latchOpen = true;

// Z-Limit switch
#define CONTACT_PIN 3
bool contactPressed = false;
bool contactChanged = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 20;

void setupLatch() {
  pinMode(CONTACT_PIN, INPUT_PULLUP);
  pinMode(COM_PIN, OUTPUT);
}

bool _contactState = false;
void checkContact() {
  contactChanged = false;
  bool currentState = digitalRead(CONTACT_PIN) == LOW;

  if (currentState != _contactState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentState != contactPressed) {
      contactPressed = currentState;
      contactChanged = true;

      if (contactPressed) {
        onContactPressed();
      } else {
        onContactReleased();
      }
    }
  }

  _contactState = currentState;
}

void updateLatch() {
  digitalWrite(COM_PIN, latchOpen ? HIGH : LOW);
}

void unLatch() {
  latchOpen = true;
  updateLatch();
}
