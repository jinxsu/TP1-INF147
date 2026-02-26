/* TEST_PILES.C
   Fichier pour tester les 3 fonctions du module "t_pile_Wilson" sur une pile d'entiers.

   Auteur  : Eric Thé
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "t_labyrinthe.h"
#include "t_pile_Wilson.h"
#include "affichage.h"
#define TEST_PILE 1
#define TEST_LABYRINTHE 0

int main(void)
{
#if TEST_PILE
	t_pile p1, p2;    //les deux piles pour les tests
	t_element el;     //un entier

	/* Création des deux piles: */
	p1 = init_pile(50);
	p2 = init_pile(7);

	printf("TESTS UNITAIRES DES PILES:");
	printf("\nTaille de p1 = %d", get_max_pile(&p1));
	printf("\nTaille de p2 = %d", get_max_pile(&p2));

	/* Ajouter un élément à p1 : */
	assert(push_pile(&p1, 10));
	assert(get_nb_elements(&p1) == 1);
	printf("\nPush de 10: il y a %d valeurs dans p1 -> ", get_nb_elements(&p1));
	afficher_pile(&p1);

	/* Remplir la pile p2 avec valeurs successives */
	el = 0;
	while (push_pile(&p2, el)) {    //push_pile() jusqu'à que la pile soit pleine
		el++;
	}
	assert(get_nb_elements(&p2) == get_max_pile(&p2));   //elle est pleine?

	printf("\nRemplir p2: il y a %d valeurs dans p2 -> ", get_nb_elements(&p2));
	afficher_pile(&p2);

	/* Tests de obtenir_pos(): au debut, milieu, sommet et valeur absente (9) */
	printf("\nLe '0' se trouve a la position %d dans p2", obtenir_pos(&p2, 0));
	printf("\nLe '3' se trouve a la position %d dans p2", obtenir_pos(&p2, 3));
	printf("\nLe '6' se trouve a la position %d dans p2", obtenir_pos(&p2, 6));
	printf("\nLe '9' se trouve a la position %d dans p2", obtenir_pos(&p2, 9));

	/* On tente d'ajouter un autre élément à p2 qui est PLEINE */
	assert(push_pile(&p2, 1234) == 0);

	/* On tente de concatener p2 à la pile p1 */
	printf("\n\nConcatenation de p2 a p1 = %d", concatener_piles(&p1, &p2));
	assert(get_nb_elements(&p1) == get_nb_elements(&p2) + 1);

	printf("\nConcatenation: il y a %d valeurs dans p1 -> ", get_nb_elements(&p1));
	afficher_pile(&p1);

	assert(push_pile(&p1, -66));
	printf("\nPush de -66: il y a %d valeurs dans p1 -> ", get_nb_elements(&p1));
	afficher_pile(&p1);

	/* On tente de tronquer p1 de -2 éléments */
	assert(tronquer_pile(&p1, get_nb_elements(&p1) - 2));
	printf("\nTronquer p1: il y a %d valeurs dans p1 -> ", get_nb_elements(&p1));
	afficher_pile(&p1);

	/* On vide la pile p1 un élément à la fois */
	while (get_nb_elements(&p1)) {
		printf("\nResultat du pop p1 = %d", pop_pile(&p1, &el));
		printf("  et valeur = %d", el);
	}
	assert(pop_pile(&p1, &el) == 0);
	assert(get_nb_elements(&p1) == 0);   //est-elle VIDE?

	/* Destruction des deux piles: */
	liberer_pile(&p1);
	liberer_pile(&p2);
#endif
#if TEST_LABYRINTHE
	t_labyrinthe lab;
	//intialiser le g�n�rateur de nombres pseudo-al�atoires
	mt_srand(12345);
	printf("\nTESTS UNITAIRES DU LABYRINTHE:\n");
	printf("\nTest de la fonction de remplissage \n");
	remplir_de_murs(lab);
	afficher_labyrinthe(lab);
	printf("\nTest de la generation du semi-labyrinthe: \n");
	init_labyrinthe(lab);
	afficher_labyrinthe(lab);
#endif

	//On termine avec le standard... HIT ANY KEY
	printf("\n");	system("pause");

	return EXIT_SUCCESS;	//et ÇA c'est un 0 avec une cravate...
}
/*-----------------------------------------------------------------*/
