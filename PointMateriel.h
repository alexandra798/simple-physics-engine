#pragma once
#include "ObjetPhysique.h"
#include <memory>

class PointMateriel : public ObjetPhysique {
public:
    // 构造函数
    PointMateriel();
    PointMateriel(const Vecteur& position, const Vecteur& vitesse, 
                 double masse, 
                 std::shared_ptr<ChampForces> champ = nullptr,
                 std::shared_ptr<Contrainte> contrainte = nullptr);
    
    // 计算运动方程（实现ObjetMobile中的虚函数）
    virtual Vecteur evolution(double temps) const override;
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const PointMateriel& pm);
};