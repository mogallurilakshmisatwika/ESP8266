#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);

  // OLED init
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C )) {
    Serial.println("OLED not found");
    while(1);
  }

  // BMP180 init
  if (!bmp.begin()) {
    Serial.println("BMP180 not found");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,20);
  display.println("READY");
  display.display();
  delay(2000);
}

void loop() {
  float temp = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude();

  Serial.print("Temperature = "); Serial.print(temp); Serial.println(" *C");
  Serial.print("Pressure = "); Serial.print(pressure); Serial.println(" Pa");
  Serial.print("Altitude = "); Serial.print(altitude); Serial.println(" meters");

  display.clearDisplay();

  // Heading
  display.setTextSize(2);     // Make it smaller so it fits
  display.setCursor(0,0);
  display.println("BMP180");

  // Temperature
  display.setTextSize(1);
  display.setCursor(0,25);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  // Pressure
  display.setCursor(0,38);
  display.print("Pres: ");
  display.print(pressure/100);  // Convert Pa to hPa
  display.println(" hPa");

  // Altitude
  display.setCursor(0,50);
  display.print("Alt: ");
  display.print(altitude);
  display.println(" m");

  display.display();
  delay(1000);
}

