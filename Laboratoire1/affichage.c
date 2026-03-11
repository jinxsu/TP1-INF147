/* AFFICHAGE.C
   Déclaration de la fonction d'affichage pour une pile d'entiers.

   Auteur  : Zhang Rui Chen et Samuel Dero
   Version : Copyright H2026

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"


/* Affiche le contenu de la pile à l'écran. */
void afficher_pile(const t_pile* pile)
{
	printf("[");

	for(int i = get_nb_elements(pile)-1; i >= 0; i--) {

		printf("%d", pile->items[i]);

		if(i > 0) {

			printf(", ");
		}
	}
	printf("]");
}

void afficher_labyrinthe(const t_labyrinthe* lab)
{
	int largeur_ecran = 80;
	int largeur_labyrinthe = (2 * lab->nb_col + 1) * 2;
	int marge = (largeur_ecran - largeur_labyrinthe) / 2;
	if(marge<0) {
		marge = 0; // éviter une marge négative si le labyrinthe est plus large que l'écran
	}

	//Afficher le labyrinthe
	printf("\n");
	for (int i = 0; i < 2 * lab->nb_lig + 1; i++) {

		// Afficher la marge
		for (int m = 0; m < marge; m++) {
			printf(" ");
		}

		// Afficher les caractères du labyrinthe
		for (int j = 0; j < 2 * lab->nb_col + 1; j++)
		{
			if (lab->matrice[i][j] == MUR) {
				printf("%c%c", 219, 219);// caractère plein pour les murs
			}
			else {
				printf("%c%c", 32, 32);// caractère espace pour les passages
			}
		}
		printf("\n");
	}
}

int valider_entier(const char* str, int min, int max)
{
	int valeur;
	do
	{
		printf("%s", str);
		scanf("%d", &valeur);
	} while (valeur<min||valeur>max);
	return valeur;
}
