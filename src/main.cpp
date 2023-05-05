#include <Arduino.h>
#include "Config.h"
#include "Display.h"
#include "lv_demo_benchmark.h"


static unsigned long last_ms;
extern lv_color_t* lv_disp_buf_p;

void setup() {
  Serial.begin(115200);
  lv_disp_buf_p = static_cast<lv_color_t*>(malloc(CONFIG_SCREEN_BUFFER_SIZE * sizeof(lv_color_t)));
  Port_Init();
  lv_demo_benchmark();
  last_ms = millis();
}

void loop() {
  lv_timer_handler();
  delay(5);
}