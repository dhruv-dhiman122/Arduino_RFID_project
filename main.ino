#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SS_PIN 10
#define RST_PIN 9

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

MFRC522 rfid(SS_PIN, RST_PIN);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Change this to your card UID
byte allowedUID[4] = {0xA3, 0x7F, 0x2C, 0x91};

void setup() {
  Serial.begin(9600);

  SPI.begin();
  pinMode(SS_PIN, OUTPUT);
  pinMode(RST_PIN, OUTPUT);

  rfid.PCD_Init();

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println("Ready...");
  display.display();
}

bool isAuthorized() {
  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != allowedUID[i]) {
      return false;
    }
  }
  return true;
}

void showMessage(const char* msg) {
  display.clearDisplay();
  display.setCursor(10, 20);
  display.println(msg);
  display.display();
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  if (isAuthorized()) {
    Serial.println("Access Granted");
    showMessage("GO");
  } else {
    Serial.println("Access Denied");
    showMessage("NOT ALLOWED");
  }

  delay(2000);  // hold message
  showMessage("Scan Card");

  rfid.PICC_HaltA();
}
