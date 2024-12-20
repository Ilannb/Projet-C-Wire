#include <stdio.h>
#include <stdlib.h>
#include "avl.h" // Inclure votre bibliothèque AVL existante


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

    char line[256];

    int h = 0; //variable pour suivre la hauteur de l'arbre 

    fgets(line, sizeof(line), file);

    while(fgets(line, sizeof(line), file)){
        int ID;
        char capaciteStr[20];
        char consoStr[20];
        long capacite;
        long conso;

        sscanf(line, "%d;%19[^;];%19s", &type, capaciteStr, consoStr);

        capacite = convertionStrEntier(capaciteStr);
        conso = convertionStrEntier(consoStr);

        Station s;
        s.ID = ID;
        s.capacite = capacite;
        s.somme_conso = conso;

        noeud = insertionAVL(noeud, s, &h);
    }

    fclose(file);
    return noeud;


}
