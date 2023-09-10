#include <EEPROM.h>
#define OPEN_COUNT_OFFSET 0
#define USAGE "Available commands: clear, count, setcount"

void setup() {
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  prompt();
  String ip = readString();

  if (ip == "clear") {
    Serial.println("Clearing EEPROM, are you sure? (y/n)");
    String yn = readString();

    if (yn == "y") {
      Serial.println("Clearing EEPROM...");
      for (int i = 0; i < EEPROM.length(); ++i) {
        EEPROM.write(i, 0);
      }
      Serial.println("Done!");
    }
  } else if (ip == "count") {
    unsigned int countValue;
    EEPROM.get(OPEN_COUNT_OFFSET, countValue);

    Serial.print("Fridge has been opened ");
    Serial.print(countValue);
    Serial.println(" times.");
  } else if (ip == "setcount") {
    Serial.println("What would you like to set the open-count to? (a negative number cancels)");
    while (Serial.available() == 0);
    long n = Serial.parseInt();
    if (n >= 0) {
      Serial.print("Writing ");
      Serial.print(n);
      Serial.println("...");

      EEPROM.put(OPEN_COUNT_OFFSET, (unsigned int)n);
      Serial.println("Done!");
    }
  }
}

String readString() {
  while (Serial.available() == 0);
  String ret = Serial.readString();
  ret.trim();
  return ret;
}

void prompt() {
  Serial.println(USAGE);
  Serial.print("> ");
}
