/*
TP5 - Puissance 4
Réalisé par :
    - Corentin Saccoman
    - Angelo Adragna
*/
#include <iostream>
#include <iomanip>
#include <cstdlib>

class Puissance4
{
public:
    int T[6][7]; // Grille de jeu
    int Col[7];  // indice de la dernière ligne utilisée dans chaque colonne
    int hmax;    // hauteur de l'arbre de recherche



    Puissance4(int h);                  // Constructeur prenant en argument la hauteur max de l'arbre de recherche

    void affichage();                   // affichage de la grille
    bool col_pleine(int j);             // renvoie true si la colonne j est pleine, false sinon
    void jouer(int j, int joueur);      // fait jouer joueur dans la colonne j
    void dejouer(int j);                // annule le dernier coup joué dans la colonne j

    bool coupgagnant(int joueur, int & bestMove);       // Détermine s'il existe une colonne dans laquelle joueur peut gagner en un coup
    bool coupgagnantCol(int joueur, int & bestMove);    // Détermine s'il existe une colonne dans laquelle joueur peut gagner en un coup, en faisant une Colonne
    bool coupgagnantLigne(int joueur, int & bestMove);  // Détermine s'il existe une colonne dans laquelle joueur peut gagner en un coup, en faisant une ligne
    bool coupgagnantDiago(int joueur, int & bestMove);  // Détermine s'il existe une colonne dans laquelle joueur peut gagner en un coup, en faisant une Diagonale

    int JeuOrdi(int & bestMove, int niveau);            // affecte à “bestMove” le “meilleur” coup de l’ordinateur, et renvoie la valeur de l’ ́evaluation de ce coup. La méthode ne réalise pas le coup
    int JeuHumain(int & bestMove, int niveau);          // affecte à “bestMove” le “meilleur” coup de l'Humain, et renvoie la valeur de l’ ́evaluation de ce coup. La méthode ne réalise pas le coup

    bool plein();   // renvoie true si la grille est pleine, false sinon

    int evaluation(int joueur, int j);                          // renvoie la valeur de l'évaluation du dernier coup joué par joueur en colonne j
    int directionCol(int joueur, int j);                        // renvoie la valeur de l'évaluation en colonne du dernier coup joué par joueur en colonne j
    int directionLigne(int joueur, int j);                      // renvoie la valeur de l'évaluation en ligne du dernier coup joué par joueur en colonne j
    int directionDiagoDescendante(int joueur, int j);           // renvoie la valeur de l'évaluation en diagonale descendante (de la gauche vers la droite) du dernier coup joué par joueur en colonne j
    int directionDiagoMontante(int joueur, int j);              // renvoie la valeur de l'évaluation en diagonale montante (de la gauche vers la droite) du dernier coup joué par joueur en colonne j

    int arbitre(int joueur, int j);     // renvoie l'état du jeu
};