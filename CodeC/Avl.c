#include <stdio.h>
#include <stdlib.h>
#include <Avl.h>

AVL* creerAVL(int ID,long long conso,long long capacité){
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
    return estVide(a) || estVide(a->fg) && estVide(a->fd);
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
    pivot->eq = max3(eqa-2, eqa+eqp-2, eqp-1);
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

AVL* insertionAVL(AVL* a, int ID, int* h,long long capacite,long long conso){
    if(estVide(a)){
        *h = 1;
        return creerAVL(a->ID,capacite,conso);
    }
    else if( a->id < element(a)){
        a->fg = insertionAVL(a->fg, s, h);
        *h = -*h;
    }
    else if( a->id> element(a)){
        a->fd = insertionAVL(a->fd, s, h);
    }
    else{
        *h = 0;
        a->conso += conso;

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

long convertionStrEntier(const char* str){
    if(strcmp(str, "-") == 0){
        return 0;
    }
    return atoll(str);
}

AVL* traiterFichier(const char* NomFichier, AVL* noeud) {
    FILE *file = fopen(NomFichier, "r");
    if(file == NULL){
        perror("Erreur lors de l'ouverture du fichier\n");
        return noeud;
    }

    int h; 
    int*ph = &h;

    char line[256];

    fgets(line, sizeof(line), file);

    while(fgets(line, sizeof(line), file)){
        int ID;
        char capaciteStr[20];
        char consoStr[20];
        long long capacite;
        long long conso;

        if (sscanf(line, "%d;%19[^;];%19s", &ID, capaciteStr, consoStr) != 3) {
            fprintf(stderr, "Erreur de format dans la ligne : %s\n", line);
            continue;
        }
        
        capacite = convertionStrEntier(capaciteStr);
        conso = convertionStrEntier(consoStr);


         AVL noeud =  insertionAVL(noeud,ID,ph,capacite,conso);
          
 
        
         
    }

    fclose(file);
    return noeud;


}

void ecrireArbreDansFichier(AVL* a, FILE *fichier){
    if(noeud == NULL){
        return;
    }

    ecrireArbreDansFichier(noeud->fg, fichier);

    fprintf(fichier, "%d:%lld:%lld\n", noeud->ID, noeud->capacite, noeud->conso);

    ecrireArbreDansFichier(noeud->fd, fichier);
}

void libererArbre(AVL *noeud){
    if(noeud == NULL){
        return;
    }

    libererArbre(noeud->fg);
    libererArbre(noeud->fd);

    free(noeud);
}

