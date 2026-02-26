/* T_PILE.C
   Module t_pile qui permettra d'implémenter des opérations de bases
   sur une pile d'entiers.

   Auteur  : Zhang Rui Chen et Samuel Dero
   Version : Copyright H2026
*/
#include <stdio.h>
#include <stdlib.h>
#include "t_pile.h"

/* Le constructeur reçoit une capacité maximale d'éléments "taille"
retourne une pile initialisée à vide de cette taille. */
t_pile init_pile(unsigned int taille)
{
	return (t_pile) {(int*)malloc(taille*sizeof(int)), -1, taille };
	
}

/* Fonction-destructeur qui va libérer le tableau dynamique de la pile.
Cette pile ne devra plus être utilisé avant d’avoir été réinitialisée. */
void liberer_pile(t_pile* pile)
{
	free(pile->items);
	pile->items = NULL;
	pile->sommet = -1;
	pile->taille = 0;
	
}

/* Obtenir le nombre d'éléments actuellement dans la pile reçue en paramètre. */
unsigned int get_nb_elements(const t_pile* pile)
{
	return pile->sommet + 1;
}

/* Obtenir la capacité maximale de la pile reçue en paramètre. */
unsigned int get_max_pile(const t_pile* pile)
{
	return pile->taille;
}

/* Obtenir une valeur actuellement dans la pile.
On reçoit trois paramètre : le pointeur d'une pile,
la position voulue (elle doit être valide, de 0 à p->sommet)
et la référence ou copier l'élément à la position reçue.
On retourne 1 si la position reçue est valide, et 0 sinon. */
int get_element(const t_pile* pile, unsigned int position, t_element* elem)
{
	if(position > pile->sommet || position < 0) {
		return 0;
	}
	*elem = pile->items[position];
	return 1;
		
	
}

/* Confirme la présence de la valeur "elem" dans la pile.
On retourne 0 si la valeur "elem" n'y est pas et 1 si elle est présente. */
int present_pile(const t_pile* pile, t_element elem)
{
	for(int i=0; i < pile->sommet; i++) {
		if(pile->items[i] == elem) {
			return 1;
		}
		
	}
	return 0;
}

/* Extraction de la pile (pop):
On reçoit le pointeur d'une pile existante et la référence ou copier l'élément extrait.
Retour de 0 si la pile est vide -- seul cas possible. Sinon 1 (extraction réussie). */
int pop_pile(t_pile* p, t_element* dest)
{
	if(p->sommet == -1) {
		return 0;
	}
	*dest = p->items[p->sommet];
	p->sommet--;
	return 1;
	
}

/* Insertion dans la pile (push):
On reçoit le pointeur d'une pile et la valeur "src" à insérer.
Retour de 0 si la pile est pleine -- seul cas possible. Sinon 1 (insertion réussie). */
int push_pile(t_pile* p, t_element src)
{
	if(p->sommet==p->taille-1) {
		return 0;
	}
	p->sommet++;
	p->items[p->sommet] = src;
	return 1;	
	
}



