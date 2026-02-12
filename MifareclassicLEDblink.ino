#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D2
#define RST_PIN D1
#define LED_PIN D4   // Built-in LED on NodeMCU (active LOW)

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // LED OFF initially
  Serial.println("Place card near the reader...");
}

void loop() {
  // Check if a card is near
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Card detected → turn LED ON
    digitalWrite(LED_PIN, LOW);
    delay(1000); // LED ON

    // Optional: print card UID
    Serial.print("Card UID: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    // Halt the card to be ready for next detection
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    
  } else {
    // No card → LED OFF
    digitalWrite(LED_PIN, HIGH); // LED OFF
  }

  delay(50); // small delay for stability
}
