#pragma once
/* T_PILE.H
   Module t_pile qui permettra d'implémenter des opérations de bases
   sur une pile d'entiers.

   Auteur  : Pierre Bélisle
   Révision: Éric Thé
   Version : Copyright H2026
*/
#ifndef T_PILE_H
#define T_PILE_H

typedef int t_element;   //modifier cette déclaration pour avoir une pile d'un autre type

/* le type-enregistrement pour une pile */
typedef struct {
	t_element* items;	//tableau dynamique des éléments de la pile
	int sommet;			//position du sommet (top) de la pile. sera == -1 lorsque vide 
	int taille;			//taille maximale du tableau dynamique
} t_pile;


/* Voici le constructeur: */

/* Le constructeur reçoit une capacité maximale d'éléments "taille"
retourne une pile initialisée à vide de cette taille. */
t_pile init_pile(unsigned int taille);


/* Voici le destructeur: */

/* Fonction-destructeur qui va libérer le tableau dynamique de la pile.
Cette pile ne devra plus être utilisé avant d’avoir été réinitialisée. */
void liberer_pile(t_pile* pile);


/* Voici quatre fonctions informatrices de l’état de la pile : */

/* Obtenir le nombre d'éléments actuellement dans la pile reçue en paramètre. */
unsigned int get_nb_elements(const t_pile* pile);

/* Obtenir la capacité maximale de la pile reçue en paramètre. */
unsigned int get_max_pile(const t_pile* pile);

/* Obtenir une valeur actuellement dans la pile.
On reçoit trois paramètre : le pointeur d'une pile,
la position voulue (elle doit être valide, de 0 à p->sommet)
et la référence ou copier l'élément à la position reçue.
On retourne 1 si la position reçue est valide, et 0 sinon. */
int get_element(const t_pile* pile, unsigned int position, t_element* elem);

/* Confirme la présence de la valeur "elem" dans la pile.
On retourne 0 si la valeur "elem" n'y est pas et 1 si elle est présente. */
int present_pile(const t_pile* pile, t_element elem);


/* Voici les deux fonctions mutatrices de l’état de la pile : */

/* Extraction de la pile (pop):
On reçoit le pointeur d'une pile existante et la référence ou copier l'élément extrait.
Retour de 0 si la pile est vide -- seul cas possible. Sinon 1 (extraction réussie). */
int pop_pile(t_pile* p, t_element* dest);

/* Insertion dans la pile (push):
On reçoit le pointeur d'une pile et la valeur "src" à insérer.
Retour de 0 si la pile est pleine -- seul cas possible. Sinon 1 (insertion réussie). */
int push_pile(t_pile* p, t_element src);

#endif // T_PILE__

