#pragma once

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QMouseEvent>
#include <QTimer>
#include "vue_opengl.h"
#include "Systeme.h"

class GLWidget : public QOpenGLWidget {
public:
    GLWidget(QWidget* parent = nullptr);
    virtual ~GLWidget() = default;

private:
    // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
    virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL() override;
    
    // Méthodes de gestion d'évènements
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void timerEvent(QTimerEvent* event) override;

    // 系统的组件
    VueOpenGL vue;          // OpenGL视图
    Systeme systeme;        // 物理系统（现在也包含了Machin对象）
    
    // 定时器
    int timerId;            // 定时器ID
    double dt;              // 时间步长
    
    // 鼠标位置
    QPoint lastMousePosition;
};