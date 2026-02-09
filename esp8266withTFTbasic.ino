#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS   D8
#define TFT_DC   D4
#define TFT_RST  D3

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.begin();
  tft.setRotation(1);   // landscape
}

void loop() {

  tft.fillScreen(ILI9341_RED);
  delay(1000);

  tft.fillScreen(ILI9341_GREEN);
  delay(1000);

  tft.fillScreen(ILI9341_BLUE);
  delay(1000);

  tft.fillScreen(ILI9341_BLACK);

  // Draw shapes
  tft.drawRect(20, 20, 100, 60, ILI9341_YELLOW);
  tft.fillCircle(200, 120, 30, ILI9341_CYAN);

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(60, 200);
  tft.println("Graphics OK");

  delay(3000);
}
