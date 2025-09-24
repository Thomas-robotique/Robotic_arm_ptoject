'''cpp
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor

# Charger ton dataset
data = pd.read_csv("dataset.csv")

# Entrées (X) = capteur
X = data[["angle_capteur", "distance_cm"]]

# Sorties (y) = angles des servos
y = data[["servo1_angle", "servo2_angle", "servo3_angle"]]

# Séparation train/test
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Modèle
model = RandomForestRegressor()
model.fit(X_train, y_train)

# Évaluer
score = model.score(X_test, y_test)
'''
print("Précision du modèle :", score)

# Exemple de prédiction
prediction = model.predict([[45, 12]])  # angle capteur = 45°, distance = 12 cm
print("Angles prédits :", prediction)

