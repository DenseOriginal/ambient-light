#include <FastLED.h>

// Focus light
#define RING_LED_COUNT 16
// #define FOCUS_LED_COUNT 0
#define FOCUS_LED_COUNT 43
#define TOTAL_LED_COUNT RING_LED_COUNT + FOCUS_LED_COUNT

#define LED_DATA_PIN 4

CRGB leds[TOTAL_LED_COUNT];

void setupAllLights() {
  FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, TOTAL_LED_COUNT);  // GRB ordering is typical
}

void setRingLed(int i, CRGB color) {
  leds[i] = color;
}

void setFocusLed(int i, CRGB color) {
  leds[i + RING_LED_COUNT] = color;
}

void clearRingLight() {
  for (int i = 0; i < RING_LED_COUNT; i++) {
    leds[i] = CRGB::Black;
  }
}

void setFocusLight(CRGB color) {
  for (int i = RING_LED_COUNT; i < TOTAL_LED_COUNT; i++) {
    leds[i] = color;
  }
}

void clearFocusLight() {
  setFocusLight(CRGB::Black);
}
