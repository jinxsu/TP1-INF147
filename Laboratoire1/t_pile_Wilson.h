#pragma once
/* T_PILE_WILSON.H
   Extension du module t_pile qui permettra d'implémenter l'algorithme
   de Wilson pour généner un labyrinthe.

   Auteur  : Pierre Bélisle
   Révision: Éric Thé
   Version : Copyright H2026
*/

#ifndef T_PILE_WILSON__
#define T_PILE_WILSON__

#include "t_pile.h"

typedef t_pile* t_pile_Wilson;    //le nouveau type-pointeur à une pile de Wilson

/* Fonctions informatrices de l’état de la pile : */

/* Retourne la position de "elem" dans la pile ou -1 si absent. */
int obtenir_pos(const t_pile_Wilson pile, t_element elem);

/* Concaténation des éléments d’une pile sur une autre pile.
On reçoit une pile existante et le poinetur d'une autre pile "p_src" dont le
contenu sera empilée sur la première en respectant l'ordre LIFO.
Retour de 1 si la concaténation a été faite entièrement
et de 0 si la seconde pile ne peut être totalement empilée dans la première
par manque de place, -- seul cas possible. */
int concatener_piles(t_pile_Wilson p_dest, const t_pile_Wilson p_src);

/* La pile est partiellement vidée sans récupération des objets éliminés.
Sa taille maximale restera la même, c'est le nombre d'éléments qui sera modifié.
On reçoit une pile existante et le nombre d’éléments à y conserver.
Retour de 1 si la pile a effectivement été tronquée. Sinon 0 (pas assez d'éléments). */
int tronquer_pile(t_pile_Wilson pile, unsigned int nb_elements);


#endif // T_PILE__
