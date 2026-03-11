/* T_LABYRINTHE.C
   Génération et affichage d'un labyrinthe
   Auteur  : Zhang Rui Chen et Samuel Dero
   Version : Copyright H2026
*/
#include <stdio.h>
#include<stdlib.h>
#include "t_labyrinthe.h"
#include "mtwister.h"


#define LONGUEUR_MAX (NB_LIG > NB_COL) ? NB_LIG : NB_COL // longueur maximale d'un passage
//fonction privée
static int obtenir_vosine(int k, int direction, int nb_lig, int nb_col);
static int ajouter_chemin_Wilson(t_pile_Wilson chemins_W, int nb_lig, int nb_col);
static int choix_v_chemin_Wilson(t_pile_Wilson chemins_W, int nb_val);
static int choisir_voisin(int k, int nb_lig, int nb_col);



void remplir_de_murs(t_semi_labyrinthe lab)
{
	//remplir le labyrinthe de murs
	for(int i=0;i<(2*NB_LIG+1);i++) {

		for(int j=0;j<(2*NB_COL+1);j++) {

			lab[i][j] = MUR;
		}
	}
}

void init_semi_labyrinthe(t_semi_labyrinthe lab)
{
	int k;
	int direction;
	int longueur;
	int voisine;
	int lig, col;
	int lig_voisine, col_voisine;


	//Initialiser le tableau du labyrinthe en le remplissant de murs
	remplir_de_murs(lab);

	//Initier le g�n�rateur de nombres pseudo-al�atoires
	mt_srandSys();// initialisation du g�n�rateur de nombres pseudo-al�atoires avec une valeur d�termin�e par l'horloge interne de la machine

	//creer des passages en creusant des cellules
	for (int i = 0;i < NB_LIG * NB_COL; i++)
	{
		//choisir une cellule, une direction et une longueur de passage au hasard
		k = mt_randi(NB_LIG * NB_COL)-1;
		direction = mt_randi(4); 
		longueur = mt_randi(LONGUEUR_MAX-1)+1; 
		
		//determiner les coordonnées de la cellule k dans le labyrinthe
		lig = 2 * (k / NB_COL) + 1; 
		col = 2 * (k % NB_COL) + 1; 
	
		lab[lig][col] = LIBRE; // creuser la cellule k
		int k_copie = k; // copier k pour le parcours du passage

		// creuser le passage en avançant dans la direction choisie pour la longueur choisie
		for (int j = 0; j < longueur; j++) {

			// obtenir la voisine de k dans la direction choisie
			voisine = obtenir_vosine(k_copie, direction, NB_LIG, NB_COL);

			// si la voisine est hors limites, arrêter le passage et passer à la cellule suivante
			if (voisine == -1) break; 

			// déterminer les coordonnées de la voisine dans le labyrinthe
			lig_voisine = 2 * (voisine / NB_COL) + 1; 
			col_voisine = 2 * (voisine % NB_COL) + 1;
			
			lab[lig_voisine][col_voisine] = LIBRE; // creuser la voisine
			lab[(lig + lig_voisine) / 2][(col + col_voisine) / 2] = LIBRE; // creuser le mur entre k_copie et sa voisine

			// mettre à jour les coordonnées de k_copie pour le prochain pas du passage
			lig = lig_voisine;
			col = col_voisine;
			k_copie = voisine;
			
		}

	}
	
}

t_labyrinthe init_labyrinthe(int nb_lig, int nb_col)
{
	t_labyrinthe laby;
	laby.nb_lig = nb_lig;
	laby.nb_col = nb_col;
	laby.nb_positions = nb_lig * nb_col;

	int lignes = 2 * nb_lig + 1;
	int colonnes = 2 * nb_col + 1;

	laby.matrice = (int**)malloc(lignes * sizeof(int*));
	for(int i = 0; i < lignes; i++) {
		laby.matrice[i] = (int*)malloc(colonnes * sizeof(int));
		for(int j = 0; j < colonnes; j++) {
			laby.matrice[i][j] = MUR;
		}
	}
	return laby;
}

void creation_des_piles_Wilson(t_pile* chemins_W, t_pile* longueurs_W, int nb_lig, int nb_col)
{
	int v = mt_randi(nb_lig * nb_col) - 1; //choisir une cellule au hasard pour commencer le labyrinthe
	push_pile(chemins_W, v); //ajouter la cellule choisie à la pile des chemins de Wilson
	push_pile(longueurs_W, 1); //ajouter la longueur du chemin de Wilson (1) à la pile des longueurs de Wilson
	int nb_accumule = 1; //initialiser le nombre de cellules déjà accumulées dans le labyrinthe à 1

	while (nb_accumule<nb_lig*nb_col)
	{
		int taille = ajouter_chemin_Wilson(chemins_W, nb_lig, nb_col);
		push_pile(longueurs_W, taille); //ajouter la longueur du chemin de Wilson ajouté à la pile des longueurs de Wilson
		nb_accumule += taille-1; //mettre à jour le nombre de cellules déjà accumulées dans le labyrinthe
	}
}

