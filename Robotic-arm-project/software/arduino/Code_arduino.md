# Code Arduino - Bras Robotique

Dans ce document, vous retrouverez l'évolution de mes codes Arduino durant le projet.



## Code


# -1ère version du code arduino, il permet de contrôler les deux premiers servomoteurs.
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

J'ai ajouté une boucle for avec des délais pour ralentir les servomoteurs, ce qui a permis de réduire  le jeu mécanique. 

J'ai également ajouté un 3ᵉ servomoteur, responsable de l'ouverture et de la fermeture de la pince.

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
int position3 = 0;   // ouverture de la pince
int cible3 = 180;    // fermeture de la pince

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
# 3e version du code arduino : contrôle par deux encodeurs

 Ce code permet de contrôler les deux premiers servomoteurs à l’aide de deux encodeurs.
```cpp
#include <Servo.h>

// Encodeur 1 
#define CLK1 12
#define DT1 8
Servo servo1;
int pos1 = 90;               // position initiale
const int min1 = 0;
const int max1 = 180;
int lastCLK1 = HIGH;

//  Encodeur 2
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
 
void loop() {
  //  Encodeur 1 
  int currentCLK1 = digitalRead(CLK1); 
  if (currentCLK1 != lastCLK1 && currentCLK1 == LOW) {
    if (digitalRead(DT1) != currentCLK1) {
      pos1 += 10; // sens horaire
    } else {
      pos1 -= 10; // sens antihoraire
    }

    // Limites
    if (pos1 < min1) pos1 = min1;  // une fois à 0 si l'on continue de diminuer la valeur en tournant                                         l'encodeur, il se bloque et revoie 0 idem pour 180.
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
      pos2 -= 10; // sens antihoraire
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

# code arduino de la vidéo 7 du bras robotique contrôlant la pince, saisie d'objet :

```cpp
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Servo.h>

// INA219
Adafruit_INA219 ina219;

//  Servos
Servo pince;
Servo servo1;
Servo servo2;
Servo servo3;
int angle_servo2_haut=100;
int angle_servo2_bas=51;
int delai=500;
int delai2=1000;

// Pince
const int PIN_SERVO = 11;
const int courantSeuil = 400;    // seuil en mA
const int mesuresConsecutives = 5;  
bool objetSaisi = false;

void setup() {
  Serial.begin(9600);

  // Attacher servos
  servo2.attach(5);
  servo3.attach(6);
  servo1.attach(3);

  pince.attach(PIN_SERVO);
  pince.write(180); // ouverte au départ


  // INA219                                     // Vérifie la connexion correcte de l’INA219 ; facilite le diagnostic en cas d’erreur.
       
  if (!ina219.begin()) {
    Serial.println("INA219 non detecte !");
    while (1);
  }
  ina219.setCalibration_32V_2A();
  Serial.println("Demarrage OK");
}

void loop() {

  //  Séquence de démonstration 

  // Position de départ
  servo1.write(85);
  servo3.write(51);
  delay(delai);

  servo_bouge_lent(angle_servo2_haut,angle_servo2_bas,servo2,20);
  delay(delai);

  ouvrirPince();
  delay(delai2);

  fermerPince();
  delay(delai);

 // Le bras se lève après avoir saisi l'objet
  servo_bouge_lent(angle_servo2_bas,angle_servo2_haut,servo2,20);
  delay(delai);

  servo3.write(80);
  delay(delai); 

// Le bras pivote avec l'objet
  servo1.write(35);
  delay(delai);

  servo3.write(51);
  delay(delai);

// Le bras se baisse avec l'objet
  servo_bouge_lent(angle_servo2_haut,angle_servo2_bas,servo2,20);
  delay(delai);
// Le bras lâche l'objet
  ouvrirPince();
  delay(delai2);

// Le bras reprend l'objet
  fermerPince();
  delay(delai);
// Le bras se lève après avoir saisi l'objet
  servo_bouge_lent(angle_servo2_bas,angle_servo2_haut,servo2,20);
  delay(delai);
 // Le bras recommence

 
  
}



void servo_bouge_lent(int position, int cible, Servo &servo, int delaiMs)
{
  if (position < cible) {
    for (int angle = position; angle <= cible; angle++) {
      servo.write(angle);
      delay(delaiMs);
    }
  } else {
    for (int angle = position; angle >= cible; angle--) {
      servo.write(angle);
      delay(delaiMs);
    }
  }
}

