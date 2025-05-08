#pragma once
#include <initializer_list>

class Vecteur {
private:

    std::vector<double> coords;

public:

    Vecteur();
    
    // 1. 构造一个指定维度的零向量
    Vecteur(size_t dimension);
        
    // 2. 通过三个坐标构造一个3D向量
    Vecteur(double x, double y, double z);

    // 3. [C++11] 通过初始化列表构造向量
    Vecteur(std::initializer_list<double> values);

    // 4. 拷贝构造函数
    Vecteur(const Vecteur& autre);

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


    double norme2() const;

    double norme() const;

    Vecteur unitaire() const;
};