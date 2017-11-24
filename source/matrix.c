/**
 * @file matrix.c
 * @brief Fichier source contenant les fonctions de base sur les matrices
 * @authors Marek Felsoci, Paul Viville
 **/ 
#include "../include/matrix.h"

/**
 * @brief Génère un scalaire aléatoire entre 'a' et 'b'
 * @param E a : un scalaire
 * @param E b : un scalaire
 * @returns E : scalaire aléatoire
 **/
E random_float(E a, E b)
{
    E random = ((E) rand()) / (E) RAND_MAX;
    E diff = b - a;
    E r = random * diff;

    return a + r;
}

/**
 * @brief Alloue une nouvelle matrice
 * @param int nbrows : nombre de lignes
 * @param int nbcolumns : nombre de colonnes
 * @returns Matrix : nouvelle matrice
 **/
Matrix newMatrix(int nbrows, int nbcolumns)
{
	Matrix new = (Matrix) malloc(sizeof(struct matrix));

	new->nrows = nbrows;
	new->ncols = nbcolumns;

	new->mat = (E*) malloc(nbrows*nbcolumns*sizeof(E));

	int i, j;
	for(i = 0; i < nbrows; i++)
		for(j = 0; j < nbcolumns; j++)
			new->mat[nbcolumns * i + j] = 0;

	return new;
}

/**
 * @brief Renvoie d'un élément
 * @param Matrix m : une matrice
 * @param int row : un indice de ligne
 * @param int column : un indice de colonne
 * @returns E : l'élément à la ligne 'row' et dans la colonne 'column'
 **/
E getElt(Matrix m, int row, int column)
{
	return m->mat[(row * m->ncols)+ column];
}

/**
 * @brief Sauvegarde d'un élément
 * @param Matrix m : une matrice
 * @param int row : un indice de ligne
 * @param int column : un indice de colonne
 * @param E val : un scalaire
 * @returns void : 'm' est modifiée par effet de bord
 **/
void setElt(Matrix m, int row, int column, E val)
{
	m->mat[(row * m->ncols)+ column] = val;
	return;
}

/**
 * @brief Désalloue une matrice
 * @param Matrix m : une matrice
 * @returns void
 **/
void deleteMatrix(Matrix m)
{
	free(m->mat);
	free(m);

	return;
}

/**
 * @brief Affiche une matrice
 * @param Matrix m : une matrice
 * @returns void
 **/
void displayMatrix(Matrix m)
{
	int i, j;

	for(i=0;i<m->nrows;i++)
	{
    printf("\t[ ");
		for(j=0;j<m->ncols;j++)
		{
			printf(" %1.2f ", getElt(m, i, j));
		}
		printf(" ]\n");
	}
	printf("\n");
	return;
}

/**
 * @brief Génère une matrice identité
 * @param int nbrows : nombre de lignes souhaité
 * @returns Matrix : matrice identité
 **/
Matrix identite(int nbrows)
{
	Matrix n = newMatrix(nbrows, nbrows);

	int i, j;

	for(i=0;i<n->nrows;i++)
	{
		for(j=0;j<n->ncols;j++)
		{
			if ( i == j )
				setElt(n, i, j, 1.0);
			else
				setElt(n, i, j, 0.0);
		}
	}

	return n;
}

/**
 * @brief Génère une matrice aux éléments aléatoires entre deux valeurs
 * @param int nbrows : nombre de lignes souhaité
 * @param int nbcolumns : nombre de colonnes souhaité
 * @param E minal : un scalaire (borne minimum)
 * @param E maxval : un scalaire (borne maximum)
 * @returns Matrix : matrice aux éléments aléatoires
 **/
Matrix aleatoire(int nbrows, int nbcolumns, E minval, E maxval)
{
	Matrix new = newMatrix(nbrows, nbcolumns);

	int i, j;

	for(i=0;i<new->nrows;i++)
	{
		for(j=0;j<new->ncols;j++)
		{
			setElt(new, i, j, random_float(minval, maxval));
		}
	}

	return new;
}
