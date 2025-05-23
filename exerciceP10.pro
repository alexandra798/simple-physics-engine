QT += core gui opengl widgets

TARGET = exerciceP10
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    main_qt_gl.cc \
    glwidget.cc \
    vue_opengl.cc \
    glsphere.cc \
    Vecteur.cc \
    ObjetMobile.cc \
    ObjetPhysique.cc \
    PointMateriel.cc \
    ChargeElectrique.cc \
    ChampNewtonien.cc \
    ForceCentrale.cc \
    GravitationConstante.cc \
    Integrateur.cc \
    IntegrateurEulerCromer.cc \
    IntegrateurRungeKutta4.cc \
    Libre.cc \
    Systeme.cc \
    TextViewer.cc

HEADERS += \
    glwidget.h \
    vue_opengl.h \
    glsphere.h \
    vertex_shader.h \
    Vecteur.h \
    ObjetMobile.h \
    ObjetPhysique.h \
    PointMateriel.h \
    ChargeElectrique.h \
    ChampForces.h \
    ChampNewtonien.h \
    ForceCentrale.h \
    GravitationConstante.h \
    Contrainte.h \
    Libre.h \
    Integrateur.h \
    IntegrateurEulerCromer.h \
    IntegrateurRungeKutta4.h \
    constantes.h \
    Systeme.h \
    TextViewer.h \
    SupportADessin.h \
    Dessinable.h \
    Machin.h \
    QuiTourne.h \
    Bloc.h \
    Moucheron.h \
    Dervish.h

RESOURCES += \
    resource.qrc

LIBS += -lGLU

DISTFILES += \
    vertex_shader.glsl \
    fragment_shader.glsl