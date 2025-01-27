## Informations Générales
- **Cours :** Algorithmique Avancée
- **Travail Pratique :** Puissance 4
- **Université :** CERI - Licence 2 Informatique, Semestre 3

## Membres de l'équipe
- **Adragna Angelo**
- **Saccoman Corentin**

# Présentation

## Description
Ce projet consiste à implémenter un jeu de Puissance 4 dans lequel un joueur humain affronte l'ordinateur. L'ordinateur utilise l'algorithme Min-Max pour déterminer le meilleur coup à jouer, tandis que le joueur humain choisit ses coups manuellement. Le plateau de jeu est représenté par une matrice \(6 \times 7\), avec les cases numérotées de 0 à 6 pour les colonnes et de 0 à 5 pour les lignes.

Les coups de l'ordinateur sont marqués par le chiffre 1, ceux du joueur humain par -1, et les cases vides sont représentées par 0. L'objectif est de déterminer la victoire de l'un des joueurs, une égalité ou un match en cours.

### Prérequis
- **Langage :** C++
- **Fichiers nécessaires :** `puissance4.h`, `puissance4.cpp`, `main.cpp`

# Mode d'emploi

## Compilation et exécution
**Compilation :**  
'''
make
'''

**Exécution :**  
Lancez le programme avec :
'''
./puissance4.exe
'''


## Fonctionnalités principales
1. **Classe Puissance4**  
   La classe principale représentant le jeu de Puissance 4. Elle contient les éléments suivants :
   - `int T[6][7]` : Plateau de jeu.
   - `int Col[7]` : Indices des dernières cases occupées dans chaque colonne.
   - `int hmax` : Profondeur à partir de laquelle l'état du jeu est évalué.
   - `Puissance4(int h)` : Constructeur qui initialise le plateau et les colonnes.
   - `void affichage()` : Méthode pour afficher le plateau de jeu.
   - `void jouer(int j, int joueur)` : Méthode pour jouer un coup sur la colonne `j`.
   - `void dejouer(int j)` : Méthode pour retirer le dernier coup joué dans la colonne `j`.
   - `bool coupgagnant(int joueur, int &bestMove)` : Méthode pour vérifier si un joueur peut gagner en un coup.
   - `int JeuOrdi(int &bestMove, int niveau)` : Méthode pour évaluer les coups de l'ordinateur avec Min-Max.
   - `int JeuHumain(int &bestMove, int niveau)` : Méthode pour évaluer les coups du joueur humain.
   - `int evaluation(int joueur, int j)` : Méthode pour évaluer un coup dans une colonne donnée.
   - `int direction1(int joueur, int j)`, `direction2(int joueur, int j)`, `direction3(int joueur, int j)`, `direction4(int joueur, int j)` : Méthodes pour calculer les points dans les différentes directions possibles pour un alignement.

2. **Main Program**  
   Un fichier `main.cpp` permet de lancer une partie de la manière suivante :
   - La partie est représentée par un objet de la classe `Puissance4` avec une profondeur de recherche `h` pour l'algorithme Min-Max.
   - Un tirage aléatoire détermine qui commence (0 pour l'ordinateur, 1 pour l'humain).
   - L'ordinateur joue grâce à la méthode `JeuOrdi(bestMove, niveau)` pour déterminer le meilleur coup.
   - L'humain joue en entrant le numéro de la colonne où il souhaite jouer.
   - La méthode `coupgagnant()` évalue l'état de la partie après chaque coup.

## Consignes
1. Implémentez les méthodes de la classe `Puissance4` en respectant les spécifications.
2. Le programme doit gérer les tours de jeu entre l'ordinateur et l'humain.
3. Implémentez l'algorithme Min-Max pour l'ordinateur.
4. Gérez l'affichage du plateau de manière claire et interactive.

## Limites
1. Le plateau est de taille fixe \(6 \times 7\), et il n'est pas nécessaire de gérer des tailles de plateau différentes.
2. Les entrées de l'utilisateur doivent être vérifiées pour s'assurer qu'elles sont valides (colonne disponible).
3. Le programme doit gérer correctement l'affichage de l'état du jeu après chaque coup.
