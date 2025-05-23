#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "PointMateriel.h"
#include "Systeme.h"
#include "Bloc.h"
#include "Moucheron.h"
#include "Dervish.h"
#include "ChargeElectrique.h"
#include <cmath>

// 绘制PointMateriel对象
void VueOpenGL::dessine(const PointMateriel& point) {
    // 获取物理点的位置
    Vecteur pos = point.position();
    
    // 创建变换矩阵
    QMatrix4x4 matrice;
    matrice.translate(pos.getCoord(0), pos.getCoord(1), pos.getCoord(2));
    matrice.scale(0.1); // 物理点的大小缩放
    
    // 使用球体表示物理点
    dessineSphere(matrice, 1.0, 0.0, 0.0); // 红色球体
}

// 绘制Systeme对象
void VueOpenGL::dessine(const Systeme& systeme) {
    // 遍历系统中的所有对象并绘制
    for (const auto& objet : systeme.get_objets()) {
        // 尝试将其转换为PointMateriel并绘制
        if (auto point = dynamic_cast<const PointMateriel*>(objet.get())) {
            dessine(*point);
        }
        // 可以添加其他类型的绘制
    }
}

// 绘制Bloc对象
void VueOpenGL::dessine(const Bloc& bloc) {
    // 创建变换矩阵
    QMatrix4x4 matrice;
    matrice.scale(0.5);
    
    // 在OpenGL着色器中设置矩阵
    prog.setUniformValue("vue_modele", matrice_vue * matrice);
    
    // 设置顶点颜色
    prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // 绿色
    
    // 绘制立方体
    glBegin(GL_QUADS);
    // 前面
    prog.setAttributeValue(SommetId, -1.0, -1.0,  1.0);
    prog.setAttributeValue(SommetId,  1.0, -1.0,  1.0);
    prog.setAttributeValue(SommetId,  1.0,  1.0,  1.0);
    prog.setAttributeValue(SommetId, -1.0,  1.0,  1.0);
    // 后面
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0,  1.0, -1.0);
    prog.setAttributeValue(SommetId,  1.0,  1.0, -1.0);
    prog.setAttributeValue(SommetId,  1.0, -1.0, -1.0);
    // 上面
    prog.setAttributeValue(SommetId, -1.0,  1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0,  1.0,  1.0);
    prog.setAttributeValue(SommetId,  1.0,  1.0,  1.0);
    prog.setAttributeValue(SommetId,  1.0,  1.0, -1.0);
    // 下面
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId,  1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId,  1.0, -1.0,  1.0);
    prog.setAttributeValue(SommetId, -1.0, -1.0,  1.0);
    // 右面
    prog.setAttributeValue(SommetId,  1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId,  1.0,  1.0, -1.0);
    prog.setAttributeValue(SommetId,  1.0,  1.0,  1.0);
    prog.setAttributeValue(SommetId,  1.0, -1.0,  1.0);
    // 左面
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0, -1.0,  1.0);
    prog.setAttributeValue(SommetId, -1.0,  1.0,  1.0);
    prog.setAttributeValue(SommetId, -1.0,  1.0, -1.0);
    glEnd();
}

// 绘制Moucheron对象
void VueOpenGL::dessine(const Moucheron& moucheron) {
    // 创建变换矩阵
    QMatrix4x4 matrice;
    matrice.translate(1.0, 0.0, 0.0);  // 位置在右侧
    matrice.rotate(45.0 + 3.0 * moucheron.infos(), 0.0, 1.0, 0.0); // 旋转
    matrice.scale(0.2);
    
    // 在OpenGL着色器中设置矩阵
    prog.setUniformValue("vue_modele", matrice_vue * matrice);
    
    // 设置顶点颜色
    prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // 蓝色
    
    // 绘制立方体
    glBegin(GL_QUADS);
    // 前面
    prog.setAttributeValue(SommetId, -1.0, -1.0,  1.0);
    prog.setAttributeValue(SommetId,  1.0, -1.0,  1.0);
    prog.setAttributeValue(SommetId,  1.0,  1.0,  1.0);
    prog.setAttributeValue(SommetId, -1.0,  1.0,  1.0);
    // 后面
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0,  1.0, -1.0);
    prog.setAttributeValue(SommetId,  1.0,  1.0, -1.0);
    prog.setAttributeValue(SommetId,  1.0, -1.0, -1.0);
    // 上面
    prog.setAttributeValue(SommetId, -1.0,  1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0,  1.0,  1.0);
    prog.setAttributeValue(SommetId,  1.0,  1.0,  1.0);
    prog.setAttributeValue(SommetId,  1.0,  1.0, -1.0);
    // 下面
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId,  1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId,  1.0, -1.0,  1.0);
    prog.setAttributeValue(SommetId, -1.0, -1.0,  1.0);
    // 右面
    prog.setAttributeValue(SommetId,  1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId,  1.0,  1.0, -1.0);
    prog.setAttributeValue(SommetId,  1.0,  1.0,  1.0);
    prog.setAttributeValue(SommetId,  1.0, -1.0,  1.0);
    // 左面
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0, -1.0,  1.0);
    prog.setAttributeValue(SommetId, -1.0,  1.0,  1.0);
    prog.setAttributeValue(SommetId, -1.0,  1.0, -1.0);
    glEnd();
}

// 绘制Dervish对象
void VueOpenGL::dessine(const Dervish& dervish) {
    // 创建变换矩阵
    QMatrix4x4 matrice;
    matrice.translate(0.0, 1.0, 0.0);  // 位置在上方
    matrice.rotate(45.0 + 3.0 * dervish.infos(), 1.0, 0.0, 0.0); // 旋转
    matrice.scale(0.25);
    
    // 在OpenGL着色器中设置矩阵
    prog.setUniformValue("vue_modele", matrice_vue * matrice);
    
    // 设置顶点颜色
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); // 紫色
    
    // 绘制立方体
    glBegin(GL_QUADS);
    // 前面
    prog.setAttributeValue