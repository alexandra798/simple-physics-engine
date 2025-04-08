#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "Vecteur.h"

using namespace std;

// Constructors (unchanged)
Vecteur::Vecteur() {
    
}

Vecteur::Vecteur(size_t dimension) {
    coords.resize(dimension, 0.0);
}

Vecteur::Vecteur(double x, double y, double z) {
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(z);
}

Vecteur::Vecteur(std::initializer_list<double> values) {
    for (double val : values) {
        coords.push_back(val);
    }
}

Vecteur::Vecteur(const Vecteur& autre) {
    coords = autre.coords;
}





// Utility methods (unchanged)

bool Vecteur::memeDimension(const Vecteur& autre) const {
    return coords.size() == autre.coords.size();
}

void Vecteur::augmente(double valeur) {
    coords.push_back(valeur);
}

void Vecteur::set_coord(size_t index, double valeur) {
    if (index >= coords.size()) {
        throw out_of_range("Index out of range");
    }
    coords[index] = valeur;
}

// P4.2: Transform affiche() and compare() into operators
// Keep the old methods for compatibility but implement using the new operators

// Original method kept for compatibility
void Vecteur::affiche() const {
    cout << *this;
}

// Original method kept for compatibility
bool Vecteur::compare(const Vecteur &autre) const {
    return *this == autre;
}

// P4.2: New operators

// operator<< replaces affiche()
ostream& operator<<(ostream& os, const Vecteur& v) {
    for (size_t i = 0; i < v.coords.size(); i++) {
        os << v.coords[i] << (i < v.coords.size() - 1 ? " " : "");
    }
    return os;
}

// operator== replaces compare()
bool Vecteur::operator==(const Vecteur& autre) const {
    if (coords.size() != autre.coords.size())
        return false;
    for (size_t i = 0; i < coords.size(); i++) {
        if (fabs(coords[i] - autre.coords[i]) > 1e-10)
            return false;
    }
    return true;
}

// operator!= (logical complement of ==)
bool Vecteur::operator!=(const Vecteur& autre) const {
    return !(*this == autre);
}

// P4.3: Transform algebraic methods into operators

// Unary operators

// operator- replaces oppose()
Vecteur Vecteur::operator-() const {
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); i++) {
        resultat.coords[i] = -coords[i];
    }
    return resultat;
}

// operator~ replaces unitaire()
Vecteur Vecteur::operator~() const {
    double n = norme();
    if (n < 1e-10)
        throw runtime_error("Zero vector has no unit vector");
    return *this * (1.0 / n);
}

// Binary operators with their compound assignment versions

// operator+ replaces addition()
Vecteur Vecteur::operator+(const Vecteur& autre) const {
    if (coords.size() != autre.coords.size())
        throw runtime_error("Dimensions different for addition");
    
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); i++) {
        resultat.coords[i] = coords[i] + autre.coords[i];
    }
    return resultat;
}

// Compound assignment operator+=
Vecteur& Vecteur::operator+=(const Vecteur& autre) {
    if (coords.size() != autre.coords.size())
        throw runtime_error("Dimensions different for addition");
    
    for (size_t i = 0; i < coords.size(); i++) {
        coords[i] += autre.coords[i];
    }
    return *this;
}

// operator- replaces soustraction()
Vecteur Vecteur::operator-(const Vecteur& autre) const {
    if (coords.size() != autre.coords.size())
        throw runtime_error("Dimensions different for subtraction");
    
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); i++) {
        resultat.coords[i] = coords[i] - autre.coords[i];
    }
    return resultat;
}

// Compound assignment operator-=
Vecteur& Vecteur::operator-=(const Vecteur& autre) {
    if (coords.size() != autre.coords.size())
        throw runtime_error("Dimensions different for subtraction");
    
    for (size_t i = 0; i < coords.size(); i++) {
        coords[i] -= autre.coords[i];
    }
    return *this;
}

// operator* replaces mult()
Vecteur Vecteur::operator*(double scalaire) const {
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); i++) {
        resultat.coords[i] = coords[i] * scalaire;
    }
    return resultat;
}

// Friend function for scalar * vector multiplication (commutative)
Vecteur operator*(double scalaire, const Vecteur& v) {
    return v * scalaire;
}

// Compound assignment operator*=
Vecteur& Vecteur::operator*=(double scalaire) {
    for (size_t i = 0; i < coords.size(); i++) {
        coords[i] *= scalaire;
    }
    return *this;
}

// operator* replaces prod_scal() (dot product)
double Vecteur::operator*(const Vecteur& autre) const {
    if (coords.size() != autre.coords.size())
        throw runtime_error("Dimensions different for dot product");
    
    double somme = 0.0;
    for (size_t i = 0; i < coords.size(); i++) {
        somme += coords[i] * autre.coords[i];
    }
    return somme;
}

// operator^ replaces prod_vect() (cross product)
Vecteur Vecteur::operator^(const Vecteur& autre) const {
    if (coords.size() != 3 || autre.coords.size() != 3)
        throw runtime_error("Cross product only defined for 3-dimensional vectors");
    
    Vecteur resultat(3);
    resultat.coords[0] = coords[1] * autre.coords[2] - coords[2] * autre.coords[1];
    resultat.coords[1] = coords[2] * autre.coords[0] - coords[0] * autre.coords[2];
    resultat.coords[2] = coords[0] * autre.coords[1] - coords[1] * autre.coords[0];
    return resultat;
}

// Compound assignment operator^=
Vecteur& Vecteur::operator^=(const Vecteur& autre) {
    *this = *this ^ autre;
    return *this;
}

// Original methods for backwards compatibility
Vecteur Vecteur::addition(const Vecteur &autre) const {
    return *this + autre;
}

Vecteur Vecteur::soustraction(const Vecteur &autre) const {
    return *this - autre;
}

Vecteur Vecteur::oppose() const {
    return -(*this);
}

Vecteur Vecteur::mult(double scalaire) const {
    return *this * scalaire;
}

double Vecteur::prod_scal(const Vecteur &autre) const {
    return *this * autre;
}

Vecteur Vecteur::prod_vect(const Vecteur &autre) const {
    return *this ^ autre;
}

// Unchanged methods
double Vecteur::norme2() const {
    double somme = 0.0;
    for (size_t i = 0; i < coords.size(); i++) {
        somme += coords[i] * coords[i];
    }
    return somme;
}

double Vecteur::norme() const {
    return sqrt(norme2());
}

Vecteur Vecteur::unitaire() const {
    return ~(*this);
}