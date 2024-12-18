#!/bin/bash

#vérification des arguments

if [ -z "$1" ]; then
  echo "Le fichier c-wire n'est pas fourni, veuillez réessayer."
  echo ""
  exit 1
fi

c_wire="$1" 

#vérification du fichier

if [ ! -f "$1" ]; then
  echo "Il n'y a pas de fichier '$1'"
  echo ""
  exit 1
fi

echo ""
echo "Le fichier d'entrée : $1"
echo ""

#type de station :

STAT="$2"

#type de consommateur : 

CONS="$3"

#ID centrale (optionnel):

IDC="$4"

#fonction de l'option d'aide(-h)(optionnel):

afficher_aide() {
  echo "Utilisation : c-wire.sh chemin_fichier station consommateur [id_centrale]" "[id_centrale] optionnel"
  echo ""
  echo "DESCRIPTION :"
  echo "  Ce script traite les données d'une station pour générer un fichier de sortie."
  echo ""
  echo "PARAMÈTRES :"
  echo "  fichier          Obligatoire. Chemin vers le fichier CSV contenant les données."
  echo "  station          Obligatoire. Type de station : hvb, hva, lv."
  echo "  consommateur     Obligatoire. Type de consommateur : comp, indiviv, all."
  echo "  id_centrale      Optionnel. Identifiant spécifique pour filtrer les données."
  echo ""
  echo "OPTIONS :"
  echo "  -h                   Affiche cette aide."
  echo ""
  echo "EXEMPLES :"
  echo "  bash c-wire.sh fichier.csv lv all"
  echo "  bash c-wire.sh fichier.csv hvb comp 1234"
  echo ""
  echo "ATTENTION ! Les paramètres suivants sont interdits/non-fonctionnels:"
  echo "  bash c-wire.sh fichier.csv hvb all"
  echo "  bash c-wire.sh fichier.csv hvb indiviv"
  echo "  bash c-wire.sh fichier.csv hva all"
  echo "  bash c-wire.sh fichier.csv hva indiviv"
}

#vérification de l'option d'aide

for arg in "$@"; do
  if [ "$arg" == "-h" ]; then
    afficher_aide
  fi
done

#vérification de la station

if [ -z "$2" ]; then
  echo "Le type de station est obligatoire mais n'est pas présent, veuillez réessayer."
  echo ""
  afficher_aide
  exit 1
fi

#vérification du consommateur

if [ -z "$3" ]; then
  echo "Le type de consommateur est obligatoire mais n'est pas présent, veuillez réessayer."
  echo ""
  afficher_aide
  exit 1
fi

#vérification des options interdites car seules les entreprises sont connectées aux stations HV-B et HV-A

if [[ "$3" != "comp" && ("$2" == "hvb" || "$3" == "hva" ) ]]; then
  echo "Seules les entreprises sont connectées aux stations HV-B et HV-A, veuillez réessayer."
  echo ""
  afficher_aide
  exit 1
fi

#fichier de sortie à la fin 

fichier_filtre="${2}_${3}_${4}cwire.csv"
echo "type de station;capacité;consommation" > "$fichier_filtre" 

#lecture du fichier d'entrée c-wire de base

start_time=$(date +%s)

awk -F';' -v station="$2" -v conso="$3" -v fichier_filtre="${2}_${3}_${4}cwire.csv" '
BEGIN {
  OFS=";" #pour bien séparer avec les point-virgules
  print "type de station;capacité;consommation" > fichier_filtre; #en-tête du fichier de sortie
}

NR > 1 { #le > 1 pour ignorer la première ligne du fichier

  #filtrage du type de station
  
  if (station == "hvb") stat = $2; #cela correspondra à HV-B Station dans le fichier
  else if (station == "hva") stat = $3; #cela correspondra à HV-A Station dans le fichier
  else if (station == "lv") stat = $4; #cela correspondra à LV Station dans le fichier
  else {
    print "Le type de station est invalide, veuillez réessayer." > "/dev/stderr";
    print ""
    exit 1;
  }

  #filtrage du type de consommateur
  
  if (conso == "comp") cons = $5; #cela correspondra à Company dans le fichier
  else if (conso == "indiv") cons = $6; #cela correspondra à Individual dans le fichier
  else if (conso == "all") cons = ($5 + $6); #cela correspondra à Company ET Indvidual dans le fichier
  else {
    print "Le type de consommateur est invalide, veuillez réessayer." > "/dev/stderr";
    print ""
    exit 1;
  }

  #enregistrement de la ligne si ce qu on entre est valide
  
  if(station == "hvb"){ #pour bien filtrer pour le cas du hvb
    if (stat != "-" && $3 == "-") {  
      print stat, $7, $8 >> fichier_filtre;
    }
  }
  
  else if(station == "hva"){ #pour bien filtrer pour le cas du hva
    if (stat != "-" && $4 == "-") { #pour bien filtrer 
      print stat, $7, $8 >> fichier_filtre;
    }
  }
  
  else { #pour bien filtrer pour le cas du lv
    if (conso == "indiv"){
      if (stat != "-" && $5 == "-"){
        print stat, $7, $8 >> fichier_filtre;
      }
    }
    
    else if (conso == "comp"){
      if (stat != "-" && $6 == "-"){
        print stat, $7, $8 >> fichier_filtre;
      }
    }
    
    else {
      if (stat != "-"){
        print stat, $7, $8 >> fichier_filtre;
      }
    }
  }
}

END {
  print "Succès du traitement. Les résultats se trouvent dans : " fichier_filtre;
  print ""
} ' "$1"

end_time=$(date +%s) #l'heure de fin en secondes
execution_time=$((end_time - start_time)) #différence entre l'heure de fin et de début pour avoir le temps d'execution total

if [[ $execution_time == 0 ]]; then
  echo "Temps d'exécution : $execution_time seconde."
  echo ""
else
  echo "Temps d'exécution : $execution_time secondes."
  echo ""
fi
