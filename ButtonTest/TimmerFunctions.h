#include "string.h"

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
const int buzzerPin = 6;

bool prepDone = 0;
int count = 0;



//////////////////////////
//    Component Horns   //
//////////////////////////
void TenSecHorn(){
  tone(buzzerPin, 100);  
  delay(500);

  noTone(buzzerPin);  
  delay(100);
}

void MinuteHorn(){
  tone(buzzerPin, 100);  
  delay(1250);

  noTone(buzzerPin);  
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
  tone(buzzerPin,100);
  delay(500);
  noTone(buzzerPin);}

void Go(){
  tone(buzzerPin,100);
  delay(1300);
  noTone(buzzerPin);
}

void PrepHorns(){
  Serial.println("running the prep signal");
  for (int i = 0; i < 7; i++) //13 * 400 ms = 
  {
    tone(buzzerPin,100);
    delay(200);
    noTone(buzzerPin);
    delay(200);
  }
  delay(5000); // delay 5 seconds
  for (int i = 0; i < 5; i++) //5 * 1000ms
  {
    tone(buzzerPin,400);
    delay(800);
    noTone(buzzerPin);
    delay(200);
  }
}

////////////////////////
//    Alt Functions   //
////////////////////////

String ReturnTime(unsigned long time){
  unsigned long totalSeconds = time / 1000;

  unsigned int minutes = totalSeconds / 60;
  unsigned int seconds = totalSeconds % 60;
  
  String stringPrint = String(minutes) + ":" + String(seconds);
  return stringPrint;
}


/////////////////////////////
//    Sequence Functions   //
/////////////////////////////
void threeMinuteStart(){

  
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
