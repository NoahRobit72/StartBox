#include "TimmerFunctions.h"
#include <LiquidCrystal_I2C.h>
#include "PinChangeInterrupt.h"


LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

const int SEQUENCE_BUTTON = 7;
const int START_BUTTON = 9;
const int ROLLING_BUTTON =  10;


const int numButtons = 5; // Number of buttons

const int resetPin = 12;  // INPUT // Need to make interupt
const int hornPinInput = 2; // INPUT


// Which sequence the user wants to pick
int minuteMode = 2; // 2 is default, other option is 3
int modeState = 0; // 0 = sequnce select , 10 = countdown

int threeInSix = 0;


volatile bool rolling = false;  // 0 = rolling , 1 = not rolling;
volatile bool prep = false;  // 0 = no prep , 1 = yes prep;


unsigned long lastRollingChangeTime = 0; // Last rolling button state change time
const unsigned long rollingDebounceDelay = 500; // Debounce time in milliseconds for rolling button

unsigned long lastPrepChangeTime = 0; // Last rolling button state change time
const unsigned long prepDebounceDelay = 500; // Debounce time in milliseconds for rolling button

unsigned long lastSecChangeTime = 0; // Last rolling button state change time
const unsigned long SecDebounceDelay = 500; // Debounce time in milliseconds for rolling button

const char* sampleText = "SETUP";

char PreviousModeOrTime[16] = "";  // Assuming a maximum length of 16 characters
char PreviousPrepString[16] = ""; // Assuming a maximum length of 16 characters
char PreviousRollString[16] = ""; // Assuming a maximum length of 16 characters
char PreviousSequenceString[16] = ""; // Assuming a maximum length of 16 characters




// Contdown Constants
unsigned long startTime;
unsigned long endTime;
unsigned long currentTime;




void setup() {
  Serial.begin(9600); // Initialize serial communication

  //SEQUENCE_BUTTON = 7;
  //START_BUTTON = 9;
  //ROLLING_BUTTON =  10;

  // INPUT Buttons
  pinMode(SEQUENCE_BUTTON, INPUT_PULLUP); // Set button pins as inputs with pull-up resistors
  pinMode(START_BUTTON, INPUT_PULLUP); // Set button pins as inputs with pull-up resistors
  pinMode(ROLLING_BUTTON, INPUT_PULLUP); // Set button pins as inputs with pull-up resistors


  
  //horn
  pinMode(hornPinInput, INPUT_PULLUP);  // Enable the internal pull-up resistor
  pinMode(hornPinOutput, OUTPUT);
  pinMode(buzzerOutput, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(hornPinInput), hornPressed, CHANGE);

  pinMode(resetPin, INPUT_PULLUP);  // Enable the internal pull-up resistor
  // attachInterrupt(digitalPinToInterrupt(resetPin), resetPressed, CHANGE);
  
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(resetPin), resetPressed, CHANGE); // interrupt connected to pin 11x  

  // initialize the lcd
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  printTest(minuteMode, rolling, prep, modeState, stringTime);
}

