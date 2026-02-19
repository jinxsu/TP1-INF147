#include <stdio.h>
#include<stdlib.h>
#include "t_labyrinthe.h"
#include "mtwister.h"


#define LONGUEUR_MAX (NB_LIG > NB_COL) ? NB_LIG : NB_COL // longueur maximale d'un passage


void remplir_de_murs(t_labyrinthe lab)
{
	//Fonctionne
	//remplir le labyrinthe de murs
	for(int i=0;i<(2*NB_LIG+1);i++) {
		for(int j=0;j<(2*NB_COL+1);j++) {
			lab[i][j] = MUR;
		}
	}
}

void init_labyrinthe(t_labyrinthe lab)
{
	//TODO: Revoir le fonctionnement
	int k;
	int direction;
	int longueur;
	int voisine;
	int lig, col;
	int lig_voisine, col_voisine;


	//Initialiser le tableau du labyrinthe en le remplissant de murs
	remplir_de_murs(lab);

	//Initier le g�n�rateur de nombres pseudo-al�atoires
	mt_srand(12345); // Initialiser avec une graine fixe pour des résultats reproductibles

	//creer des passages en creusant des cellules et leurs voisines dans une direction choisie au hasard
	for (int i = 0;i < NB_LIG * NB_COL; i++)
	{
		//choisir une cellule, une direction et une longueur de passage au hasard
		k = mt_randi(NB_LIG * NB_COL)-1;
		direction = mt_randi(4); 
		longueur = mt_randi(LONGUEUR_MAX-1)+1; 
		
		//determiner les coordonnées de la cellule k dans le labyrinthe
		lig = 2 * (k / NB_COL) + 1; 
		col = 2 * (k % NB_COL) + 1; 
	
		lab[lig][col] = LIBRE; // creuser la cellule k
		int k_copie = k; // copier k pour le parcours du passage

		// creuser le passage en avançant dans la direction choisie pour la longueur choisie
		for (int j = 0; j < longueur; j++) {

			voisine = obtenir_vosine(k_copie, direction); // obtenir la voisine de k dans la direction choisie
			
			if (voisine == -1) break; // si la voisine est hors limites, arrêter le passage et passer à la cellule suivante

			lig_voisine = 2 * (voisine / NB_COL) + 1; // calculer la ligne de la voisine
			col_voisine = 2 * (voisine % NB_COL) + 1; // calculer la colonne de la voisine
			
			lab[lig_voisine][col_voisine] = LIBRE; // creuser la voisine
			lab[(lig + lig_voisine) / 2][(col + col_voisine) / 2] = LIBRE; // creuser le mur entre k_copie et sa voisine

			// mettre à jour les coordonnées de k_copie pour le prochain pas du passage
			lig = lig_voisine;
			col = col_voisine;
			k_copie = voisine;
			
		}

	}
	
}

void afficher_labyrinthe(const t_labyrinthe lab)
{
	
	int largeur_ecran = 80;
	int largeur_labyrinthe = (2 * NB_COL + 1)/2;
	int marge = (largeur_ecran - largeur_labyrinthe) / 2;
	
	//Afficher le labyrinthe
	printf("\n");
	for(int i=0; i < 2 * NB_LIG + 1; i++) {

		// Afficher la marge
		for(int m = 0; m < marge; m++) {
			printf(" ");
		}

		// Afficher les caractères du labyrinthe
		for (int j = 0; j < 2 * NB_COL + 1; j++)
		{
			if(lab[i][j] == MUR) {
				printf("%c", 219);// caractère plein pour les murs
			} else {
				printf("%c", 32);// caractère espace pour les passages
			}
		}
		printf("\n");
	}

}

int obtenir_vosine(int k ,int direction)
{
	//calculer la position du voisin de k dans la direction donnée
	int lig = 2 * (k / NB_COL) + 1;
	int col = 2 * (k % NB_COL) + 1;

	switch (direction) {
		case NORD:
			if (lig - 2 < 0) return -1; // Hors limites
			return k - NB_COL;
		case SUD:
			if (lig + 2 > 2 * NB_LIG + 1) return -1; // Hors limites
			return k + NB_COL;
		case OUEST:
			if (col - 2 < 0) return -1; // Hors limites
			return k - 1;
		case EST:
			if (col + 2 > 2 * NB_COL + 1) return -1; // Hors limites
			return k + 1;
		default:
			return -1; // Direction invalide
	}
	

	
}

