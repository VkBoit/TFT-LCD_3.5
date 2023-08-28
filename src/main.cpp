#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>


TFT_eSPI tft = TFT_eSPI();

int px = 0; // player car x- coordinate
int py = 416;     // player car y-coordinate

int ex;  // enemy x - coordinate
int ey = 32;  // enemy y - coordinate

int carSize = 64;
unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

bool gameRun = true;

int t;
int score = 0;

// Functions
void drawPlayer(void);
void drawEnemy(void);
void checkCollision(void);

void setup() {
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.drawLine(0, 31, 320, 31, TFT_WHITE);
  tft.drawString("SCORE:", 5, 5, 4);
  ex = random(0, 5)*64;
  tft.fillRect(ex, ey, carSize, carSize, TFT_RED);
  tft.fillRect(px, py, carSize, carSize, TFT_GREEN);  
}

void loop() {
  if (gameRun == true) {
    t++;
    if (t > 1000000) {
      drawEnemy();
      t = 0;
    }
    drawPlayer();
  }
  else {
    tft.fillScreen(TFT_BLACK);    
    tft.drawString ("GAME OVER!", 100, 200, 4);
    delay(100);
  }
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

void drawEnemy() {
  tft.fillRect(ex, ey, 64, 64, TFT_BLACK);
  ey = ey + 64;
  tft.fillRect(ex, ey, 64, 64, TFT_RED);
  checkCollision();
  if (ey > 480) {
    ey = 32;
    ex = random(0, 5)*64;
    score++;
    tft.drawString (String(score), 100, 5, 4);
  }
}

void checkCollision() {
  if (px == ex && py == ey) {
    gameRun = false;
  }
}