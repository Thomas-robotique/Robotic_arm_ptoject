# Code Arduino - Bras Robotique

Dans ce document, vous retrouverez l'évolution de mes codes Arduino durant le projet.



## Code


# -1ère version du code arduino, il permet de controller les deux servo moteurs pour la rotation du 1er et 2e servomoteur.
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

# 2ᵉ version du code : 

j'ai ajouté une boucle for avec des délais pour ralentir les servomoteurs, ce qui a permis de réduire davantage le jeu mécanique. 

J'ai également ajouté un 3ᵉ servomoteur, responsable de l'ouverture et de la pince.

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
# 3e version du code arduino : contrôle par 2 encodeurs
```cpp
#include <Servo.h>

// === Encodeur 1 ===
#define CLK1 12
#define DT1 8
Servo servo1;
int pos1 = 90;               // position initiale
const int min1 = 0;
const int max1 = 180;
int lastCLK1 = HIGH;

// === Encodeur 2 ===
#define CLK2 2
#define DT2 7
Servo servo2;
int pos2 = 90;               // position initiale
const int min2 = 0;
const int max2 = 180;
int lastCLK2 = HIGH;

void setup() {
  pinMode(CLK1, INPUT_PULLUP);
  pinMode(DT1, INPUT_PULLUP);
  pinMode(CLK2, INPUT_PULLUP);
  pinMode(DT2, INPUT_PULLUP);

  Serial.begin(9600);

  // Attachement des servos
  servo1.attach(3);  // servo 1 sur D3
  servo2.attach(5);  // servo 2 sur D5

  // Position initiale
  servo1.write(pos1);
  servo2.write(pos2);
}
f 
void loop() {
  //  Encodeur 1 
  int currentCLK1 = digitalRead(CLK1); 
  if (currentCLK1 != lastCLK1 && currentCLK1 == LOW) {
    if (digitalRead(DT1) != currentCLK1) {
      pos1 += 10; // sens horaire
    } else {
      pos1 -= 10; // sens antihoraire, une fois à 0 si l'on continue de diminuer la valeur en tournant l'encodeur, il se bloque et revois 0 idem pour 180.
    }

    // Limites
    if (pos1 < min1) pos1 = min1;
    if (pos1 > max1) pos1 = max1;

    servo1.write(pos1);
    Serial.print("Servo1 = "); Serial.println(pos1);
  }
  lastCLK1 = currentCLK1;

  // Encodeur 2 
  int currentCLK2 = digitalRead(CLK2);
  if (currentCLK2 != lastCLK2 && currentCLK2 == LOW) { 
    if (digitalRead(DT2) != currentCLK2) {
      pos2 += 10; // sens horaire
    } else {
      pos2 -= 10; // sens antihoraire,
    }

    // Limites
    if (pos2 < min2) pos2 = min2;
    if (pos2 > max2) pos2 = max2;

    servo2.write(pos2);
    Serial.print("Servo2 = "); Serial.println(pos2);
  }
  lastCLK2 = currentCLK2;
}


```

# code arduino controlant la pince, saisi d'objet :

```cpp
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Servo.h>

Adafruit_INA219 ina219;
Servo pince;

const int courantSeuil = 600; // mA
int targetPos = 180;          // position cible initiale
bool objetSaisi = false;

void setup() {
  Serial.begin(9600);
  ina219.begin();
  pince.attach(11);
  Serial.println("Systeme demarre");
}

void loop() {
  // Aller vers la cible
  pince.write(targetPos);

  // Surveiller pendant 1s environs, ( mesures au cour du mouvement)
  for (int t = 0; t < 100; t++) {
    float current = ina219.getCurrent_mA();
    float voltage = ina219.getBusVoltage_V();

// print de la tension et du courant et de l'état de la pince (entrain de fermer ou d'ouvrire)
    Serial.print("Cible: "); Serial.print(targetPos);
    Serial.print(" | Tension: "); Serial.print(voltage);
    Serial.print(" V | Courant: "); Serial.print(current);
    Serial.println(" mA");

    // Détection objet uniquement en fermeture (vers 20),Quand la pince se ferme, elle se positionne à 180 degrés, et lorsqu’elle s’ouvre, elle revient à 20 degrés.

    if (targetPos == 20 && current > courantSeuil) {
      Serial.println(" Objet detecte donc servo desactive !");
      objetSaisi = true;

      // On coupe le signal du servo, il garde sa position mécanique sans forcer pour maintenir l'objet saisi
      pince.detach();
      break;
    }

    delay(10);
  }

  // Si objet saisi, on attend avant de repartir
  if (objetSaisi) {
    delay(10000);             // garde l'objet sans forcer pendant 10s
    objetSaisi = false;

    // On réattache le servo pour pouvoir le bouger de nouveau
    pince.attach(11);
    targetPos = 20;          // repartir en ouverture
  } else {
    // Sinon on alterne simplement
    if (targetPos == 180) targetPos = 20;
    else targetPos = 180;
  }
}
```
