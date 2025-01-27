/*
TP5 - Puissance 4
Réalisé par :
    - Corentin Saccoman
    - Angelo Adragna
*/
#include "puissance4.h"

using namespace std;
Puissance4::Puissance4(int h){      // *****CONSTRUCTEUR*****
    for(int j = 0; j < 7; j++){     // parcours colonnes lignes
        Col[j] = -1;                // Colonnes vides
        for(int i = 0; i < 6; i++){ // Grille vide
            T[i][j] = 0;
        }
    }
    hmax = h;                       // profondeur de l'arbre de recherche
}

void Puissance4::affichage(){
    cout << setw(3) << "+" << "-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    cout << setw(3) << "|" << " i/j |  0  |  1  |  2  |  3  |  4  |  5  |  6  |" << endl;
    
    for(int i = 5; i >= 0; i--){
        cout << setw(3) << "+" << "-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
        cout << setw(3) << "|" << setw(3) << i;
        for(int j = 0; j < 7; j++){
            cout << setw(3) << "|" << setw(3);
            if(T[i][j] != 0){
                if(T[i][j] == -1){cout << "X";}
                else{cout << "O";}
            }
            else{cout << " ";}
        }
        cout << setw(3) << "|" << endl;
    }
    cout << setw(3) << "+" << "-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
}

bool Puissance4::col_pleine(int j){ // renvoie true si la colonne j est pleine, false sinon
    return Col[j] == 5;
}

void Puissance4::jouer(int j, int joueur){      // fait jouer "joueur" dans la colonne j
    if(0 <= j && j <= 6 && !col_pleine(j) ){    // la colonne sélectionnée est valide et la colonne n'est pas pleine
        Col[j]++;
        T[Col[j]][j] = joueur;
    }
    else if(j < 0 || 6 < j){
        cerr << "Colonne invalide : la colonne doit être comprise entre 0 et 6" << endl;
    }
    else{
        cerr << "Impossible de jouer dans la colonne " << j << ". La colonne " << j << " est pleine" << endl;
    }
}

void Puissance4::dejouer(int j){            // Annule le dernier coup joué dans la colonne j
    if(0 <= j && j <= 6 && -1 < Col[j]){    // On s'assure que la colonne est valide et qu'elle n'est pas vide
        T[Col[j]][j] = 0;
        Col[j]--;
    }
}

bool Puissance4::coupgagnant(int joueur, int & bestMove){ // Détermine s'il existe une colonne dans laquelle joueur peut gagner en un coup
    return(coupgagnantCol(joueur, bestMove) || coupgagnantLigne(joueur, bestMove) || coupgagnantDiago(joueur, bestMove));
}

bool Puissance4::coupgagnantCol(int joueur, int & bestMove){ // Détermine s'il existe une colonne dans laquelle joueur peut gagner en un coup, en faisant une Colonne
    for(int j = 0; j < 7; j++){             // Evaluation de chaque colonne
        if(Col[j] >= 2 && !col_pleine(j)){  // minimum 3 valeurs sur la colonne
            int compteur = 0;
            for(int i = Col[j]; i >= Col[j] - 2; i--){
                if(T[i][j] == joueur){      // incrémentation du compteur tant qu'on croise des cases à joueurs sous la case vide étudiée
                    compteur++;
                }
                else{                       // On sort de la bouckle dès qu'on rencontre une case vide ou occupée par l'adversaire
                    break;
                }
            }
            if(compteur == 3){              // Si déjà 3 cases à joueur empilées avec rien au dessus
                bestMove = j;
                return true;                // alors possibilité de gagner en un coup
            }

        }
    }
    return false;
}

bool Puissance4::coupgagnantLigne(int joueur, int & bestMove){ // Détermine s'il existe une colonne dans laquelle joueur peut gagner en un coup, en faisant une ligne
    
    for(int j = 0; j <= 6; j++){    // Parcours de chaque colonne afin d'évaluer à partir du haut de la colonne (case vide)
        if(!col_pleine(j)){         // On vérifie que la colonne n'est pas pleine
            int compteur = 0;
            int j_gauche = j, j_droite = j; // définition de 2 compteurs d'indices de colonnes à partir de j, un à gauche et 1 à droite

            while(j_gauche > 0){    // Tant qu'on ne déborde par à gauche
                j_gauche--;         // On passe à la colonne suivante (à gauche)
                if(T[Col[j] + 1][j_gauche] == joueur){compteur++;}
                else{break;}        // On arrête de compter dès qu'on rencontre une case vide ou occupée par l'adversaire
            }
            while(j_droite < 6){    // Tant qu'on ne déborde par à droite
                j_droite++;         // On passe à la colonne suivante (à droite)
                if(T[Col[j] + 1][j_droite] == joueur){compteur++;}
                else{break;}        // On arrête de compter dès qu'on rencontre une case vide ou occupée par l'adversaire
            }
            if(compteur >= 3){      // Si déjà 3 cases à joueur alignées (à droite ou à gauche)
                bestMove = j;
                return true;        // alors possibilité de gagner en un coup
            }
        }
    }
    
    return false;
}

