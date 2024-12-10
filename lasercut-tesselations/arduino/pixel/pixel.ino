#include <Adafruit_NeoPixel.h>

const int led_count = 1;
const int led_pin = 2;
Adafruit_NeoPixel strip(led_count, led_pin, NEO_GRBW + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(255);
  strip.show();
}

void loop() {
  strip.setPixelColor(0, 255, 255, 255, 255);
  delay(10000);
}
