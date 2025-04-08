#include "IntegrateurEulerCromer.h"

// Constructeur - appelle le constructeur de la classe mère
IntegrateurEulerCromer::IntegrateurEulerCromer(double dt)
    : Integrateur(dt) {}

// Méthode d'intégration selon l'algorithme d'Euler-Cromer
void IntegrateurEulerCromer::integre(ObjetMobile& objet, double temps) const {
    // Sauvegarde des états initiaux
    Vecteur pos_initiale = objet.getParametres();
    Vecteur vit_initiale = objet.getDeriveeParametres();
    
    // 1. Mise à jour de la vitesse (méthode d'Euler explicite)
    // v(t+dt) = v(t) + a(t) * dt
    Vecteur acceleration = objet.evolution(temps);
    Vecteur nouvelle_vitesse = vit_initiale + acceleration * pas_temps;
    
    // 2. Mise à jour de la position en utilisant la nouvelle vitesse (semi-implicite)
    // x(t+dt) = x(t) + v(t+dt) * dt
    Vecteur nouvelle_position = pos_initiale + nouvelle_vitesse * pas_temps;
    
    // Mise à jour des paramètres de l'objet
    objet.setParametres(nouvelle_position);
    objet.setDeriveeParametres(nouvelle_vitesse);
}