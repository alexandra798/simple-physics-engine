#include <iostream>
#include <memory>
#include "PointMateriel.h"
#include "ChampNewtonien.h"
#include "Libre.h"
#include "IntegrateurRungeKutta4.h"

int main() {
    try {
        // 创建地球（质心在原点）
        double masse_terre = 5.972e24;  // 单位：kg
        double rayon_terre = 6371e3;    // 单位：m
        
        auto terre = std::make_shared<PointMateriel>(
            Vecteur(0, 0, 0),           // 位置
            Vecteur(0, 0, 0),           // 速度
            masse_terre,                // 质量
            nullptr,                    // 暂时没有力场
            std::make_shared<Libre>()   // 无约束
        );
        
        // 创建苹果（在地球表面上方10米处）
        double masse_pomme = 0.1;       // 单位：kg
        double altitude = rayon_terre + 10.0;  // 距离地心的距离
        
        auto pomme = std::make_shared<PointMateriel>(
            Vecteur(0, 0, altitude),    // 位置
            Vecteur(0, 0, 0),           // 初始速度为0
            masse_pomme,                // 质量
            std::make_shared<ChampNewtonien>(terre),  // 牛顿引力场
            std::make_shared<Libre>()   // 无约束
        );
        
        // 创建龙格-库塔积分器
        IntegrateurRungeKutta4 integrateur(1e-3);  // 时间步长为1毫秒
        
        // 初始状态
        std::cout << "=== 初始状态 ===" << std::endl;
        std::cout << "时间: 0.0 s" << std::endl;
        std::cout << "苹果位置: " << pomme->position() << std::endl;
        std::cout << "苹果速度: " << pomme->vitesse() << std::endl;
        std::cout << std::endl;
        
        // 模拟100步
        double temps = 0.0;
        for (int i = 0; i < 100; ++i) {
            // 更新时间
            temps += integrateur.getPasTemps();
            
            // 执行一步积分
            integrateur.integre(*pomme, temps);
            
            // 打印结果
            std::cout << "=== 步骤 " << (i + 1) << " ===" << std::endl;
            std::cout << "时间: " << temps << " s" << std::endl;
            std::cout << "苹果位置: " << pomme->position() << std::endl;
            std::cout << "苹果速度: " << pomme->vitesse() << std::endl;
            std::cout << "高度: " << pomme->position().norme() - rayon_terre << " m" << std::endl;
            std::cout << std::endl;
        }
        
        // 模拟1.4秒，每0.1秒输出一次
        std::cout << "\n=== 每0.1秒输出一次 ===" << std::endl;
        
        for (int i = 0; i < 13; ++i) {  // 13步到达1.4秒
            // 计算100步
            for (int j = 0; j < 100; ++j) {
                temps += integrateur.getPasTemps();
                integrateur.integre(*pomme, temps);
            }
            
            // 打印结果
            std::cout << "时间: " << temps << " s" << std::endl;
            std::cout << "苹果位置: " << pomme->position() << std::endl;
            std::cout << "苹果速度: " << pomme->vitesse() << std::endl;
            std::cout << "高度: " << pomme->position().norme() - rayon_terre << " m" << std::endl;
            std::cout << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 