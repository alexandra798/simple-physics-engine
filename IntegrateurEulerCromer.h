#pragma once
#include "Integrateur.h"

class IntegrateurEulerCromer : public Integrateur {
public:
    // Constructeur avec pas de temps par défaut
    IntegrateurEulerCromer(double dt = 0.01);
    
    // Implémentation de la méthode d'intégration d'Euler-Cromer
    virtual void integre(ObjetMobile& objet, double temps) const override;
};