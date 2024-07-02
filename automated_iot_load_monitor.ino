#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <HX711.h>
#include <Servo.h>


#define SS_PIN 10
#define RST_PIN 5


MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;


int block = 2;
byte readbackblock[18];


// Load Cell
const int DOUT_PIN = 2;
const int SCK_PIN = 3;
long weight;
long actualWeight;




HX711 scale;


// LCD SCREEN
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();


  // Prepare the security key for the read function.
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }


  scale.begin(DOUT_PIN, SCK_PIN);
  Serial.println("HX711 Initialized");


  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome!");
}


int extractInteger(byte* data) {
  // Assuming the first two bytes represent the integer value
  int extractedValue = (data[0] - '0') * 10 + (data[1] - '0');
  return extractedValue;
}


void loop() {


  // LOAD CELL
 
    // Print the LOAD Cell value
    weight = scale.get_units();
    actualWeight = ((fabs(weight - 253500) * 2) - 3000)/1000;
     Serial.print("LOAD CELL : ");
    Serial.println(actualWeight);




  // Look for new cards
  Serial.println("Scan TAG");
  if (!mfrc522.PICC_IsNewCardPresent()) {
    delay(2000);
    return;
  }


  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }


  // Read the specified block from RFID
  if (readBlock(block, readbackblock)) {
    // Print the RFID block contents
    Serial.print("Read block from RFID: ");
    for (int j = 0; j < 16; j++) {
      Serial.write(readbackblock[j]);
    }
    Serial.println();


    // Extract an integer from the block data
    int extractedValue = extractInteger(readbackblock);


    // Print the extracted value
    Serial.print("Extracted Integer: ");
    Serial.println(extractedValue);


    if (actualWeight <= extractedValue) {
      // Open barriers
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Gate Opened");
      // myservo.write(90);
      delay(1500);
      // myservo.write(0);
      // lcd.clear();
    } else {
      // Display a message indicating vehicle overload
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Vehicle Overload");
      lcd.setCursor(0, 1);
      lcd.print("Not Allowed");
      delay(1500);
      // lcd.clear();
    }
  }


  // Halt the card and stop encryption
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();


  // Delay before looking for a new card
  delay(5000);
}


// Read specific block
bool readBlock(int blockNumber, byte arrayAddress[]) {
  int trailerBlock = (blockNumber / 4) * 4 + 3;


  // Authentication of the desired block for access
  if (mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid)) != MFRC522::STATUS_OK) {
    Serial.println("Authentication failed");
    return false;
  }


  // Reading a block
  byte bufferSize = 18;
  if (mfrc522.MIFARE_Read(blockNumber, arrayAddress, &bufferSize) != MFRC522::STATUS_OK) {
    Serial.println("Read failed");
    return false;
  }


  // Print status
  Serial.println("Block read successful");
  return true;
}
