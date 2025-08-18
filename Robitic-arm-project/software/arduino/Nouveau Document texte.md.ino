# Code Arduino






#include <Servo.h>

// C++ code
//
Servo myservo2;
Servo myservo1;
Servo myservo;

            
void setup()
{
  Serial.begin(9600);
   myservo2.attach(4);

myservo1.attach (3) ;
  myservo.attach(2);
  pinMode(7,INPUT);
}

void loop()
{



  
  myservo1.write(180);
  delay(1000);
    myservo1.write(90);
delay(1000);
  myservo.write(180);
  delay(1000);
    myservo.write(90);

 
  

  
}
