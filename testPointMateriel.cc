

#include <iostream>
#include "Vecteur.h"
#include "GravitationConstante.h"
#include "PointMateriel.h"

using namespace std;

int main() {
    try {
        // Création d'un champ de gravité terrestre
        GravitationConstante gravite;
        
        // Création de deux points matériels
        Vecteur position1(1.0, 2.0, 3.0);
        Vecteur vitesse1(0.0, 0.1, 0.2);
        PointMateriel point1(position1, vitesse1, 0.1, gravite);
        
        Vecteur position2(-1.1, 1.2, 1.3);
        Vecteur vitesse2(0.2, 0.1, 0.0);
        PointMateriel point2(position2, vitesse2, 2.0, gravite);
        
        // Affichage des objets
        cout << "Nous avons :" << endl;
        
        cout << "un champ de force :" << endl;
        cout << gravite << endl << endl;
        
        cout << "un point matériel :" << endl;
        cout << point1 << endl << endl;
        
        cout << "et un autre point matériel :" << endl;
        cout << point2 << endl;
        
    } catch (const exception& e) {
        cerr << "Erreur : " << e.what() << endl;
        return 1;
    }
    
    return 0;
}