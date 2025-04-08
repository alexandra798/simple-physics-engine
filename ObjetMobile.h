
// ObjetMobile.h
#pragma once
#include "Vecteur.h"

class ObjetMobile {
private:
    Vecteur parametres;         // Vecteur E (degrés de liberté)
    Vecteur derivee_parametres; // Vecteur E' (dérivée temporelle)

public:
    // Constructeurs
    ObjetMobile();
    ObjetMobile(const Vecteur& param, const Vecteur& deriv);
    virtual ~ObjetMobile() = default; // Destructeur virtuel
    
    // Accesseurs
    const Vecteur& getParametres() const;
    const Vecteur& getDeriveeParametres() const;
    
    // Modificateurs
    void setParametres(const Vecteur& param);
    void setDeriveeParametres(const Vecteur& deriv);
    
    // Méthode virtuelle pure représentant l'équation d'évolution f(t, E, E')
    virtual Vecteur evolution(double temps) const = 0;
    
    // Surcharge de l'opérateur << pour l'affichage
    friend std::ostream& operator<<(std::ostream& os, const ObjetMobile& obj);
};