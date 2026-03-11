/* Main.c :
   programme principal qui permettra de tester les fonctions des autres modules

   Auteur  : Zhang Rui Chen et Samuel Dero
   Version : Copyright H2026

*/

/*=========================================================*/
//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include "affichage.h"
#include "mtwister.h"

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

/*=========================================================*/
/*=========================================================*/
//Programme principal: fonction principale qui retourne un entier (int)
int main(void)
{
	int nb_lig = valider_entier("Entrez le nombre de lignes  [4..10] : ", 4, 10);
	int nb_col = valider_entier("Entrez le nombre de colonnes [4..18] : ", 4, 18);

	mt_srandSys(); // initialisation du générateur de nombres pseudo-aléatoires avec une valeur déterminée par l'horloge interne de la machine

	t_pile chemins_W = init_pile(2*nb_lig * nb_col); //initialiser la pile des chemins de Wilson
	t_pile longueurs_W = init_pile(nb_lig * nb_col); //initialiser la pile des longueurs de Wilson
    
	creation_des_piles_Wilson(&chemins_W, &longueurs_W, nb_lig, nb_col); //créer les piles de Wilson pour le labyrinthe de taille nb_lig x nb_col

	printf("\n Contenu de la pile des chemins de Wilson : ");
	afficher_pile(&chemins_W); //afficher le contenu de la pile chemins_W

	printf("\n Contenu de la pile des longueurs de Wilson : ");
	afficher_pile(&longueurs_W); //afficher le contenu de la pile longueurs_W

	//erreur commence ici
	t_labyrinthe laby = init_labyrinthe(nb_lig, nb_col); //initialiser le labyrinthe de taille nb_lig x nb_col
	ouvrir_chemins(&laby, &chemins_W, &longueurs_W); //ouvrir les chemins de Wilson dans le labyrinthe

	int contour1 = mt_randi(4); //choisir un contour au hasard pour creuser une porte
	creuser_porte(&laby, contour1); //creuser une porte dans le contour choisi

	int contour2;
	do {
		contour2 = mt_randi(4); //choisir un autre contour au hasard pour creuser une porte
	} while (contour1 == contour2);
	creuser_porte(&laby, contour2); //creuser une porte dans le second contour choisi

	printf("\n Labyrinthe généré de taille %d x %d : \n",nb_lig,nb_col);
	afficher_labyrinthe(&laby); //afficher le labyrinthe généré

	liberer_pile(&chemins_W); //libérer la pile des chemins de Wilson
	liberer_pile(&longueurs_W); //libérer la pile des longueurs de Wilson
	detruire_labyrinthe(&laby); //libérer la mémoire allouée pour le labyrinthe


	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."	
	system("pause");
	return EXIT_SUCCESS;     //retour obligatoire si le "main()" est de type "int"
}

/*=========================================================*/

