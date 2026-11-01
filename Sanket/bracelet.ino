// BRACELET (UNO WiFi board, wired link) - reacts to ALERT / CLEAR
// Wiring: Safety Box Mega pin 14 (TX3) -> pin 2 here, GND <-> GND
// Optional buzzer on pin 8 (through a resistor or a buzzer module).
#include <SoftwareSerial.h>

SoftwareSerial link(2, 3);      // RX = 2, TX = 3 (unused)

#define LED_PIN    13
#define BUZZER_PIN 8
const unsigned long LINK_TIMEOUT = 5000;   // no message for 5 s -> CLEAR

String line = "";
bool alertOn = false;
unsigned long lastMsg = 0;
unsigned long lastBlink = 0;
bool blinkState = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(115200);
  link.begin(9600);
  Serial.println("Bracelet ready (wired link)");
}

void setAlert(bool on) {
  if (on != alertOn) {
    alertOn = on;
    Serial.println(on ? "ALERT received" : "CLEAR received");
    if (!on) {
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
}

void loop() {
  // read one line at a time
  while (link.available()) {
    char c = link.read();
    if (c == '\n') {
      line.trim();
      if (line == "ALERT")      { setAlert(true);  lastMsg = millis(); }
      else if (line == "CLEAR") { setAlert(false); lastMsg = millis(); }
      line = "";
    } else if (line.length() < 16) {
      line += c;
    }
  }

  // lost link -> clear
  if (alertOn && millis() - lastMsg > LINK_TIMEOUT) {
    Serial.println("Link lost - clearing");
    setAlert(false);
  }

  // fast blink + buzz while alert is on
  if (alertOn && millis() - lastBlink >= 250) {
    lastBlink = millis();
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
    digitalWrite(BUZZER_PIN, blinkState);
  }
}