bool Puissance4::coupgagnantDiago(int joueur, int & bestMove){
    for(int j = 0; j <= 6; j++){
        if(!col_pleine(j)){
            int compteur_diag_gauche = 0, compteur_diag_droite = 0;
            int i_haut = Col[j] + 1, i_bas = Col[j] + 1; // Col[j] + 1 et pas seulement Col[j] car on étudie une case vide
            int j_gauche = j, j_droite = j; 

            while(i_haut < 5 && j_gauche > 0){ // diagonale haute gauche
                i_haut++;
                j_gauche--;
                if(T[i_haut][j_gauche] == joueur){
                    compteur_diag_gauche++;
                }
                else{break;}
            }
            while(i_bas > 0 && j_gauche < 6){ // diagonale basse droite
                i_bas--;
                j_droite++;
                if(T[i_bas][j_droite] == joueur){
                    compteur_diag_gauche++;
                }
                else{break;}
            }

            j_gauche = j_droite = j; // On repart des coordonnées de la case évaluée pour regarder la deuxième diagonale
            i_haut = i_bas = Col[j] + 1;

            while(i_haut < 5 && j_droite < 6){ // diagonale haute droite
                i_haut++;
                j_droite++;
                if(T[i_haut][j_droite] == joueur){
                    compteur_diag_droite++;
                }
                else{break;}
            }
            while(i_bas > 0 && j_gauche > 0){ // diagonale basse gauche
                i_bas--;
                j_gauche--;
                if(T[i_bas][j_gauche] == joueur){
                    compteur_diag_droite++;
                }
                else{break;}
            }
            if(compteur_diag_gauche >= 3 || compteur_diag_droite >= 3){
                bestMove = j;
                return true;
            }
        }
    }
    return false;
}

int Puissance4::JeuOrdi(int & bestMove, int niveau){
    int arg = 0;                    // on souhaite éviter des débordements avec arg généré aléatoirement par "int arg;"
    int joueur = 1;
    int VORDI = 1000;
    int VHUMAIN = -VORDI;

    if(plein()){return 0;}          // match nul      

    if(coupgagnant(joueur, bestMove)){
        return VORDI;
    }
    if(niveau == hmax){
        int somme = 0;
        for(int j = 0; j < 7; j++){
            if(!col_pleine(j)){
                jouer(j, joueur);
                somme += evaluation(joueur, j);
                dejouer(j);
            }
        }
        return somme;
    }
    int val = VHUMAIN;
    for(int j = 0; j < 7; j++){
        if(!col_pleine(j)){
            jouer(j, joueur);
            int res = JeuHumain(arg, niveau + 1);
            dejouer(j);
            if(res > val){
                val = res;
                bestMove = j;
            }
        }
    } 
    return val;
}

int Puissance4::JeuHumain(int & bestMove, int niveau){
    int arg = 0;                    // on souhaite éviter des débordements avec arg généré aléatoirement par "int arg;"
    int joueur = -1;
    int VHUMAIN = -1000;
    int VORDI = -VHUMAIN;

    if(plein()){return 0;}          // match nul

    if(coupgagnant(joueur, bestMove)){
        return VHUMAIN;
    }
    
    if(niveau == hmax){
        int somme = 0;
        for(int j = 0; j < 7; j++){
            if(!col_pleine(j)){
                jouer(j, joueur);
                somme += evaluation(joueur, j);
                dejouer(j);
            }
        }
        return somme;
    }
    
    int val = VORDI;
    for(int j = 0; j < 7; j++){
        if(!col_pleine(j)){
            jouer(j, joueur);
            int res = JeuOrdi(arg, niveau + 1);
            dejouer(j);
            if(res < val){
                val = res;
                bestMove = j;
            }
        }
    } 
    return val;
}

bool Puissance4::plein(){                   // renvoie true si la grille est pleine, false sinon
    for(int j = 0; j < 7; j++){
        if(!col_pleine(j)){return false;}   // Renvoie faux quand il existe une colonne non pleine
    }
    return true;
}

int Puissance4::evaluation(int joueur, int j){ // renvoie l'évaluation d'un coup joué en colonne j par joueur
    return directionCol(joueur, j) + directionLigne(joueur, j) + directionDiagoDescendante(joueur, j) + directionDiagoMontante(joueur, j);
}

int Puissance4::directionCol(int joueur, int j){
    int somme = 0;
    for(int i = Col[j]; i <= Col[j] + 3; i++){      // On regarde la case du dernier coup joué dans la colonne ainsi que les 3 cases au dessus
        if(i <= 5){
            if(T[i][j] == joueur){
                somme += 5;
            }
            else if(T[i][j] == 0){
                somme += 1;
            }

        }
    }
    for(int i = Col[j] - 1; i >= Col[j] - 3; i--){  // on regarde les 3 cases en dessous
        if(i >= 0){
            if(T[i][j] == joueur){
                somme += 5;
            }
            else if(T[i][j] == 0){
                somme += 1;
            }
            else{
                break;
            }

        }
    }
    
    if(somme >= 20){somme = 1000;} // si au moins 4 valeurs joueurs empilées les unes sur les autres
    return somme*joueur; // signe de la victoire = signe du joueur
}

