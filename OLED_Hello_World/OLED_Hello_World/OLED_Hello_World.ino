//Documentation for the U8g2lib is available here:
//https://github.com/olikraus/u8g2/wiki/u8g2reference#drawbitmap
#include <U8g2lib.h>
#include <Wire.h> //Wire.h needed since the screen uses I2C

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

//Setting variables for strings
String directions = "NA";
String distance = "N";

boolean newData = false;
const byte numChars = 50;
char receivedChars[numChars];   // an array to store the received data


//Starting text position for the direction instruction display
int currentY = 10;

int updateRate = 2000;

void setup(void) {
  //Setting all of the buttons as inputs

  //Starting u8g2
  u8g2.begin();
  Serial.begin(38400);
  delay(50);
  Serial.flush();
  Serial.print("START\n");
  Serial.print("check\n");
}

void loop(void) {
  while (directions == "NA") {
    recvWithEndMarker();
    for (int i = 0; i < 10; i++) {
      Serial.print(directions[i]);
    }
    Serial.print("\n");  
  }
 
  
  //creating maneuversymbol variable
  //Determines if maneuver contains left or right and will display arrow
  String maneuverSymbol;
  if (distance.indexOf("left") != -1) { 
      maneuverSymbol = "<-"; 
  } else if (distance.indexOf("right") != -1) { 
     maneuverSymbol = "->"; 
  } else { 
     maneuverSymbol = " "; 
  }

  //Reading the button state
 
   
  u8g2.clearBuffer(); // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

  // Segment 1 (Will have 3 lines of text
  // Limit text to 20 characters
  String tempDirections = directions; // Create a copy of the directions string
  while (tempDirections.length() > 0) {
    int lineLength = min(20, tempDirections.length()); // Maximum 20 characters per line
    int lastSpace = tempDirections.lastIndexOf(' ', lineLength); // Find last space within limit

    if (lastSpace != -1) {
      // Print up to last space and move to next line
      u8g2.setCursor(0, currentY);
      u8g2.print(tempDirections.substring(0, lastSpace));
      tempDirections.remove(0, lastSpace + 1);
    } else {
      // Print remaining text and break
      u8g2.setCursor(0, currentY);
      u8g2.print(tempDirections);
      tempDirections = "";
    }

    currentY += 10; // Move to next line
  }

  // Draw line after Segment 1
  u8g2.drawHLine(0, 32, 128);


  // Segment 2 (Large numbers)
  u8g2.setFont(u8g2_font_ncenB14_tr); // Choose a larger font
  u8g2.setCursor(0, 55); // Adjust vertical spacing
  u8g2.print("1234m");


  // Segment 3
  // Limit text to 10 characters
  u8g2.setCursor(95, 55);
  u8g2.print(maneuverSymbol);// Draw an arrow

  u8g2.sendBuffer(); // transfer internal memory to the display
  delay(updateRate); // Delay for the update
  currentY = 10;

}

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();
        Serial.print(rc);
        delay(50);

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        } 
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
       
}
