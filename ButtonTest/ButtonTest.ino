#include "TimmerFunctions.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

const int buttonPins[] = {8, 9, 10, 11, 12}; // Pins for 7 buttons
const int numButtons = 5; // Number of buttons

int hornPinInput = 3; // INPUT
int hornPinOutput = 4; // OUTPUT
int prepPinOutput = 4; // OUTPUT  - Change in the future with more LEDS

int rollingPinOutput = 5; // OUTPUT

// Which sequence the user wants to pick
int minuteMode = 2; // 2 is default, other option is 3
int modeState = 0; // 0 = sequnce select , 10 = countdown

const int resetPin = 2;  // INPUT

volatile bool rolling = false;  // 0 = rolling , 1 = not rolling;
volatile bool prep = false;  // 0 = no prep , 1 = yes prep;


unsigned long lastRollingChangeTime = 0; // Last rolling button state change time
const unsigned long rollingDebounceDelay = 500; // Debounce time in milliseconds for rolling button


unsigned long lastPrepChangeTime = 0; // Last rolling button state change time
const unsigned long prepDebounceDelay = 500; // Debounce time in milliseconds for rolling button




// Contdown Constants
unsigned long startTime;
unsigned long endTime;
unsigned long currentTime;




void setup() {
  Serial.begin(9600); // Initialize serial communication
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Set button pins as inputs with pull-up resistors
  }
  
  //horn
  pinMode(hornPinInput, INPUT_PULLUP);  // Enable the internal pull-up resistor
  pinMode(hornPinOutput, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(hornPinInput), hornPressed, CHANGE);

  pinMode(resetPin, INPUT_PULLUP);  // Enable the internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(resetPin), resetPressed, CHANGE);

  // initialize the lcd
  lcd.init();
  lcd.backlight();

  printTest();
}

void hornPressed() {
  // Check if the button is pressed (LOW state)
  if (digitalRead(hornPinInput) == LOW) {
    digitalWrite(hornPinOutput, HIGH);  // Pull the output pin HIGH
    tone(buzzerPin, 100);
  } else {
    digitalWrite(hornPinOutput, LOW);   // Pull the output pin LOW
    noTone(buzzerPin);

  }
}

void resetPressed() {
  // Read the current state of the button
  bool currentState = digitalRead(resetPin);

  // Check if the button state has changed to LOW (pressed)
  if (currentState == LOW) {
    // Toggle the buttonState variable
    modeState = 0;
  }

  Serial.println("SETUP MODE");
}

void printTest(){
  
  lcd.clear();                 // clear display
  lcd.setCursor(8, 0);         // move cursor to   (0, 0)
  lcd.print("Mode: 2 ");        // print message at (0, 0)
  lcd.setCursor(0, 1);         // move cursor to   (2, 1)
  lcd.print("Roll: 0 Prep: 0"); // print message at (2, 1)

  delay(2000);                 // display the above for two seconds
}

void rollingDebounce(){
  if (millis() - lastRollingChangeTime >= rollingDebounceDelay) {
    rolling = !rolling;
    digitalWrite(rollingPinOutput, rolling);
    Serial.print("Rolling changed to: ");
    Serial.println(rolling);
    lastRollingChangeTime = millis();
  }
}

void prepDebounce(){
  if (millis() - lastPrepChangeTime >= prepDebounceDelay) {
    prep = !prep;
    digitalWrite(prepPinOutput, prep);
    Serial.print("Prepatory Signnal changed to: ");
    Serial.println(prep);
    lastPrepChangeTime = millis();
  }
}

void loop() {
  switch (modeState)
  {
  case 0: // mode sele
        // Read the state of each button and send a text message
    for (int i = 0; i < numButtons; i++) { // We add one here for the start
        int buttonState = digitalRead(buttonPins[i]);
        if (buttonState == LOW) {
          if(i == 0){minuteMode = 3;}
          if(i == 1){minuteMode = 2;}
          if(i == 2){ // this coresponds to input pin 10 and Start Button
              modeState = 10;
              if(prep){PrepHorns();}
              startTime = millis();
              if(minuteMode == 2){endTime = startTime + TWOMIN;}
              if(minuteMode == 3){endTime = startTime + THREEMIN;}
              
          }
          if(i == 3){ // this coresponds to input pin 11 and rolling button
            rollingDebounce();
            delay(10);
            break;
          }
          if(i == 4){ // this coresponds to input pin 12 and prep button
            prepDebounce();
            delay(10);
            break;
          }

          Serial.print("MODE: ");
          Serial.print(minuteMode);
          Serial.println(" minutes");
          } else {
        // code
        }
        delay(10); // Add a small delay to debounce the button (adjust as needed)
    }
  break;

  case 10: // sequence countdown
    currentTime = millis();
    bool completedSequence;

    switch (minuteMode){
      case 2:
          completedSequence = twoMinuteStart(prep, rolling, endTime, currentTime);
          if(completedSequence & rolling){
            startTime = millis();
            endTime = startTime + TWOMIN;
            delay(1000);
          }else if(completedSequence & !rolling){
            modeState = 0;
          }
          break;
      
      case 3:
          threeMinuteStart();
          break;
      
      default:
          break;
    } 

    break;
  
  default:
    break;
  }

}


