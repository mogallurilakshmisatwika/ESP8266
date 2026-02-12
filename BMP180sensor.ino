#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);

  if (!bmp.begin()) {
    Serial.println("BMP180 not found");
    while (1);
  }

  Serial.println("BMP180 Ready");
}

void loop() {

  Serial.print("Temp: ");
  Serial.print(bmp.readTemperature());
  Serial.println(" C");

  Serial.print("Pressure: ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.println("----------------");
  delay(2000);
}
