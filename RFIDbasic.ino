#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D1   // NodeMCU pin connected to RST
#define SS_PIN  D2   // NodeMCU pin connected to SDA/SS

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);       // Initialize serial communication
  while (!Serial);          // Wait for serial port to open (for some boards)
  SPI.begin();              // Init SPI bus
  mfrc522.PCD_Init();       // Init MFRC522
  delay(4);                 // Small delay
  mfrc522.PCD_DumpVersionToSerial(); // Show reader details
  Serial.println(F("Scan an RFID card/tag to see UID and info..."));
}

void loop() {
  // Check if a new card is present
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Print UID
  Serial.print(F("Card UID: "));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Print card type
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.print(F("PICC type: "));
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  // Dump the card details to serial
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  Serial.println();
  delay(1000); // Optional: small delay before next read
}
