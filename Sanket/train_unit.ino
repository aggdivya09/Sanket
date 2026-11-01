// TRAIN UNIT (demo, simulated GPS) - sends TRAIN,1,lat,lon over LoRa
// Library: "LoRa" by Sandeep Mistry. Module assumed: SX1278 (Ra-02) 433 MHz.
// Wiring for Uno/Nano: SCK 13, MISO 12, MOSI 11, NSS 10, RST 9, DIO0 2
#include <SPI.h>
#include <LoRa.h>

#define LORA_SS   10
#define LORA_RST  9
#define LORA_DIO0 2
#define LORA_FREQ 433E6          // must match the Safety Box

const float START_LAT = 30.299950;   // 3000 m north of the Safety Box
const float END_LAT   = 30.265000;   // a little past the Safety Box
const float LON       = 77.999496;
const float STEP_DEG  = 0.000898;    // about 100 m per packet
const unsigned long SEND_INTERVAL = 2000;

float lat = START_LAT;
unsigned long lastSend = 0;

void setup() {
  Serial.begin(115200);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(LORA_FREQ)) {
    Serial.println("LoRa init FAILED - check wiring");
    while (true) {}
  }
  Serial.println("Train Unit Ready - DEMO (simulated GPS)");
}

void loop() {
  if (millis() - lastSend >= SEND_INTERVAL) {
    lastSend = millis();

    String msg = "TRAIN,1," + String(lat, 6) + "," + String(LON, 6);
    LoRa.beginPacket();
    LoRa.print(msg);
    LoRa.endPacket();
    Serial.print("SENT: ");
    Serial.println(msg);

    lat -= STEP_DEG;
    if (lat < END_LAT) lat = START_LAT;   // restart the demo run
  }
}