void ouvrir_chemins(t_labyrinthe* laby, t_pile* chemins_W, t_pile* longueurs_W)
{
	int taille;
	int k, k_prec;
	int lig, col;
	int new_lig, new_col;
	while (get_nb_elements(chemins_W) != 0) {

		pop_pile(longueurs_W, &taille); //obtenir la longueur du chemin de Wilson à ouvrir
		pop_pile(chemins_W, &k); //obtenir le chemin de Wilson à ouvrir

		lig = 2 * (k / laby->nb_col) + 1; //déterminer les coordonnées de la cellule k dans le labyrinthe
		col = 2 * (k % laby->nb_col) + 1;
		laby->matrice[lig][col] = LIBRE; //creuser la cellule k dans le labyrinthe
		k_prec = k;

		for(int i = 1; i < taille; i++) {

			pop_pile(chemins_W, &k); //obtenir la prochaine cellule du chemin de Wilson à ouvrir
			new_lig = 2 * (k / laby->nb_col) + 1; //déterminer les coordonnées de la cellule k dans le labyrinthe
			new_col = 2 * (k % laby->nb_col) + 1;

			if (k == k_prec - laby->nb_col)
			{
				laby->matrice[lig - 1][col] = LIBRE; //creuser le mur entre k_prec et k
			}

			else if (k == k_prec + laby->nb_col)
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
			lig = new_lig; //mettre à jour les coordonnées de k_prec pour le prochain pas du chemin de Wilson
			col = new_col;
		}
	}
}

void creuser_porte(t_labyrinthe* laby, int no_contour)
{
	int lig, col;
	int lig_porte, col_porte;
	int porte_creusee = 0;

	while(!porte_creusee) {
		switch (no_contour)
		{
		case NORD:
			lig = 1;
			col = 2 * mt_randi(laby->nb_col)-1;
			lig_porte = 0;
			col_porte = col;
			break;
		case SUD:
			lig = 2 * laby->nb_lig - 1;
			col = 2 * mt_randi(laby->nb_col)-1;
			lig_porte = 2 * laby->nb_lig;
			col_porte = col;
			break;
		case OUEST:
			lig = 2 * mt_randi(laby->nb_lig)-1;
			col = 1;
			lig_porte = lig;
			col_porte = 0;
			break;
		case EST:
			lig = 2 * mt_randi(laby->nb_lig)-1;
			col = 2 * laby->nb_col - 1;
			lig_porte = lig;
			col_porte = 2 * laby->nb_col;
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

void detruire_labyrinthe(t_labyrinthe* laby)
{
	int lignes = 2 * laby->nb_lig + 1;
	for(int i = 0; i < lignes; i++) {
		free(laby->matrice[i]);
	}
	free(laby->matrice);
	laby->matrice = NULL;
	laby->nb_lig = 0;
	laby->nb_col = 0;
	laby->nb_positions = 0;
}


int obtenir_vosine(int k ,int direction,int nb_lig, int nb_col)
{
	//calculer la position du voisin de k dans la direction donnée
	int lig = k/nb_col;
	int col = k%nb_col;

	switch (direction) {
		case NORD:
			if (lig==0) return -1; // Hors limites
			return k - nb_col;
		case SUD:
			if (lig>=nb_lig-1) return -1; // Hors limites
			return k + nb_col;
		case OUEST:
			if (col==0) return -1; // Hors limites
			return k - 1;
		case EST:
			if (col>=nb_col-1) return -1; // Hors limites
			return k + 1;
		default:
			return -1; // Direction invalide
	}
	
}

int ajouter_chemin_Wilson(t_pile_Wilson chemins_W, int nb_lig, int nb_col)
{
	if (get_nb_elements(chemins_W) == 0) {
		return 0;
	}

	t_pile p_chemin = init_pile(nb_lig * nb_col);
	t_pile_Wilson p_chemin_W = &p_chemin;
	t_pile_Wilson chemins_W_copie = chemins_W;

	
	int v = choix_v_chemin_Wilson(chemins_W, nb_lig * nb_col);
	push_pile(p_chemin_W, v);

	int chemin_complet = 0;
	int sommet, voisin, position;

	while (!chemin_complet) {
		get_element(p_chemin_W, get_nb_elements(p_chemin_W) - 1, &sommet);
		voisin = choisir_voisin(sommet, nb_lig, nb_col);
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

int choisir_voisin(int k, int nb_lig, int nb_col)
{
	int direction;
	int voisin;
	do
	{
		direction = mt_randi(4);
		voisin = obtenir_vosine(k, direction, nb_lig, nb_col);

	} while (voisin==-1);
	return voisin;

}

