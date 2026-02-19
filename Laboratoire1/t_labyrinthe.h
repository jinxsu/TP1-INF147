
/* T_LABYRINTHE.H
   Fichier d'en-tête factice pour résoudre l'erreur d'inclusion.
   À compléter selon les besoins du projet.
*/

#ifndef T_LABYRINTHE_H
#define T_LABYRINTHE_H
#define NB_LIG 8
#define NB_COL 4
#define MUR 1
#define LIBRE 0
#define MAX(a,b) (a>b) ? a : b

typedef int t_labyrinthe[2*NB_LIG+1][2*NB_COL+1];
//typedef int t_labyrinthe[2 * NB_COL + 1][2 * NB_LIG + 1];
enum direction { NORD=1, SUD=2, OUEST=3, EST=4 };

void remplir_de_murs(t_labyrinthe lab);
void init_labyrinthe(t_labyrinthe lab);
void afficher_labyrinthe(const t_labyrinthe lab);
void pos_set(int, int, int, t_labyrinthe lab);
#endif // T_LABYRINTHE_H