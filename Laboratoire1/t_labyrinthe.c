/* T_LABYRINTHE.C
   Génération et affichage d'un labyrinthe
   Auteur  : Zhang Rui Chen et Samuel Dero
   Version : Copyright H2026
*/
#include <stdio.h>
#include<stdlib.h>
#include "t_labyrinthe.h"
#include "mtwister.h"


// prototypes des fonctions privées
static int obtenir_vosine(int k, int direction, int M, int N);
static int ajouter_chemin_Wilson(t_pile_Wilson chemins_W, int M, int N);
static int choix_v_chemin_Wilson(t_pile_Wilson chemins_W, int nb_val);
static int choisir_voisin(int k, int M, int N);


/**************************************************************************
*							FONCTIONS PUBLIQUES							  *
***************************************************************************/

//initialiser le labyrinthe de la partie 2 en remplissant la matrice de murs
t_labyrinthe init_laby(int M, int N)
{
	
	t_labyrinthe laby;
	laby.M = M;
	laby.N = N;
	laby.nb_positions = M * N;

	int lignes = 2 * M + 1;
	int colonnes = 2 * N + 1;

	laby.matrice = (int**)malloc(lignes * sizeof(int*));
	for(int i = 0; i < lignes; i++) {
		laby.matrice[i] = (int*)malloc(colonnes * sizeof(int));
		for(int j = 0; j < colonnes; j++) {
			laby.matrice[i][j] = MUR;
		}
	}
	return laby;
}

//créer les piles de Wilson pour le labyrinthe de taille nb_lig(M) x nb_col(N)
void etape_des_2piles(t_pile* chemins_W, t_pile* longueurs_W, int M, int N)
{
	int v = mt_randi(M * N - 1); //choisir une cellule au hasard pour commencer le labyrinthe
	push_pile(chemins_W, v); //ajouter la cellule choisie à la pile des chemins de Wilson
	push_pile(longueurs_W, 1); //ajouter la longueur du chemin de Wilson (1) à la pile des longueurs de Wilson
	int nb_accumule = 1; //initialiser le nombre de cellules déjà accumulées dans le labyrinthe à 1

	//tant que le nombre de cellules accumulées dans le labyrinthe est inférieur au nombre
	//total de cellules, continuer à ajouter des chemins de Wilson
	while (nb_accumule<M*N)
	{
		//ajouter un chemin de Wilson à la pile des chemins de Wilson et obtenir sa longueur
		int taille = ajouter_chemin_Wilson(chemins_W, M, N);
		//ajouter la longueur du chemin de Wilson ajouté à la pile des longueurs de Wilson
		push_pile(longueurs_W, taille);
		//mettre à jour le nombre de cellules déjà accumulées dans le labyrinthe
		nb_accumule += taille-1;
	}
}

//ajouter un chemin de Wilson à la pile des chemins de Wilson et retourner sa longueur
void etape_ouverture_chemins(t_labyrinthe* laby, t_pile* chemins_W, t_pile* longueurs_W)
{
	
	int taille;
	int k, k_prec;
	int lig, col;
	int new_lig, new_col;

	while (get_nb_elements(chemins_W) != 0) {

		pop_pile(longueurs_W, &taille); //obtenir la longueur du chemin de Wilson à ouvrir
		pop_pile(chemins_W, &k); //obtenir le chemin de Wilson à ouvrir

		//déterminer les coordonnées de la cellule k dans le labyrinthe
		lig = 2 * (k / laby->N) + 1; 
		col = 2 * (k % laby->N) + 1;
		laby->matrice[lig][col] = LIBRE; //creuser la cellule k dans le labyrinthe
		k_prec = k;

		for(int i = 1; i < taille; i++) {

			pop_pile(chemins_W, &k); //obtenir la prochaine cellule du chemin de Wilson à ouvrir
			//déterminer les coordonnées de la cellule k dans le labyrinthe
			new_lig = 2 * (k / laby->N) + 1; 
			new_col = 2 * (k % laby->N) + 1;

			//creuser le mur entre k_prec et k en fonction de leur position relative dans le labyrinthe
			if (k == k_prec - laby->N)
			{
				laby->matrice[lig - 1][col] = LIBRE; //creuser le mur entre k_prec et k
			}

			else if (k == k_prec + laby->N)
			{
				laby->matrice[lig + 1][col] = LIBRE; //creuser le mur entre k_prec et k
			}

			else if (k == k_prec - 1)
			{
				laby->matrice[lig][col - 1] = LIBRE; //creuser le mur entre k_prec et k
			}

			else if (k == k_prec + 1)
			{
				laby->matrice[lig][col + 1] = LIBRE; //creuser le mur entre k_prec et k
			}

			laby->matrice[new_lig][new_col] = LIBRE; //creuser la cellule k dans le labyrinthe
			k_prec = k; //mettre à jour k_prec pour le prochain pas du chemin de Wilson
			//mettre à jour les coordonnées de k_prec pour le prochain pas du chemin de Wilson
			lig = new_lig; 
			col = new_col;
		}
	}
}