int Puissance4::directionLigne(int joueur, int j){
    int somme = 0;
    int enchainement = 0;

    bool enchainement_gauche = true, enchainement_droite = true;

    int j_gauche = j, j_droite = j + 1;     // On ne fait pas partir le j_droite au même endroit que j_gauche pour ne pas compter la case 2 fois

    while(j_gauche >= 0 && j_gauche >= j - 3){ // parcours à gauche des 4 colonnes à partir de l'actuelle (comprise) (dans la limite de la grille)
        if(T[Col[j]][j_gauche] == joueur){     // Si la case rencontrée est occupée par joueur
            somme += 5; 
            if(enchainement_gauche){           // et qu'on n'a pas déjà croisé une case vide
                enchainement++;                // incrémentation du nombre de cases à joueur qui s'enchainent
            }
        }
        else if(T[Col[j]][j_gauche] == 0){  // Quand on croise une case vide
            somme += 1;
            enchainement_gauche = false;    // l'enchainement à gauche s'arrête
        }
        else{break;}                        // sortie de la boucle quand case occupée par adversaire
        j_gauche--;                         // On passe à la colonne suivante
    }
    // Simétrique à droite en faisant attention de ne pas compter la colonne j une deuxième fois
    while(j_droite <= 6 && j_droite <= j + 3){
        if(T[Col[j]][j_droite] == joueur){
            somme += 5;
            if(enchainement_droite){
                enchainement++;
            }
        }
        else if(T[Col[j]][j_droite] == 0){
            somme += 1;
            enchainement_droite = false;
        }
        else{break;}
        j_droite++;
    }
    
    if(enchainement >= 4){  // Si au moins 4 cases s'enchainent
        somme = 1000;       // victoire
    }
    return somme * joueur;  // signe de la victoire = signe du joueur
}

int Puissance4::directionDiagoDescendante(int joueur, int j){
    // Même logique que l'enchainement sur la ligne
    int somme = 0;
    int enchainement = 0;
    int i_haut = Col[j];
    int i_bas = Col[j] - 1;
    int j_gauche = j, j_droite = j + 1;
    bool enchainement_gauche = true, enchainement_droite = true;


    while(i_haut <= 5 && j_gauche >= 0 && j_gauche >= j - 3){ // diagonale haute gauche
        if(T[i_haut][j_gauche] == joueur){
            somme += 5;
            if(enchainement_gauche){
                enchainement++;
            }
        }
        else if(T[i_haut][j_gauche] == 0){
            somme++;
            enchainement_gauche = false;
        }
        else{break;}
        i_haut++;
        j_gauche--;
    }
    while(i_bas >= 0 && j_droite <= 6 && j_droite <= j + 3){ // diagonale basse droite
        if(T[i_bas][j_droite] == joueur){
            somme += 5;
            if(enchainement_droite){
                enchainement++;
            }
        }
        else if(T[i_bas][j_droite] == 0){
            somme++;
            enchainement_droite = false;
        }
        else{break;}
        i_bas--;
        j_droite++;
    }
    if(enchainement >= 4){
        somme = 1000;
    }
    return somme * joueur;
}

int Puissance4::directionDiagoMontante(int joueur, int j){
    // symétrique de la diagonale descendante
    int somme = 0;
    int enchainement = 0;
    int i_haut = Col[j];
    int i_bas = Col[j] - 1;
    int j_gauche = j - 1, j_droite = j;
    bool enchainement_gauche = true, enchainement_droite = true;


    while(i_haut <= 5 && j_droite <= 6 && j_droite <= j + 3){ // diagonale haute droite
        if(T[i_haut][j_droite] == joueur){
            somme += 5;
            if(enchainement_droite){
                enchainement++;
            }
        }
        else if(T[i_haut][j_droite] == 0){
            somme++;
            enchainement_droite = false;
        }
        else{break;}
        i_haut++;
        j_droite++;
    }
    while(i_bas >= 0 && j_gauche >= 0 && j_gauche >= j - 3){ // diagonale basse gauche
        if(T[i_bas][j_gauche] == joueur){
            somme += 5;
            if(enchainement_gauche){
                enchainement++;
            }
        }
        else if(T[i_bas][j_gauche] == 0){
            somme++;
            enchainement_gauche = false;
        }
        else{break;}
        i_bas--;
        j_gauche--;
    }
    if(enchainement >= 4){
        somme = 1000;
    }
    return somme * joueur;
}

int Puissance4::arbitre(int joueur, int j){
    int etat_jeu = evaluation(joueur, j);   // Evaluation du dernier coup joué par joueur en colonne j
    if(joueur == -1 && etat_jeu <= -1000 || joueur == 1 && etat_jeu >= 1000){   // en cas de victoire de joueur
        return joueur;
    }
    if(plein()){
        return 0;   // match nul si grille pleine et pas de victoire
    }
    return -2;      // partie en cours si pas de victoire et pas match nul
}
