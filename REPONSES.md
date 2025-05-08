
### [Question P1.1]Comment représentez-vous ces vecteurs ? Comment sont-ils organisés : quels attributs ? quelles méthodes ? quels droits d'accès ?
Pour représenter un vecteur de dimension quelconque, je propose:

Attributs (privés):

Un tableau dynamique (comme std::vector<double>) pour stocker les composantes du vecteur
Une variable entière pour suivre la dimension du vecteur


Méthodes (publiques):

Méthodes d'opérations de base: augmente(), set_coord(), affiche(), compare()
Opérations arithmétiques vectorielles: addition(), oppose(), mult(), prod_scal(), prod_vect()
Méthodes liées à la normalisation: norme(), norme2(), unitaire()


Droits d'accès:

Tous les membres de données devraient être privés pour assurer l'encapsulation et la sécurité
Toutes les méthodes d'opération devraient être publiques pour permettre l'utilisation externe



Les avantages de cette conception sont:

L'utilisation d'un tableau dynamique permet de représenter des vecteurs de dimension quelconque de manière flexible
La déclaration des membres de données comme privés garantit la sécurité et la cohérence des données
Fournir un ensemble complet de méthodes publiques rend les opérations sur les vecteurs simples et intuitives

### [Question P1.2]Quel choix avez vous fait pour les opérations entre vecteurs de dimensions différentes ?
Je choisis l'approche "déterminée par la plus petite dimension" (c'est-à-dire la projection). Voici mes raisons:

Sécurité: Cette méthode garantit que toutes les opérations sont bien définies, sans référence à des composantes non définies
Cohérence mathématique: Dans de nombreuses applications pratiques, lorsque les dimensions diffèrent, on projette généralement un vecteur de l'espace de plus grande dimension vers celui de plus petite dimension
Simplicité d'implémentation: L'implémentation du code est relativement simple, il suffit de parcourir jusqu'à la plus petite dimension
Prévention de perte d'information inattendue: Bien que certaines informations du vecteur de plus grande dimension soient perdues, c'est un choix conscient plutôt qu'un comportement accidentel dû à un dépassement

Ce choix signifie que, par exemple, dans une opération v1.addition(v2), si v1 est un vecteur à deux dimensions et v2 est un vecteur à trois dimensions, le résultat sera un vecteur à deux dimensions, utilisant uniquement les deux premières composantes de v2 pour le calcul.



### [Question P4.1]Avez-vous ajouté un constructeur de copie ? Pourquoi (justifiez votre choix) ?

Oui, j'ajouterais un constructeur de copie pour la classe Vecteur. Voici mes raisons:

1. La classe Vecteur contient un membre qui est un tableau dynamique (std::vector<double>), ce qui signifie qu'une copie superficielle (bit à bit) pourrait ne pas être suffisante.
2. Bien que C++ fournisse un constructeur de copie par défaut qui fonctionnerait correctement avec std::vector (qui gère déjà la copie profonde), il est préférable d'être explicite pour garantir le comportement attendu.
3. Dans le cas où nous déciderions plus tard de modifier la structure interne de la classe, avoir déjà défini un constructeur de copie explicite facilitera les futures modifications.
4. Cela permet également de clarifier les intentions du code et d'assurer que la copie d'un vecteur crée bien un nouvel objet indépendant avec ses propres données.

### Question P4.2
a) Si l'on souhaitait ajouter un constructeur par coordonnées sphériques (deux angles et une longueur) pour les vecteurs de dimension 3, que cela impliquerait-il au niveau des attributs de la classe ?

L'ajout d'un constructeur par coordonnées sphériques n'impliquerait pas nécessairement de modifications des attributs de la classe Vecteur. Les attributs actuels (un tableau pour les composantes et éventuellement une variable pour la dimension) suffisent, car:
- Le constructeur convertirait simplement les coordonnées sphériques (r, θ, φ) en coordonnées cartésiennes (x, y, z) selon les formules trigonométriques classiques.
- Les composantes cartésiennes calculées seraient ensuite stockées dans le tableau existant.

