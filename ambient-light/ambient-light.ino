#include <FastLED.h>

// Animation stuff
#define DIAL_STATE_SETTING 0
#define DIAL_STATE_BLINKING 1
#define DIAL_STATE_OFF 2
#define FOCUS_STATE_OFF 0
#define FOCUS_STATE_FOCUSING 1
#define FOCUS_STATE_STOPPING 2

extern bool dialChanged;
extern bool dialUpdatePending;
extern bool latchOpen;
extern int count;

void setup() {
  Serial.begin(9600);
  setupRotaryEncoder();
  setupLatch();
  setupTimer();

  setupAllLights();
  setupDialLight();
  setupFocusLight();

  updateDialLight();
  updateLatch();
}

void loop() {
  checkRotaryEncoder();
  checkContact();
  updateTimer();

  if (dialChanged) dialUpdatePending = true;

  updateDialLight();
  updateFocusLight();

  FastLED.show();
}

void onContactPressed() {
  latchOpen = !latchOpen;

  updateLatch();

  if (latchOpen) {
    setDialAnimationState(DIAL_STATE_SETTING);
    setFocusAnimationState(FOCUS_STATE_STOPPING);
    stopTimer();
  } else {
    setDialAnimationState(DIAL_STATE_BLINKING);
    setFocusAnimationState(FOCUS_STATE_FOCUSING);
    startTimer(count);
  }
}

void onContactReleased() {
}

void onTimerEnd() {
  unLatch();
  setDialAnimationState(DIAL_STATE_SETTING);
  setFocusAnimationState(FOCUS_STATE_STOPPING);
}