void hornPressed() {
  // Check if the button is pressed (LOW state)
  Serial.println("HORN");
  if (digitalRead(hornPinInput) == LOW) {
    digitalWrite(hornPinOutput, HIGH);  // Pull the output pin HIGH
  } else {
    digitalWrite(hornPinOutput, LOW);   // Pull the output pin LOW
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

void printTest(int minuteMode, bool rolling, bool prep, int modeState, String timeText) {
  char modeOrTime[16] = "SETUP";  // Temporary storage for new value
  char prepString[16] = "Prep: 0"; // Temporary storage for new value
  char rollString[16] = "Roll: 0"; // Temporary storage for new value
  char sequenceString[16] = ""; // Temporary storage for new value

  if (modeState == 10) {
    strcpy(modeOrTime, timeText.c_str()); // Copy the new value into the temporary storage
  }
  if (prep) {
    strcpy(prepString, "Prep: 1"); // Copy the new value into the temporary storage
  }
  if (rolling) {
    strcpy(rollString, "Roll: 1"); // Copy the new value into the temporary storage
  }
  switch (minuteMode)
  {
  case 0:
    strcpy(sequenceString, "2 Min"); // Copy the new value into the temporary storage
    break;
  
    case 1:
    strcpy(sequenceString, "3 Min"); // Copy the new value into the temporary storage
    break;
  
    case 2:
    strcpy(sequenceString, "3 in 6"); // Copy the new value into the temporary storage
    break;

    case 3:
    strcpy(sequenceString, "5 Min"); // Copy the new value into the temporary storage
    break;
  
  default:
    break;
  }

  bool modeChanged = strcmp(modeOrTime, PreviousModeOrTime);
  bool prepChanged = strcmp(prepString, PreviousPrepString);
  bool rollChanged = strcmp(rollString,  PreviousRollString);
  bool sequenceChanged = strcmp(sequenceString, PreviousSequenceString);


  if(modeChanged || prepChanged || rollChanged || sequenceChanged){
    // debug print
    Serial.println(sequenceString);

    lcd.clear();
    lcd.setCursor(0, 0);         // move cursor to   (0, 0)
    lcd.print(modeOrTime);        // print message at (0, 0)
    Serial.println(modeOrTime);

    lcd.setCursor(8, 0);         // move cursor to   (0, 0)
    lcd.print(sequenceString);        // print message at (0, 0)

    lcd.setCursor(0, 1);         // move cursor to   (2, 1)
    lcd.print(rollString); // print message at (2, 1)

    // lcd.setCursor(8, 1);         // move cursor to   (2, 1)
    // lcd.print(prepString); // print message at (2, 1)

  }

  // Update the previous values with the new values
  strcpy(PreviousModeOrTime, modeOrTime);
  strcpy(PreviousPrepString, prepString);
  strcpy(PreviousRollString, rollString);
  strcpy(PreviousSequenceString, sequenceString);

  delay(10); // display the above for two seconds
}


void rollingDebounce(){
  if (millis() - lastRollingChangeTime >= rollingDebounceDelay) {
    rolling = !rolling;
    Serial.print("Rolling changed to: ");
    Serial.println(rolling);
    lastRollingChangeTime = millis();
  }
}

void secquenceDebounce(){
  if (millis() - lastSecChangeTime >= SecDebounceDelay) {
    minuteMode++;
    lastSecChangeTime = millis();

    if(minuteMode > 3){
      minuteMode = 0;
    }

    Serial.print("Starting sequence mode changed to: ");
    Serial.println(minuteMode);
  }
}

void loop() {
  returnInfo returnData;

  switch (modeState){
    case 0: // mode select 

      //SEQUENCE_BUTTON = 7;
      //START_BUTTON = 9;
      //ROLLING_BUTTON =  10;   

      if(!digitalRead(7)){
        secquenceDebounce();
        delay(10);
      }

      if(!digitalRead(9)){ // this coresponds to input pin 10 and Start Button
        modeState = 10;
        {PrepHorns();}
        startTime = millis();
        if(minuteMode == 0){endTime = startTime + TWOMIN;}
        if(minuteMode == 1){endTime = startTime + THREEMIN;}  
        if(minuteMode == 2){endTime = startTime + TWOMIN;}  
        if(minuteMode == 3){endTime = startTime + FIVEMINUTES;}   

      }
      break;

    case 10: // sequence countdown
      currentTime = millis();
      switch (minuteMode){
        case 0:
            returnData = twoMinuteStart(prep, rolling, endTime, currentTime);
            if(returnData.completed & rolling){
              startTime = millis();
              endTime = startTime + TWOMIN;
              delay(1000);
            }else if(returnData.completed & !rolling){
              modeState = 0;
            }
            break;
        
        case 1:
            returnData = threeMinuteStart(prep, rolling, endTime, currentTime);
            if(returnData.completed & rolling){
              startTime = millis();
              endTime = startTime + THREEMIN;
              delay(1000);
            }else if(returnData.completed & !rolling){
              modeState = 0;
            }
            break;

          case 2:
            returnData = threeInSixStart(prep, rolling, endTime, currentTime);
            if(returnData.completed){
              threeInSix++;
              startTime = millis();
              endTime = startTime + TWOMIN;
              delay(1000);
            }
            if(threeInSix == 3){
              modeState = 0;
              threeInSix = 0;
            }
            break;

          case 3: // five minutes
            returnData = fiveMinuteStart(prep, rolling, endTime, currentTime);
            if(returnData.completed & rolling){
              startTime = millis();
              endTime = startTime + FIVEMINUTES;
              delay(1000);
            }else if(returnData.completed & !rolling){
              modeState = 0;
            }
            break;

        default:
            break;
      } 
    break;
  
  default:
    break;
  }
  
  printTest(minuteMode, rolling, prep, modeState, returnData.stringTime);
  if(!digitalRead(10)){ // this coresponds to input pin 11 and rolling button
    rollingDebounce();
    delay(10);
  }
}


