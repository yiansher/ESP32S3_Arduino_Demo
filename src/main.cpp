#include <Arduino.h>
#include "Config.h"
#include "Display.h"
#include "lv_demo_benchmark.h"


static unsigned long last_ms;

void setup() {
  Serial.begin(115200);
  Port_Init();
  lv_demo_benchmark();
  last_ms = millis();
}

void loop() {
  lv_timer_handler();
  delay(5);
}