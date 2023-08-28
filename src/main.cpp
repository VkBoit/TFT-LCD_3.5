#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <enemy.h>
#include <player.h>



TFT_eSPI tft = TFT_eSPI();

int px = 0; // player car x- coordinate
int py = 416;     // player car y-coordinate

int ex[5];  // enemy x - coordinate
int ey[5] = {32, -32, -96, -160, -224};  // enemy y - coordinate

int carSize = 64;
unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

bool gameRun = true;

long t;
long gameSpeed = 500000;
int score = 0;

// Functions
void drawPlayer(void);
void drawEnemy(void);
void checkCollision(void);

void setup() {
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  tft.init();
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  tft.drawLine(0, 31, 320, 31, TFT_WHITE);
  tft.drawString("SCORE:", 5, 5, 4);
  for (int n; n < 5; n++)
    ex[n] = random(0, 5)*64;
  tft.pushImage(ex[0], ey[0], carSize, carSize, enemy);
  tft.pushImage(px, py, carSize, carSize, player);  
}

void loop() {
  if (gameRun == true) {
    t++;
    if (t > gameSpeed) {
      drawEnemy();
      t = 0;
    }
    drawPlayer();
    checkCollision();
  }
  else {
    //tft.fillScreen(TFT_BLACK);    
    tft.drawString ("GAME OVER!", 100, 200, 4);
    delay(100);
  }
}

void drawPlayer() {
  if (digitalRead(34) && px < 256) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      tft.fillRect(px, py, carSize, carSize, TFT_BLACK);
      px = px + 64;
      tft.pushImage(px, py, carSize, carSize, player);
    }
    lastDebounceTime = millis();
  }

  if (digitalRead(35) && px > 0) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      tft.fillRect(px, py, carSize, carSize, TFT_BLACK);
      px = px - 64;
      tft.pushImage(px, py, carSize, carSize, player);
    }
    lastDebounceTime = millis();
  } 
}

void drawEnemy() {
  for (int n; n < 5; n++) {
    if (ey[n] > -3) {
      tft.fillRect(ex[n], ey[n], 64, 64, TFT_BLACK);
      ey[n] = ey[n] + 64;
      tft.pushImage(ex[n], ey[n], 64, 64, enemy);
    }
    else {
      ey[n] = ey[n] + 64;
    }
    if (ey[n] > 480) {
      ey[n] = 32;
      ex[n] = random(0, 5)*64;
      score++;
      gameSpeed = gameSpeed-4000;
      tft.drawString (String(score), 100, 5, 4);
      tft.drawString (String(gameSpeed), 200, 5, 4);
    }
  }
}

void checkCollision() {
  for (int n; n < 5; n++) {
    if (px == ex[n] && py == ey[n]) {
      gameRun = false;
    }
  }
}