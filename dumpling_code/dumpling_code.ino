//TODO: add stepper motor functions in rotateTable and clampDumpling

#include <Servo.h>

//for the table
int Pin0 = 5;//definition digital 11 pins as pin to control the IN1 (ULN24L01)
int Pin1 = 4;//definition digital 10 pins as pin to control the IN2 (ULN24L01)
int Pin2 = 3;//definition digital 9 pins as pin to control the IN3 (ULN24L01)
int Pin3 = 2;//definition digital 8 pins as pin to control the IN4 (ULN24L01)

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
#define PUSHER_LATCH_LEFT_PIN 35
#define PUSHER_LATCH_RIGHT_PIN 37
#define PUSHER_CUTTER_PIN 39

#define TURNTABLE_INDEX_PIN 6

//BACK CLAMPER STEPPER PINS
//pins for the back clamper (closer to meat pusher) 
int back_1 = 41;//to control the IN1 (ULN24L01)
int back_2 = 43;//to control the IN2 (ULN24L01)
int back_3 = 45;//to control the IN3 (ULN24L01)
int back_4 = 47;//to control the IN4 (ULN24L01)

//FRONT CLAMPER STEPPER PINS
//pins for the front clamper 
int front_1 = 46;//to control the IN1 (ULN24L01)
int front_2 = 48;//to control the IN2 (ULN24L01)
int front_3 = 50;//to control the IN3 (ULN24L01)
int front_4 = 52;//to control the IN4 (ULN24L01)

//LADLE CLAMPER STEPPER PINS
//pins for the ladle
int ladle_1 = 8;//to control the IN1 (ULN24L01)
int ladle_2 = 9;//to control the IN2 (ULN24L01)
int ladle_3 = 10;//to control the IN3 (ULN24L01)
int ladle_4 = 11;//to control the IN4 (ULN24L01)


//SERVO LIMITS
#define PUSHER_LEFT_MIN 30
#define PUSHER_LEFT_MAX 150

#define PUSHER_RIGHT_MIN 150
#define PUSHER_RIGHT_MAX 30

#define PUSHER_CUTTER_MIN 140
#define PUSHER_CUTTER_SHAKE_OFFSET 30
#define PUSHER_CUTTER_MAX 25

bool leftLatchEngaged = true;
char data; 

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
  cutterServo.write(PUSHER_CUTTER_MAX);
    leftLatchServo.write(PUSHER_LEFT_MAX);
    rightLatchServo.write(PUSHER_RIGHT_MAX);

  //initialize back clamp stepper
  pinMode(back_1, OUTPUT);
  pinMode(back_2, OUTPUT);
  pinMode(back_3, OUTPUT);
  pinMode(back_4, OUTPUT);
  //initialize front clamp stepper
  pinMode(front_1, OUTPUT);
  pinMode(front_2, OUTPUT);
  pinMode(front_3, OUTPUT);
  pinMode(front_4, OUTPUT);
  //initialize ladle stepper
  pinMode(ladle_1, OUTPUT);
  pinMode(ladle_2, OUTPUT);
  pinMode(ladle_3, OUTPUT);
  pinMode(ladle_4, OUTPUT);
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
    delay(100);
    cutterServo.write(PUSHER_CUTTER_MAX);
    delay(100);
  }
}


void makeDumplings() {
  for(int i = 0; i < DUMPLING_COUNT; i++)
  {
    fillDumpling();
    clampDumpling();
    rotateTable();
  }
}

void clampDumpling() {
  //move motors up and down
  moveClampFront(550);
  moveClampBack(550);
  delay(1000);
  moveClampBack(-550);
  moveClampFront(-550);
}

//CLAMPER AND LADLE STEPPER MOTOR FUNCTIONS//
void moveClampFront(int steps)
{
  //positive moves stepper up, negative moves down
  step_front(steps);  
}

void moveClampBack(int steps)
{
  //positive moves stepper up, negative moves down
  step_back(steps);  
}

void moveLadle(int steps)
{
  //positive unravels, negative pulls 
  step_ladle(steps);  
}

