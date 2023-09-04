#include <Arduino.h>
#include <TFT_eSPI.h>
#include "dog.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite dogSprite = TFT_eSprite(&tft);

int x = 0;

// Functions

void setup() {
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  tft.init();
  tft.setRotation(1); 
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);

  dogSprite.createSprite(128, 128);
  dogSprite.setSwapBytes(true);
  dogSprite.pushImage(0, 0, 128, 128, dog);
  dogSprite.pushSprite(20, 20);
}

void loop() {
}
