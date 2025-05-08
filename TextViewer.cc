#include "TextViewer.h"
#include "PointMateriel.h"
#include "Systeme.h"



// 绘制PointMateriel对象
void TextViewer::dessine(const PointMateriel& point) {
    sortie << point;
}

// 绘制Systeme对象
void TextViewer::dessine(const Systeme& systeme) {
    sortie << systeme;
}