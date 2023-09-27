
int startPin = 7;
int twoMinPin = 8;
int threeMinPin = 9;

int startLED = 2;
int twoMinLED = 3;
int threeMinLED = 4;

int mode;

bool startStatus;
bool twoMinStatus;
bool threeMinStatus;

bool startState;
bool twoMinState;
bool threeMinState;

// Which time the start is in
int startMode = 





void setup() {
    Serial.begin(9600);
    pinMode(startLED, OUTPUT);
    pinMode(twoMinLED, OUTPUT);
    pinMode(threeMinLED, OUTPUT);
}

void loop() {

  startStatus = digitalRead(startPin);
  if(startStatus){
    mode = 1;
    startState = 1;
    digitalWrite(startLED, 1);
  };



  switch (mode)
  {
  case 1: // Start the time
    Serial.println("hi");
    break;

  case 2: // Change Mode
    if(digitalRead(twoMinPin)){startMode = 2;}
    else if(digitalRead(threeMinPin)){startMode = 3;}
    break;
  
  default:
    break;
  }

  twoMinStatus = digitalRead(twoMinPin);
  threeMinStatus = digitalRead(threeMinPin);

  if(startStatus){Serial.println("Start High");}
  if(twoMinStatus){Serial.println("Two High");}
  if(threeMinStatus){Serial.println("Three High");}

  delay(250);
}