//creuser une porte dans le mur du contour no_contour du labyrinthe
void creuser_une_porte(t_labyrinthe* laby, int no_contour)
{
	int lig, col;
	int lig_porte, col_porte;
	int porte_creusee = 0;

	while(!porte_creusee) {

		switch (no_contour)
		{
		case NORD:
			lig = 1;
			col = 2 * mt_randi(laby->N)-1;
			lig_porte = 0;
			col_porte = col;
			break;
		case SUD:
			lig = 2 * laby->M - 1;
			col = 2 * mt_randi(laby->N)-1;
			lig_porte = 2 * laby->M;
			col_porte = col;
			break;
		case OUEST:
			lig = 2 * mt_randi(laby->M)-1;
			col = 1;
			lig_porte = lig;
			col_porte = 0;
			break;
		case EST:
			lig = 2 * mt_randi(laby->M)-1;
			col = 2 * laby->N - 1;
			lig_porte = lig;
			col_porte = 2 * laby->N;
			break;
		default:
			break;
		}
		if (laby->matrice[lig][col] == LIBRE) {
			laby->matrice[lig_porte][col_porte] = LIBRE; //creuser la porte dans le mur du contour
			porte_creusee = 1;
		}
		
	}
}

//libérer la mémoire allouée pour le labyrinthe et réinitialiser ses champs
void detruire_laby(t_labyrinthe* laby)
{
	if (laby == NULL)
		return;
	int lignes = 2 * laby->M + 1;
	for(int i = 0; i < lignes; i++) {
		free(laby->matrice[i]);
	}

	if (laby->matrice == NULL)
		return;

	free(laby->matrice);
	laby->matrice = NULL;
	laby->M = 0;
	laby->N = 0;
	laby->nb_positions = 0;
}


/**************************************************************************
*							FONCTIONS PRIVÉES							  *
***************************************************************************/

//calculer la position du voisin de k dans la direction donnée
int obtenir_vosine(int k ,int direction,int M, int N)
{
	
	int lig = k / N;
	int col = k % N;

	switch (direction) {
		case NORD:
			if (lig==0) return -1; // Hors limites
			return k - N;
		case SUD:
			if (lig>=M-1) return -1; // Hors limites
			return k + N;
		case OUEST:
			if (col==0) return -1; // Hors limites
			return k - 1;
		case EST:
			if (col>=N-1) return -1; // Hors limites
			return k + 1;
		default:
			return -1; // Direction invalide
	}
	
}

//ajouter un chemin de Wilson à la pile des chemins de Wilson et retourner sa longueur
int ajouter_chemin_Wilson(t_pile_Wilson chemins_W, int M, int N)
{
	//si la pile des chemins de Wilson est vide, retourner 0
	if (get_nb_elements(chemins_W) == 0) {
		return 0;
	}
	
	t_pile p_chemin = init_pile(M * N);
	t_pile_Wilson p_chemin_W = &p_chemin;
	t_pile_Wilson chemins_W_copie = chemins_W;
	int v = choix_v_chemin_Wilson(chemins_W, M * N);
	
	push_pile(p_chemin_W, v);

	int chemin_complet = 0;
	int sommet, voisin, position;

	//tant que le chemin de Wilson n'est pas complet, continuer à choisir des voisins et à les ajouter au chemin
	while (!chemin_complet) {

		get_element(p_chemin_W, get_nb_elements(p_chemin_W) - 1, &sommet);
		voisin = choisir_voisin(sommet, M, N);
		position = obtenir_pos(p_chemin_W, voisin);
		
		if (position != -1) {
			tronquer_pile(p_chemin_W, position + 1);
		}
		else if (obtenir_pos(chemins_W_copie, voisin) != -1) {
			push_pile(p_chemin_W, voisin);
			concatener_piles(chemins_W_copie, p_chemin_W);
			chemin_complet = 1;
		}
		else {
			push_pile(p_chemin_W, voisin);

		}
	}
	
	int taille_chemin = get_nb_elements(p_chemin_W);
	liberer_pile(&p_chemin);
	return taille_chemin;
}
//choisir une cellule au hasard qui n'est pas déjà dans la pile des chemins de Wilson et retourner sa valeur
int choix_v_chemin_Wilson(t_pile_Wilson chemins_W, int nb_val)
{
	int v;
	t_pile_Wilson cw = chemins_W;
	do
	{
		v = mt_randi(nb_val) - 1;

	} while (obtenir_pos(cw, v) != -1);

	return v;
}
//choisir un voisin au hasard de la cellule k qui est dans les limites du labyrinthe et retourner sa valeur
int choisir_voisin(int k, int M, int N)
{
	int direction;
	int voisin;
	do
	{
		direction = mt_randi(4);
		voisin = obtenir_vosine(k, direction, M, N);

	} while (voisin==-1);
	return voisin;

}

