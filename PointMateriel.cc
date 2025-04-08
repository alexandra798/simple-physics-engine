#include "PointMateriel.h"
#include "Vecteur.h"
#include <iostream>
#include <stdexcept>
#include <memory>

// Constructeur par défaut
PointMateriel::PointMateriel()
    : ObjetPhysique() {}

// Constructeur avec paramètres
PointMateriel::PointMateriel(const Vecteur& position, const Vecteur& vitesse, 
                           double masse, 
                           std::shared_ptr<ChampForces> champ,
                           std::shared_ptr<Contrainte> contrainte)
    : ObjetPhysique(position, vitesse, masse, champ, contrainte) {
    
    if (!(position.memeDimension(vitesse))) {
        throw std::runtime_error("Les dimensions de la position et de la vitesse doivent être égales");
    }
    
    if (masse <= 0) {
        throw std::runtime_error("La masse doit être positive");
    }
}



// Calcule l'équation d'évolution du point matériel à un instant donné
Vecteur PointMateriel::evolution(double temps) const {
    // Seconde loi de Newton: a = F/m
    return force(temps) * (1.0 / getMasse());
}

// Surcharge de l'opérateur << pour afficher les informations du point matériel
std::ostream& operator<<(std::ostream& os, const PointMateriel& pm) {
    os << pm.getMasse() << " # masse" << std::endl;
    os << pm.position() << " # position" << std::endl;
    os << pm.vitesse() << " # vitesse" << std::endl;
    
    // Calculer et afficher la force à l'instant t=0
    os << pm.force(0) << " # force";
    
    return os;
}
