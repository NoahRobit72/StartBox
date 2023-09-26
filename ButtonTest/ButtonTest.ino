const int buttonPins[] = {8, 9, 10, 11}; // Pins for 7 buttons
const int numButtons = 4; // Number of buttons
const int minuteButtons = 2; // Number of minute options

int hornPinInput = 3;
int hornPinOutput = 4;

int rollingPinOutput = 5;

// Which sequence the user wants to pick
int minuteMode = 2; // 2 is default, other option is 3

// The state of the box
int modeState = 0; // 0 = sequnce select , 10 = countdown

const int resetPin = 2;  // Pin for the button
volatile bool rolling = false;  // 0 = rolling , 1 = not rolling;

unsigned long lastRollingChangeTime = 0; // Last rolling button state change time
const unsigned long rollingDebounceDelay = 500; // Debounce time in milliseconds for rolling button



void setup() {
  Serial.begin(9600); // Initialize serial communication
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Set button pins as inputs with pull-up resistors
  }
  
  //horn
  pinMode(hornPinInput, INPUT_PULLUP);  // Enable the internal pull-up resistor
  pinMode(hornPinOutput, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(hornPinInput), hornPressed, CHANGE);


  pinMode(resetPin, INPUT_PULLUP);  // Enable the internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(resetPin), resetPressed, CHANGE);


}

void hornPressed() {
  // Check if the button is pressed (LOW state)
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

void loop() {
  switch (modeState)
  {
  case 0: // mode sele
        // Read the state of each button and send a text message
    for (int i = 0; i < numButtons; i++) { // We add one here for the start
        int buttonState = digitalRead(buttonPins[i]);
        if (buttonState == LOW) {
          if(i == 0){ // this coresponds to input pin 8 and 3 minute button
              minuteMode = 3;
          }
          if(i == 1){ // this coresponds to input pin 9 and 2 minute button
              minuteMode = 2;
          }
          if(i == 2){ // this coresponds to input pin 10 and Start Button
              modeState = 10;
          }
          if(i == 3){ // this coresponds to input pin 11 and rolling putton
            rollingDebounce();
            delay(10);
            break;
          }
          Serial.print("The mode is: ");
          Serial.println(minuteMode);
          } else {
        // code
        }
        delay(10); // Add a small delay to debounce the button (adjust as needed)
    }
  break;

  case 10: // sequence countdown

    // allows you to turn off the rolling while in sequence
    int buttonState = digitalRead(buttonPins[3]);
    if(!buttonState){
      rollingDebounce();
    }

    Serial.print("This code will run a sequence for a ");
    Serial.print(minuteMode);
    Serial.println(" minute sequence.");
    Serial.println("//////////");
    Serial.println("Sequence started");
    delay(1000);
    Serial.println("Sequence ended");
    Serial.println("//////////");
    if(rolling){
      modeState = 10;
    }else{
      modeState = 0;
    }
    break;
  
  default:
    break;
  }

}


