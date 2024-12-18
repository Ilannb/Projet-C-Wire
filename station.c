#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "Station.h"

void verif_erreur(File * file){
    if(file == NULL){
        printf("Il y a une erreur lors de l'ouverture du fichier\n");
        exit(1);
    }
}
int* recupValFichier(const char *nomFichier){
    File *fichier;
    Station * val;

    fichier = fopen(nomFichier, "r");
    verif_erreur(ficher);

    printf("\n les entier dans le fichier")

}




int somme(AVL* s){

  
  
}
