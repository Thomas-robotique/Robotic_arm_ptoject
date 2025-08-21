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
En prenant le plan XY comme référence (le sol), le bras peut effectuer une rotation autour de l’axe Z. Cette rotation est caractérisée par un angle θ, que l’on peut définir comme l’angle entre l’axe X et son image X’. Une fois cette rotation effectuée, on définit le plan X’Z comme le plan dans lequel le bras peut se déplacer.
Sur cette photo, le servomoteur responsable de la rotation dans le plan X’Z autour de Y' est contrôlé par un encodeur rotatif ( comme un joystik).


Pour une meilleur vidualisation, vous retrouverez une vidéo de démonstration du bras dans le dossier hardware/image.
La carte électrique permet l'alimentation des deux servomoteurs concernés par les 2 rotations, ainsi que le contrôle des servos par la carte Arduino.

Voici une photo de la première version du cêblage

<img width="2048" height="1536" alt="Photo du montage du bras robotique" src="https://github.com/user-attachments/assets/a13fcfdc-6194-4018-b971-6d5550d6d26e" />






