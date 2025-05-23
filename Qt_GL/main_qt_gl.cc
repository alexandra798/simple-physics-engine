#include <QApplication>
#include <QMainWindow>
#include "glwidget.h"

int main(int argc, char* argv[]) {
    // 创建Qt应用程序
    QApplication app(argc, argv);
    
    // 创建主窗口
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Simulation Physique 3D");
    
    // 创建OpenGL小部件并将其设置为主窗口的中心部件
    GLWidget* glWidget = new GLWidget();
    mainWindow.setCentralWidget(glWidget);
    
    // 设置窗口大小
    mainWindow.resize(800, 600);
    
    // 显示窗口
    mainWindow.show();
    
    // 运行应用程序事件循环
    return app.exec();
}