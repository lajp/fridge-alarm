#include <EEPROM.h>

#define BUTTON_PIN 2
#define PIEZO_PIN 13
#define OPEN_COUNT_OFFSET 0

static unsigned int openCount;

void setup() {
  EEPROM.get(OPEN_COUNT_OFFSET, openCount);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(PIEZO_PIN, OUTPUT);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    // Initially wait for 10 seconds
    for (int i = 0; i < 10; ++i) {
      if (digitalRead(BUTTON_PIN) == LOW) break;
      delay(1000);
    }

    while (digitalRead(BUTTON_PIN) == HIGH) {
      digitalWrite(PIEZO_PIN, HIGH);
      delay(50);
    }

    digitalWrite(PIEZO_PIN, LOW);
    openCount += 1;
    EEPROM.put(OPEN_COUNT_OFFSET, openCount);
  }
}
