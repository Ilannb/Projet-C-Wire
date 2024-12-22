#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Avl.h"

int main(int argc, char** argv){
  AVL *racine = NULL;

  racine = traiterFichier(argv[1], racine);
  FILE* fichier = fopen(argv[2], "w");
  if(fichier == NULL){
    exit(1);
  }
  ecrireArbreDansFichier(racine, fichier, argv[3]);
  fclose(fichier);
  libererArbre(racine);
  return 0;
}
