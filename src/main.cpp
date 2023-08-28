#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>


TFT_eSPI tft = TFT_eSPI();

int px = 0; // player car x- coordinate
int py = 416;     // player car y-coordinate

int carSize = 64;
unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

// Functions
void drawPlayer(void);

void setup() {
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(px, py, carSize, carSize, TFT_GREEN);
}

void loop() {
  drawPlayer();
}

void drawPlayer() {
  if (digitalRead(34) && px < 256) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      tft.fillRect(px, py, carSize, carSize, TFT_BLACK);
      px = px + 64;
      tft.fillRect(px, py, carSize, carSize, TFT_GREEN);
    }
    lastDebounceTime = millis();
  }

  if (digitalRead(35) && px > 0) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      tft.fillRect(px, py, carSize, carSize, TFT_BLACK);
      px = px - 64;
      tft.fillRect(px, py, carSize, carSize, TFT_GREEN);
    }
    lastDebounceTime = millis();
  } 
}