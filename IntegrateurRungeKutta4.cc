

#include "IntegrateurRungeKutta4.h"

// Constructeur - appelle le constructeur de la classe mère
IntegrateurRungeKutta4::IntegrateurRungeKutta4(double dt)
    : Integrateur(dt) {}

// Méthode d'intégration selon l'algorithme de Runge-Kutta d'ordre 4
void IntegrateurRungeKutta4::integre(ObjetMobile& objet, double temps) const {
    // Sauvegarde des états initiaux
    Vecteur pos_initiale = objet.getParametres();
    Vecteur vit_initiale = objet.getDeriveeParametres();
    
    // Étape 1: Calcul de k1 (utilisation des valeurs initiales)
    Vecteur k1_vit = objet.evolution(temps) * pas_temps;
    Vecteur k1_pos = vit_initiale * pas_temps;
    
    // Étape 2: Calcul de k2 (utilisation de k1 à mi-pas)
    objet.setParametres(pos_initiale + k1_pos * 0.5);
    objet.setDeriveeParametres(vit_initiale + k1_vit * 0.5);
    Vecteur k2_vit = objet.evolution(temps + pas_temps * 0.5) * pas_temps;
    Vecteur k2_pos = (vit_initiale + k1_vit * 0.5) * pas_temps;
    
    // Étape 3: Calcul de k3 (utilisation de k2 à mi-pas)
    objet.setParametres(pos_initiale + k2_pos * 0.5);
    objet.setDeriveeParametres(vit_initiale + k2_vit * 0.5);
    Vecteur k3_vit = objet.evolution(temps + pas_temps * 0.5) * pas_temps;
    Vecteur k3_pos = (vit_initiale + k2_vit * 0.5) * pas_temps;
    
    // Étape 4: Calcul de k4 (utilisation de k3 à pas complet)
    objet.setParametres(pos_initiale + k3_pos);
    objet.setDeriveeParametres(vit_initiale + k3_vit);
    Vecteur k4_vit = objet.evolution(temps + pas_temps) * pas_temps;
    Vecteur k4_pos = (vit_initiale + k3_vit) * pas_temps;
    
    // Calcul de la nouvelle position et vitesse en utilisant la moyenne pondérée
    Vecteur nouvelle_position = pos_initiale + (k1_pos + k2_pos * 2.0 + k3_pos * 2.0 + k4_pos) * (1.0 / 6.0);
    Vecteur nouvelle_vitesse = vit_initiale + (k1_vit + k2_vit * 2.0 + k3_vit * 2.0 + k4_vit) * (1.0 / 6.0);
    
    // Mise à jour des paramètres de l'objet
    objet.setParametres(nouvelle_position);
    objet.setDeriveeParametres(nouvelle_vitesse);
}