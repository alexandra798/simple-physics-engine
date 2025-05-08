#include <iostream>
#include <memory>
#include "Systeme.h"
#include "PointMateriel.h"
#include "ChampNewtonien.h"
#include "Libre.h"
#include "GravitationConstante.h"
#include "TextViewer.h"

int main() {
    try {
        // 创建一个系统
        Systeme systeme;
        
        // 创建地球（大质量物体）
        auto terre = std::make_shared<PointMateriel>(
            Vecteur(0, 0, 0),           // 位置
            Vecteur(0, 0, 0),           // 速度
            5.972e24,                    // 质量
            nullptr,                     // 暂时没有力场
            std::make_shared<Libre>()    // 自由约束
        );
        
        // 创建一个小物体（例如卫星）
        auto satellite = std::make_shared<PointMateriel>(
            Vecteur(6.37101e6, 0, 0),    // 初始位置（地球半径）
            Vecteur(0, 0, 0),           // 初始速度
            0.1,                         // 质量
            nullptr,                     // 暂时没有力场
            std::make_shared<Libre>()    // 自由约束
        );
        
        // 创建牛顿引力场
        auto champ_newton_terre = std::make_shared<ChampNewtonien>(terre);
        auto champ_newton_satellite = std::make_shared<ChampNewtonien>(satellite);
        
        // 创建自由约束
        auto contrainte_libre = std::make_shared<Libre>();
        
        // 将对象添加到系统
        systeme.ajoute_objet(terre);
        systeme.ajoute_objet(satellite);
        
        // 添加力场
        systeme.ajoute_champ(champ_newton_terre);
        systeme.ajoute_champ(champ_newton_satellite);
        
        // 添加约束
        systeme.ajoute_contrainte(contrainte_libre);
        
        // 应用力场和约束
        systeme.applique_champ(0, 1);  // 地球的引力作用于卫星
        systeme.applique_contrainte(0, 0);  // 自由约束应用于地球
        systeme.applique_contrainte(0, 1);  // 自由约束应用于卫星
        
        // 创建文本查看器
        TextViewer viewer(std::cout);
        
        // 绘制系统
        systeme.dessine_sur(viewer);
        
    } catch (const std::exception& e) {
        std::cerr << "错误：" << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}