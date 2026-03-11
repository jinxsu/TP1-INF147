/* T_PILE_WILSON.C
    Extension du module t_pile qui permettra d'implémenter l'algorithme
   de Wilson pour généner un labyrinthe.

   Auteur  : Zhang Rui Chen et Samuel Dero
   Version : Copyright H2026
*/

#include <stdio.h>
#include <stdlib.h>
#include "t_pile_Wilson.h"

/* Retourne la position de "elem" dans la pile ou -1 si absent. */
int obtenir_pos(const t_pile_Wilson pile, t_element elem)
{
	t_element element;
	for(int i=0; i < get_nb_elements(pile); i++) {

		get_element(pile, i, &element);
		if(element == elem) {
			return i;
		}
	}
	return -1;
}

/* Concaténation des éléments d’une pile sur une autre pile.
On reçoit une pile existante et le pointeur d'une autre pile "p_src" dont le
contenu sera empilée sur la première en respectant l'ordre LIFO.
Retour de 1 si la concaténation a été faite entièrement
et de 0 si la seconde pile ne peut être totalement empilée dans la première
par manque de place, -- seul cas possible. */
int concatener_piles(t_pile_Wilson p_dest, const t_pile_Wilson p_src)
{
	t_element elem;
	//adding elements of p_src to p_dest in the same order as they are in p_src
	for (int i = 0; i < get_nb_elements(p_src); i++) {
		get_element(p_src, i, &elem);
		if(push_pile(p_dest, elem) == 0) {
			return 0;
		}
	}
		
	return 1;
}

/* La pile est partiellement vidée sans récupération des objets éliminés.
Sa taille maximale restera la même, c'est le nombre d'éléments qui sera modifié.
On reçoit une pile existante et le nombre d’éléments à y conserver.
Retour de 1 si la pile a effectivement été tronquée. Sinon 0 (pas assez d'éléments). */
int tronquer_pile(t_pile_Wilson pile, unsigned int nb_elements)
{
	int element;
	if(get_nb_elements(pile) <= nb_elements) {
		return 0;
	}
	while(get_nb_elements(pile) > nb_elements) {
		pop_pile(pile, &element);
	}
	return 1;
}
