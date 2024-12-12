#ifndef AVL_H
#define AVL_H

typedef struct AVL {
    struct AVL* fg;
    struct AVL* fd;
    int eq;
    int val;
}AVL;

AVL* creerAVL(int r);
int estVide(AVL* a);
int estFeuille(AVL* a);
int element(AVL* a);
int existeFG(AVL* a);
int existeFD(AVL* a);
int ajouterFG(AVL* a, int r);
int ajouterFD(AVL* a, int r);
AVL* rechercheAVL(AVL* a, int elmt);
void affichePrefixeEq(AVL* a);
void afficheInfixeEq(AVL* a);
AVL* rotaG(AVL* a);
AVL* rotaD(AVL* a);
AVL* doubleRotaG(AVL* a);
AVL* doubleRotaD(AVL* a);
AVL* equilibrage(AVL* a);
AVL* insertionAVL(AVL* a, int r, int* h);

#endif 
