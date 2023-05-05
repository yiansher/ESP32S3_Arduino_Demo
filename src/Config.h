#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdbool.h>
#include <stdint.h>

#define NUMPIXELS 1
#define PIN_NEOPIXEL 48

// #define TFT_SCLK 12
// #define TFT_MOSI 11
// #define TFT_CS 10
// // #define TFT_BLK 13
// #define TFT_DC 14
// #define TFT_RST 9

#define CONFIG_SCREEN_HOR_RES       240
#define CONFIG_SCREEN_VER_RES       240
#define CONFIG_SCREEN_BUFFER_SIZE   (CONFIG_SCREEN_HOR_RES * CONFIG_SCREEN_VER_RES /2)

#define LOG_INFO(format, ...) Serial.printf("\r\nLOG INFO: "), Serial.printf(format, ##__VA_ARGS__)

#endif