void step_front(int _step)//Stepper motor rotation
{
  if(_step>=0){  // Stepper motor forward
    for(int i=0;i<_step;i++){   
      setStepFront(1, 0, 0, 1);
      delay(_speed); 
      setStepFront(1, 0, 0, 0);
      delay(_speed);
      setStepFront(1, 1, 0, 0);
      delay(_speed);
      setStepFront(0, 1, 0, 0);
      delay(_speed);
      setStepFront(0, 1, 1, 0);
      delay(_speed);
      setStepFront(0, 0, 1, 0);
      delay(_speed);
      setStepFront(0, 0, 1, 1);
      delay(_speed); 
      setStepFront(0, 0, 0, 1);
      delay(_speed);
    }
  }else{ // Stepper motor backward
     for(int i=_step;i<0;i++){  
      setStepFront(0, 0, 0, 1);
      delay(_speed);
      setStepFront(0, 0, 1, 1);
      delay(_speed);
      setStepFront(0, 0, 1, 0);
      delay(_speed);
      setStepFront(0, 1, 1, 0);
      delay(_speed);
      setStepFront(0, 1, 0, 0);
      delay(_speed);
      setStepFront(1, 1, 0, 0);
      delay(_speed);
      setStepFront(1, 0, 0, 0);
      delay(_speed);
      setStepFront(1, 0, 0, 1);
      delay(_speed);
    }
   }
}

void step_back(int _step)//Stepper motor rotation
{
  if(_step>=0){  // Stepper motor forward
    for(int i=0;i<_step;i++){   
      setStepBack(1, 0, 0, 1);
      delay(_speed); 
      setStepBack(1, 0, 0, 0);
      delay(_speed);
      setStepBack(1, 1, 0, 0);
      delay(_speed);
      setStepBack(0, 1, 0, 0);
      delay(_speed);
      setStepBack(0, 1, 1, 0);
      delay(_speed);
      setStepBack(0, 0, 1, 0);
      delay(_speed);
      setStepBack(0, 0, 1, 1);
      delay(_speed); 
      setStepBack(0, 0, 0, 1);
      delay(_speed);
    }
  }else{ // Stepper motor backward
     for(int i=_step;i<0;i++){  
      setStepBack(0, 0, 0, 1);
      delay(_speed);
      setStepBack(0, 0, 1, 1);
      delay(_speed);
      setStepBack(0, 0, 1, 0);
      delay(_speed);
      setStepBack(0, 1, 1, 0);
      delay(_speed);
      setStepBack(0, 1, 0, 0);
      delay(_speed);
      setStepBack(1, 1, 0, 0);
      delay(_speed);
      setStepBack(1, 0, 0, 0);
      delay(_speed);
      setStepBack(1, 0, 0, 1);
      delay(_speed);
    }
   }
}

void step_ladle(int _step)//Stepper motor rotation
{
  if(_step>=0){  // Stepper motor forward
    for(int i=0;i<_step;i++){   
      setStepLadle(1, 0, 0, 1);
      delay(_speed); 
      setStepLadle(1, 0, 0, 0);
      delay(_speed);
      setStepLadle(1, 1, 0, 0);
      delay(_speed);
      setStepLadle(0, 1, 0, 0);
      delay(_speed);
      setStepLadle(0, 1, 1, 0);
      delay(_speed);
      setStepLadle(0, 0, 1, 0);
      delay(_speed);
      setStepLadle(0, 0, 1, 1);
      delay(_speed); 
      setStepLadle(0, 0, 0, 1);
      delay(_speed);
    }
  }else{ // Stepper motor backward
     for(int i=_step;i<0;i++){  
      setStepLadle(0, 0, 0, 1);
      delay(_speed);
      setStepLadle(0, 0, 1, 1);
      delay(_speed);
      setStepLadle(0, 0, 1, 0);
      delay(_speed);
      setStepLadle(0, 1, 1, 0);
      delay(_speed);
      setStepLadle(0, 1, 0, 0);
      delay(_speed);
      setStepLadle(1, 1, 0, 0);
      delay(_speed);
      setStepLadle(1, 0, 0, 0);
      delay(_speed);
      setStepLadle(1, 0, 0, 1);
      delay(_speed);
    }
   }
}
void setStepFront(int a, int b, int c, int d)  
{  
    digitalWrite(front_1, a);     
    digitalWrite(front_2, b);     
    digitalWrite(front_3, c);     
    digitalWrite(front_4, d);     
}  
void setStepBack(int a, int b, int c, int d)  
{  
    digitalWrite(back_1, a);     
    digitalWrite(back_2, b);     
    digitalWrite(back_3, c);     
    digitalWrite(back_4, d);     
}  
void setStepLadle(int a, int b, int c, int d)  
{  
    digitalWrite(ladle_1, a);     
    digitalWrite(ladle_2, b);     
    digitalWrite(ladle_3, c);     
    digitalWrite(ladle_4, d);     
}  

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() == 0) {
  
  }
  int myNumber = Serial.parseInt();
  switch(myNumber)
  {
    case 1:
      clampDumpling();
      break;
    case 2:
      moveLadle(-550)
      break;


  }  
}