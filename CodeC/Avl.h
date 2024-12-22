#ifndef AVL_H
#define AVL_H

#include <stdio.h>   
#include <stdlib.h>
#include <string.h>

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min3(a,b,c) (min(min(a,b),c))
#define max3(a,b,c) (max(max(a,b),c))

typedef struct AVL {
    struct AVL* fg;
    struct AVL* fd;
    int eq;
    int ID;
    long long capacite;
    long long conso;
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
AVL* insertionAVL(AVL* a, int ID, int* h, long long capacite, long long conso);
long long convertionStrEntier(const char* str);
void ajouterConsommation(AVL* a, int ID,long long conso);
AVL* traiterFichier(const char* NomFichier, AVL* noeud);
void ecrireArbreDansFichier(AVL* noeud, FILE *fichier, char* typeconso);
void libererArbre(AVL *noeud);

#endif 
