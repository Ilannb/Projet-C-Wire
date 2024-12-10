#include <stdio.h>
#include <stdlib.h>

typedef struct AVL{
    struct AVL* fg;
    struct AVL* fd;
    int eq;
    int val;
}AVL;

AVL* creerAVL(int r){
    AVL* newAVL=malloc(sizeof(newAVL));
    if(newAVL==NULL){
        exit(1);
    }
    newAVL->fg=NULL;
    newAVL->fd=NULL;
    newAVL->eq=0;
    newAVL->val=r;
    return newAVL;
}

int estVide(AVL* a){
    return a==NULL;
}

int estFeuille(AVL* a){
    return estVide(a) || estVide(a->fg) && estVide(a->fd);
}

int element(AVL* a){
    return estVide(a) ? 0 : a->val;
}

int existeFG(AVL* a){
    return !estVide(a) && !estVide(a->fg);
}

int existeFD(AVL* a){
    return !estVide(a) && !estVide(a->fd);
}

int ajouterFG(AVL* a, int r){
    if(estVide(a)){
        return 0;
    }
    a->fg=creerAVL(r);
    return 1;
}

int ajouterFD(AVL* a, int r){
    if(estVide(a)){
        return 0;
    }
    a->fd=creerAVL(r);
    return 1;
}

AVL* rechercheAVL(AVL* a, int elmt){
    if(estVide(a)){
        return NULL;
    }
    else if(element(a)==elmt){
        return a;
    }
    else if(element(a)>elmt){
        return rechercheAVL(a->fg, elmt);
    }
    else{
        return rechercheAVL(a->fd, elmt);
    }
}

void affichePrefixeEq(AVL* a){
    if(!estVide(a)){
        printf("Valeur : %d, Equilibre : %d\n",element(a),a->eq);
        affichePrefixeEq(a->fg);
        affichePrefixeEq(a->fd);
   }
}

void afficheInfixeEq(AVL* a){
    if(!estVide(a)){
        afficheInfixeEq(a->fg);
        printf("Valeur : %d, equilibre : %d",element(a),a->eq);
        afficheInfixeEq(a->fd);
   }
}

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min3(a,b,c) (min(min(a,b),c))
#define max3(a,b,c) (max(max(a,b),c))

AVL* rotaG(AVL* a){
    AVL* pivot;
    int eqa, eqp;

    a->fd = pivot->fg;
    pivot->fg = a;
    eqa = a->eq;
    eqp = pivot->eq;

    a->eq = eqa - max(eqp, 0) - 1;
    pivot->eq = max3(eqa-2, eqa+eqp-2, eqp-1);
    a = pivot;

    return a;
}

AVL* rotaD(AVL* a){
    AVL* pivot;
    int eqa, eqp;

    a->fg = pivot->fd;
    pivot->fd = a;
    eqa = a->eq;
    eqp = pivot->eq;

    a->eq = eqa - max(eqp, 0) + 1;
    pivot->eq = max3(eqa+2, eqa+eqp+2, eqp-1);
    a = pivot;

    return a;
}

AVL* doubleRotaG(AVL* a){
    a->fd = rotaD(a);
    return rotaG(a);
}

AVL* doubleRotaD(AVL* a){
    a->fg = rotaG(a);
    return rotaD(a);
}

AVL* equilibrage(AVL* a){
    if(a->eq >= 2){
        if(a->fd->eq >= 0){
            return rotaG(a);
        }
        else{
            return doubleRotaG(a);
        }
    }
    else if (a->eq <= -2){
        if(a->fg->eq <= 0){
            return rotaD(a);
        }
        else{
            doubleRotaD(a);
        }
    }
    return a;
}

AVL* insertionAVL(AVL* a, int r,  int* h){
    if(estVide(a)){
        *h = 1;
        return creerAVL(r);
    }
    else if(r < element(a)){
        a->fg = insertionAVL(a->fg, r, h);
        *h = -*h;
    }
    else if(r > element(a)){
        a->fd = insertionAVL(a->fd, r, h);
    }
    else{
        *h = 0;
        return a;
    }

    if(*h != 0){
        a->eq = a->eq + *h;
        a = equilibrage(a);
        if(a->eq == 0){
            *h = 0;
            return a;
        }
        else{
            *h = 1;
        }
    }
    return a;
}
