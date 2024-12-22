#include "Avl.h"

//on entre nos fonctions usuelles habituelles d'AVL et on réadapte avec 3 valeurs, la consommation, la capacité et l'ID

AVL* creerAVL(int ID,long long conso,long long capacite){
    AVL* newAVL=malloc(sizeof(AVL));
    if(newAVL==NULL){
        exit(1);
    }
    newAVL->fg=NULL;
    newAVL->fd=NULL;
    newAVL->eq=0;
    newAVL->conso = conso;
    newAVL->capacite = capacite; 
    newAVL->ID = ID;

    return newAVL;
}

int estVide(AVL* a){
    return a==NULL;
}

int estFeuille(AVL* a){
    return estVide(a) || (estVide(a->fg) && estVide(a->fd));
}

int existeFG(AVL* a){
    return !estVide(a) && !estVide(a->fg);
}

int existeFD(AVL* a){
    return !estVide(a) && !estVide(a->fd);
}

AVL* rotaG(AVL* a){
    AVL* pivot = a->fd;
    int eqa, eqp;

    a->fd = pivot->fg;
    pivot->fg = a;
    eqa = a->eq;
    eqp = pivot->eq;

    a->eq = eqa - max(eqp, 0) - 1;
    pivot->eq = min3(eqa-2, eqa+eqp-2, eqp-1);
    a = pivot;

    return a;
}

AVL* rotaD(AVL* a){
    AVL* pivot = a->fg;
    int eqa, eqp;

    a->fg = pivot->fd;
    pivot->fd = a;
    eqa = a->eq;
    eqp = pivot->eq;

    a->eq = eqa - min(eqp, 0) + 1;
    pivot->eq = max3(eqa+2, eqa+eqp+2, eqp+1);
    a = pivot;

    return a;
}

AVL* doubleRotaG(AVL* a){
    a->fd = rotaD(a->fd);
    return rotaG(a);
}

AVL* doubleRotaD(AVL* a){
    a->fg = rotaG(a->fg);
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

//dans notre fonction insertion, il y'aura alors la capacité et la consommation en paramètres

AVL* insertionAVL(AVL* a, int ID, int* h, long long capacite, long long conso){
    if(estVide(a)){
        *h = 1;
        return creerAVL(ID, conso, capacite);
    }
    else if(ID < a->ID){
        a->fg = insertionAVL(a->fg, ID, h, capacite, conso);
        *h = -*h;
    }
    else if(ID > a->ID){
        a->fd = insertionAVL(a->fd, ID, h, capacite, conso);
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
        }
        else{
            *h = 1;
        }
    }
    return a;
}

//pour convertir les tirets en 0 et qu'on puisse par la suite sommer correctement

long long convertionStrEntier(const char* str){
    if(strcmp(str, "-") == 0){
        return 0;
    }
    return strtoll(str, NULL, 10);
}

//pour pouvoir sommer la consommation

void ajouterConsommation(AVL* a, int ID,long long conso){
    if(!estVide(a)){
        if(ID<a->ID){
            ajouterConsommation(a->fg, ID, conso);
        }
        else if(ID>a->ID){
            ajouterConsommation(a->fd, ID, conso);
        }
        else{
            a->conso += conso;
        }
    }
}

//ouverture et lecture du fichier, traitage des lignes du fichier crée depuis le bash

AVL* traiterFichier(const char* NomFichier, AVL* noeud) {
    FILE *file = fopen(NomFichier, "r");
    if(file == NULL){
        perror("Erreur lors de l'ouverture du fichier\n");
        return noeud;
    }

    int h; 
    int*ph = &h;

    int ID;
    char capaciteStr[20];
    char consoStr[20];
    long long capacite;
    long long conso;
    
    while(fscanf(file, "%d;%20[^;];%20[^\n]", &ID, capaciteStr, consoStr) != EOF){
        capacite = convertionStrEntier(capaciteStr);
        conso = convertionStrEntier(consoStr); 
        if(conso!=0){
            ajouterConsommation(noeud, ID, conso);
        }
        else{
            noeud = insertionAVL(noeud, ID, ph, capacite, conso);
        }
    }
    fclose(file);
    return noeud;
}

//réecriture du fichier avec sommation de la consommation

void ecrireArbreDansFichier(AVL*noeud, FILE *fichier, char* typeconso){
    if(estVide(noeud)){
        return;
    }

    ecrireArbreDansFichier(noeud->fg, fichier, typeconso);
    if(strcmp(typeconso,"all") == 0){
        fprintf(fichier, "%d:%lld:%lld:%lld\n", noeud->ID, noeud->capacite, noeud->conso, noeud->capacite - noeud->conso);
    }
    else{
        fprintf(fichier, "%d:%lld:%lld\n", noeud->ID, noeud->capacite, noeud->conso);
    }
    ecrireArbreDansFichier(noeud->fd, fichier, typeconso);
}

void libererArbre(AVL *noeud){
    if(estVide(noeud)){
        return;
    }

    libererArbre(noeud->fg);
    libererArbre(noeud->fd);

    free(noeud);
}

