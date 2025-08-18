# Code Arduino - Bras Robotique

Dans ce document, vous retrouverez l'évolution de mes codes Arduino durant le projet.

## Description
Ce code contrôle un bras robotique à trois servomoteurs. Chaque servo est attaché à une broche spécifique et effectue des mouvements simples. 

## Code

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

