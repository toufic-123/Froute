// Example 2 - Receive with an end-marker

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data


boolean message_received = false;
boolean newData = false;

void setup() {
    Serial.begin(9600);
    delay(1);
    Serial.print("@");
    Serial.print("Wazzup!\n");
}

void loop() {
    Serial.print("Message 1\n");
    Serial.print("Toufic; more like Threefic\n");
    Serial.print("Is this good?\n");
    Serial.print("Frig me >:)))\n");
    Serial.print("Looks good king <3\n");
    }
