#pragma once

#include <vector>
#include <QOpenGLShaderProgram>

// GLSphere类用于生成和绘制OpenGL球体
class GLSphere {
public:
    // 构造和析构函数
    GLSphere();
    ~GLSphere();
    
    // 初始化球体数据
    void initialize(int resolution = 20);
    
    // 绘制球体
    void draw(QOpenGLShaderProgram& prog, int attributeLocation);
    
private:
    // 顶点数据
    std::vector<float> vertices;
    
    // 索引数据
    std::vector<unsigned int> indices;
    
    // 计算球体顶点和索引
    void compute(int resolution);
};