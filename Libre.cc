#include "Libre.h"
#include "ObjetPhysique.h"

// 无约束下的力的应用，将力除以质量（如果质量不为0）
Vecteur Libre::applique_force(const ObjetPhysique& objet, const Vecteur& force, double /* temps */) const {
    double masse = objet.getMasse();
    if (masse > 0) {
        return force * (1.0 / masse);
    } else {
        return force;
    }
}

// 无约束下的位置就是对象的状态向量
Vecteur Libre::position(const ObjetPhysique& objet) const {
    return objet.getParametres();
}

// 无约束下的速度就是对象的状态导数向量
Vecteur Libre::vitesse(const ObjetPhysique& objet) const {
    return objet.getDeriveeParametres();
} 