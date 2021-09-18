
#include <Servo.h>
#define LED 13

Servo myservo;  
char data;
int pos = 0;

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  myservo.write(0);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {

    data = Serial.read();
    
    if(data == 'a'){
      myservo.write(90);
      digitalWrite(LED, HIGH);
      delay(20);
      Serial.write('a');
       }

      
    }else if(data == 'b'){
      myservo.write(180);
      digitalWrite(LED, LOW);
      delay(20);
      Serial.write('b');
      

    }
  
  }
