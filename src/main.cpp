#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>


TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.init();
  tft.fillScreen(TFT_BLACK);
  
}

void loop() {

}
