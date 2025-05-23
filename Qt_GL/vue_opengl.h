#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include <QTime>
#include "SupportADessin.h"
#include "glsphere.h"

class VueOpenGL : public SupportADessin {
  public:
      // 构造函数
      VueOpenGL() : SupportADessin() {}
      
      // 析构函数
      virtual ~VueOpenGL() = default;
      
      // 实现绘制方法
      virtual void dessine(const PointMateriel& point) override;
      virtual void dessine(const Systeme& systeme) override;
      virtual void dessine(const Bloc& bloc) override;
      virtual void dessine(const Moucheron& moucheron) override;
      virtual void dessine(const Dervish& dervish) override;
      virtual void dessine(const ChargeElectrique& charge) override;
      
      // 初始化OpenGL环境
      void init();
      void initializePosition();
      
      // 设置投影矩阵
      void setProjection(QMatrix4x4 const& projection)
      { prog.setUniformValue("projection", projection); }
      
      // 变换方法
      void translate(double x, double y, double z);
      void rotate(double angle, double dir_x, double dir_y, double dir_z);
      
      // 实用绘制方法
      void dessineSphere(QMatrix4x4 const& point_de_vue = QMatrix4x4(),
                         double rouge = 1.0, double vert = 1.0, double bleu = 1.0);
      void dessineAxes(QMatrix4x4 const& point_de_vue, bool en_couleur = true);
      void dessineCercle(double rayon, QMatrix4x4 const& point_de_vue = QMatrix4x4(),
                        double rouge = 1.0, double vert = 1.0, double bleu = 1.0);
      
  private:
      QOpenGLShaderProgram prog;
      GLSphere sphere;
      QMatrix4x4 matrice_vue;
  };

#endif
