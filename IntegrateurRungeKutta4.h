
#pragma once
#include "Integrateur.h"

class IntegrateurRungeKutta4 : public Integrateur {
public:
    // Constructeur avec pas de temps par défaut
    IntegrateurRungeKutta4(double dt = 0.01);
    
    // Implémentation de la méthode d'intégration de Runge-Kutta d'ordre 4
    virtual void integre(ObjetMobile& objet, double temps) const override;
};