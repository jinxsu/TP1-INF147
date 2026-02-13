#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"

/* Affiche le contenu de la pile à l'écran. */
void afficher_pile(const t_pile* pile)
{
	printf("[");
	for(int i=0; i < pile->taille; i++) {
		if(pile->items[i] != 0) {
			printf("%d", pile->items[i]);
			if(i < pile->taille - 1) {
				printf(", ");
			}
		}
	}
	printf("]");
}
