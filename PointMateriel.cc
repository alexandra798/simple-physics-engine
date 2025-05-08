#include "PointMateriel.h"
#include "Vecteur.h"
#include "SupportADessin.h"
#include <iostream>
#include <stdexcept>
#include <memory>

// 构造函数
PointMateriel::PointMateriel()
    : ObjetPhysique() {}

// 带参数的构造函数
PointMateriel::PointMateriel(const Vecteur& position, const Vecteur& vitesse, 
                           double masse, 
                           std::shared_ptr<ChampForces> champ,
                           std::shared_ptr<Contrainte> contrainte)
    : ObjetPhysique(position, vitesse, masse, champ, contrainte) {
    
    if (!(position.memeDimension(vitesse))) {
        throw std::runtime_error("位置和速度的维度必须相同");
    }
    
    if (masse <= 0) {
        throw std::runtime_error("质量必须为正值");
    }
}

// 计算物质点在给定时间的演化方程
Vecteur PointMateriel::evolution(double temps) const {
    // 牛顿第二定律：a = F/m
    return force(temps) * (1.0 / getMasse());
}




// 输出运算符重载
std::ostream& operator<<(std::ostream& os, const PointMateriel& pm) {
    os << static_cast<const ObjetPhysique&>(pm) << std::endl;
    
    // 计算并显示t=0时的力
    os << pm.force(0) << " # 力";
    
    return os;
}
