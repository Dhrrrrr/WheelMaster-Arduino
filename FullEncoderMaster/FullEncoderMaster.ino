/*

*/
#include <SoftwareSerial.h>
SoftwareSerial Master(2,3); // RX TX
bool runThrough;

// Pin inputs
const int firePin = 5;

const int bridge1Pin1 = 7;
const int bridge1Pin2 = 8;

const int bridge2Pin1 = 11;
const int bridge2Pin2 = 12;

void setup() {
    Master.begin(9600);
    Serial.begin(9600);

    // First H-Bridge Pins
    pinMode(bridge1Pin1, INPUT_PULLUP);
    pinMode(bridge1Pin2, INPUT_PULLUP); 

    // Second H-Bridge Pins
    pinMode(bridge2Pin1, INPUT_PULLUP);
    pinMode(bridge2Pin2, INPUT_PULLUP); 

    // Launch Pin
    pinMode(firePin, INPUT_PULLUP);
}

void loop() {
  int state = 0;

  // First digit is for H-Bridge 1, Second digit is for H-Bridge 2, Third digit is for fire control
  
  // If statement for fire control bridge
  if(digitalRead(firePin) == HIGH) {
    state += 100;
  }
  else {
    state += 200;
  }

  // Second round of if statements for the second H-Bridge
  if (digitalRead(bridge2Pin1) == HIGH) {
    state += 10;
  }
  else if (digitalRead(bridge2Pin2) == HIGH) {
    state += 20;
  }
  else {
    state += 30;
  }

  // Final round of if statements for the last H-Bridge
    if (digitalRead(bridge1Pin1) == HIGH) {
    state += 8;
  }
  else if (digitalRead(bridge1Pin2) == HIGH) {
    state += 6;
  }
  else {
    state += 4;
  }
  
  // Output to serial and master (note: serial is for testing and can be removed)
  Master.write(state);
  Serial.println(state);
}
