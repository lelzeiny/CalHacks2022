#include "accl.h"

int tapCount = 0;

void setup() {
    Serial.begin(115200);
    accl_init(300);
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
    // delay(200);
}