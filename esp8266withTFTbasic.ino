#include <SPI.h>
#include <SD.h>

#define SD_CS D2

void setup() {
  Serial.begin(9600);
  delay(3000);

  Serial.println();
  Serial.println("ESP8266 SD RAW TEST");

  SPI.begin();   // force SPI start

  if (!SD.begin(SD_CS)) {
    Serial.println("SD INIT FAILED");
    return;
  }

  Serial.println("SD INIT SUCCESS");
}

void loop() {}
