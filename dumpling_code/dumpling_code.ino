//TODO: add stepper motor functions in rotateTable and clampDumpling

#include <Servo.h>

int Pin0 = 9;//definition digital 11 pins as pin to control the IN1 (ULN24L01)
int Pin1 = 10;//definition digital 10 pins as pin to control the IN2 (ULN24L01)
int Pin2 = 11;//definition digital 9 pins as pin to control the IN3 (ULN24L01)
int Pin3 = 12;//definition digital 8 pins as pin to control the IN4 (ULN24L01)

int _step = 512; 
int _speed = 1; 

#define MOTORSPEED 15
#define DUMPLING_COUNT 6

//TIMINGS
#define LATCH_RETRACT_TIME 1000
#define CUTTER_RETRACT_TIME 1000
#define CUTTER_SHAKE_TIME


//TURNTABLE INDEXING
//#define INDEX_USE_FEEDBACK

#ifndef INDEX_USE_FEEDBACK
#define TURNS_PER_DUMPLING 500
#endif

//PINOUTS
#define PUSHER_LATCH_LEFT_PIN 2
#define PUSHER_LATCH_RIGHT_PIN 3
#define PUSHER_CUTTER_PIN 4

#define TURNTABLE_INDEX_PIN 6

//SERVO LIMITS
#define PUSHER_LEFT_MIN 30
#define PUSHER_LEFT_MAX 150

#define PUSHER_RIGHT_MIN 30
#define PUSHER_RIGHT_MAX 150

#define PUSHER_CUTTER_MIN 40
#define PUSHER_CUTTER_SHAKE_OFFSET -10
#define PUSHER_CUTTER_MAX 140

bool leftLatchEngaged = true;

Servo leftLatchServo;
Servo rightLatchServo;
Servo cutterServo;

void dropLeftLatch();
void dropRightLatch();
void pushMeat();
void rotateTable();
void fillDumpling();
void makeDumplings();
void clampDumpling();

void Speed(int stepperspeed)//set Stepper speed 
{
    _speed = 15 - stepperspeed;
    if( _speed<1){
     _speed = 1;
    }
    if( _speed>15){
     _speed = 15;
    }
}
void Step(int _step)//Stepper motor rotation
{
  if(_step>=0){  // Stepper motor forward
    for(int i=0;i<_step;i++){   
      setStep(1, 0, 0, 1);
      delay(_speed); 
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed); 
      setStep(0, 0, 0, 1);
      delay(_speed);
    }
  }else{ // Stepper motor backward
     for(int i=_step;i<0;i++){  
      setStep(0, 0, 0, 1);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 1);
      delay(_speed);
    }
   }
}
void setStep(int a, int b, int c, int d)  
{  
    digitalWrite(Pin0, a);     
    digitalWrite(Pin1, b);     
    digitalWrite(Pin2, c);     
    digitalWrite(Pin3, d);     
} 

void setup() {
  // put your setup code here, to run once:
  leftLatchServo.attach(PUSHER_LATCH_LEFT_PIN);
  rightLatchServo.attach(PUSHER_LATCH_RIGHT_PIN);
  cutterServo.attach(PUSHER_CUTTER_PIN);
  pinMode(TURNTABLE_INDEX_PIN, INPUT_PULLUP);
  pinMode(Pin0, OUTPUT);//Set digital 8 port mode, the OUTPUT for the output
  pinMode(Pin1, OUTPUT);//Set digital 9 port mode, the OUTPUT for the output
  pinMode(Pin2, OUTPUT);//Set digital 10 port mode, the OUTPUT for the output
  pinMode(Pin3, OUTPUT);//Set digital 11 port mode, the OUTPUT for the output
  Serial.begin(9600);
}

void dropLeftLatch(){
  leftLatchServo.write(PUSHER_LEFT_MIN);
  delay(1000);
  leftLatchServo.write(PUSHER_LEFT_MAX);
}

void dropRightLatch(){
  rightLatchServo.write(PUSHER_RIGHT_MIN);
  delay(1000);
  rightLatchServo.write(PUSHER_RIGHT_MAX);
}

void pushMeat(){
  if(leftLatchEngaged)
  {
    dropLeftLatch();
  }
  else
  {
    dropRightLatch();
  }
  leftLatchEngaged = !leftLatchEngaged;
}

void rotateTable() {
  #ifdef INDEX_USE_FEEDBACK
  while(digitalRead(TURNTABLE_INDEX_PIN) == HIGH)
  {
    //rotate table
    delay(1);
  }
  #else
  //rotate table set steps
  Speed(MOTORSPEED);//Stepper motor speed = 15 fast (note:speed from 1 to 15)
  Step(TURNS_PER_DUMPLING);//Stepper motor forward 512 steps ---- 360 angle
  #endif
}

void fillDumpling() {
  cutterServo.write(PUSHER_CUTTER_MIN);
  delay(1000);
  pushMeat();
  cutterServo.write(PUSHER_CUTTER_MAX);
  for(int i = 0; i < 4; i++)
  {
    cutterServo.write(PUSHER_CUTTER_MAX + PUSHER_CUTTER_SHAKE_OFFSET);
    delay(30);
    cutterServo.write(PUSHER_CUTTER_MAX);
    delay(30);
  }
}

void clampDumpling() {
  //move motors up and down
}



void makeDumplings() {
  for(int i = 0; i < DUMPLING_COUNT; i++)
  {
    fillDumpling();
    clampDumpling();
    rotateTable();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1);
  if(Serial.available())
  {
    Serial.read();
    rotateTable();
    Serial.write("turning");
    cutterServo.write(PUSHER_CUTTER_MAX);
    leftLatchServo.write(PUSHER_LEFT_MAX);
    
  }
}
