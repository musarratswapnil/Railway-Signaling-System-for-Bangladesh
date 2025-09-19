#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <ESP32Servo.h>

// Track sensor pins
const int trackPins[4] = {2, 18, 4, 5}; // Track 1 to 4

// Signal LED pins for each signal
const int outerRed = 14;
const int outerYellow1 = 15;
const int outerYellow2 = 16;
const int outerGreen = 13;

const int homeRed = 19;
const int homeYellow = 33;
const int homeGreen = 26;

const int starterRed = 12;
const int starterYellow = 25;
const int starterGreen = 17;

const int advStarterRed = 27;
const int advStarterGreen = 32;

// Variables to store the state of each light
bool lastState[4] = {LOW, LOW, LOW, LOW};
bool currentState[4] = {LOW, LOW, LOW, LOW};
Servo myServo;

void updateSignals();

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // I2C pins for ESP32
  myServo.attach(23);


  // Set Track Pins as INPUT_PULLDOWN (prevents floating)
  for (int i = 0; i < 4; i++) {
    pinMode(trackPins[i], INPUT_PULLDOWN);
  }

  

  // Set signal pins as OUTPUT
  pinMode(outerRed, OUTPUT);
  pinMode(outerYellow1, OUTPUT);
  pinMode(outerYellow2, OUTPUT);
  pinMode(outerGreen, OUTPUT);

  pinMode(homeRed, OUTPUT);
  pinMode(homeYellow, OUTPUT);
  pinMode(homeGreen, OUTPUT);

  pinMode(starterRed, OUTPUT);
  pinMode(starterYellow, OUTPUT);
  pinMode(starterGreen, OUTPUT);

  pinMode(advStarterRed, OUTPUT);
  pinMode(advStarterGreen, OUTPUT);

  digitalWrite(outerGreen, HIGH); // Start with all signals green

    digitalWrite(homeGreen, HIGH);
    digitalWrite(starterGreen, HIGH);
    digitalWrite(advStarterGreen, HIGH);

  delay(2000);
 
}

void loop() {
  bool updateNeeded = false;
if (Serial.available() > 0) {  // Check if data is available to read
    char input = Serial.read();  // Read the incoming byte

    if (input == '1') {
      myServo.write(180);  // Move the servo to 170 degrees
      Serial.println("Servo moved to 170 degrees");
    }
    else if (input == '0') {
      myServo.write(30);   // Move the servo to 30 degrees
      Serial.println("Servo moved to 30 degrees");
    }
  }
  // Check track states
  for (int i = 0; i < 4; i++) {
    currentState[i] = digitalRead(trackPins[i]);

    // if (currentState[i] != lastState[i]) {
    //   updateNeeded = true;
    //   lastState[i] = currentState[i];
    // }

    if (currentState[i] != lastState[i]) {
        if (currentState[i] == HIGH) {
          Serial.print("Train DETECTED on Track ");
          Serial.println(i + 1);
        } else {
          Serial.print("Train LEFT from Track ");
          Serial.println(i + 1);
        }
        updateNeeded = true;
        lastState[i] = currentState[i];
      }
  
  }

  // Read loop line
  
//   if (currentLoopLineState != lastLoopLineState) {
//     updateNeeded = true;
//     lastLoopLineState = currentLoopLineState;
//   }


  if (updateNeeded) {
    updateSignals();
  }

  delay(100);
}

