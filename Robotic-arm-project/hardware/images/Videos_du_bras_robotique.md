# Suivi du fonctionnement du bras articulé

Ce document présente, dans l’ordre chronologique, les différentes étapes d’évolution du bras robotisé.  
Chaque vidéo illustre une amélioration technique, comme la résolution d’un bug, la correction d’un problème mécanique ou l’ajout d’une nouvelle fonctionnalité.

---

### - 17/08/2025 20:28, Suivi du développement, Bras robotique
1ʳᵉ vidéo du bras : il dispose de deux rotations, mais présente encore du jeu mécanique à corriger.  
[Voir la vidéo](https://youtu.be/0k7IBRY94nI)

---

### - 18/08/2025 9:23, Suivi du développement, Bras robotique
- Correction du code de pilotage des servomoteurs afin de réduire le jeu mécanique ([Voir le code Arduino](../../software/arduino/Code_arduino.md))  
- Fixation du bras sur une planche en bois pour limiter les vibrations  
- Ajout d’une nouvelle articulation destinée à soutenir la pince  

2ᵉ vidéo du bras robotique : [2e vidéo][https://youtu.be/2np7a8PfgLk](https://youtu.be/2np7a8PfgLk)

#### Points d’amélioration futurs :
- Améliorer encore le jeu mécanique  
- Finaliser la fixation de la pince  

---

### - 19/08/2025 13:20, Suivi du développement, Bras robotique
- Modification de la fixation du servomoteur situé au sommet du bras pour réduire le jeu mécanique et améliorer l’angle de rotation  

3ᵉ vidéo du bras robotique : [3e vidéo](https://youtu.be/AkJcX3Q7wKA)
#### Points d’amélioration futurs :
- Optimiser davantage la mécanique pour stabiliser le bras  
- Finaliser la fixation de la pince  
- Réduire le jeu mécanique  

---

### - 27/08/2025 22:56, Suivi du développement, Bras robotique
- Ajout d’un encodeur rotatif pour contrôler la rotation du premier servomoteur  

4ᵉ vidéo du bras robotique : [4e vidéo](https://youtu.be/zPzh-STQNL8)

#### Points d’amélioration futurs :
- Finaliser la fixation de la pince  
- Ajouter 2 encodeurs supplémentaires  
- Réduire le jeu mécanique  

---

### - 28/08/2025 22:04, Suivi du développement, Bras robotique
- Ajout d’un 2ᵉ encodeur pour le second servomoteur  
- Ajout de 2 pieds métalliques afin de supprimer le jeu mécanique  
- Reprise du câblage sur breadboard pour un montage plus propre  

5ᵉ vidéo du bras robotique : [5e vidéo](https://youtu.be/TMBsFKxXWAc)

#### Points d’amélioration futurs :
- Finaliser la fixation de la pince  
- Ajouter 1 encodeur supplémentaire  
- Réaliser une vidéo de meilleure qualité (meilleure luminosité)  

---

### - 06/09/2025 20:42, Suivi du développement, Bras robotique
- Ajout de deux pieds métalliques supplémentaires (équerres usinées) pour réduire le jeu mécanique  
- Fixation définitive de la pince et vérification de la capacité des servomoteurs à supporter son poids  
- Amélioration de la partie électrique (meilleure tenue des composants, réduction des faux contacts)  

6ᵉ vidéo du bras robotique : [6e vidéo](https://youtu.be/Qs0z032AmsQ)

- Mise en fonctionnement de la pince avec détection de la saisie d’objet (arrêt automatique pour éviter la surchauffe)  
- Intégration d’un capteur INA219 en série avec le servomoteur pour surveiller le courant. Lorsque le capteur détecte un pic prolongé (objet saisi), le code stoppe la pince.  
[Voir le code Arduino](../../software/arduino/Code_arduino.md)  

Vidéo de la pince : [vidéo de la pince](https://youtu.be/Qs0z032AmsQ)

#### Points d’amélioration futurs :
- Réduire encore le jeu mécanique  
- Regrouper toutes les fonctionnalités du bras (déplacement + saisie d’objet) dans un seul code  

---

### - 19/09/2025 16:04, Suivi du développement, Bras robotique
Le bras robotique est désormais pleinement fonctionnel : il combine les mouvements du bras et la saisie d’objets avec la pince.  
Le montage final de la pince avait déjà été réalisé le 06/09/2025. Un code Arduino complet a ensuite été développé pour piloter l’ensemble du bras et la pince.  

Une séquence de démonstration a été programmée : le bras saisit un objet, le déplace puis le relâche.  

7ᵉ vidéo du bras robotique en fonctionnement : [7e vidéo](https://youtu.be/GEP4Osftczw)

#### Points d’amélioration futurs :
- Améliorer l’esthétique et la sécurité du bras  
- Organiser et sécuriser le câblage afin d’éviter tout faux contact ou court-circuit  
