#define FOCUS_LED_COUNT 43

extern int count;

// Animation stuff
#define FOCUS_STATE_OFF 0
#define FOCUS_STATE_FOCUSING 1
#define FOCUS_STATE_STOPPING 2
int focusState = FOCUS_STATE_OFF;
int focusAnimationCount = 0;
unsigned long focusStart = 0;
bool focusUpdatePending = true;

// Focus on color
int focus_R = 214;
int focus_G = 81;
int focus_B = 10;

// int focus_R = 214;
// int focus_G = 91;
// int focus_B = 17;

// int focus_R = 194;
// int focus_G = 73;
// int focus_B = 3;

// int focus_R = 194;
// int focus_G = 93;
// int focus_B = 20;

// Focus off color
int standby_R = 214;
int standby_G = 81;
int standby_B = 10;
CRGB standbyColor = CRGB(standby_R * 0, standby_G * 0, standby_B * 0);

bool stripIsOn = false;
float pulseSpeed = 0.001;
float phaseOffset[FOCUS_LED_COUNT];

void setupFocusLight() {
  for (int i = 0; i < FOCUS_LED_COUNT; i++) {
    phaseOffset[i] = random(0, 628) / 100.0;  // 0 to ~6.28 (0..2π)
  }
}

void updateFocusLight() {
  if (!focusUpdatePending) return;
  focusUpdatePending = false;

  switch (focusState) {
    case FOCUS_STATE_OFF:
      setFocusLight(standbyColor);
      break;
    case FOCUS_STATE_FOCUSING:
      breatheAnimation();
      focusUpdatePending = true;
      break;
    case FOCUS_STATE_STOPPING:
      turnOffAnimation();
      focusUpdatePending = true;
      break;
  }
}

void breatheAnimation() {
  unsigned long t = millis();
  double fadeInBrightness = min((t - focusStart) / 2000.0, 1);

  for (int i = 0; i < FOCUS_LED_COUNT; i++) {
    // Phase-shifted sine wave
    float phase = sin((t * pulseSpeed) + phaseOffset[i]);

    // Convert -1..1 -> 0..1
    float b = (phase + 1) * 0.5;

    //minimum brightness = 50%
    b = (0.15 + (b * 0.5)) * fadeInBrightness;

    // Breathing color (soft white here)
    uint8_t R = focus_R * b;
    uint8_t G = focus_G * b;
    uint8_t B = focus_B * b;

    setFocusLed(i, CRGB(R, G, B));
  }
}

void turnOffAnimation() {
  unsigned long t = millis();
  unsigned long duration = (t - focusStart);
  double fadeOutBrightness = 1 - (duration / 500.0);
  if (fadeOutBrightness <= 0) {
    setFocusAnimationState(FOCUS_STATE_OFF);
    return;
  }

  for (int i = 0; i < FOCUS_LED_COUNT; i++) {
    // Phase-shifted sine wave
    float phase = sin((t * pulseSpeed) + phaseOffset[i]);

    // Convert -1..1 -> 0..1
    float b = (phase + 1) * 0.5;

    //minimum brightness = 50%
    b = (0.15 + (b * 0.5)) * fadeOutBrightness;

    // Breathing color (soft white here)
    uint8_t R = focus_R * b;
    uint8_t G = focus_G * b;
    uint8_t B = focus_B * b;

    setFocusLed(i, CRGB(R, G, B));
  }
}

void setFocusAnimationState(int state) {
  focusState = state;
  focusUpdatePending = true;

  switch (state) {
    case FOCUS_STATE_FOCUSING:
      Serial.println("State: Focusion");
      focusStart = millis();
      break;
    case FOCUS_STATE_STOPPING:
      Serial.println("State: Stopping");
      focusStart = millis();
      break;
  }
}
