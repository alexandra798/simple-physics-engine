#pragma once
#include <iostream>

// 前向声明
class PointMateriel;
class Systeme;

class SupportADessin {
public:

    virtual ~SupportADessin() = default;
    
    // 纯虚函数，用于绘制不同类型的对象
    virtual void dessine(PointMateriel const&) = 0;
    virtual void dessine(Systeme const&) = 0;
    // 如果需要，可以添加更多绘制方法

private:
    SupportADessin(SupportADessin const&) = delete;
};