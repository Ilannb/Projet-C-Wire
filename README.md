# Projet-C-Wire
C-Wire est un projet développé par Anas CHOKRI, Nassim Izza et Ilann BOUDRIA. (2024/2025) 

 1 - Assurez vous d'utiliser Linux ou d'avoir installer un termial Linux

 2 - Comment mettre en route le Projet ?

   Utilisez les commandes suivantes :
   ```sh
   ./c-wire.sh <Fichier CSV> <Type de station > <Type de consommateur> [ID de la centrale mère]
   ```
   Si vous n'avez pas les droits nécessaire utilisez :
   ```sh
   bash c-wire.sh <Fichier CSV> <Type de station> <Type de consommateur> [ID de la centrale mère]
   ```
   Exemple : 
   ```sh
    ./c-wire.sh data.csv hva comp 4
   ```
   3 - Options
   
 - `<Fichier CSV>`: Chemin vers le fichier CSV.
 - `<Type de station>`: Type de station (hva, hvb, lv).
 - `<Type de consommateur>`: Type de consommateur (comp, indiv, all). Note: Les stations hvb et hva ne fonctionnes qu'avec les consommateur suivant : comp.
 - `[ID de la Centrale mère]`: (Optionel) ID de la centrale mère, doit être un nombre positif.

   4 - Option d'aide 
      
  Pour afficher l'option d'aide, utilisez l'option -h
  ```sh
  ./c-wire.sh -h
  ```

  5 - Besoins du projet

  Avant de mettre en route le projet assurez vous d'avoir installé :
  
    - **GCC** pour compiler le code
    - **Make** pour assembler le projet
    
  Afin d'installer les besoins du projet sur un systeme Ubuntu/Debian, entrez:
  ```bash
  sudo apt update
  sudo apt install build-essential
  ```
  6 - Projet créé grâce aux moyen suivant : 

  - Programmation C
  - Programmation Shell
  - Platforme Vs code
  - Plateforme GitHub

  7 - Collaborateurs

  - Ilannb
  - Anas-csv
  - nassiimz  
