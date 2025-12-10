#include <FastLED.h>

#define RING_LED_COUNT 16

extern int count;

// Animation stuff
#define DIAL_STATE_SETTING 0
#define DIAL_STATE_BLINKING 1
#define DIAL_STATE_OFF 2
int dialState = DIAL_STATE_SETTING;
unsigned long dialAnimationStart = 0;
bool dialUpdatePending = true;

void setupDialLight() {
}

void setDialAnimationState(int state) {
  dialState = state;
  dialUpdatePending = true;

  switch (state) {
    case DIAL_STATE_BLINKING:
      dialAnimationStart = millis();
      break;
  }
}

// CRGB color = CRGB(235, 91, 52);
// CRGB color = CRGB(156, 44, 0);
// CRGB color = CRGB(255, 202, 79);
// CRGB color = CRGB(247, 150, 52); // Very good
int R = 250;
int G = 142;
int B = 32;
CRGB color = CRGB(R, G, B);  // Even better
void updateDialLight() {
  if (!dialUpdatePending) return;
  dialUpdatePending = false;

  switch (dialState) {
    case DIAL_STATE_SETTING:
      for (int i = 0; i < RING_LED_COUNT; i++) {
        setRingLed(i, count > (i * 2) ? color : CRGB::Black);
      }
      break;

    case DIAL_STATE_OFF:
      clearRingLight();
      break;

    case DIAL_STATE_BLINKING:
      double dialAnimationCount = (millis() - dialAnimationStart) / 2.5;
      if (dialAnimationCount > (PI * 40 * 7)) {
        setDialAnimationState(DIAL_STATE_OFF);
        return;
      }

      double scaleFactor = (cos((double)dialAnimationCount / 40) + 1) / 2;
      for (int i = 0; i < RING_LED_COUNT; i++) {
        setRingLed(i, count > (i * 2) ? CRGB(R * scaleFactor, G * scaleFactor, B * scaleFactor) : CRGB::Black);
      }

      dialUpdatePending = true;
      break;
  }
}