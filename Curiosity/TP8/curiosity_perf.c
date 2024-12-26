#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generation_terrains.h"
#include "environnement.h"
#include "programme.h"
#include "interprete.h"
#include "terrain.h"
#include "robot.h"
#include "type_pile.h"

void gestion_erreur_terrain(erreur_terrain e) {
  switch(e) {
  case OK: break;
  case ERREUR_FICHIER:
    printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
    exit(1);
  case ERREUR_LECTURE_LARGEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la largeur\n");
    exit(1);
  case ERREUR_LECTURE_HAUTEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la hauteur\n");
    exit(1);
  case ERREUR_LARGEUR_INCORRECTE:
    printf("Erreur lecture du terrain : largeur incorrecte\n");
    exit(1);
  case ERREUR_HAUTEUR_INCORRECTE:
    printf("Erreur lecture du terrain : hauteur incorrecte\n");
    exit(1);
  case ERREUR_CARACTERE_INCORRECT:
    printf("Erreur lecture du terrain : caractère incorrect\n");
    exit(1);
  case ERREUR_LIGNE_TROP_LONGUE:
    printf("Erreur lecture du terrain : ligne trop longue\n");
    exit(1);
  case ERREUR_LIGNE_TROP_COURTE:
    printf("Erreur lecture du terrain : ligne trop courte\n");
    exit(1);
  case ERREUR_LIGNES_MANQUANTES:
    printf("Erreur lecture du terrain : lignes manquantes\n");
    exit(1);
  case ERREUR_POSITION_ROBOT_MANQUANTE:
    printf("Erreur lecture du terrain : position initiale du robot manquante\n");
    exit(1);
  }
}

void affichage_position_programme(erreur_programme e) {
  int i;
  printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
  printf("%s\n", e.ligne);
  /* Impression de e.num_colonne-1 espaces */
  for(i = 1; i < e.num_colonne; i++) {
    printf(" ");
  }
  /* Impression d'un curseur de position */
  printf("^\n");
}

void gestion_erreur_programme(erreur_programme e) {
  switch(e.type_err) {
  case OK_PROGRAMME: break;
  case ERREUR_FICHIER_PROGRAMME:
    printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
    exit(2);
  case ERREUR_BLOC_NON_FERME:
    printf("Erreur lecture du programme : bloc non fermé\n");
    exit(2);
  case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
    printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
    affichage_position_programme(e);
    exit(2);
  case ERREUR_COMMANDE_INCORRECTE:
    printf("Erreur lecture du programme : commande incorrecte\n");
    affichage_position_programme(e);
    exit(2);
  }
}



int main(int argc, char ** argv){
	int N, i, l, h , pas;
	int graine;
  	float dObst;
 	FILE* resFile;
  	Terrain T;
  	Environnement envt;
	Programme prog;
	erreur_terrain errt;
	erreur_programme errp;
	etat_inter etat;
	resultat_inter res;
	int a=0,b=0,c=0,d=0;

  	if (argc < 9) {
   		printf("Usage: %s <fichier_prog> <N> <l> <h> <d> <g> <pas> <fichier_res>\n", argv[0]);
    	return 1;
  	}


  	N = strtol(argv[2], NULL, 10);
  	l = strtol(argv[3], NULL, 10);
  	h = strtol(argv[4], NULL, 10);
  	dObst = strtof(argv[5], NULL);
	graine = strtof(argv[6], NULL);
	pas = strtof(argv[7], NULL);

  	// test de l et h
  	if (l>DIM_MAX || l%2 == 0) {
    	printf("Largeur incorrecte : Largeur doit être impaire et <= %d\n", DIM_MAX);
    	return 1;
  	}
  	if (h>DIM_MAX || h%2 == 0) {
    	printf("Hauteur incorrecte : Hauteur doit être impaire et <= %d\n", DIM_MAX);
    	return 1;
  	}
  	if ((dObst > 1) || (dObst < 0)) {
    	printf("Densité incorrecte :Densité doit être comprise entre 0 et 1\n");
    	return 1;
  	}
	


	resFile = fopen(argv[8], "w");

	srand(graine);

  	fprintf(resFile, "%d\n", N);


	 
	for (i=0;i<N;i++){
    	FILE *terrainfile=fopen("abcdabcd","w");
		int itt=0;
			do{
            generation_aleatoire(&T,l,h,dObst);
          	}while(! existe_chemin_vers_sortie(T));
         //afficher_terrain(&T);
		ecrire_terrain(terrainfile,T,l/2, h/2);
        fclose(terrainfile);
		errt = initialise_environnement(&envt, "abcdabcd");
        gestion_erreur_terrain(errt);

		errp = lire_programme(&prog, argv[1]);
        gestion_erreur_programme(errp);

        /* Initialisation de l'état */
		init_etat(&etat);
		do {
			res = exec_pas(&prog, &envt, &etat);
            itt++;
		} while(res == OK_ROBOT && itt < pas );

		switch(res) {
			case OK_ROBOT:
          	case ARRET_ROBOT : fprintf(resFile, "%d\n", -1);a++; break;
			case SORTIE_ROBOT: fprintf(resFile, "%d\n", itt);d+=itt;b++; break;
			case PLOUF_ROBOT: fprintf(resFile, "%d\n",-2);c++; break;
			case CRASH_ROBOT: fprintf(resFile, "%d\n", -3);c++ ;break;
          	case ERREUR_PILE_VIDE: printf("ERREUR : pile vide\n"); break;
          	case ERREUR_ADRESSAGE: printf("ERREUR : erreur d'adressage\n"); break;
          	case ERREUR_DIVISION_PAR_ZERO: printf("ERREUR : division par 0\n"); break;
		}
	}
	// Affichage des statistiques
    float s=0;
    if(b!=0) s=((float)d/b);
	printf("nombre de terrain d'ou le robot est sortie %d , un pourcentage de %.2f %% \nnombre de terrain d'ou le robot est bloque %d avec pourcentage de %.2f %% \n nombre de terrain d'ou le robot a rentre dans un obstacle %d avec un pourcentage de %.2f %% \n nombre moyen de pas pour la sortie est %0.2f\n",b,((float)b)*100/N,a,((float)a)*100/N,c,((float)c)*100/N,s);

  // Écriture des terrains générés dans le fichier resFile
  // fermeture des fichiers
  fclose(resFile);
  return 0;
}

