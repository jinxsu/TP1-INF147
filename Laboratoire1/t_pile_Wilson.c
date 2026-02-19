/* T_PILE_WILSON.C
    Extension du module t_pile qui permettra d'implémenter l'algorithme
   de Wilson pour généner un labyrinthe.

   Auteur  :
   Version : Copyright H2026
*/

#include <stdio.h>
#include <stdlib.h>
#include "t_pile_Wilson.h"

/* Retourne la position de "elem" dans la pile ou -1 si absent. */
int obtenir_pos(const t_pile_Wilson pile, t_element elem)
{
	for(int i=0; i < pile->taille; i++) {
		if(pile->items[i] == elem) {
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
	//adding elements of p_src to p_dest in the same order as they are in p_src
	for(int i=0; i < p_src->taille; i++) {
		if(p_src->items[i] != 0) {
			if(!push_pile(p_dest, p_src->items[p_src->taille-i])) {
				return 1;
			}
		}
	}
	return 0;
}

/* La pile est partiellement vidée sans récupération des objets éliminés.
Sa taille maximale restera la même, c'est le nombre d'éléments qui sera modifié.
On reçoit une pile existante et le nombre d’éléments à y conserver.
Retour de 1 si la pile a effectivement été tronquée. Sinon 0 (pas assez d'éléments). */
int tronquer_pile(t_pile_Wilson pile, unsigned int nb_elements)
{
	//removing elements from the top of the pile until only nb_elements are left
	while(get_nb_elements(pile) > nb_elements) {
		pop_pile(pile, NULL);
	}
	if(get_nb_elements(pile) == nb_elements) {
		return 1;
	}
	return 0;
}
