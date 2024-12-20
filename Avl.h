 #ifndef AVL_H
#include "Avl.c"
#define AVL_H

typedef struct AVL {
    struct AVL* fg;
    struct AVL* fd;
    int eq;
    int ID;
    long long capacité;
    long long conso
}AVL;

AVL* creerAVL(int ID,long long capacite, long long conso);
int estVide(AVL* a);
int estFeuille(AVL* a);
int element(AVL* a);
int existeFG(AVL* a);
int existeFD(AVL* a);
AVL* rotaG(AVL* a);
AVL* rotaD(AVL* a);
AVL* doubleRotaG(AVL* a);
AVL* doubleRotaD(AVL* a);
AVL* equilibrage(AVL* a);
AVL* insertionAVL(AVL* a,int* h,int ID,long long capacite, long long conso);

#endif 
