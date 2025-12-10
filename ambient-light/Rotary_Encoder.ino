// KY-040 rotary encoder
#define ENCODER_PIN_A 8    // CLK pin
#define ENCODER_PIN_B 9    // DT pin
#define ENCODER_BUTTON 10  // SW pin
int count = 14;
int encoderPinA_prev;
int encoderPinA_value;
bool bool_CW;
bool dialChanged = false;

void setupRotaryEncoder() {
  pinMode(ENCODER_PIN_A, INPUT);
  pinMode(ENCODER_PIN_B, INPUT);
  pinMode(ENCODER_BUTTON, INPUT_PULLUP);
  encoderPinA_prev = digitalRead(ENCODER_PIN_A);
}

void checkRotaryEncoder() {
  // Dont change when latched
  if (!latchOpen) {
    return;
  }

  dialChanged = false;
  encoderPinA_value = digitalRead(ENCODER_PIN_A);
  if (encoderPinA_value != encoderPinA_prev) {  // check if knob is rotating
    dialChanged = true;
    // if pin A state changed before pin B, rotation is clockwise
    if (digitalRead(ENCODER_PIN_B) != encoderPinA_value) {
      if (count >= 0) {
        count--;
      }
      bool_CW = true;
    } else {
      // if pin B state changed before pin A, rotation is counter-clockwise
      bool_CW = false;
      if (count < 36) {
        count++;
      }
    }
    if (bool_CW) {
      // Serial.print("Clockwise | ");
    } else {
      // Serial.print("Counter-Clockwise | ");
    }
  }
  encoderPinA_prev = encoderPinA_value;
}