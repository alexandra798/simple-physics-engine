#pragma once

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include "vue_opengl.h"
#include "contenu.h"

class GLWidget : public QOpenGLWidget {
public:
    GLWidget(QWidget* parent = nullptr)
    : QOpenGLWidget(parent)
    {}
    virtual ~GLWidget() = default;

private:
    // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
    virtual void initializeGL()                  override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL()                       override;
    //les événements (clavier, souris, temps) sont des méthodes virtuelles à redéfinir.
    
    // Méthodes de gestion d'évènements
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event)  override;

    
    
    VueOpenGL vue;
    Contenu c;
    QPoint lastMousePosition;
};
