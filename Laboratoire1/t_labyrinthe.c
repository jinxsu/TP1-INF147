#include <stdio.h>
#include<stdlib.h>
#include "t_labyrinthe.h"
#include "mtwister.h"


void remplir_de_murs(t_labyrinthe lab)
{
	//remplir le labyrinthe de murs
	for(int i=0;i<(NB_LIG+1);i++) {
		for(int j=0;j<(NB_COL+1);j++) {
			lab[i][j] = MUR;
		}
	}
}

void init_labyrinthe(t_labyrinthe lab)
{
	int k;
	int lig;
	int col;
	int direction;

	for(int i=0;i<(NB_LIG*NB_COL+1);i++) {

		k = mt_randi(NB_COL * NB_LIG - 1);
		lig = 2 * (k / NB_COL + 1);
		col = 2 * (k % NB_COL + 1);
		k = LIBRE;
		direction= mt_randi(4);
		k = obtenir_vosine(k, direction);
		k = LIBRE;
	}
	
}

void afficher_labyrinthe(const t_labyrinthe lab)
{
	//print the maze in the center of the console depending on the number of columns
	for(int i=0;i<(NB_LIG+1);i++) {
		for(int j=0;j<(NB_COL+1);j++) {
			if(lab[i][j] == MUR) {
				printf("%c");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}

}
int obtenir_vosine(int k ,int direction)
{
	switch (direction)
	{
	case NORD:
		return k-2*NB_COL-1;
		break;
	case SUD:
		return k+2*NB_COL+1;
		break;
	case OUEST:
		return k-2;
		break;
	case EST:
		return k+2;
		break;
	default:
		return -1;
		break;
	}

	
}