b) Quelle serait la difficulté majeure (voire l'impossibilité) de sa réalisation en C++ ?

La difficulté majeure en C++ serait l'ambiguïté de la surcharge du constructeur. En effet:
- Un constructeur par coordonnées sphériques prendrait trois paramètres double (rayon, angle θ, angle φ)
- Le constructeur par coordonnées cartésiennes prend déjà trois paramètres double (x, y, z)
- Ces deux signatures sont identiques du point de vue du compilateur (trois double)

Il serait donc impossible pour le compilateur de déterminer quel constructeur appeler lorsqu'on écrit `Vecteur(1.0, 0.5, 2.0)`. Cette ambiguïté n'est pas résolvable en C++ standard sans recourir à des techniques comme:
- Utiliser des types différents pour les angles
- Utiliser des structures intermédiaires distinctes
- Utiliser des méthodes de fabrication statiques plutôt que des constructeurs

### Question P4.3
Quels opérateurs avez vous introduits ?

J'aurais introduit les opérateurs suivants:

1. `operator<<` (remplaçant affiche()) pour l'affichage
2. `operator==` et `operator!=` (remplaçant compare()) pour les comparaisons
3. `operator+` et `operator+=` (remplaçant addition())
4. `operator-` et `operator-=` (remplaçant soustraction())
5. `operator-` (unaire, remplaçant oppose())
6. `operator*` et `operator*=` (pour la multiplication par un scalaire, remplaçant mult())
7. `operator*` (entre deux vecteurs, remplaçant prod_scal())
8. `operator^` et `operator^=` (remplaçant prod_vect())
9. `operator~` (unaire, remplaçant unitaire())

Ces opérateurs faciliteraient considérablement l'utilisation de la classe Vecteur en permettant une syntaxe plus naturelle et plus proche des notations mathématiques conventionnelles.



## [Question P8.1] 

La méthode `dessine_sur()` est, du point de vue de la programmation orientée objet, une méthode virtuelle pure. Elle est déclarée dans la classe abstraite `Dessinable` et doit être implémentée par toutes les classes dérivées. 

Cette méthode est un exemple parfait du principe de polymorphisme, permettant à différents objets d'être "dessinés" de manière spécifique tout en partageant une interface commune. C'est une application du patron de conception "Visiteur" (Visitor pattern), où la méthode `dessine_sur()` accepte un visiteur (`SupportADessin`) qui applique une opération appropriée selon le type concret de l'objet.

Le fait que cette méthode doive être implémentée de manière identique dans toutes les classes dérivées, avec un appel à `support.dessine(*this)`, est une solution technique pour contourner l'absence de "double dispatch" natif en C++.

## [Question P8.2] 

Pour les classes contenant des pointeurs, il faut faire attention aux aspects suivants :

1. **La gestion de mémoire** : Les pointeurs bruts ne gèrent pas automatiquement la mémoire, ce qui peut entraîner des fuites de mémoire ou des pointeurs pendants.

2. **La propriété des ressources** : Il faut clairement définir qui est responsable de la création et de la destruction des objets pointés.

3. **La règle des trois/cinq** : Si une classe nécessite un destructeur personnalisé, un constructeur de copie ou un opérateur d'affectation, elle a généralement besoin des trois. Avec C++11, cette règle s'étend à cinq avec les sémantiques de déplacement.

Les solutions possibles sont :

1. **Utiliser des pointeurs intelligents** :
   - `std::shared_ptr` pour la propriété partagée
   - `std::unique_ptr` pour la propriété exclusive
   - `std::weak_ptr` pour éviter les références circulaires

2. **Copie profonde** : Implémenter des constructeurs de copie et des opérateurs d'affectation qui créent de nouvelles copies des ressources.

3. **Sémantique de déplacement** : Utiliser des constructeurs de déplacement et des opérateurs d'affectation par déplacement pour améliorer l'efficacité.

4. **Suivre le principe RAII** (Resource Acquisition Is Initialization) : S'assurer que les ressources sont acquises dans le constructeur et libérées dans le destructeur.

Dans notre système de simulation physique, l'utilisation de `std::shared_ptr` est particulièrement appropriée car plusieurs objets peuvent partager des références à des contraintes ou des champs de force communs.

## [Question P8.3] 

La classe `Systeme` est conçue pour représenter l'ensemble du système physique à simuler. Voici mon explication de sa conception :

**Attributs** :
- `std::vector<std::shared_ptr<ObjetPhysique>> objets` : Collection des objets physiques du système
- `std::vector<std::shared_ptr<ChampForces>> champs` : Collection des champs de forces
- `std::vector<std::shared_ptr<Contrainte>> contraintes` : Collection des contraintes
- `std::shared_ptr<Integrateur> integrateur` : L'intégrateur utilisé pour faire évoluer le système
- `double temps` : Le temps actuel du système

**Interface** :
1. **Constructeurs** :
   - Constructeur par défaut initialisant un système vide avec un intégrateur d'Euler-Cromer
   - Constructeur avec un intégrateur spécifié

2. **Méthodes d'ajout de composants** :
   - `ajoute_objet()` : Ajoute un objet physique au système
   - `ajoute_contrainte()` : Ajoute une contrainte au système
   - `ajoute_champ()` : Ajoute un champ de forces au système

3. **Méthodes d'application** :
   - `applique_contrainte()` : Applique une contrainte spécifique à un objet spécifique
   - `applique_champ()` : Applique un champ de forces spécifique à un objet spécifique

4. **Méthode d'évolution** :
   - `evolue(double dt)` : Fait évoluer le système d'un pas de temps dt

5. **Accesseurs** :
   - Méthodes pour obtenir les objets, champs, contraintes et le temps du système

6. **Méthode d'affichage** :
   - `dessine_sur()` : Héritée de `Dessinable`, permet d'afficher le système
   - Surcharge de l'opérateur `<<` pour afficher toutes les informations du système

**Choix de conception** :
- J'ai choisi d'utiliser des `std::shared_ptr` pour gérer les objets, contraintes et champs de forces, ce qui permet un partage sécurisé des ressources.
- La responsabilité du temps est confiée à la classe `Systeme`, qui incrémente son propre temps lors de chaque évolution.
- La séparation claire entre la simulation physique (via `evolue()`) et l'affichage (via `dessine_sur()`) permet de respecter le principe de séparation des préoccupations.
- L'intégrateur est un composant interne du système, ce qui permet d'utiliser différentes méthodes d'intégration sans modifier le reste du code.

Cette conception modulaire permet une grande flexibilité et extensibilité du système, tout en maintenant une interface cohérente et facile à utiliser.

