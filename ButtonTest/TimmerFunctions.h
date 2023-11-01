#include "string.h"

#define FIVEMINUTES 300000
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


struct returnInfo{
  String stringTime;
  bool completed;
};
 
unsigned long timeToStart = -1;
String stringTime = "not set";

bool prepDone = 0;
int count = 0;

const int hornPinOutput = A3; // OUTPUT
const int buzzerOutput = 13; // OUTPUT



//////////////////////////
//    Component Horns   //
//////////////////////////
void TenSecHorn(){
  digitalWrite(hornPinOutput, HIGH);  
  delay(500);

  digitalWrite(hornPinOutput, LOW); 
  delay(100);
}

void MinuteHorn(){
  digitalWrite(hornPinOutput, HIGH); 
  delay(1250);

  digitalWrite(hornPinOutput, LOW);  
  delay(300);

}


///////////////////////
//    Minute Horns   //
///////////////////////
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


//////////////////////
//    Second Horns  //
//////////////////////
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

void SingleHorn(){
  digitalWrite(hornPinOutput, HIGH);
  delay(500);
  digitalWrite(hornPinOutput, LOW);
}

void Go(){
  digitalWrite(hornPinOutput, HIGH);
  delay(1300);
  digitalWrite(hornPinOutput, LOW);
}

void PrepHorns(){
  Serial.println("running the prep signal");
  for (int i = 0; i < 5; i++) //13 * 400 ms = 
  {
    digitalWrite(hornPinOutput, HIGH);
    delay(200);
    digitalWrite(hornPinOutput, LOW);
    delay(200);
  }
  delay(2500); // delay 5 seconds
}

////////////////////////
//    Alt Functions   //
////////////////////////

String ReturnTime(unsigned long time){
  Serial.print("Total time (ms) is: ");
  Serial.println(time);
  unsigned long totalSeconds = time / 1000;
  Serial.print("Total time (sec) is: ");
  Serial.println(totalSeconds);

  unsigned int minutes = totalSeconds / 60;
  unsigned int seconds = totalSeconds % 60;
  
  String stringPrint = String(minutes) + ":" + String(seconds);
  Serial.println(stringPrint);
  return stringPrint;
}


/////////////////////////////
//    Sequence Functions   //
/////////////////////////////

returnInfo threeMinuteStart(bool prep, bool rolling, unsigned long endTime, unsigned long currentTime){
    returnInfo returnData;

    returnData.completed = false;
    timeToStart = endTime - currentTime;
     // Will print on the screen in the futur

    returnData.stringTime = ReturnTime(timeToStart);

    if( (timeToStart < (THREEMIN + MARGIN + 50)) & (timeToStart > (THREEMIN - MARGIN - 50)) ){ThreeHorn();} // two min start

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

      if( (timeToStart < (MARGIN + MARGIN))){ // two min start
        Go();
        returnData.completed = true;
      }
  return returnData;
}

returnInfo twoMinuteStart(bool prep, bool rolling, unsigned long endTime, unsigned long currentTime){
    returnInfo returnData;

    returnData.completed = false;
    timeToStart = endTime - currentTime;
     // Will print on the screen in the futur

    returnData.stringTime = ReturnTime(timeToStart);

    if( (timeToStart < (TWOMIN + MARGIN + 50)) & (timeToStart > (TWOMIN - MARGIN - 50)) ){TwoHorn();} // two min start

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

      if( (timeToStart < (MARGIN + MARGIN))){ // two min start
        Go();

        returnData.completed = true;
      }
  return returnData;
}

returnInfo threeInSixStart(bool prep, bool rolling, unsigned long endTime, unsigned long currentTime){
    returnInfo returnData;

    returnData.completed = false;
    timeToStart = endTime - currentTime;
     // Will print on the screen in the futur

    returnData.stringTime = ReturnTime(timeToStart);

    if( (timeToStart < (TWOMIN + MARGIN + 50)) & (timeToStart > (TWOMIN - MARGIN - 50)) ){TwoHorn();} // two min start

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

      if( (timeToStart < (MARGIN + MARGIN))){ // two min start
        Go();
        returnData.completed = true;
      }
  return returnData;
}

returnInfo fiveMinuteStart(bool prep, bool rolling, unsigned long endTime, unsigned long currentTime){
    returnInfo returnData;

    returnData.completed = false;
    timeToStart = endTime - currentTime;
     // Will print on the screen in the futur

    returnData.stringTime = ReturnTime(timeToStart);

    if( (timeToStart < (FIVEMINUTES + MARGIN + 50)) & (timeToStart > (FIVEMINUTES - MARGIN - 50)) ){OneHorn();} // two min start
    if( (timeToStart < (FIVEMINUTES - ONEMIN + MARGIN + 50)) & (timeToStart > (FIVEMINUTES - ONEMIN- MARGIN - 50)) ){OneHorn();} // two min start
    if( (timeToStart < (ONEMIN + MARGIN)) & (timeToStart > (ONEMIN - MARGIN)) ){OneHorn();} // one min start
    if( (timeToStart < (MARGIN + MARGIN))){ // two min start
      OneHorn();
      returnData.completed = true;
    }
  return returnData;
}