void updateSignals() {
  // Default: Turn off all signals
  digitalWrite(outerRed, LOW);
  digitalWrite(outerYellow1, LOW);
  digitalWrite(outerYellow2, LOW);
  digitalWrite(outerGreen, LOW);

  digitalWrite(homeRed, LOW);
  digitalWrite(homeYellow, LOW);
  digitalWrite(homeGreen, LOW);

  digitalWrite(starterRed, LOW);
  digitalWrite(starterYellow, LOW);
  digitalWrite(starterGreen, LOW);

  digitalWrite(advStarterRed, LOW);
  digitalWrite(advStarterGreen, LOW);

  // Track 1: Outer Red Signal
  if (currentState[0] == HIGH) {
    digitalWrite(outerRed, HIGH);
    // digitalWrite(outerGreen, LOW);
    // digitalWrite(outerYellow1, LOW);
    // digitalWrite(outerYellow2, LOW);
    // digitalWrite(homeRed, LOW);
    // digitalWrite(homeYellow, LOW);
    digitalWrite(homeGreen, HIGH);
    // digitalWrite(starterRed, LOW);
    // digitalWrite(starterYellow, LOW);
    digitalWrite(starterGreen, HIGH);
    // digitalWrite(advStarterRed, LOW);
    digitalWrite(advStarterGreen, HIGH);
  }  
//   if (currentState[0] == LOW){
//     digitalWrite(outerGreen, HIGH);
//     digitalWrite(outerRed, LOW);
//     digitalWrite(outerYellow1, LOW);
//     digitalWrite(outerYellow2, LOW);
//     digitalWrite(homeRed, LOW);
//     digitalWrite(homeYellow, LOW);  
//     digitalWrite(homeGreen, HIGH);
//     digitalWrite(starterRed, LOW);
//     digitalWrite(starterYellow, LOW);
//     digitalWrite(starterGreen, HIGH);
//     digitalWrite(advStarterRed, LOW);
//     digitalWrite(advStarterGreen, HIGH);
//   }

  // Track 2: Outer Red Signal (if Track 1 is occupied)
  else if (currentState[1] == HIGH) {
    digitalWrite(outerRed, HIGH);
    // digitalWrite(outerYellow1, LOW);
    // digitalWrite(outerYellow2, LOW);
    // digitalWrite(outerGreen, LOW);
    digitalWrite(homeRed, HIGH);

    // digitalWrite(homeYellow, HIGH);
    // digitalWrite(homeGreen, LOW);
    // digitalWrite(starterRed, LOW);
    // digitalWrite(starterYellow, LOW);
     digitalWrite(starterGreen, HIGH);
    // digitalWrite(advStarterRed, LOW);
    digitalWrite(advStarterGreen, HIGH);
  } 
//   else if (currentState[1] == LOW) {
//     digitalWrite(homeRed, LOW);
//     digitalWrite(homeGreen, HIGH);
//   }

  // Track 3: Home Red and Outer Yellow1
  else if (currentState[2] == HIGH) {
    digitalWrite(homeRed, HIGH);
    // digitalWrite(homeYellow, LOW);
    // digitalWrite(outerRed, LOW);
    digitalWrite(outerYellow1, HIGH);
    digitalWrite(starterRed, HIGH);
    // digitalWrite(homeGreen, LOW);
    // digitalWrite(starterGreen, LOW);
    // digitalWrite(outerGreen, LOW);
    // digitalWrite(starterYellow, LOW);
    // digitalWrite(advStarterRed, LOW);
    digitalWrite(advStarterGreen, HIGH);
  } 
//   else if (currentState[2] == LOW) {
//     digitalWrite(starterRed, LOW);
//     digitalWrite(starterYellow, HIGH);
//     digitalWrite(starterGreen, LOW);
//     digitalWrite(homeRed, LOW);
//     digitalWrite(homeGreen, HIGH);
//     digitalWrite(homeYellow, LOW);
//     digitalWrite(outerRed, LOW);
//     digitalWrite(outerYellow1, LOW);
//     digitalWrite(outerYellow2, LOW);
//     digitalWrite(outerGreen, HIGH);

//   }

  // Track 4: Starter Red, Home Yellow, Outer Yellow1 & Yellow2
  else if (currentState[3] == HIGH) {
    digitalWrite(starterRed, HIGH);
    digitalWrite(homeYellow, HIGH);
    digitalWrite(outerYellow1, HIGH);
    digitalWrite(outerYellow2, HIGH);
    digitalWrite(advStarterRed, HIGH);
    // digitalWrite(outerGreen, LOW);
    // digitalWrite(homeGreen, LOW);
    // digitalWrite(starterGreen, LOW);
    // digitalWrite(advStarterGreen, LOW);
    digitalWrite(starterYellow, HIGH);
    // digitalWrite(outerRed, LOW);
    // digitalWrite(homeRed, LOW); 
  }
  if(currentState[0] == HIGH && currentState[2] == HIGH){
    digitalWrite(outerRed, HIGH);
    digitalWrite(homeRed, HIGH);
    digitalWrite(starterRed, HIGH);
    digitalWrite(advStarterGreen, HIGH);
    digitalWrite(homeGreen, LOW);
    digitalWrite(starterGreen, LOW);


  }
  if(currentState[3] == HIGH && currentState[0] == HIGH){
    digitalWrite(outerRed, HIGH);
    digitalWrite(homeYellow, HIGH);
    digitalWrite(starterRed, HIGH);
    digitalWrite(advStarterRed, HIGH);
    digitalWrite(homeGreen, LOW);
    digitalWrite(starterGreen, LOW);
    digitalWrite(advStarterGreen, LOW);


  }
  if(currentState[3] == HIGH && currentState[1] == HIGH){
    digitalWrite(homeRed, HIGH);
    digitalWrite(outerRed, HIGH);
    digitalWrite(starterRed, HIGH);
    digitalWrite(advStarterRed, HIGH);
    digitalWrite(homeGreen, LOW);
    digitalWrite(starterGreen, LOW);
    digitalWrite(advStarterGreen, LOW);


  }

  // If tracks are not occupied, turn on green signals
  else if (currentState[0] == LOW && currentState[1] == LOW && currentState[2] == LOW && currentState[3] == LOW) {
    digitalWrite(outerGreen, HIGH);
    digitalWrite(homeGreen, HIGH);
    digitalWrite(starterGreen, HIGH);
    digitalWrite(advStarterGreen, HIGH);
  }

 
}