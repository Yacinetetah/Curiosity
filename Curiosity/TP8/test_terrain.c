#include "terrain.h"
#include <stdio.h>

int main(int argc, char ** argv) {
  Terrain t;
  int x, y;
  
  if(argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }
	erreur_terrain erreur;
  erreur = lire_terrain(argv[1], &t, &x, &y);
	switch (erreur) {
	
	case ERREUR_FICHIER :
		printf ("ERREUR : fichier incorrect, veuillez rentrer un fichier valide\n");
		char nom_f[20];
		while (erreur == ERREUR_FICHIER) {
			printf ("ERREUR : fichier incorrect, veuillez rentrer un fichier valide\n");
			printf ("Nouveau nom de fichier :\n");
			scanf ("%s", nom_f);
			erreur = lire_terrain(nom_f, &t, &x, &y);
		}
	break;

  case ERREUR_LARGEUR_INCORRECTE:
		printf ("ERREUR : la largeur lue est incorrecte\n");
		return 1;
	break;

  case ERREUR_HAUTEUR_INCORRECTE :
		printf ("ERREUR : la hauteur lue est incorrecte\n");
		return 1;
	break;

  case ERREUR_LIGNE_TROP_COURTE :
		printf ("ERREUR : une des lignes est trop courte\n");
		return 1;
	break;

  case ERREUR_LIGNE_TROP_LONGUE :
		printf ("ERREUR : une des lignes est trop longue\n");
		return 1;
	break;

  case ERREUR_CARACTERE_INCORRECT :
		printf ("ERREUR : le caractere lu est incorrect \n");
		return 1;
	break;

  case ERREUR_LIGNES_MANQUANTES :
		printf ("ERREUR : pas assez de lignes\n");
		return 1;
	break;

  case ERREUR_LECTURE_LARGEUR :
		printf ("ERREUR : dans la lecture de la largeur\n");
		return 1;
	break;
	
  case ERREUR_LECTURE_HAUTEUR :
		printf ("ERREUR : dans la lecture de la hauteur\n");
		return 1;
	break;

  case ERREUR_POSITION_ROBOT_MANQUANTE :
		printf ("ERREUR : il manque la position du robot\n");
		return 1;
	break;
  case OK:
  		break;

	}

  afficher_terrain(&t);
  printf("Position initiale du robot : (%d, %d)\n", x, y);
}

