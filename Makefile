
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



testVecteur.o: testVecteur.cc Vecteur.h
testIntegrateur1.o: testIntegrateur1.cc PointMateriel.h IntegrateurEulerCromer.h






testVecteur: testVecteur.o Vecteur.o

testIntegrateur1: testIntegrateur1.o Vecteur.o GravitationConstante.o ObjetMobile.o PointMateriel.o Integrateur.o IntegrateurEulerCromer.o
