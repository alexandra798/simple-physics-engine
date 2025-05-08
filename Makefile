
CC  = $(CXX)

CXXFLAGS = -std=c++11  # C++11, ou autre suivant vos préférences

# Partie commentée : choisissez les options que vous voulez avoir
#                    en décommentant la/les lignes correspondantes
#
CXXFLAGS += -pedantic -Wall         # pour les pur(e)s et dur(e)s
CXXFLAGS += -g                    # pour debugger
# CXXFLAGS += -O2                   # pour optimiser la vitesse


all: testVecteur testIntegrateur1

Vecteur.o: Vecteur.cc Vecteur.h

GravitationConstante.o: GravitationConstante.cc GravitationConstante.h Vecteur.h constantes.h

ObjetMobile.o: ObjetMobile.cc ObjetMobile.h Vecteur.h

PointMateriel.o: PointMateriel.cc PointMateriel.h ObjetMobile.h Vecteur.h GravitationConstante.h

Integrateur.o: Integrateur.cc Integrateur.h ObjetMobile.h

IntegrateurRungeKutta4.o: IntegrateurRungeKutta4.cc IntegrateurRungeKutta4.h Integrateur.h ObjetMobile.h
IntegrateurEulerCromer.o: IntegrateurEulerCromer.cc IntegrateurEulerCromer.h Integrateur.h ObjetMobile.h


# 可绘制和支持类
Dessinable.o: Dessinable.h
SupportADessin.o: SupportADessin.h
TextViewer.o: TextViewer.cc TextViewer.h SupportADessin.h

# 系统类
Systeme.o: Systeme.cc Systeme.h Dessinable.h ObjetPhysique.h ChampForces.h Contrainte.h Integrateur.h



testVecteur.o: testVecteur.cc Vecteur.h
testIntegrateur1.o: testIntegrateur1.cc PointMateriel.h IntegrateurEulerCromer.h
testSysteme.o: testSysteme.cc Systeme.h PointMateriel.h ChampNewtonien.h Libre.h GravitationConstante.h TextViewer.h
exercice9.o: exercice9.cc Systeme.h PointMateriel.h GravitationConstante.h Libre.h IntegrateurEulerCromer.h TextViewer.h





testVecteur: testVecteur.o Vecteur.o
testIntegrateur1: testIntegrateur1.o Vecteur.o GravitationConstante.o ObjetMobile.o PointMateriel.o Integrateur.o IntegrateurEulerCromer.o
testSysteme: testSysteme.o Systeme.o Vecteur.o ObjetMobile.o ObjetPhysique.o PointMateriel.o ChampForces.o ForceCentrale.o ChampNewtonien.o Contrainte.o Libre.o Integrateur.o IntegrateurEulerCromer.o Dessinable.o SupportADessin.o TextViewer.o GravitationConstante.o
exercice9: exercice9.o Systeme.o Vecteur.o ObjetMobile.o ObjetPhysique.o PointMateriel.o ChampForces.o GravitationConstante.o Contrainte.o Libre.o Integrateur.o IntegrateurEulerCromer.o Dessinable.o SupportADessin.o TextViewer.o