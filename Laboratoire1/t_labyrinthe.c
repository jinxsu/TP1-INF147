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
	int lon;

	for(int i=0;i<(NB_LIG * NB_COL + 1);i++) {

		k = mt_randi(NB_COL * NB_LIG - 1);
		//k = 4; //Test k a position fixe
		lig = 2 * (k % NB_LIG) + 1;	//ligne de k
		col = 2 * (k / NB_LIG) + 1; //colone de k
		lab[lig][col] = LIBRE; //met position initial a libre
		direction= mt_randi(4);
		//direction = SUD; //test avec direction fixe
		lon = mt_randi(max(NB_COL, NB_LIG));
		//lon = 1; //test avec longeur fixe

		//find next position and set to LIBRE
		for (int j = 0; j < lon && k != -1; j++) {
			k = obtenir_vosine(k, direction);
			if (k != -1) {
				lig = 2 * (k % NB_LIG) + 1;
				col = 2 * (k / NB_LIG) + 1;
				lab[lig][col] = LIBRE;
				switch (direction) {
				case NORD:
					lab[lig][col + 1] = LIBRE;
					break;
				case SUD:
					lab[lig][col - 1] = LIBRE;
					break;
				case OUEST:
					lab[lig + 1][col] = LIBRE;
					break;
				case EST:
					lab[lig - 1][col] = LIBRE;
					break;
				}
			}
		}


		k = obtenir_vosine(k, direction);
		//k = LIBRE;
	}
	
}

void afficher_labyrinthe(const t_labyrinthe lab)
{
	//print the maze in the center of the console depending on the number of columns
	printf("\n");
	for(int i=0;i<(2*NB_COL+1);i++) {
		for (int k = 0;k < 55 - NB_COL;k++)
			printf(" ");
		for(int j=0;j<(2*NB_LIG+1);j++) {
			if(lab[j][i] == LIBRE) {
				printf("  ");
			} else {
				printf("%c%c", 0xDB, 0xDB);
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
		if (k < NB_LIG)
			return -1;
		return k - NB_LIG;
		break;
	case SUD:
		if ((k+NB_LIG) > (NB_LIG*NB_COL-1))
			return -1;
		return k + NB_LIG;
		break;
	case OUEST:
		if (k % NB_LIG == 0)
			return -1;
		return k-1;
		break;
	case EST:
		if (k % NB_LIG == (NB_LIG - 1))
			return -1;
		return k+1;
		break;
	default:
		return -1;
		break;
	}

	
}
