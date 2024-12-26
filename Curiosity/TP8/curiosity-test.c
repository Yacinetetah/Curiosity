#include <stdio.h>
#include <stdlib.h>
#include "programme.h"
#include "interprete.h"
#include "terrain.h"
#include "environnement.h"


void gestion_erreur_terrain(erreur_terrain e) {
  switch (e) {
  case OK:
    break;
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
    printf(
        "Erreur lecture du terrain : position initiale du robot manquante\n");
    exit(1);
  }
}

void affichage_position_programme(erreur_programme e) {
  int i;
  printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
  printf("%s\n", e.ligne);
  /* Impression de e.num_colonne-1 espaces */
  for (i = 1; i < e.num_colonne; i++) {
    printf(" ");
  }
  /* Impression d'un curseur de position */
  printf("^\n");
}

void gestion_erreur_programme(erreur_programme e) {
  switch (e.type_err) {
  case OK_PROGRAMME:
    break;
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


int main(int argc, char **argv) {
  Environnement envt;
  Programme prog;
  erreur_terrain errt;
  erreur_programme errp;
  etat_inter etat;
  resultat_inter res;
  FILE *f;
  char terrain[50];
  char programme[50];
  int nombre_pas_maximum,x,y;
  int j=0,var=1; 
  char e;
  char o;
  Orientation or;

  if (argc < 2) {
    printf("Usage: %s <terrain> <programme>\n", argv[0]);
    return 1;
  }
  
    f=fopen(argv[1],"r");
    if(f == NULL) {
      printf("erreur le fichier n'a pas pu etre ouvert\n");
      return-1;} 
     
    fscanf(f,"%s", terrain);
    fscanf(f,"%s", programme);
    fscanf(f,"%d", &nombre_pas_maximum);
    fscanf(f,"\n");
    fscanf(f,"%c",&e);
    if (e == 'N' || e == 'F')
     { fscanf(f,"%d",&x); 
       fscanf(f,"%d",&y);
       fscanf(f,"\n");
       fscanf(f,"%c",&o);
       switch(o)
	      {
		case 'N':
			or = Nord;
			break;
		case 'E':
			or = Est;
			break;
		case 'S':
			or = Sud;
			break;
		case 'O':
			or = Ouest;
			break;
	       }
	 
     }
     fclose(f);
 
  /* Initialisation de l'environnement : lecture du terrain,
     initialisation de la position du robot */
  errt = initialise_environnement(&envt, terrain);
  gestion_erreur_terrain(errt);

  /* Lecture du programme */
  errp = lire_programme(&prog, programme);
  gestion_erreur_programme(errp);

  affichage_position_programme(errp); 

  /* Initialisation de l'état */
  init_etat(&etat);
  do {
    res = exec_pas(&prog, &envt, &etat);
    j++;
    afficher_envt(&envt);
  } while (res == OK_ROBOT && j<nombre_pas_maximum);

  /* Affichage du résultat */
  switch(res) {
     case OK_ROBOT:
	if (e != 'N')
	 {printf("OK_ROBOT, evenement inattendu\n");
	  printf("l'evenement attendu est : %c\n", e);
	  var=0;}
	  printf("OK_ROBOT,OK\n"); 
	  break;
     case SORTIE_ROBOT:
	 if (e != 'S')
	  {printf("SORTIE_ROBOT, evenement inattendu\n");
           printf("l'evenement attendu est : %c\n", e);
	   var=0;
	  }
	  printf("SORTIE_ROBOT,OK\n"); 
	  break;
     case ARRET_ROBOT:
	 if (e != 'F')
	 {
	  printf("ARRET_ROBOT, evenement inattendu\n");
          printf("l'evenement attendu est : %c \n", e);
	  var=0;
	 }else{
	 printf("ARRET_ROBOT, programme termine Robot sur une case libre :-/\n"); 
	 }
         break;
    case PLOUF_ROBOT: 
	 if (e != 'P')
	  {printf("PLOUF_ROBOT,:evenement inattendu\n");
	   printf("l'evenement attendu est : %c\n", e);
	   var=0;
	  }
	  printf("PLOUF_ROBOT, le robot est tombe dans l'eau\n"); 
	  break;
    case CRASH_ROBOT: 
	  if (e != 'O')
	   {printf("CRASH_ROBOT, evenement inattendu : %c\n", e);
    	    printf("l'evenement attendu est : %c\n", e);
	    var=0;
	   }
	   printf("CRASH_ROBOT,Le Robot s'est ecrase sur un rocher\n"); 
	   break;
    case ERREUR_PILE_VIDE: 
	 printf("ERREUR : Pile Vide\n"); 
	 break;
    case ERREUR_ADRESSAGE: 
	 printf("ERREUR : erreur d'adressage\n"); 
	 break;
    case ERREUR_DIVISION_PAR_ZERO: 
	 printf("ERREUR : Division par 0\n"); 
	 break;
	}
   if (e == 'N' || e == 'F')
      {
       if (envt.r.x != x || envt.r.y !=y)
        {
         printf("la position finale du robot est incorrecte\n");
         printf("la position finale du robot attendue est (%d,%d), position du robot est (%d,%d)\n",x,y,envt.r.x, envt.r.y);
         var =0;  
        }
        else
           printf("POS Ok\n");
        if (envt.r.o != or)
           {     
             printf("L'orentation finale du robot est incorrecte\n");
             printf("L'orentation attendue est %c\n",or);
             var = 0;
           }
        else 
          printf("Orentation OK\n");
    } 
    if(var == 1)
	printf("Les Tests ont reussis\n");
    else
        printf("Les Tests ont echoues\n"); 
    return 0;    
   
}



