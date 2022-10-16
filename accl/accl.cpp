#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_LIS2DH12.h" //Click here to get the library: http://librarymanager/All#SparkFun_LIS2DH12
SPARKFUN_LIS2DH12 accel;
int accelInterruptPin = 4;

unsigned long secondsToCount;
int shakeThreshold;
unsigned long lastCheckTime;
unsigned long lastRefreshTime;
unsigned long lastInc;
int tappedCount;

void accl_init(int secsToCount, int threshold) {
    tappedCount = 0;
    shakeThreshold = threshold;
    secsToCount = secondsToCount;
    Wire.begin();
    pinMode(accelInterruptPin, INPUT_PULLUP);
    if (accel.begin() == false)
    {
        Serial.println("Accelerometer not detected. Check address jumper and wiring. Freezing...");
        while (1)
        ;
    }

    lastRefreshTime = millis();
    lastCheckTime = millis();
    lastInc = millis();

    // accel.setDataRate(LIS2DH12_POWER_DOWN); //Stop measurements

    // //INT1_CFG - enable X and Y events
    // //accel.setInt1(true);
    // accel.setInt1(false);

    // //Set INT POLARITY to Active Low
    // //CTRL_REG6, INT_POLARITY = 1 active low
    // accel.setIntPolarity(LOW);

    // //Set INT1 interrupt
    // //CTRL_REG3, I1_IA1 = 1 - Enable IA1 Interrupt on INT1 pin
    // accel.setInt1IA1(true);

    // accel.setTapThreshold(20); //0 to 127. 5 is a soft tap. 100 is hard tap.
    // accel.enableTapDetection();
    // //accel.disableTapDetection();

    // //Set INT1 Duration
    // //INT1_DURATION = 500
    // //accel.setInt1Duration(30);
    // accel.setInt1Duration(9);

    // //Latch interrupt 1, CTRL_REG5, LIR_INT1
    // //accel.setInt1Latch(true);
    // accel.setInt1Latch(false);

    // //Clear the interrupt
    // while (accel.getInt1()) delay(10); //Reading int will clear it

    //accel.setDataRate(LIS2DH12_ODR_1Hz); //Very low power
    //accel.setDataRate(LIS2DH12_ODR_100Hz);
    // accel.setDataRate(LIS2DH12_ODR_400Hz); 

    // accel.setInt1(true); //Enable interrupts

}

int accl_sample() {
    if (accel.isTapped()) {
        tappedCount += 1;
        lastInc = millis();
        // Serial.print("got tapped!! at time ");
        // Serial.println(lastInc);
    }
    unsigned long windowBegin = millis() - secondsToCount * 1000; 
    // Serial.print("lastCheckTime ");
    // Serial.print(lastCheckTime);
    // Serial.print(" lastInc ");
    // Serial.print(lastInc);
    // Serial.print(" lastRefreshTime ");
    // Serial.print(lastRefreshTime);
    // Serial.print(" windowBegin ");
    // Serial.println(windowBegin);
    if (lastCheckTime > lastInc && lastRefreshTime <= windowBegin) { // if have most up-to-date data and time to refresh
        tappedCount = 0;
        lastRefreshTime = millis();
    }
    return tappedCount;
}

bool accl_isShaken() {
    bool ret = tappedCount >= shakeThreshold;
    lastCheckTime = millis();
    // Serial.print("tapped count at time of shaken ");
    // Serial.println(tappedCount);
    return ret;
}