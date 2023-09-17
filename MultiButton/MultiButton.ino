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
bool repeating;
int inSequence = 0; // 0 = not in sequence and the integers mean the time;

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


#define MARGIN 10



void setup() {
  Serial.begin(9600);
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50); // set debounce time to 50 milliseconds
  button3.setDebounceTime(50); // set debounce time to 50 milliseconds

  Serial.println("setup complete");
}

// Horns
void ThreeHorn(){
  Serial.println("Three long horns");
}

void TwoHorn(){
  Serial.println("Two long horns");
  delay(1000);

}

void OneThirtyHorn(){
  Serial.println("One long horn and three short");
  delay(1000);

}

void OneHorn(){
  Serial.println("One long horn");
  delay(1000);


}

void ThirtyHorn(){
  Serial.println("Three short horns");
  delay(1000);


}

void TwentyHorn(){
  Serial.println("Two short horns");
  delay(1000);

}

void TenHorn(){
  Serial.println("One short horn");
  delay(1000);

}

void FiveTilGo(){
  Serial.println("5,4,3,2,1, go horns");
  delay(1000);
  inSequence = false;
}

String ReturnTime(unsigned long time){
  unsigned long totalSeconds = time / 1000;

  unsigned int minutes = totalSeconds / 60;
  unsigned int seconds = totalSeconds % 60;


  
  String stringPrint = String(minutes) + ":" + String(seconds);
  return stringPrint;
}



void loop() {
  currentTime = millis();
  // Serial.println(currentTime - startTime);

  switch (inSequence) {
    case 1:
    if(currentTime == startTime){ThreeHorn();}
      // statements
      break;
    
    //
    case 2:
      timeToStart = endTime - currentTime;
      Serial.println(ReturnTime(timeToStart));


      if( (timeToStart < (TWOMIN + MARGIN)) & (timeToStart > (TWOMIN - MARGIN)) ){TwoHorn();} // two min start

      if( (timeToStart < (ONETHIRTY + MARGIN)) & (timeToStart > (ONETHIRTY - MARGIN)) ){OneThirtyHorn();} // two min start
      if( (timeToStart < (ONEMIN + MARGIN)) & (timeToStart > (ONEMIN - MARGIN)) ){OneHorn();} // two min start

      if( (timeToStart < (THIRTYSEC + MARGIN)) & (timeToStart > (THIRTYSEC - MARGIN)) ){ThirtyHorn();} // two min start
      if( (timeToStart < (TWENTYSEC + MARGIN)) & (timeToStart > (TWENTYSEC - MARGIN)) ){TwentyHorn();} // two min start
      if( (timeToStart < (TENSEC + MARGIN)) & (timeToStart > (TENSEC - MARGIN)) ){TenHorn();} // two min start

      if( (timeToStart < (FIVESEC + MARGIN)) & (timeToStart > (FIVESEC - MARGIN)) ){FiveTilGo();} // two min start

      // statements
      break;
    case 3:
      // statements
      break;
    default:
      // statements
      break;
  }

  if(!inSequence){
    button1.loop(); // MUST call the loop() function first
    button2.loop(); // MUST call the loop() function first
    button3.loop(); // MUST call the loop() function first

    if(button1.isPressed()){ // reset start
      
    }

    if(button2.isPressed()){
        startTime = millis();
        endTime = startTime + TWOMIN;
        inSequence = 2;
        Serial.println("This is the two Minute Start");
    }

    if(button3.isPressed()){
        startTime = millis();
        endTime = startTime + THREEMIN;
        inSequence = 3;
        Serial.println("This is the three Minute Start");
    }
  }
}
