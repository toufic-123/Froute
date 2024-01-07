#include <Arduino.h>
//Documentation for the U8g2lib is available here:
//https://github.com/olikraus/u8g2/wiki/u8g2reference#drawbitmap
#include <U8g2lib.h>
#include <Wire.h> //Wire.h needed since the screen uses I2C
#include <ezButton.h> 

/* configuring u8g2
 *  SSD1306 based OLED display
 *  128x64 is the display resolution
 *  NONAME Generic display model without a specific manufacturer
 *  F font mode for better text rendering
 *  SW_I2C uses software controlled I2C
 *  U8G2_R0 specifies the rotation of the display
 *  SCL Assigns the SDA pin for I2C communication
 *  SDA Assigns the SDA pin for I2C communication
 *  U8x8_PIN_NONE indicates that no dedicated reset pin is not being used for the display
 */
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

const int nextButton = 3;
const int backButton = 4;

ezButton buttonnext(nextButton);  // create ezButton object that attach to pin 3;
ezButton buttonback(backButton);  // create ezButton object that attach to pin 4;

String distance[] = {"24 m", "170 m", "85 m"};
String maneuver[] = {"ahead", "left", "right"};

int currentY = 10;
int updaterate = 2000;
int currentindex = 0;  // to keep track of the current direction

void setup(void) {
  u8g2.begin();
  buttonnext.setDebounceTime(50); // set debounce time to 50 milliseconds
  buttonback.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop(void) {
  buttonnext.loop(); // must call the loop() function first
  buttonback.loop(); // must call the loop() function first

  if (buttonnext.isPressed()) {
    currentindex = (currentindex + 1) % 3; 
  } else if (buttonback.isPressed()) {
    currentindex = (currentindex - 1 + 3) % 3;
  }
 
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.setCursor(0, 32);
  u8g2.print(distance[currentindex]);
  u8g2.setCursor(65, 32);
  u8g2.print(maneuver[currentindex]);
  u8g2.sendBuffer();
  delay(updaterate);
}
