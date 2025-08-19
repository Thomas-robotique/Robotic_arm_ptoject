# Code Arduino - Bras Robotique

Dans ce document, vous retrouverez l'évolution de mes codes Arduino durant le projet.

## Description
Ce code contrôle un bras robotique à trois servomoteurs. Chaque servo est attaché à une broche spécifique et effectue des mouvements simples. 

## Code


-1ère version du code arduino, il permet de controller les deux servo moteurs pour la rotation, XY, XZ et YZ
```cpp
#include <Servo.h>

Servo myservo;   // Base
Servo myservo1;  // Articulation 1

void setup() {
    Serial.begin(9600);
    myservo.attach(2);
    myservo1.attach(3);
}

void loop() {
    myservo1.write(180);
    delay(1000);
    myservo1.write(90);
    delay(1000);

    myservo.write(180);
    delay(1000);
    myservo.write(90);
    delay(1000);
}

```

-18/08/2025, 2ᵉ version du code : 

j'ai ajouté une boucle for avec des délais pour ralentir les servomoteurs, ce qui a permis de réduire davantage le jeu mécanique. 

J'ai également ajouté un 3ᵉ servomoteur, responsable de la rotation de la pince.

```cpp
#include <Servo.h>

Servo servo1;  // branché sur D2
Servo servo2;  // branché sur D3
Servo servo3;  // branché sur D5

int position1 = 0;   // position fixe du servo1
int position2 = 0;   // départ servo2
int cible2 = 100;    // on veut l’amener de 90° à 180°
int cible1 = 90;
int delaiMs = 20;    // temps entre chaque pas
int position3 = 0;
int cible3 = 180; 

void setup() {
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(5);

  // Initialisation positions
  servo1.write(position1);
  servo2.write(position2);
  servo3.write(position3);

  delay(500);
}

void loop() {

  // Servo2 bouge doucement de 0 à cible2
  for (int angle = position2; angle <= cible2; ++angle) {
    servo2.write(angle);
    delay(delaiMs);
  }

  // Retour doucement à position2
  for (int angle = cible2; angle >= position2; --angle) {
    servo2.write(angle);
    delay(delaiMs);
  }

  // Servo1 bouge doucement de position1 à cible1
  for (int angle = position1; angle <= cible1; ++angle) {
    servo1.write(angle);
    delay(delaiMs);
  }

  // Retour doucement à position1
  for (int angle = cible1; angle >= position1; --angle) {
    servo1.write(angle);
    delay(delaiMs);
  }

  // Servo3 bouge doucement de position3 à cible3
  for (int angle = position3; angle <= cible3; angle += 3) {
    servo3.write(angle);
    delay(delaiMs);
  }

  // Retour doucement à position3
  for (int angle = cible3; angle >= position3; angle -= 3) {
    servo3.write(angle);
    delay(delaiMs);
  }
}


```
