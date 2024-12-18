#ifndef AVL_H
#include "Station.h"
#define AVL_H

typedef struct AVL {
    struct AVL* fg;
    struct AVL* fd;
    int eq;
    Station val;
}AVL;

AVL* creerAVL(Station s);
int estVide(AVL* a);
int estFeuille(AVL* a);
int element(AVL* a);
int existeFG(AVL* a);
int existeFD(AVL* a);
int  ajouterFG(AVL* a, Station s);
int  ajouterFD(AVL* a, Station s);
AVL* rechercheAVL(AVL* a, int ID);
void affichePrefixeEq(AVL* a);
void afficheInfixeEq(AVL* a);
AVL* rotaG(AVL* a);
AVL* rotaD(AVL* a);
AVL* doubleRotaG(AVL* a);
AVL* doubleRotaD(AVL* a);
AVL* equilibrage(AVL* a);
AVL* insertionAVL(AVL* a, Station s, int* h);

#endif 
