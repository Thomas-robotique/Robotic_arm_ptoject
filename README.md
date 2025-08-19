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
En prenant z positif vers le haut et x positif vers nous,
le bras est composé de 2 rotations : une dans le plan xy et une dans le plan xz et yz.
Vous trouverez une vidéo de démonstration du bras dans le dossier hardware/image.
La carte électrique permet l'alimentation des deux servomoteurs concernés par les 2 rotations, ainsi que le contrôle des servos par la carte Arduino.

Voici une photo de la première version du cêblage

<img width="2048" height="1536" alt="Photo du montage du bras robotique" src="https://github.com/user-attachments/assets/a13fcfdc-6194-4018-b971-6d5550d6d26e" />






