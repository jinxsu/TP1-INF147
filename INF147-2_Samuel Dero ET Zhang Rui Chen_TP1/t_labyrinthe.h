#pragma once
/* T_LABYRINTHE.H
   Génération et affichage d'un labyrinthe
   Auteur  : Zhang Rui Chen et Samuel Dero
   Version : Copyright H2026
*/

#ifndef T_LABYRINTHE_H
#define T_LABYRINTHE_H
#define NB_LIG 4
#define NB_COL 4
#define MUR 1
#define LIBRE 0

typedef int t_labyrinthe[2*NB_LIG+1][2*NB_COL+1];
enum direction { NORD=1, SUD=2, OUEST=3, EST=4 };

void remplir_de_murs(t_labyrinthe lab);
void init_labyrinthe(t_labyrinthe lab);
void afficher_labyrinthe(const t_labyrinthe lab);
#endif //T_LABYRINTHE_H