#pragma once
/* T_LABYRINTHE.H
   Génération et affichage d'un labyrinthe
   Auteur  : Zhang Rui Chen et Samuel Dero
   Version : Copyright H2026
*/

#ifndef T_LABYRINTHE_H
#define T_LABYRINTHE_H
#include <stdio.h>
#include<stdlib.h>
#include "t_pile_Wilson.h"
#define MUR 1
#define LIBRE 0



//structure pour représenter le labyrinthe dans la partie 2
typedef struct 
{
	int** matrice;
	int nb_lig;
	int nb_col;
	int nb_positions;

}t_labyrinthe;

enum direction { NORD=1, SUD=2, OUEST=3, EST=4 };

//Partie 2
t_labyrinthe init_labyrinthe(int nb_lig, int nb_col);
void creation_des_piles_Wilson(t_pile* chemins_W, t_pile* longueurs_W,int nb_lig, int nb_col);
void ouvrir_chemins(t_labyrinthe* laby, t_pile* chemins_W, t_pile* longueurs_W);
void creuser_porte(t_labyrinthe* laby, int no_contour);
void detruire_labyrinthe(t_labyrinthe* laby);

#endif //T_LABYRINTHE_H