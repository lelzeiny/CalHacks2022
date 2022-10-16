#include "accl.h"

int tapCount = 0;

void setup() {
    Serial.begin(9600);
    accl_init(3, 3);
}

void loop() {
    int count = accl_sample();
    // Serial.print("tapped count ");
    // Serial.println(count);
    if (accl_isShaken()) {
        tapCount += 1;
        Serial.print("Got shaken ");
        Serial.println(tapCount);
    }
    delay(200);
}