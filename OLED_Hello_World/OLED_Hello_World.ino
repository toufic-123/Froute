#include <Arduino.h>
//Documentation for the U8g2lib is available here:
//https://github.com/olikraus/u8g2/wiki/u8g2reference#drawbitmap
#include <U8g2lib.h>
//Wire.h needed since the screen uses I2C
#include <Wire.h>

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
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.clearBuffer(); // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

  // Segment 1 (Will have 3 lines of text
  // Limit text to 20 characters
  u8g2.setCursor(0,10);
  u8g2.print("Head south on ");
  u8g2.setCursor(0,20);
  u8g2.print("116 St NW toward ");
  u8g2.setCursor(0,30);
  u8g2.print("Green & Gold Trl");

  // Draw line after Segment 1
  u8g2.drawHLine(0, 32, 128);


  // Segment 2 (Large numbers)
  u8g2.setFont(u8g2_font_ncenB14_tr); // Choose a larger font
  u8g2.setCursor(0, 55); // Adjust vertical spacing
  u8g2.print("1234");
  u8g2.print("m");


  // Segment 3
  // Limit text to 10 characters
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.drawGlyph(95, 55, 0x23f6); // Draw an arrow

  u8g2.sendBuffer(); // transfer internal memory to the display
  delay(1000);
}
