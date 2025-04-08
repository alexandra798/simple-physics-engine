
// Integrateur.cc
#include "Integrateur.h"
#include <stdexcept>

// Constructeur avec pas de temps
Integrateur::Integrateur(double dt) {
    if (dt <= 0) {
        throw std::runtime_error("Le pas de temps doit être strictement positif");
    }
    pas_temps = dt;
}

// Accesseur pour le pas de temps
double Integrateur::getPasTemps() const {
    return pas_temps;
}

// Modificateur pour le pas de temps
void Integrateur::setPasTemps(double dt) {
    if (dt <= 0) {
        throw std::runtime_error("Le pas de temps doit être strictement positif");
    }
    pas_temps = dt;
}