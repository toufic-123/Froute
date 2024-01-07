// Example 2 - Receive with an end-marker
#include <SoftwareSerial.h>

const byte numChars = 60;
char receivedChars[numChars];   // an array to store the received data
String distance[20];
String instructions[20];
String manuevre[20];
String list[61];
int end_index = 0;
int state = 0;

const int PREPARING = 0;
const int TRAVELLING = 1;


boolean newData = false;

void setup() {
    Serial.begin(38400);
    delay(50);
    Serial.flush();
    Serial.print("START\n");
}

void loop() {
//    Serial.print("a");
    switch(state) {
        case PREPARING:
            recvWithEndMarker();
            showNewData();
            break;
        case TRAVELLING:
//            for (int i = 0; i <= end_index; i++) {
//                Serial.print(list[i] + "\n");
//                delay(50);
//            }
            break;
        default:
            ;
            break;
    }
    
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
    if (list[end_index] == "STOP") {
        state = TRAVELLING;
        Serial.print("Travellingnow...\n");
        delay(50);
        return;
    } else {
        list[end_index] = receivedChars;
        end_index++;
    }
    
    
    
}

void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        delay(50);
        Serial.println(receivedChars);
        delay(50);
        newData = false;
    }
}
