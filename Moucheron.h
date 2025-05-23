#pragma once
#include "QuiTourne.h"
#include "SupportADessin.h"

// Moucheron类，继承自QuiTourne
class Moucheron : public QuiTourne {
public:
    // 构造函数
    Moucheron(double a = 0.0) : QuiTourne(a) {}
    
    // 实现dessine_sur方法
    virtual void dessine_sur(SupportADessin& support) override {
        support.dessine(*this);
    }
};