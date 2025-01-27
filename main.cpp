/*
TP5 - Puissance 4
Réalisé par :
    - Corentin Saccoman
    - Angelo Adragna
*/

#include "puissance4.h"

using namespace std;

int main(){
    // Initialisation de la partie => sélection de la complexité 
    cout << "----------------------------------------------------------------------------" << endl;      

    int niveau;
    cout << "Choisir niveau de difficulte (entre 1 et 6) : ";
    cin >> niveau;
    while(niveau < 1 || 6 < niveau){
        cout << "La difficulte doit etre comprise entre 1 et 6 !" << endl;
        cout << "Choisir niveau de difficulte (entre 1 et 6) : ";
        cin >> niveau;
    }
    
    Puissance4 partie(niveau);

    srand(time(NULL));

    // tirage au sort du joueur débutant la partie
    cout << "----------------------------------------------------------------------------" << endl;      
    cout << "Tirage au sort du joueur débutant la partie (0 -> Ordi | 1 -> Humain) : ";
    int piece = rand()%2;
    cout << piece << endl;

    int joueur[2] = {1, -1};

    if(piece == 0){
        cout << "Ordi commence la partie !" << endl;
    }
    else{
        cout << "Humain commence la partie !" << endl;
    }

    int num_col = 0;                // on souhaite éviter des débordements avec num_col généré aléatoirement par "int num_col;"
    
    partie.affichage();             // affichage de a grille vide
    int etat_partie = -2;           // etat initial de la partie = partie en cours
    while(etat_partie == -2){       // tant que partie en cours

        if(joueur[piece%2] == 1){   // si au tour de Ordi
            partie.JeuOrdi(num_col, 0);
            cout << endl << "Ordi joue en Colonne n°" << num_col << endl << endl;
        }
        else{                       // si au tour de Humain
            cout << endl << "Au tour de Humain : " << endl;
            cout << endl << "Choisir une Colonne : ";
            cin >> num_col;
            while(num_col < 0 || 6 < num_col || partie.Col[num_col] >= 5){  // on s'assure que la colonne sélectionnée est valide et non pleine
                if(num_col < 0 || 6 < num_col){cout << "La Colonne doit etre comprise entre 0 et 6 (inclus)..." << endl;}
                else{cout << "La Colonne n°" << num_col << " est pleine... Veuillez en selectionner une autre." << endl;}
                cout << "Choisir une Colonne : ";
                cin >> num_col;
            }
            cout << endl << "Humain joue en Colonne n°" << num_col << endl <<  endl;
        }
        partie.jouer(num_col, joueur[piece%2]);                     // le joueur joue
        etat_partie = partie.arbitre(joueur[piece%2], num_col);     // calcul de l'état de la partie
        piece++;                                                    // on passe au joueur suivant
        partie.affichage();                                         // affichage de la nouvelle grille
    }
    if(etat_partie == 1){       // si victoire de Ordi
        cout << "Victoire de Ordi" << endl;
    }
    else if(etat_partie == -1){ // si victoire de Humain
        cout << "Victoire de Humain" << endl;
    }
    else{                       // si match nul
        cout << "Match nul !" << endl;
    }

    
    return 0;
}