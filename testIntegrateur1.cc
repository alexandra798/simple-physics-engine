
#include "PointMateriel.h"
#include "IntegrateurRungeKutta4.h"
#include <iostream>

int main() {
    // Création d'un point matériel
    // Position initiale (x=0, y=0, z=1), vitesse initiale (x=0, y=1, z=2)
    Vecteur position_initiale(0, 0, 1);
    Vecteur vitesse_initiale(0, 1, 2);
    double masse = 0.127; // kg
    
    // Création du point matériel avec le champ de gravité terrestre par défaut
    PointMateriel point(position_initiale, vitesse_initiale, masse);
    
    // Création d'un intégrateur Runge-Kutta d'ordre 4 avec un pas de temps de 0.01s
    IntegrateurRungeKutta4 integrateur(0.01);
    
    // Affichage initial
    std::cout << point.position() << " # parametre" << std::endl;
    std::cout << point.vitesse() << " # vitesse" << std::endl;
    std::cout << std::endl;
    
    // Intégration sur plusieurs pas de temps
    double temps = 0.0;
    
    for (int i = 0; i < 10; ++i) {
        // Mise à jour du temps
        temps += integrateur.getPasTemps();
        
        // Intégration d'un pas de temps
        integrateur.integre(point, temps);
        
        // Affichage des résultats
        std::cout << "========================" << std::endl;
        std::cout << "t = " << temps << std::endl;
        std::cout << point.position() << " # parametre" << std::endl;
        std::cout << point.vitesse() << " # vitesse" << std::endl;
        std::cout << std::endl;
    }
    
    return 0;
}