#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_LIS2DH12.h" //Click here to get the library: http://librarymanager/All#SparkFun_LIS2DH12
#define buffer_len 2
SPARKFUN_LIS2DH12 accel;
int accelInterruptPin = 4;

int shakeThreshold;
unsigned long lastRefreshTime;
unsigned long currTime;
int tappedCount;
int buffer_index = 0;
int tap_buffer[buffer_len];

void buffer_init() {
  int i;
  for (i = 0; i < buffer_len; i++) {
    tap_buffer[i] = 0;
  }
}

void accl_init(int threshold) {
    tappedCount = 0;
    shakeThreshold = threshold;
    // Init buffer
    buffer_init();
    Wire.begin();
  
    if (accel.begin() == false)
    {
        Serial.println("Accelerometer not detected. Check address jumper and wiring. Freezing...");
        while (1);
    }
    accel.enableTapDetection();
    accel.setTapThreshold(20);
    lastRefreshTime = millis();
    currTime = millis();
}

int accl_sample() {
    if (accel.isTapped()) {
      tappedCount += 1;
    }
    // check time
    currTime = millis();    
    if (lastRefreshTime >> 9 != currTime >> 9) {
      lastRefreshTime = currTime;
      tap_buffer[buffer_index] = tappedCount;
      tappedCount = 0;
      buffer_index = (buffer_index + 1) % buffer_len;
    }
    return tappedCount;
}

bool accl_isShaken() {
    int sum = 0;
    int i;
    for (i = 0; i < buffer_len; i++) {
      sum += tap_buffer[i];
    }
    bool ret = sum >= shakeThreshold;
    if (ret) {
      Serial.print("tapped count at time of shaken ");
      Serial.println(tappedCount);
      buffer_init();
    }
    return ret;
}