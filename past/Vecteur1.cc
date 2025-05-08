
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "Vecteur.h"

using namespace std;

Vecteur::Vecteur() {
    
}
// 1. 构造一个指定维度的零向量
Vecteur::Vecteur(size_t dimension) {
    coords.resize(dimension, 0.0);
}

// 2. 通过三个坐标构造一个3D向量
Vecteur::Vecteur(double x, double y, double z) {
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(z);
}

// 3. [C++11] 通过初始化列表构造向量
Vecteur::Vecteur(std::initializer_list<double> values) {
    for (double val : values) {
        coords.push_back(val);
    }
}

// 4. 拷贝构造函数
Vecteur::Vecteur(const Vecteur& autre) {
    coords = autre.coords; // 使用std::vector的拷贝赋值运算符
}


// Méthode augmente() : ajoute une nouvelle dimension avec la valeur donnée.
void Vecteur::augmente(double valeur) {
    coords.push_back(valeur);
}

// Méthode set_coord() : modifie la valeur de la coordonnée à l'indice spécifié.
// On considère ici un indexage commençant à 0.

void Vecteur::set_coord(size_t index, double valeur) {
    if (index >= coords.size()) {
        throw out_of_range("Index out of range");
    }
    coords[index] = valeur;
}

// Méthode affiche() : affiche les composantes du vecteur sur cout

void Vecteur::affiche() const {
    for (size_t i = 0; i < coords.size(); i++) {
        cout << coords[i] << (i < coords.size() - 1 ? " " : "");
    }
}

// Méthode compare() : teste l'égalité entre le vecteur courant et un autre

bool Vecteur::compare(const Vecteur &autre) const {
    if (coords.size() != autre.coords.size())
        return false;
    for (size_t i = 0; i < coords.size(); i++) {
        if (fabs(coords[i] - autre.coords[i]) > 1e-10)
            return false;
    }
    return true;
}

// Méthode addition() : retourne la somme de deux vecteurs.
// Pour simplifier, nous choisissons de lancer une exception en cas de dimension différente.
Vecteur Vecteur::addition(const Vecteur &autre) const {
    if (coords.size() != autre.coords.size())
        throw runtime_error("Dimensions different for addition");
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); i++) {
        resultat.augmente(coords[i] + autre.coords[i]);
    }
    return resultat;
}

// Méthode soustraction() : retourne la différence (vecteur courant moins autre).
Vecteur Vecteur::soustraction(const Vecteur &autre) const {
    if (coords.size() != autre.coords.size())
        throw runtime_error("Dimensions different for subtraction");
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); i++) {
        resultat.augmente(coords[i] - autre.coords[i]);
    }
    return resultat;
}

// Méthode oppose() : retourne le vecteur opposé (changement de signe de chaque composante).
Vecteur Vecteur::oppose() const {
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); i++) {
        resultat.augmente(-coords[i]);
    }
    return resultat;
}

// multiplication du vecteur par un scalaire.
Vecteur Vecteur::mult(double scalaire) const {
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); i++) {
        resultat.augmente(coords[i] * scalaire);
    }
    return resultat;
}

// produit scalaire entre deux vecteurs.
double Vecteur::prod_scal(const Vecteur &autre) const {
    if (coords.size() != autre.coords.size())
        throw runtime_error("Dimensions different for dot product");
    double somme = 0.0;
    for (size_t i = 0; i < coords.size(); i++) {
        somme += coords[i] * autre.coords[i];
    }
    return somme;
}

// produit vectoriel entre deux vecteurs en dimension 3.
// Si les vecteurs ne sont pas en dimension 3, on lance une exception.
Vecteur Vecteur::prod_vect(const Vecteur &autre) const {
    if (coords.size() != 3 || autre.coords.size() != 3)
        throw runtime_error("Cross product only defined for 3-dimensional vectors");
    Vecteur resultat(coords.size());
    resultat.augmente(coords[1] * autre.coords[2] - coords[2] * autre.coords[1]);
    resultat.augmente(coords[2] * autre.coords[0] - coords[0] * autre.coords[2]);
    resultat.augmente(coords[0] * autre.coords[1] - coords[1] * autre.coords[0]);
    return resultat;
}

// Méthode norme2() : calcule le carré de la norme (somme des carrés des composantes).
double Vecteur::norme2() const {
    double somme = 0.0;
    for (size_t i = 0; i < coords.size(); i++) {
        somme += coords[i] * coords[i];
    }
    return somme;
}

// Méthode norme() : retourne la norme (longueur) du vecteur.
double Vecteur::norme() const {
    return sqrt(norme2());
}

// Méthode unitaire() : retourne le vecteur unitaire (de même direction),
// en vérifiant que le vecteur n'est pas nul.
Vecteur Vecteur::unitaire() const {
    double n = norme();
    if (n < 1e-10)
        throw runtime_error("Zero vector has no unit vector");
    return mult(1.0 / n);
}
