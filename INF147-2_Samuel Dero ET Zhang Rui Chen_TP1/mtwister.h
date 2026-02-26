#pragma once
/*==========================================================*/

/*
	le module offrant un mersenne twister, un g�n�rateur de nombres
	pseudo-al�atoires consid�r� comme le meilleur pour la simulation num�rique

	Une courte pr�sentation francaise suit l'introduction en anglais des auteurs japonais
	et donnera le caract�re g�n�ral de chaque  fonction offerte

   Les 2 auteurs n'offraient originallement que des mtwister uniformes
   qui peuvaient parfois paraitre redondantes. Pour un professionnel qui sait
   construire des mtwister diff�rentes de l'uniforme, �a va
   mais j'ai choisi d'ajouter pour les �tudiants quelques fonctions standardis�es
   permettant d'obtenir des �v�nements dans une distribution :

		uniforme g�n�rale , sans ou avec des bornes, enti�re ou r�elle
		normale centr�e r�duite Z(0,1) ou normale � moyenne et �cart-type d�finis
*/

/*==========================================================*/
/* Le module offre donc sept fonctions :

	deux fonctions capables d'initialiser le g�n�rateur
	1 - void mt_srand(unsigned long s);
	2 - unsigned long mt_srandSys(void);

	deux fonctions pour �mettre un nombre r�el dans une uniforme
	double mt_rand(void);
	double mt_randf(double b1, double b2);

	une fonction pour �mettre un nombre entier dans une uniforme
	int mt_randi(int borne);

	deux fonctions pour �mettre un r�el dans une distribution normale
	double mt_randz(void);
	double mt_randnormal(double mu, double sigma);

*/
/*==========================================================*/


/*==========================================================*/

/*
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

	 1. Remtwister of source code must retain the above copyright
		notice, this list of conditions and the following disclaimer.

	 2. Remtwister in binary form must reproduce the above copyright
		notice, this list of conditions and the following disclaimer in the
		documentation and/or other materials provided with the distribution.

	 3. The names of its contributors may not be used to endorse or promote
		products derived from this software without specific prior written
		permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

/*==========================================================*/

#ifndef _MT19937AR_H_
#define _MT19937AR_H_
/*==========================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


/*==========================================================*/

/* UNE INTERFACE MODULAIRE STANDARD POUR MES �TUDIANTS */

/*==========================================================*/

/*  Voici deux fonctions d'initialisation du
	 g�n�rateur. Un g�n�rateur non-initialis� s'initialise
	 en fait � 0 et �met la m�me s�quence ce qui fait douter
	 du caract�re al�atoire.... C'est au client de l'initialiser
	 MAIS JUSTE UNE FOIS dans tout le programme de simulation.
*/

/*==========================================================*/
/* La fonction mt_srand
 la forme d'initialisation la plus classique d'un g�n�rateur
 � partir d'un entier quelconque, la s�quence pseudo al�atoire
 � venir est totalement d�termin�e par la valeur re�ue

PARAMETRE(s): s, un entier quelconque

SORTIE: aucune

SPECS: aucune
*/
void mt_srand(unsigned long s);

/*==========================================================*/


/*==========================================================*/
/* la fonction mt_srandSys
 une forme alternative d'initialisation du g�n�rateur � partir
 de l'horloge interne de la machine,  l'horloge donne un entier
 qui sert de param�tre � la fonction pr�c�dente.
 Cette valeur est retourn�e

PARAMETRE(s): Aucun

SORTIE: l'entier qui a v�ritablement initialis� le g�n�rateur

SPECS: aucune
*/
unsigned long mt_srandSys(void);
/*==========================================================*/

/* LES CINQ FONCTIONS D'�MISSION DANS LES mtwister SP�CIFI�ES */

/*==========================================================*/
/* La fonction mt_rand
L'�mission d'un nombre r�el dans la distribution uniforme 0,1

PARAMETRE(s): Aucun

SORTIE : la valeur �mise par le g�n�rateur

SPECS : aucune
*/
double mt_rand(void);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randf

L'�mission d'un nombre r�el dans une  uniforme [b1, b2]

PARAMETRE(s): deux valeurs r�elles quelconques qui serviront
			   de bornes � l'intervalle

SORTIE : la valeur �mise par le g�n�rateur

SPECS : l'ordre des param�tres n'a aucune importance
*/
double mt_randf(double b1, double b2);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randi

L'�mission d'un nombre entier positif dans une uniforme [1, borne]

PARAMETRE(s): une valeur enti�re quelconque

SORTIE : la valeur enti�re �mise par le g�n�rateur

SPECS :  si le param�tre effectif < 0 , c'est la valeur absolue
			du param�tre  qui sera consid�r�e
		 recevant 0 elle retourne automatiquement 0 et
			c'est le seul 0 possible
*/
int mt_randi(int borne);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randz

L'�mission d'un nombre r�el dans la distribution normale Z,
la plus classique  de moyenne 0 et d'�cart type 1

PARAMETRE(s) : Aucun

SORTIE : la valeur r�elle �mise par le g�n�rateur

SPECS : aucune
*/
double mt_randz(void);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randnormal

L'�mission d'un nombre r�el dans une distribution normale quelconque,
  de moyenne mu  et d'�cart-type sigma donn�s

PARAMETRE(s) : mu d�finit la moyenne voulue et sigma l'�cart-type

SORTIE : la valeur r�elle �mise par le g�n�rateur

SPECS : le signe de sigma n'aura pas d'importance.
*/
double mt_rand_normal(double mu, double sigma);

/*==========================================================*/
/*==========================================================*/

/* L'INTERFACE ORIGINALE DES DEUX CR�ATEURS SERA DANS LE .C 	*/

/*==========================================================*/
#endif	
/*==========================================================*/


