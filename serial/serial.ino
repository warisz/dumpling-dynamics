
#include <Servo.h>

Servo myservo;  
char data;
int pos = 0;

void setup() {
  myservo.attach(9);  
  Serial.begin(9600);
  myservo.write(0);
}

void loop() {
  if (Serial.available() > 0) {

    data = Serial.read();
    
    if(data == 'a'){
      myservo.write(90);
       }
      Serial.write('a');
      
    }else if(data == 'b'){
      myservo.write(180);
      delay(20);
      Serial.write('b');
      

    }
  
  }
