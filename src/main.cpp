#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <dog.h>
# include <font.h>


TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);

  tft.pushImage(30, 30, 128, 128, dog);
  tft.setFreeFont(&Creepster_Caps_Regular_23);

  tft.drawString("Ceberus", 20, 130);

}

void loop() {

}
