#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D2
#define RST_PIN D1

MFRC522 mfrc522(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

byte block = 4;   // Block to write (sector 1, block 0)

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  // Default key FF FF FF FF FF FF
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println("Scan card to write 'univision'");
}

void loop() {

  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  Serial.println("Card detected");

  // Authenticate
  MFRC522::StatusCode status;
  status = mfrc522.PCD_Authenticate(
             MFRC522::PICC_CMD_MF_AUTH_KEY_A,
             block,
             &key,
             &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK) {
    Serial.print("Auth failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // Data to write (16 bytes)
  byte dataBlock[16] = "UNIVISION";

  // Write block
  status = mfrc522.MIFARE_Write(block, dataBlock, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Write failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  Serial.println("Written successfully!");

  // Read back
  byte buffer[18];
  byte size = sizeof(buffer);

  status = mfrc522.MIFARE_Read(block, buffer, &size);
  if (status == MFRC522::STATUS_OK) {
    Serial.print("Read data: ");
    for (byte i = 0; i < 16; i++) {
      Serial.write(buffer[i]);
    }
    Serial.println();
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
