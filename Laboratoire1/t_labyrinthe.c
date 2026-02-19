#include <stdio.h>
#include<stdlib.h>
#include "t_labyrinthe.h"
#include "mtwister.h"


void remplir_de_murs(t_labyrinthe lab)
{
	//Fonctionne
	//remplir le labyrinthe de murs
	for(int i=0;i<(NB_LIG+1);i++) {
		for(int j=0;j<(NB_COL+1);j++) {
			lab[i][j] = MUR;
		}
	}
}

void init_labyrinthe(t_labyrinthe lab)
{
	//TODO: Revoir le fonctionnement
	int k;
	int lig;
	int col;
	int longueur;
	int direction;
	t_labyrinthe voisin;

	for(int i=0;i<(NB_LIG*NB_COL+1);i++) {
		
		k = mt_randi(0, NB_LIG * NB_COL - 1);
		direction = mt_randi(2,4);
		lig =2*( k / NB_COL)+1;
		col = 2 * (k % NB_COL) + 1;
		lab[lig][col] = LIBRE;
		longueur = 2;
		
		for(int j=0; j<longueur; j++) {
			k = obtenir_vosine(k, direction);
			lig = 2 * (k / NB_COL) + 1;
			col = 2 * (k % NB_COL) + 1;
			lab[lig][col] = LIBRE;
			
		}
		
		k = LIBRE;
	}
	
}

void afficher_labyrinthe(const t_labyrinthe lab)
{
	//Fonctionne
	printf("\n");
	for(int i=0;i<(NB_LIG+1);i++) {
		for (int k = 0; k < (2*NB_COL + 1) / 2; k++) {
			printf("\t");
		}
		for(int j=0;j<(NB_COL+1);j++) {
			if(lab[i][j] == MUR) {
				printf("%c%c", 219,219);
			} else {
				printf(" ");
			}
		}
		printf("\n");
		
	}

}
int obtenir_vosine(int k ,int direction)
{
	//TODO: Revoir le fonctionnement
	//calculer la position du voisin de k dans la direction donnée
	switch (direction)
	{
	case NORD:
		return k-(NB_COL-1);
		break;
	case SUD:
		return k+(NB_COL+1);
		break;
	case OUEST:
		return k-1;
		break;
	case EST:
		return k+1;
		break;
	default:
		return -1;
		break;
	}

	
}
