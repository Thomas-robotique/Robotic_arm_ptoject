#  Bras Robotique avec Détection de Prise

##  Description du projet
Ce projet est un bras robotique contrôlé par servomoteurs et équipé d’un système de détection automatique d’objet via mesure du courant.  
Il combine mécanique, électronique et, dans les futures étapes, intelligence artificielle pour la reconnaissance et la manipulation d’objets.







## Matériel utilisé
- Arduino UNO R3

- Servomoteurs MG995
- Pince mécanique 
- Capteur INA219 pour mesure de courant
- Structure métallique
- Alimentation externe pour servos

---

## Situation actuelle
En prenant le plan XY comme référence (le sol), le bras peut effectuer grâce au 1er servomoteur, une rotation autour de l’axe Z. Cette rotation est caractérisée par un angle θ, que l’on peut définir comme l’angle entre l’axe X et son image X’. Une fois cette rotation effectuée, on définit le plan X’Z comme le plan qui contient le bras robotique et dans lequel il peut se déplacer.

Sur cette photo, le 1e servomoteur et le 2e (en partant du bas) sont contrôlés par 2 encodeurs rotatifs ( joystik).


Pour une meilleur vidualisation, vous retrouverez différentes vidéos de démonstration du bras robotique ici [Voir le code Arduino](Robitic-arm-project/software/arduino/Code_arduino.md)


La carte électrique permet l'alimentation des deux servomoteurs concernés par les 2 rotations, ainsi que le contrôle des servos par la carte Arduino.

Voici une photo de la  version actuelle du bras robotique

![photo du bras robotique v5](https://github.com/user-attachments/assets/93f615bb-70fa-482b-91ab-54e0d070fe3c)
