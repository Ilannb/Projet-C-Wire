#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Avl.h"

int main(){
  char nomfichier[256];
  char typeStation[10];
  char typeConsommateur[10];
  char nomFichierResultat[10];
  AVL *racine == NULL;

  printf("Entrez le nom de fichier CSV à traiter : ");
  if(fgets(nomfichier, sizeof(nomfichier), stdin) != NULL)){
    nomFichier[strcspn(nomFichier, "\n ")] = 0;
    
  }
  else{
    fprintf(stderr, "ERREUR IMPOSSIBLE DE LIRE LE NOM DU FICHIER\n");
    return 1;
  }

  printf("Entrez le type de station a traiter(hvb, hva, lv) : ");
  if(fgets(typeStation, sizeof(typeStation), stdin) != NULL){
    typeStation[strcspn(typeStation, "\n")] = 0;
  }
  else{
    fprintf(stderr, "erreur : impossible de lire le type de station.\n");
    return 1;


  printf("Entrze le type de consommateur a traiter (comp, indiv, all) : ");
  if(fgets(typeConsommateur, sizeof(typeConsommateur),stdin) != NULL){
    typeConsommateur[strcspn(typeConsommateur, "\n")] = 0;
    
  }

  else{
    fprintf(stderr, "erreur impossible de lire le type de consommateur.\n)");
    return 1;
  }

  if(strcmp(typeStation,"hvb") != 0 && strcmp(typeStation, "hva") != 0 && strcmp(typeStation,"lv") != 0){
    fprintf(stderr, "erreur type de station invalide.\n");
    return 1;
  }

   if(strcmp(typeConsommateur,"hvb") != 0 && strcmp(typeConsommateur, "hva") != 0 && strcmp(typeConsommateur,"lv") != 0){
      fprintf(stderr, "erreur type de consommateur invalide.\n");
      return 1;
    }

  snprintf(nomFichierResultat, sizeof(nomFichierResultat), "%s_%s.csv", typeStation, typeConsommateur);
    printf("Lecture et traitement du fichier : %s\n", nomfichier);
    racine = traiterFichier(nomfichier, racine);

    if(racine == NULL){
      fprintf(stderr, "erreur : aucune donnée valide n'a été trouvée dans le fichier.\n");
      return 2;
    }
    printf("Exportation des résultats dans le fichier : %s\n", nomFichierResultat);
    FILE *sortie = fopen(nomFichierResultat,"w");
    if(sortie == NULL){
      perror("erreur lors de la création du fichier de sortie.\n");
      libererArbre(racine);
      return 3;
      
    }
    fprintf(sortie, "ID:Capacité:Consommation\n");
    ecrireArbreDansFichier(racine, sortie);
    fclose(sortie);

    printf("Résultats sauvegardés dans 's'%.\n", nomFichierResultat);

    libererArbre(racine);

    return 0;
  }
