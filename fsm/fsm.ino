#include <Wire.h>
#include <SFE_MicroOLED.h> //Click here to get the library: http://librarymanager/All#SparkFun_Micro_OLED
#include "accl.h"
#include "pdm_ex.h"

#define PIN_RESET 9
#define DC_JUMPER 1 // Set to either 0 (SPI, default) or 1 (I2C) based on jumper, matching the value of the DC Jumper
MicroOLED oled(PIN_RESET, DC_JUMPER);

uint8_t state_bitmaps[][384] = {
  //idle
  {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0x7f, 0x3f, 0x1f, 0x1f, 0x1f, 0x8f, 0x8f, 0x8f, 0x0f, 0x1f, 0x1f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 
0xff, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x8f, 0x8f, 0x8f, 0x1f, 0x1f, 0x1f, 0x3f, 0x7f, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0x00, 
0x00, 0x78, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xe0, 0xe1, 
0xe0, 0xf8, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x78, 0x00, 0x00, 
0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0x7f, 0x7f, 0x7c, 
0xf0, 0xe0, 0xc1, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x01, 0x40, 0x70, 0x7c, 
0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0x7f, 0x0f, 0x07, 0x07, 0x61, 0xf0, 0xf0, 0xfc, 0xfc, 0xf8, 0xf0, 0xf0, 0xf8, 0xfc, 0xf8, 
0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 0xf1, 0xe1, 0xe3, 0x03, 0x07, 0x07, 0x0f, 
0x0f, 0x07, 0x03, 0x03, 0xe1, 0xf1, 0xf0, 0xf8, 0xf0, 0xf0, 0xf0, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 
0xfc, 0xfe, 0xfc, 0xf8, 0xf8, 0xfc, 0xfe, 0xfe, 0xf8, 0xf0, 0x70, 0x03, 0x03, 0x0f, 0x7f, 0xff, 
0xff, 0xf8, 0xe0, 0xc0, 0xc2, 0x06, 0x03, 0x01, 0x71, 0xf9, 0xff, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x66, 0x62, 0x00, 0x00, 
0x00, 0x00, 0x31, 0x33, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x7f, 0x7c, 0x38, 0x00, 0x01, 0x82, 0xe0, 0xe0, 0xf0, 0xfc, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf0, 0xe1, 0xe3, 
0xe3, 0xe3, 0xe3, 0xe1, 0xf1, 0xf8, 0xf1, 0xf1, 0xf1, 0xf1, 0xf0, 0xf0, 0xfc, 0xfe, 0xfe, 0xfe, 
0xff, 0xfe, 0xfe, 0xfe, 0xf8, 0xf8, 0xf9, 0xf9, 0xf9, 0xf8, 0xfc, 0xf8, 0xf1, 0xf1, 0xf1, 0xf1, 
0xf1, 0xf1, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  // look
  {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f, 
0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0f, 
0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xbf, 0x1f, 0x0f, 0x07, 0xc3, 0xc3, 0xe1, 0xe0, 0xf8, 0xf8, 0xfc, 0xfc, 0x02, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x3e, 0x3e, 0x1c, 0x18, 
0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0xfc, 0xf8, 0xf8, 0xf0, 0xf0, 0xc1, 0xc1, 0x03, 0x07, 0x0f, 
0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe3, 0xc3, 0xc7, 0x9f, 0x1f, 0x3f, 0x3f, 0x78, 
0x60, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0xc0, 0x60, 0x78, 0x7c, 0x3f, 0x3f, 0x9f, 0x8f, 0xcf, 0xc3, 0xe0, 0xf8, 0xfc, 0xfe, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 
0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 
0xf8, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  // listen
  {0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x0f, 0x87, 0xc7, 0xc7, 0xe3, 0xe3, 0xe3, 
0xe3, 0xe3, 0xe3, 0xc7, 0xc7, 0x87, 0x0f, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0x0f, 0x01, 0x00, 0xf0, 0xfc, 0xfe, 0x1f, 0x07, 0xc3, 0xe3, 0xf3, 0xf1, 0xf9, 
0xf9, 0xf9, 0xf9, 0xf1, 0xe3, 0x87, 0x9f, 0xff, 0xfc, 0xf0, 0x00, 0x01, 0x0f, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xf8, 0xf8, 0xf9, 0xf9, 0xf9, 0xf1, 0x63, 
0x07, 0x07, 0x0f, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x0f, 0x03, 0x80, 0xe0, 0xf8, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x1f, 0x1f, 0xff, 0xff, 0xf0, 0xf1, 0xf1, 0xf0, 0xf8, 
0xf8, 0xfc, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xe0, 0xc3, 0x87, 0x8f, 0x0f, 0x1f, 0x1f, 0x1f, 
0x1f, 0x0f, 0x8f, 0x87, 0xc3, 0xe0, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
  // touch
  {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xbf, 0xdf, 0xef, 0xef, 0xef, 
0xef, 0xef, 0xef, 0xdf, 0xbf, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0x7e, 0xff, 0xff, 0xc3, 0xbd, 0x06, 0x02, 
0x02, 0x06, 0xbd, 0xc3, 0xff, 0xff, 0x3c, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfd, 0xfb, 0xfb, 0x00, 0x00, 
0x00, 0x00, 0x0b, 0x0b, 0x0d, 0x1c, 0x0f, 0x0f, 0x1f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xc0, 0x80, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf8, 0xe0, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf8, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf8, 0xf8, 
0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
};

bool displayDetected = false;

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(115200);

  //0x3D is default address on Qwiic board
  if (isConnected(0x3D) == true || isConnected(0x3C) == true)
  {
    displayDetected = true;
  }
  else
  {
    while (1);
  }

  if (displayDetected)
  {
    oled.begin();     // Initialize the OLED
    oled.clear(PAGE); // Clear the display's internal memory
    oled.clear(ALL);  // Clear the library's display buffer
    oled.setFontType(1);
    oled.setColor(BLACK);
    oled.display();   // Display what's in the buffer (splashscreen)
  }
  accl_init(300);
  init_pdm();
}

enum State {IDLE, LOOK, LISTEN, TOUCH};

State curr_state = IDLE;
int counter = 0;

void loop() {
  
  oled.setCursor(0, 0);
  oled.drawBitmap(state_bitmaps[curr_state]);
  oled.setCursor(50, 30);
  oled.write(48 + counter);
  oled.display();
  int _ = accl_sample();
  bool isShaken = accl_isShaken();
  bool isTriggered = process_samples_timeout();

  switch (curr_state) {
    case IDLE:    
      if (isTriggered) { 
        curr_state = LOOK;
        counter = 0;
      }
      break;
    case LOOK:
      if (isTriggered) {
        counter++;
        if (counter == 5) {
          curr_state = LISTEN;
          counter = 0;
        }
      }
      break;
    case LISTEN:
      if (isTriggered) {
        counter++;
        if (counter == 4) {
          curr_state = TOUCH;
          counter = 0;        
        }
      }      
      break;
    case TOUCH:
      if (isTriggered) {
        counter++;
        if (counter == 3) {
          curr_state = IDLE;
          counter = 0;
        }
      }
      break;
  }
}

bool isConnected(uint8_t deviceAddress)
{
  Wire.beginTransmission(deviceAddress);
  if (Wire.endTransmission() == 0)
    return true;
  return false;
}

int mic_isTriggered_count = 0;
bool mic_isTriggered() {
  mic_isTriggered_count ++;
  return mic_isTriggered_count%100 == 0;
}
