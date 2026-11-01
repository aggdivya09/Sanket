// SAFETY BOX (Arduino Mega) - receives train position by LoRa,
// sends ALERT only while the train is INSIDE 2 km, otherwise CLEAR.
// Library: "LoRa" by Sandeep Mistry.
// LoRa wiring on Mega: SCK 52, MISO 50, MOSI 51, NSS 53, RST 49, DIO0 2
// Bracelet link: Mega pin 14 (TX3) -> bracelet pin 2, and GND <-> GND
#include <SPI.h>
#include <LoRa.h>

#define LORA_SS   53
#define LORA_RST  49
#define LORA_DIO0 2
#define LORA_FREQ 433E6          // must match the Train Unit

#define BRIDGE Serial3           // TX3 = pin 14

// Fixed position of the Safety Box (level crossing)
const float BOX_LAT = 30.273000;
const float BOX_LON = 77.999496;

const float ALERT_RADIUS_M = 2000.0;
const unsigned long LINK_INTERVAL = 1000;   // send state to bracelet every 1 s
const unsigned long TRAIN_TIMEOUT = 8000;   // no LoRa packet for 8 s -> CLEAR

float trainDistance = 99999;
unsigned long lastPacket = 0;
unsigned long lastLink = 0;
bool wasInside = false;

float distanceMeters(float lat1, float lon1, float lat2, float lon2) {
  const float M_PER_DEG = 111195.0;
  float dLat = (lat2 - lat1) * M_PER_DEG;
  float dLon = (lon2 - lon1) * M_PER_DEG * cos(lat1 * DEG_TO_RAD);
  return sqrt(dLat * dLat + dLon * dLon);
}

void handlePacket(String msg) {
  // expected: TRAIN,1,30.295458,77.999496
  if (!msg.startsWith("TRAIN")) return;
  int c1 = msg.indexOf(',');
  int c2 = msg.indexOf(',', c1 + 1);
  int c3 = msg.indexOf(',', c2 + 1);
  if (c1 < 0 || c2 < 0 || c3 < 0) return;

  float lat = msg.substring(c2 + 1, c3).toFloat();
  float lon = msg.substring(c3 + 1).toFloat();

  trainDistance = distanceMeters(BOX_LAT, BOX_LON, lat, lon);
  lastPacket = millis();

  Serial.print("LoRa Received: ");
  Serial.println(msg);
  Serial.print("Train distance: ");
  Serial.print((long)trainDistance);
  Serial.println(" m");
}

void setup() {
  Serial.begin(115200);
  BRIDGE.begin(9600);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(LORA_FREQ)) {
    Serial.println("LoRa init FAILED - check wiring");
    while (true) {}
  }
  Serial.println("Safety Box Ready");
}

void loop() {
  // 1) read LoRa
  int size = LoRa.parsePacket();
  if (size) {
    String msg = "";
    while (LoRa.available()) msg += (char)LoRa.read();
    handlePacket(msg);
  }

  // 2) decide state
  bool fresh  = (lastPacket != 0) && (millis() - lastPacket < TRAIN_TIMEOUT);
  bool inside = fresh && (trainDistance <= ALERT_RADIUS_M);

  if (inside != wasInside) {
    Serial.println(inside ? ">>> WITHIN 2 km - ALERT" : ">>> Outside 2 km - CLEAR");
    wasInside = inside;
  }

  // 3) send to bracelet once per second
  if (millis() - lastLink >= LINK_INTERVAL) {
    lastLink = millis();
    BRIDGE.println(inside ? "ALERT" : "CLEAR");
  }
}