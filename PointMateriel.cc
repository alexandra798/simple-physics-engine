#include "PointMateriel.h"
#include "Vecteur.h"
#include "SupportADessin.h"
#include <iostream>
#include <stdexcept>
#include <memory>

// Default constructor
PointMateriel::PointMateriel()
    : ObjetPhysique() {}

// Parameterized constructor
PointMateriel::PointMateriel(const Vecteur& position, const Vecteur& vitesse, double masse,
                           std::shared_ptr<ChampForces> champ,
                           std::shared_ptr<Contrainte> contrainte)
    : ObjetPhysique(position, vitesse, masse, champ, contrainte) {
    // Validate parameters
    if (masse <= 0) {
        throw std::runtime_error("Mass must be positive");
    }
    if (!position.memeDimension(vitesse)) {
        throw std::runtime_error("Position and velocity must have same dimension");
    }
}

void PointMateriel::setMasse(double m) {
    if (m <= 0) {
        throw std::runtime_error("质量必须为正值");
    }
    masse = m;
}

// Evolution equation (F = ma)
Vecteur PointMateriel::evolution(double temps) const {
    // Return force divided by mass (Newton's second law)
    return force(temps) * (1.0 / getMasse());
}

// Output operator
std::ostream& operator<<(std::ostream& os, const PointMateriel& point) {
    // Display mass
    os << point.getMasse() << " # mass" << std::endl;
    
    // Display position
    os << point.position() << " # position" << std::endl;
    
    // Display velocity
    os << point.vitesse() << " # velocity" << std::endl;
    
    // Display force at t=0
    os << point.force(0) << " # force" << std::endl;
    
    return os;
}