// Fonction pour fermer la pince 
void fermerPince() {
  Serial.println("Fermeture de la pince...");
  pince.attach(PIN_SERVO);
  pince.write(40); // fermée


  int compteur = 0;           // Le compteur sert à compter le nombre de fois que l'intensité du courant est au dessus du seuil                                   
                                // afin d’éviter que la pince interprète une variation de courant anodine comme un objet saisi.


  for (int t = 0; t < 50; t++) {  // surveillance rapide
    float current = ina219.getCurrent_mA();
    Serial.print("Courant pince = ");
    Serial.print(current);
    Serial.println(" mA");

    if (current > courantSeuil) {
      compteur++;                                // À chaque fois que le seuil est dépassé, le compteur est incrémenté de 1.
                
      if (compteur >= mesuresConsecutives)     // Si le compteur dépasse le seuil défini, cela signifie qu’un objet a été détecté par la pince.
{
        Serial.println("Objet saisi ! Servo détaché pour bloquer sans forcer.");
        pince.detach(); // bloque mécaniquement
        objetSaisi = true;
        return;
      }
    } else {
      compteur = 0;
    }
    delay(5);
  }
  objetSaisi = false;
}

//  Fonction pour ouvrir la pince
void ouvrirPince() {
  Serial.println("Ouverture de la pince...");
  pince.attach(PIN_SERVO);
  pince.write(180); // ouverte
  objetSaisi = false;
}
```




# Code Arduino permettant le contrôle du bras robotique et de la pince avec trois encodeurs

```cpp
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Servo.h>

// INA219
Adafruit_INA219 ina219;

//  Servos
Servo pince;
Servo servo1;
Servo servo2;
Servo servo3;
int angle_servo2_haut=100;
int angle_servo2_bas=51;
int delai=500;
int delai2=1000;

// Pince
const int PIN_SERVO = 11;
const int courantSeuil = 400;    // seuil en mA
const int mesuresConsecutives = 5;  
bool objetSaisi = false;

void setup() {
  Serial.begin(9600);

  // Attacher servos
  servo2.attach(5);
  servo3.attach(6);
  servo1.attach(3);

  pince.attach(PIN_SERVO);
  pince.write(180); // ouverte au départ


  // INA219                                     // Vérifie la connexion correcte de l’INA219 ; facilite le diagnostic en cas d’erreur.
       
  if (!ina219.begin()) {
    Serial.println("INA219 non detecte !");
    while (1);
  }
  ina219.setCalibration_32V_2A();
  Serial.println("Demarrage OK");
}

void loop() {

  //  Séquence de démonstration 

  // Position de départ
  servo1.write(85);
  servo3.write(51);
  delay(delai);

  servo_bouge_lent(angle_servo2_haut,angle_servo2_bas,servo2,20);
  delay(delai);

  ouvrirPince();
  delay(delai2);

  fermerPince();
  delay(delai);

 // Le bras se lève après avoir saisi l'objet
  servo_bouge_lent(angle_servo2_bas,angle_servo2_haut,servo2,20);
  delay(delai);

  servo3.write(80);
  delay(delai); 

// Le bras pivote avec l'objet
  servo1.write(35);
  delay(delai);

  servo3.write(51);
  delay(delai);

// Le bras se baisse avec l'objet
  servo_bouge_lent(angle_servo2_haut,angle_servo2_bas,servo2,20);
  delay(delai);
// Le bras lâche l'objet
  ouvrirPince();
  delay(delai2);

// Le bras reprend l'objet
  fermerPince();
  delay(delai);
// Le bras se lève après avoir saisi l'objet
  servo_bouge_lent(angle_servo2_bas,angle_servo2_haut,servo2,20);
  delay(delai);
 // Le bras recommence

 
  
}



void servo_bouge_lent(int position, int cible, Servo &servo, int delaiMs)
{
  if (position < cible) {
    for (int angle = position; angle <= cible; angle++) {
      servo.write(angle);
      delay(delaiMs);
    }
  } else {
    for (int angle = position; angle >= cible; angle--) {
      servo.write(angle);
      delay(delaiMs);
    }
  }
}

// Fonction pour fermer la pince 
void fermerPince() {
  Serial.println("Fermeture de la pince...");
  pince.attach(PIN_SERVO);
  pince.write(40); // fermée


  int compteur = 0;           // Le compteur sert à compter le nombre de fois que l'intensité du courant est au dessus du seuil                                   
                                // afin d’éviter que la pince interprète une variation de courant anodine comme un objet saisi.


  for (int t = 0; t < 50; t++) {  // surveillance rapide
    float current = ina219.getCurrent_mA();
    Serial.print("Courant pince = ");
    Serial.print(current);
    Serial.println(" mA");

    if (current > courantSeuil) {
      compteur++;                                // À chaque fois que le seuil est dépassé, le compteur est incrémenté de 1.
                
      if (compteur >= mesuresConsecutives)     // Si le compteur dépasse le seuil défini, cela signifie qu’un objet a été détecté par la pince.
{
        Serial.println("Objet saisi ! Servo détaché pour bloquer sans forcer.");
        pince.detach(); // bloque mécaniquement
        objetSaisi = true;
        return;
      }
    } else {
      compteur = 0;
    }
    delay(5);
  }
  objetSaisi = false;
}

//  Fonction pour ouvrir la pince
void ouvrirPince() {
  Serial.println("Ouverture de la pince...");
  pince.attach(PIN_SERVO);
  pince.write(180); // ouverte
  objetSaisi = false;
}


```
