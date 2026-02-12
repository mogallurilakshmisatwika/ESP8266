#include <Adafruit_ILI9341.h>

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {

  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, LOW);
  delay(100);
  digitalWrite(TFT_RST, HIGH);

  tft.begin();
  tft.fillScreen(ILI9341_RED);
}

void loop() {}
