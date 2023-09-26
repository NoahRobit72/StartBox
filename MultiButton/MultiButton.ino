/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button-debounce
 */

#include <ezButton.h>


ezButton button1(1);  // create ezButton object that attach to pin 6;
ezButton button2(8);  // create ezButton object that attach to pin 7;
ezButton button3(9);  // create ezButton object that attach to pin 8;

// Globals
bool repeating = 0;
int inSequence = 0; // 0 = not in sequence and the integers mean the time;
bool startSequence = false;

int relayPin = 4;

int startPin = 7;
int twoMinPin = 8;

int threeMinPin = 9;



unsigned long startTime;
unsigned long endTime;
unsigned long currentTime;

unsigned long timeToStart;

#define THREEMIN 180000
#define TWOMIN 120000

#define ONETHIRTY 90000
#define ONEMIN 60000

#define THIRTYSEC 30000
#define TWENTYSEC 20000
#define TENSEC 10000

#define FIVESEC 5000
#define FOURSEC 4000
#define THREESEC 3000
#define TWOSEC 2000
#define ONESEC 1000



#define MARGIN 75



void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);

  Serial.println("setup complete");
}

void MinuteHorn();



// Horns
void ThreeHorn(){
  Serial.println("Three Minutes");

  // First Horn
  MinuteHorn();

  // Second Horn
  MinuteHorn();

  // Third Horn
  MinuteHorn();
}

void TwoHorn(){
  Serial.println("Two Minutes");

  // First Horn
  MinuteHorn();

  // Second Horn
  MinuteHorn();
}

void OneThirtyHorn(){
  Serial.println("One Minute");

  MinuteHorn();

  // Three short horns
  TenSecHorn();
  TenSecHorn();
  TenSecHorn();
}


void OneHorn(){
  Serial.println("One Minute");
  MinuteHorn();
}

void ThirtyHorn(){
  Serial.println("Three short horns");
  delay(1000);

  TenSecHorn();
  TenSecHorn();
  TenSecHorn();
}

void TwentyHorn(){
  Serial.println("Two short horns");
  TenSecHorn();
  TenSecHorn();

}

void TenHorn(){
  Serial.println("One short horn");
  TenSecHorn();
}

void Go(){
  digitalWrite(relayPin, HIGH);
  delay(1300);
  digitalWrite(relayPin, LOW);
}


// Component Horns
void TenSecHorn(){
  digitalWrite(relayPin, HIGH);
  delay(100);

  digitalWrite(relayPin, LOW);
  delay(50);
}

void MinuteHorn(){
  digitalWrite(relayPin, HIGH);
  delay(1000);

  digitalWrite(relayPin, LOW);
  delay(300);

}

void SingleHorn(){
  digitalWrite(relayPin, HIGH);
  delay(500);
  digitalWrite(relayPin, LOW);
}


// Modes
void TwoMinINIT(){
  inSequence = 2;
  Serial.println("Mode: 2 minute start");
}

void OneMinINIT(){
  inSequence = 1;
  Serial.println("Mode: 1 minute start");
}




String ReturnTime(unsigned long time){
  unsigned long totalSeconds = time / 1000;

  unsigned int minutes = totalSeconds / 60;
  unsigned int seconds = totalSeconds % 60;
  
  String stringPrint = String(minutes) + ":" + String(seconds);
  return stringPrint;
}

void StartAction(){
  switch (inSequence)
  {
  case 2:
      startTime = millis();
      endTime = startTime + TWOMIN;
    break;
  
  default:
    break;
  }
}



void loop() {
  currentTime = millis();
  // Serial.println(currentTime - startTime);

  if(startSequence){

  }
  else{
    switch (inSequence) {
      case 1:
      if(currentTime == startTime){ThreeHorn();}
        // statements
        break;

      //
      case 2:
        timeToStart = endTime - currentTime;
        Serial.print("Entered case 2 with insequence value of:");
        Serial.println(inSequence);
        
        // Will print on the screen in the future
        Serial.println(ReturnTime(timeToStart));

        if( (timeToStart < (TWOMIN + MARGIN)) & (timeToStart > (TWOMIN - MARGIN)) ){TwoHorn();} // two min start

        if( (timeToStart < (ONETHIRTY + MARGIN)) & (timeToStart > (ONETHIRTY - MARGIN)) ){OneThirtyHorn();} // one thirty min start

        if( (timeToStart < (ONEMIN + MARGIN)) & (timeToStart > (ONEMIN - MARGIN)) ){OneHorn();} // one min start

        if( (timeToStart < (THIRTYSEC + MARGIN)) & (timeToStart > (THIRTYSEC - MARGIN)) ){ThirtyHorn();} // two min start
        if( (timeToStart < (TWENTYSEC + MARGIN)) & (timeToStart > (TWENTYSEC - MARGIN)) ){TwentyHorn();} // two min start
        if( (timeToStart < (TENSEC + MARGIN)) & (timeToStart > (TENSEC - MARGIN)) ){TenHorn();} // two min start

        if( (timeToStart < (FIVESEC + MARGIN)) & (timeToStart > (FIVESEC - MARGIN)) ){SingleHorn();} // two min start
        if( (timeToStart < (FOURSEC + MARGIN)) & (timeToStart > (FOURSEC - MARGIN)) ){SingleHorn();} // two min start
        if( (timeToStart < (THREESEC + MARGIN)) & (timeToStart > (THREESEC - MARGIN)) ){SingleHorn();} // two min start
        if( (timeToStart < (TWOSEC + MARGIN)) & (timeToStart > (TWOSEC - MARGIN)) ){SingleHorn();} // two min start
        if( (timeToStart < (ONESEC + MARGIN)) & (timeToStart > (ONESEC - MARGIN)) ){SingleHorn();} // two min start

        if( (timeToStart < (50))){ // two min start

          Go();
          
          if(!repeating){
            Serial.println("insequence is now 0");
            inSequence = 0;
            delay(1000);
            Serial.print("Entered leaving with insequence value of:");
            Serial.println(inSequence);
        
          }
          else{
            TwoMinINIT();
            Serial.print("I am going to repeat");
          } 
        }
        delay(25);
        // statements
        break;
      case 3:
        // statements
        break;

      default:
        // statements
        break;
    }
  }

  if(!inSequence){}
    if(digitalRead(twoMinPin)){
      Serial.print("Button two was pressed");
      TwoMinINIT();
    }

    if(digitalRead(startPin)){
      startSequence = true;
      StartAction();
      
    }
  }

