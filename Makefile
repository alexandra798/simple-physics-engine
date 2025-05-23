CC  = $(CXX)

CXXFLAGS = -std=c++17  # 升级到 C++17

# Partie commentée : choisissez les options que vous voulez avoir
#                    en décommentant la/les lignes correspondantes
#
CXXFLAGS += -pedantic -Wall -Wextra -Werror  # 更严格的警告和错误检查
CXXFLAGS += -g                    # pour debugger
# CXXFLAGS += -O2                   # pour optimiser la vitesse


all: testVecteur testIntegrateur1 testPointMateriel testSysteme exercice9

Vecteur.o: Vecteur.cc Vecteur.h

GravitationConstante.o: GravitationConstante.cc GravitationConstante.h Vecteur.h constantes.h

ObjetMobile.o: ObjetMobile.cc ObjetMobile.h Vecteur.h

PointMateriel.o: PointMateriel.cc PointMateriel.h ObjetMobile.h Vecteur.h GravitationConstante.h


IntegrateurRungeKutta4.o: IntegrateurRungeKutta4.cc IntegrateurRungeKutta4.h Integrateur.h ObjetMobile.h
IntegrateurEulerCromer.o: IntegrateurEulerCromer.cc IntegrateurEulerCromer.h Integrateur.h ObjetMobile.h

# 可绘制和支持类


TextViewer.o: TextViewer.cc TextViewer.h SupportADessin.h

# 系统类
Systeme.o: Systeme.cc Systeme.h Dessinable.h ObjetPhysique.h ChampForces.h Contrainte.h Integrateur.h



testVecteur.o: testVecteur.cc Vecteur.h
testIntegrateur1.o: testIntegrateur1.cc PointMateriel.h IntegrateurEulerCromer.h
testSysteme.o: testSysteme.cc Systeme.h PointMateriel.h ChampNewtonien.h Libre.h GravitationConstante.h TextViewer.h
exercice9.o: exercice9.cc Systeme.h PointMateriel.h GravitationConstante.h Libre.h IntegrateurEulerCromer.h TextViewer.h
testPointMateriel.o: testPointMateriel.cc PointMateriel.h Vecteur.h ObjetMobile.h ObjetPhysique.h ChampForces.h GravitationConstante.h Contrainte.h Libre.h Integrateur.h IntegrateurEulerCromer.h Dessinable.h SupportADessin.h TextViewer.h




testVecteur: testVecteur.o Vecteur.o
testIntegrateur1: testIntegrateur1.o PointMateriel.o Vecteur.o ObjetMobile.o ObjetPhysique.o GravitationConstante.o   IntegrateurEulerCromer.o
	g++ -o testIntegrateur1 testIntegrateur1.o PointMateriel.o Vecteur.o ObjetMobile.o ObjetPhysique.o  GravitationConstante.o   IntegrateurEulerCromer.o
testSysteme: testSysteme.o Systeme.o Vecteur.o ObjetMobile.o ObjetPhysique.o PointMateriel.o ForceCentrale.o ChampNewtonien.o  IntegrateurEulerCromer.o   TextViewer.o GravitationConstante.o
exercice9: exercice9.o Systeme.o Vecteur.o ObjetMobile.o ObjetPhysique.o PointMateriel.o GravitationConstante.o   IntegrateurEulerCromer.o   TextViewer.o
testPointMateriel: testPointMateriel.o PointMateriel.o Libre.o Vecteur.o ObjetMobile.o ObjetPhysique.o GravitationConstante.o IntegrateurEulerCromer.o TextViewer.o ChargeElectrique.o Systeme.o