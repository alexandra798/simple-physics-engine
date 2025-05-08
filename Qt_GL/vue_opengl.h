#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include <QTime>
#include "../head/Support.h"
#include "glsphere.h"

class VueOpenGL : public SupportADessin {
public:
  VueOpenGL() : SupportADessin() {}
  // méthode(s) de dessin (héritée(s) de SupportADessin)
  virtual void dessine(Particule& p)    override;
  virtual void dessine(Element& el)      override;

  // méthodes de (ré-)initialisation
  void init();
  void initializePosition();

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);

  //Méthode pratique pour dessiner une sphere
  void dessineSphere(QMatrix4x4 const& point_de_vue = QMatrix4x4(),double rouge = 1.0, double vert = 1.0, double bleu = 1.0);

  //Dessine un repère pour aider à la représentation
  void dessineAxes(QMatrix4x4 const& point_de_vue, bool en_couleur = true);

  //Méthode pratique pour dessiner un cercle (esquisse d'élément)
  void dessineCercle(double rayon, QMatrix4x4 const& point_de_vue = QMatrix4x4 (),double rouge = 1.0, double vert = 1.0, double bleu = 1.0);

  void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4() );

  void dessineCoupes(Element& el);
  void dessineLignes(Element& el);

  void suitPart(Particule* p);

private:
  
  QOpenGLShaderProgram prog;

  GLSphere sphere;

  QMatrix4x4 matrice_vue;
};

#endif
