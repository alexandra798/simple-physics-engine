#include "glwidget.h"
#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include <memory>
#include "Bloc.h"
#include "Moucheron.h"
#include "Dervish.h"
#include "PointMateriel.h"
#include "GravitationConstante.h"
#include "Libre.h"
#include "IntegrateurEulerCromer.h"

// 构造函数
GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent), dt(0.01) {
    
    // 初始化物理系统
    auto integrateur = std::make_shared<IntegrateurEulerCromer>(dt);
    systeme = Systeme(integrateur);
    
    // 创建重力场
    auto gravite = std::make_shared<GravitationConstante>();
    
    // 创建自由约束
    auto libre = std::make_shared<Libre>();
    
    // 添加约束和力场到系统
    systeme.ajoute_contrainte(libre);
    systeme.ajoute_champ(gravite);
    
    // 创建一个物理点
    auto point = std::make_shared<PointMateriel>(
        Vecteur(0, 0, 0),  // 初始位置
        Vecteur(1, 0.5, 0),  // 初始速度
        1.0,  // 质量
        gravite,  // 重力场
        libre  // 自由约束
    );
    
    // 添加物理点到系统
    systeme.ajoute_objet(point);
    
    // 向系统添加各类Machin对象，用于测试
    systeme.ajoute_machin(std::make_shared<Bloc>());
    systeme.ajoute_machin(std::make_shared<Moucheron>());
    systeme.ajoute_machin(std::make_shared<Dervish>());
}

// ======================================================================
void GLWidget::initializeGL() {
    // 初始化OpenGL视图
    vue.init();
    
    // 启动定时器
    timerId = startTimer(16); // 约60fps
}

// ======================================================================
void GLWidget::resizeGL(int width, int height) {
    // 设置视口
    glViewport(0, 0, width, height);
    
    // 创建投影矩阵
    QMatrix4x4 matrice;
    matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
    vue.setProjection(matrice);
}

// ======================================================================
void GLWidget::paintGL() {
    // 清除颜色和深度缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 绘制系统（包含物理对象和Machin对象）
    systeme.dessine_sur(vue);
}

// ======================================================================
void GLWidget::timerEvent(QTimerEvent* event) {
    if (event->timerId() == timerId) {
        // 更新物理系统的状态（包括所有Machin对象）
        systeme.evolue(dt);
        
        // 重绘OpenGL窗口
        update();
    }
}

// ======================================================================
void GLWidget::keyPressEvent(QKeyEvent* event) {
    constexpr double petit_angle(5.0); // 角度单位
    constexpr double petit_pas(1.0);   // 移动步长

    switch (event->key()) {
    case Qt::Key_Left:
        vue.rotate(petit_angle, 0.0, -1.0, 0.0);
        break;

    case Qt::Key_Right:
        vue.rotate(petit_angle, 0.0, +1.0, 0.0);
        break;

    case Qt::Key_Up:
        vue.rotate(petit_angle, -1.0, 0.0, 0.0);
        break;

    case Qt::Key_Down:
        vue.rotate(petit_angle, +1.0, 0.0, 0.0);
        break;

    case Qt::Key_PageUp:
    case Qt::Key_W:
        vue.translate(0.0, 0.0, petit_pas);
        break;

    case Qt::Key_PageDown:
    case Qt::Key_S:
        vue.translate(0.0, 0.0, -petit_pas);
        break;

    case Qt::Key_A:
        vue.translate(petit_pas, 0.0, 0.0);
        break;

    case Qt::Key_D:
        vue.translate(-petit_pas, 0.0, 0.0);
        break;

    case Qt::Key_R:
        vue.translate(0.0, -petit_pas, 0.0);
        break;

    case Qt::Key_F:
        vue.translate(0.0, petit_pas, 0.0);
        break;

    case Qt::Key_Q:
        vue.rotate(petit_angle, 0.0, 0.0, -1.0);
        break;

    case Qt::Key_E:
        vue.rotate(petit_angle, 0.0, 0.0, +1.0);
        break;

    case Qt::Key_Home:
        vue.initializePosition();
        break;
    };

    update(); // 重绘
}

// ======================================================================
void GLWidget::mousePressEvent(QMouseEvent* event) {
    // 记录鼠标按下位置
    lastMousePosition = event->pos();
}

// ======================================================================
void GLWidget::mouseMoveEvent(QMouseEvent* event) {
    // 计算鼠标移动的距离
    int dx = event->x() - lastMousePosition.x();
    int dy = event->y() - lastMousePosition.y();

    // 根据鼠标按键选择操作
    if (event->buttons() & Qt::LeftButton) {
        // 左键拖动旋转视图
        vue.rotate(0.5 * dx, 0.0, 1.0, 0.0);
        vue.rotate(0.5 * dy, 1.0, 0.0, 0.0);
    } else if (event->buttons() & Qt::RightButton) {
        // 右键拖动平移视图
        vue.translate(0.01 * dx, -0.01 * dy, 0.0);
    }

    // 更新鼠标位置
    lastMousePosition = event->pos();
    
    // 重绘
    update();
}