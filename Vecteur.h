#pragma once
#include <initializer_list>
#include <vector>
#include <iostream>

class Vecteur {
private:
    std::vector<double> coords;

public:
    // Constructors
    Vecteur();
    Vecteur(size_t dimension);
    Vecteur(double x, double y, double z);
    Vecteur(std::initializer_list<double> values);
    Vecteur(const Vecteur& autre);

    bool memeDimension(const Vecteur& autre) const;
    
    void augmente(double valeur);

    void set_coord(size_t index, double valeur);

    void affiche() const;

    bool compare(const Vecteur &autre) const;

    Vecteur addition(const Vecteur &autre) const;

    Vecteur soustraction(const Vecteur &autre) const;

    Vecteur oppose() const;

    Vecteur mult(double scalaire) const;

    double prod_scal(const Vecteur &autre) const;

    Vecteur prod_vect(const Vecteur &autre) const;

    Vecteur unitaire() const;

    
    // P4.2: Transform affiche() and compare() into operators
    // operator<< replaces affiche()
    friend std::ostream& operator<<(std::ostream& os, const Vecteur& v);
    
    // operator== replaces compare()
    bool operator==(const Vecteur& autre) const;
    
    // operator!= (logical complement of ==)
    bool operator!=(const Vecteur& autre) const;
    
    // P4.3: Transform algebraic methods into operators
    // Unary operators
    Vecteur operator-() const;         // oppose()
    Vecteur operator~() const;         // unitaire()
    
    // Binary operators with their compound assignment versions
    Vecteur operator+(const Vecteur& autre) const;     // addition()
    Vecteur& operator+=(const Vecteur& autre);
    
    Vecteur operator-(const Vecteur& autre) const;     // soustraction()
    Vecteur& operator-=(const Vecteur& autre);
    
    Vecteur operator*(double scalaire) const;          // mult()
    Vecteur& operator*=(double scalaire);
    
    // Friend functions for commutative operations
    friend Vecteur operator*(double scalaire, const Vecteur& v);
    
    double operator*(const Vecteur& autre) const;      // prod_scal()
    
    Vecteur operator^(const Vecteur& autre) const;     // prod_vect()
    Vecteur& operator^=(const Vecteur& autre);
    
    // Other methods that don't become operators
    double norme2() const;
    double norme() const;
};