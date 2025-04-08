
// Integrateur.h
#pragma once
#include "ObjetMobile.h"

class Integrateur {
protected:
    double pas_temps; // Pas d'intégration dt
    
public:
    // Constructeurs
    Integrateur(double dt = 0.01);
    virtual ~Integrateur() = default; // Destructeur virtuel
    
    // Accesseur et modificateur pour le pas de temps
    double getPasTemps() const;
    void setPasTemps(double dt);
    
    // Méthode virtuelle pure pour intégrer un objet mobile sur un pas de temps
    virtual void integre(ObjetMobile& objet, double temps) const = 0;
};