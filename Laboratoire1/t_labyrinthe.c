#include <stdio.h>
#include<stdlib.h>
#include "t_labyrinthe.h"
#include "mtwister.h"

/*--------------------------------------------------------------------------*/
/*                            ***IMPORTANT***                               */
//Note: line and column in this code is lines as x axis and column as y axis
//The opposite of the instruction document
/*--------------------------------------------------------------------------*/

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

		k = mt_randi(NB_COL * NB_LIG - 1); //random position
		//k = 4; //Test k a position fixe
		lig = 2 * (k % NB_LIG) + 1;	//ligne de k
		col = 2 * (k / NB_LIG) + 1; //colone de k
		lab[lig][col] = LIBRE; //met position initial a libre
		direction= mt_randi(4); //random direction
		//direction = SUD; //test avec direction fixe
		lon = mt_randi(max(NB_COL, NB_LIG)); //random lenght
		//lon = 1; //test avec longeur fixe

		//find next position and set to LIBRE
		//Loop until full lenght has been printed or -1 was returned
		for (int j = 0; j < lon && k != -1; j++) {
			k = obtenir_vosine(k, direction);
			//only print next value if -1 wasn't returned
			if (k != -1) {
				lig = 2 * (k % NB_LIG) + 1; //ligne de k
				col = 2 * (k / NB_LIG) + 1; //colone de k
				lab[lig][col] = LIBRE; //Set next position LIBRE
				//Set the position in between next and current position LIBRE
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
	}
	
}

void afficher_labyrinthe(const t_labyrinthe lab)
{
	//print the maze in the center of the console depending on the number of columns
	printf("\n"); //Seperate labyrinthe from banner
	//Loop for ever column
	for(int i=0;i<(2*NB_COL+1);i++) {
		//Put the labyrinth in the middle
		for (int k = 0;k < 55 - NB_COL;k++)
			printf(" ");
		//Loop for ever row
		for(int j=0;j<(2*NB_LIG+1);j++) {
			if(lab[j][i] == LIBRE) {
				printf("  "); //print blank
			} else {
				printf("%c%c", 0xDB, 0xDB); //print wall
			}
		}
		printf("\n");
	}




}
//Find neignour depending on direction
int obtenir_vosine(int k ,int direction)
{
	
	switch (direction)
	{
	case NORD:
		//if the outside wall is north, return -1
		if (k < NB_LIG)
			return -1;
		return k - NB_LIG; //next position
		break;
	case SUD:
		//if the outside wall is south, return -1
		if ((k+NB_LIG) > (NB_LIG*NB_COL-1))
			return -1;
		return k + NB_LIG; //next position
		break;
	case OUEST:
		//if the outside wall is west, return -1
		if (k % NB_LIG == 0)
			return -1;
		return k-1; //next position
		break;
	case EST:
		//if the outside wall is est, return -1
		if (k % NB_LIG == (NB_LIG - 1))
			return -1;
		return k+1; //next position
		break;
	default:
		return -1;
		break;
	}

	
}
