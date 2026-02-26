/* AFFICHAGE.C
   Déclaration de la fonction d'affichage pour une pile d'entiers.

   Auteur  : Zhang Rui Chen et Samuel Dero
   Version : Copyright H2026

*/
#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"

/* Affiche le contenu de la pile à l'écran. */
void afficher_pile(const t_pile* pile)
{
	printf("[");
	for(int i=0; i <= pile->sommet; i++) {

		printf("%d ", pile->items[i]);

		if(i<pile->sommet) {

			printf(", ");
		}
	}
	printf("]");
}
