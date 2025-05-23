#include <cmath>
#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "PointMateriel.h"
#include "Systeme.h"
#include "Bloc.h"
#include "Moucheron.h"
#include "Dervish.h"
#include "ChargeElectrique.h"


using namespace std;


void VueOpenGL::dessine(PointMateriel const& point) {
  dessinePoint(point);
}
void VueOpenGL::dessine(Particule& a) {
  double x = a.getX();
  double y = a.gety();
  double z = a.getZ();
  double n = a.getVitesse().norme();
  double angle = x / n;
  angle = acos(angle); //en radians
  angle *=  M_PI / 180; //conversion en ° pour QT

  QMatrix4x4 matrice;

  Vecteur3D pos = a.getVitesse();
  pos = ~pos;
  pos = pos.absolue();

  matrice.translate(x, y, z);
  matrice.rotate(angle, 0, 0, 1);
  matrice.scale(0.05);
  //Permet de voir que v = v(t)
  VueOpenGL::dessineSphere(matrice, pos*Vecteur3D(1,0,0), pos*Vecteur3D(0,1,0), pos*Vecteur3D(1,0.5,0));
}



void VueOpenGL::dessineLignes(Element& el){

    double l(el.longueurEl());

    QMatrix4x4 matrice;
    double x;
    double y;
    double z;

    //matrice.setToIdentity();
    //prog.setUniformValue("vue_modèle", matrice_vue * point_de_vue.inverted());
    //matrice.scale(0.1);
    //prog.setUniformValue("vue_modèle", matrice_vue * matrice);

    double lignes(10.0);
    double nbpoints(30);

    Vecteur3D pt;

    for(int j(1); j <= lignes; ++j){

        glBegin(GL_LINE_STRIP);
        for(int i(1); i <= nbpoints; ++i){
            matrice.setToIdentity();
            pt = el.coupe(el.posCercle(i*l/nbpoints), j*2*M_PI/lignes);
            //std::cout << pt << std::endl;
            x = pt*Vecteur3D(1,0,0);
            y = pt*Vecteur3D(0,1,0);
            z = pt*Vecteur3D(0,0,1);

            matrice.translate(x, y, z);
            pt = ~pt;
            matrice.rotate(90, pt*Vecteur3D(1,0,0), pt*Vecteur3D(0,1,0), pt*Vecteur3D(0,0,1));
            matrice.scale(10);

            prog.setUniformValue("vue_modèle", matrice * matrice_vue);
            prog.setAttributeValue(SommetId, x, y, z);

        }
        glEnd();


        //prog.setUniformValue("vue_modèle", matrice_vue * matrice);
    }
}



void VueOpenGL::dessineCoupes(Element& el){

    double distance(0.1);

    double anneaux(el.longueurEl()/distance);

    double rayon(el.getRayon());

    double l(el.longueurEl());

    Vecteur3D e;
    QMatrix4x4 matrice;
    double x;
    double y;
    double z;

    Vecteur3D couleur;

    //Dessine les cercles verticaux autour de l'élément
    for(int i(1); i <= anneaux; ++i){
        matrice.setToIdentity();

        e = el.posCercle(i*l/anneaux);
        couleur = el.couleur(i*l/anneaux);

        x = (e*Vecteur3D(1,0,0));
        y = (e*Vecteur3D(0,1,0));
        z = (e*Vecteur3D(0,0,1));
        matrice.translate(x, y, z);

        e = ~e;

        matrice.rotate(90, e*Vecteur3D(1,0,0), e*Vecteur3D(0,1,0), e*Vecteur3D(0,0,1));

        matrice.scale(2);

        dessineCercle(rayon, matrice, couleur*Vecteur3D(1,0,0), couleur*Vecteur3D(0,1,0), couleur*Vecteur3D(0,0,1));
    }

}






// ======================================================================
void VueOpenGL::init()
{

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);

  // Compilation du shader OpenGL
  prog.link();

  // Activation du shader
  prog.bind();


  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  sphere.initialize();
  initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition()
{
  matrice_vue.setToIdentity();
  matrice_vue.translate(0.0, 0.0, -8.0);
  matrice_vue.rotate(-60.0, 0.0, 1.0, 0.0);
  matrice_vue.rotate(-135.0, 0.0, 0.0, 1.0);
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{

  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{

  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}


//下面的就是教程中的进阶部分，没有要求必做

void VueOpenGL::dessineSphere (QMatrix4x4 const& point_de_vue, double rouge, double vert, double bleu)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setAttributeValue(CouleurId, rouge, vert, bleu);  // met la couleur
  sphere.draw(prog, SommetId);                           // dessine la sphère
}


void VueOpenGL::dessineAxes (QMatrix4x4 const& point_de_vue, bool en_couleur)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_LINES);

  // axe X
  if (en_couleur) {
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  } else {
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // blanc
  }
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 1.0, 0.0, 0.0);

  // axe Y
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 1.0, 0.0);

  // axe Z
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 0.0, 1.0);

  glEnd();
}

// ======================================================================
void VueOpenGL::dessineCercle(double rayon, QMatrix4x4 const& point_de_vue, double rouge, double vert, double bleu){

    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    //Partie y > 0
    prog.setAttributeValue(CouleurId, rouge, vert, bleu);
    glBegin(GL_LINE_STRIP);                               // la primitive LINE_STRIP ne referme par le tracé (n-1 lignes)
    double xpas(rayon/ 128.0);
    for (double x(-rayon); x <= rayon; x += xpas) {
      double y = sqrt(rayon*rayon - x*x);
      prog.setAttributeValue(SommetId, x, y, 0.0);
    }

    //Partie y < 0 (on parcourt la boucle précédente à l'envers pour n'avoir qu'un seul trait)
    for (double x(rayon); x >= -rayon; x -= xpas) {
      double y = -sqrt(rayon*rayon - x*x);
      prog.setAttributeValue(SommetId, x, y, 0.0);
    }
    glEnd();

    //prog.setUniformValue("vue_modèle", matrice_vue * point_de_vue.inverted());
}

//=================================================================================
void VueOpenGL::suitPart(Particule* p){
    if(p == nullptr){
        initializePosition();
        return;
    }

    matrice_vue.setToIdentity();

    //On met la vue dans le plan de l'accélérateur, le long de l'axe y
    matrice_vue.rotate(-90, 1, 0, 0);

    Vecteur3D v(p->getVitesse());
    Vecteur3D e1(1.0, 0.0, 0.0);
    Vecteur3D e2(0.0, 1.0, 0.0);

    //L'angle entre la vitesse et la vue (axe y)
    double angle(angleOuverture(v, e2));

    //Si la composante x est négative, l'angle ¢]pi, 2pi]
    if(v*e1 < 0) angle = 2*M_PI - angle;

    //Conversion d'unité
    angle *=  180/M_PI;

    //On fait la rotation de la vue
    matrice_vue.rotate(180 + angle, 0, 0, 1);

    //Puis on se met à la position de la particule
    matrice_vue.translate(p->getX(), p->gety(), p->getZ());

}
