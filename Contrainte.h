#pragma once
#include "Vecteur.h"

// 前向声明以避免循环引用
class ObjetPhysique;

class Contrainte {
public:
    // 构造函数和虚析构函数
    Contrainte() = default;
    virtual ~Contrainte() = default;
    
    // 纯虚函数，应用约束后的力
    virtual Vecteur applique_force(const ObjetPhysique& objet, const Vecteur& force, double temps) const = 0;
    
    // 纯虚函数，获取物理对象的实际位置
    virtual Vecteur position(const ObjetPhysique& objet) const = 0;
    
    // 纯虚函数，获取物理对象的实际速度
    virtual Vecteur vitesse(const ObjetPhysique& objet) const = 0;
}; 