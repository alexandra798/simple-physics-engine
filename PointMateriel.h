#pragma once
#include "ObjetPhysique.h"
#include <memory>

class PointMateriel : public ObjetPhysique {
public:
    // Constructors
    PointMateriel();
    PointMateriel(const Vecteur& position, const Vecteur& vitesse, double masse,
                  std::shared_ptr<ChampForces> champ = nullptr,
                  std::shared_ptr<Contrainte> contrainte = nullptr);

    // Destructor
    virtual ~PointMateriel() = default;


    void setMasse(double m);

    Vecteur evolution(double temps) const override;

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const PointMateriel& point);
private:
    double masse;
};