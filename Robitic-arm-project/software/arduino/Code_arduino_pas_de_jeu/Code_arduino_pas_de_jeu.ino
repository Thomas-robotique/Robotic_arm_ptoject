#include <Servo.h>

Servo servo1;  // branché sur D2
Servo servo2;  // branché sur D3
Servo servo3;  // branché sur D5

int pos1 = 0;  // position fixe du servo1
int pos2 = 0;  // départ servo2
int cible2 = 100;  // on veut l’amener de 90° à 180°
int cible1= 90;
int pasDeg = 1;    // taille des pas
int delaiMs = 20;  // temps entre chaque pas
int pos3=0;
int cible3 = 180; 


void setup() {
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(5);

  // Initialisation positions
  servo1.write(pos1);
  servo2.write(pos2);
    servo3.write(pos3);

  delay(500);
}

void loop() {
  // Servo1 reste fixe

  // Servo2 bouge doucement de 90 à 180
  for (int angle = pos2; angle <= cible2; angle += pasDeg) {
    servo2.write(angle);
    delay(delaiMs);
  }

  // On revient doucement à 90
  for (int angle = cible2; angle >= pos2; angle -= pasDeg) {
    servo2.write(angle);
    delay(delaiMs);
  }

  for (int angle = pos1; angle <= cible1; angle += pasDeg) {
    servo1.write(angle);
    delay(delaiMs);
  }

   for (int angle = cible1; angle >= pos1; angle -= pasDeg) {
    servo1.write(angle);
    delay(delaiMs);
  }

   for (int angle = pos3; angle <= cible3; angle += 3) {
    servo3.write(angle);
    delay(delaiMs);
  }

  // On revient doucement à 90
  for (int angle = cible3; angle >= pos3; angle -= 3) {
    servo3.write(angle);
    delay(delaiMs);
  }
 
}
