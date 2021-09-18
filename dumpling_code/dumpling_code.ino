//TODO: add stepper motor functions in rotateTable and clampDumpling

#include <Servo.h>

#define DUMPLING_COUNT 6

//TIMINGS
#define LATCH_RETRACT_TIME 1000
#define CUTTER_RETRACT_TIME 1000
#define CUTTER_SHAKE_TIME


//TURNTABLE INDEXING
#define INDEX_USE_FEEDBACK

#ifndef INDEX_USE_FEEDBACK
#define TURN_PER_DUMPLING
#endif

//PINOUTS
#define PUSHER_LATCH_LEFT_PIN 3
#define PUSHER_LATCH_RIGHT_PIN 4
#define PUSHER_CUTTER_PIN 5

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
void clampDumpling()

void setup() {
  // put your setup code here, to run once:
  leftLatchServo.attach(PUSHER_LATCH_LEFT_PIN);
  rightLatchServo.attach(PUSHER_LATCH_RIGHT_PIN);
  cutterServo.attach(PUSHER_CUTTER_PIN);
  pinMode(TURNTABLE_INDEX_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void dropLeftLatch(){
  leftLatchServo.write(PUSHER_LEFT_MIN);
  delay(LATCH_RETRACT_TIME);
  leftLatchServo.write(PUSHER_LEFT_MAX);
}

void dropRightLatch(){
  rightLatchServo.write(PUSHER_RIGHT_MIN);
  delay(LATCH_RETRACT_TIME);
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
  }
  #else
  //rotate table set steps
  #endif
}

void fillDumpling() {
  cutterServo.write(PUSHER_CUTTER_MIN);
  delay(CUTTER_RETRACT_TIME);
  pushMeat();
  cutterServo.write(PUSHER_CUTTER_MAX);
  for(int i = 0; i < 4; i++)
  {
    cutterServo.write(PUSHER_CUTTER_MAX + PUSHER_CUTTER_SHAKE_OFFSET);
    delay(CUTTER_SHAKE_TIME);
    cutterServo.write(PUSHER_CUTTER_MAX + PUSHER_CUTTER_SHAKE_OFFSET);
    delay(CUTTER_SHAKE_TIME);
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
