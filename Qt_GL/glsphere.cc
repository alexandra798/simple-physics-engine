#include "glsphere.h"
#include <cmath>

// 构造函数
GLSphere::GLSphere() {}

// 析构函数
GLSphere::~GLSphere() {}

// 初始化球体
void GLSphere::initialize(int resolution) {
    // 计算球体的顶点和索引
    compute(resolution);
}

// 计算球体的顶点和索引
void GLSphere::compute(int resolution) {
    // 清空之前的数据
    vertices.clear();
    indices.clear();
    
    // 参数
    const float PI = 3.14159265358979323846f;
    const float radius = 1.0f;  // 球体半径
    
    // 计算顶点数量
    int stackCount = resolution;
    int sectorCount = resolution * 2;
    
    float stackStep = PI / stackCount;
    float sectorStep = 2 * PI / sectorCount;
    
    // 生成顶点
    for (int i = 0; i <= stackCount; ++i) {
        float stackAngle = PI / 2 - i * stackStep;  // 从顶部开始 [-PI/2, PI/2]
        float xy = radius * cosf(stackAngle);       // r * cos(u)
        float z = radius * sinf(stackAngle);        // r * sin(u)
        
        for (int j = 0; j <= sectorCount; ++j) {
            float sectorAngle = j * sectorStep;     // 从0开始 [0, 2PI]
            
            // 顶点位置 (x, y, z)
            float x = xy * cosf(sectorAngle);       // r * cos(u) * cos(v)
            float y = xy * sinf(sectorAngle);       // r * cos(u) * sin(v)
            
            // 添加顶点
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }
    
    // 生成索引
    for (int i = 0; i < stackCount; ++i) {
        int k1 = i * (sectorCount + 1);
        int k2 = k1 + sectorCount + 1;
        
        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            
            if (i != (stackCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

// 绘制球体
void GLSphere::draw(QOpenGLShaderProgram& prog, int attributeLocation) {
    // 如果没有顶点数据，则返回
    if (vertices.empty() || indices.empty()) {
        return;
    }
    
    // 使用三角形绘制球体
    glBegin(GL_TRIANGLES);
    
    for (size_t i = 0; i < indices.size(); i += 3) {
        // 获取三个顶点的索引
        unsigned int idx1 = indices[i];
        unsigned int idx2 = indices[i + 1];
        unsigned int idx3 = indices[i + 2];
        
        // 设置第一个顶点
        prog.setAttributeValue(attributeLocation, 
                               vertices[idx1 * 3], 
                               vertices[idx1 * 3 + 1], 
                               vertices[idx1 * 3 + 2]);
        
        // 设置第二个顶点
        prog.setAttributeValue(attributeLocation, 
                               vertices[idx2 * 3], 
                               vertices[idx2 * 3 + 1], 
                               vertices[idx2 * 3 + 2]);
        
        // 设置第三个顶点
        prog.setAttributeValue(attributeLocation, 
                               vertices[idx3 * 3], 
                               vertices[idx3 * 3 + 1], 
                               vertices[idx3 * 3 + 2]);
    }
    
    glEnd();
}