/**
 * @file resol.c
 * @brief Fichier source contenant les fonctions sur les matrices
 * @authors Marek Felsoci, Paul Viville
 **/ 
#include "../include/resol.h"

/**
 * @brief Copie d'une matrice
 * @param Matrix m : une matrice
 * @returns Matrix : la copie de la matrice 'm'
 **/
Matrix copyMatrix(const Matrix m)
{
	Matrix copy = newMatrix(m->nrows, m->ncols);

	int i, j;

	for(i=0;i<m->nrows;i++)
	{
		for(j=0;j<m->ncols;j++)
		{
			setElt(copy, i, j, getElt(m, i, j));
		}
	}

	return copy;
}

/**
 * @brief Multiplication d'une matrice par un scalaire
 * @param E v : un scalaire
 * @param Matrix m : une matrice
 * @returns Matrix : le résultat de la multiplication de 'm' par 'v'
 **/
Matrix mult_scal(E v, const Matrix m)
{
	Matrix result = newMatrix(m->nrows, m->ncols);

	int i, j;

	for(i=0;i<m->nrows;i++)
	{
		for(j=0;j<m->ncols;j++)
		{
			setElt(result, i, j, v*getElt(m, i, j));
		}
	}

	return result;
}

/**
 * @brief Calcul de la norme d'un vecteur
 * @param Matrix V : une matrice soit sous forme 1*n soit n*1
 * @returns E : la norme de 'V'
 **/
E norme(const Matrix V)
{
	if ( (V->ncols > 1) && (V->nrows == 1) )
	{
		int i;

		E result;

		for(i=0;i<V->ncols;i++)
		{
			result += pow(getElt(V, 0, i), 2);
		}

		return (sqrt(result));
	}
	else if ( (V->ncols == 1) && (V->nrows > 1) )
	{
		int i;

		E result;

		for(i=0;i<V->nrows;i++)
		{
			result += pow(getElt(V, i, 0), 2);
		}

		return (sqrt(result));
	}
}

/**
 * @brief Addition de deux matrices
 * @param Matrix m1 : une matrice
 * @param Matrix m2 : une matrice
 * @returns Matrix : le résultat de l'addition de 'm1' plus 'm2'
 **/
Matrix addition(Matrix m1, Matrix m2)
{
	if((m1->nrows != m2->nrows) || (m1->ncols != m2->ncols))
	{
		printf("somme impossible\n");
		return NULL;
	}
	Matrix mSum = newMatrix(m1->nrows, m1->ncols);
	int i, j;
	for(i = 0; i < mSum->nrows; i++)
		for(j = 0; j < mSum->ncols; j++)
		{
			E temp = getElt(m1, i, j) + getElt(m2, i , j);
			setElt(mSum, i, j, temp);
		}
	return mSum;
}

/**
 * @brief Soustraction de deux matrices
 * @param Matrix m1 : une matrice
 * @param Matrix m2 : une matrice
 * @returns Matrix : le résultat de la soustraction de 'm1' moins 'm2'
 **/
Matrix soustraction(Matrix m1, Matrix m2)
{
	if((m1->nrows != m2->nrows) || (m1->ncols != m2->ncols))
	{
		printf("soustraction impossible\n");
		return NULL;
	}
	Matrix mSub = newMatrix(m1->nrows, m1->ncols);
	int i, j;
	for(i = 0; i < mSub->nrows; i++)
		for(j = 0; j < mSub->ncols; j++)
		{
			E temp = getElt(m1, i, j) - getElt(m2, i , j);
			setElt(mSub, i, j, temp);
		}
	return mSub;
}

/**
 * @brief Multiplication de deux matrices
 * @param Matrix m1 : une matrice
 * @param Matrix m2 : une matrice
 * @returns Matrix : le résultat de la multiplication de 'm1' fois 'm2'
 **/
Matrix multiplication(Matrix m1, Matrix m2)
{
	if(m1->ncols != m2->nrows)
	{
		printf("produit impossible\n");
		return NULL;
	}
	Matrix mProd = newMatrix(m1->nrows, m2->ncols);
	int i, j, k;
	for(i = 0; i < m1->nrows; i++)
		for(j = 0; j < m2->ncols; j++)
		{
			E temp = 0;
			for(k = 0; k < m1->ncols; k++)
			{
				temp += getElt(m1, i, k) * getElt(m2, k, j);
			}
			setElt(mProd, i, j, temp);
		}
	return mProd;
}

/**
 * @brief Echange de deux lignes dans une matrice
 * @param Matrix m : une matrice
 * @param int l1 : un indice de ligne
 * @param int l2 : un indice de ligne
 * @returns void : 'm' est modifiée par effet de bord
 **/
void swapLine(Matrix m, int l1, int l2)
{
	int i;

	for(i=0;i<m->ncols;i++)
	{
		E temp = getElt(m, l1, i);

		setElt(m, l1, i, getElt(m, l2, i));
		setElt(m, l2, i, temp);
	}

	return;
}

/**
 * @brief Combinaison linéaire de deux lignes d'une matrice
 * @param Matrix m : une matrice
 * @param E c1 : un scalaire
 * @param int l1 : un indice de ligne
 * @param E c2 : un scalaire
 * @param int l2 : un indice de ligne 
 * @returns void : 'm' est modifié par effet de bord ( l2 ← c1*l1 + c2*l2 )
 **/
void combineLines(Matrix m, E c1, int l1, E c2, int l2)
{
	int i;

	for(i=0;i<m->ncols;i++)
	{
		setElt(m, l2, i, (c1*getElt(m, l1, i) + c2*getElt(m, l2, i)));
	}

	return;
}

/**
 * @brief Choix du premier pivot non-nul
 * @param Matrix A : une matrice
 * @param int l : un indice de ligne
 * @returns int : l'indice de ligne où se trouve le pivot
 **/
int choixPivot(Matrix A, int l)
{
	int j;

	for(j = l; j < A->nrows; j++)
	{
		if( getElt(A, j, l) != 0 )
			return j;
	}

	return -1;
}

/**
 * @brief Déterminant d'une matrice
 * @param Matrix X : une matrice
 * @returns E : le le déterminant de 'X'
 **/
E determinant(Matrix X)
{
	E det = 1;

	Matrix A = copyMatrix(X);

	int n = A->nrows;
	
	if( n == 1 )
		return getElt(X, 0, 0);
	
	int i, j, c = 0, p;
	for(j = 0; j < (n-1); j++)
	{
		if( getElt(A, j, j) == 0 )
		{
			for( i = j + 1; i < n; i++ )
			{
				if( getElt(A, i, j) != 0 )
					c = 1;
			}

			if( c == 0 )
			{
				deleteMatrix(A);
				return 0;
			}

			p = choixPivot(A, j);

			for(i = 0; i < n; i++)
				setElt(A, p, i, getElt(A, p, i) * (-1.0));

			swapLine(A, j, p);
		}
		else
		{
			for( i = j + 1; i < n; i++ )
			{
				combineLines(A, (-(getElt(A, i, j) / getElt(A, j, j))), j, 1, i);
			}
		}
		det *= getElt(A, j, j);
	}
	det *= getElt(A, (n-1), (n-1));

	deleteMatrix(A);

	return det;
}

/**
 * @brief Transposée d'une matrice
 * @param Matrix m : une matrice
 * @returns Matrix : transposé de m
 **/
Matrix transpose(Matrix m)
{
	Matrix new = newMatrix(m->ncols, m->nrows);
	int i, j;

	for(i = 0; i < m->nrows; i++)
		for(j = 0; j < m->ncols; j++)
			setElt(new, j, i, getElt(m, i, j));

	return new;
}

/**
 * @brief Exposant d'une matrice
 * @param Matrix A : une matrice
 * @param int exp : la puissance
 * @returns Matrix : A^exp
 **/
Matrix exposant(Matrix m, int exp)
{
	if(m->nrows != m->ncols)
	{
		printf("produit impossible\n");
		return NULL;
	}

	if(exp == 0)
		return identite(m->nrows);

	Matrix trans = mult_scal(1, m);
	Matrix mTemp = newMatrix(m->nrows, m->ncols);
	int i, j, k, l;

	for(l = 1; l < exp; l++)
	{
		for(i = 0; i < trans->nrows; i++)
			for(j = 0; j < trans->nrows; j++)
			{
				E temp = 0;
				for(k = 0; k < trans->nrows; k++)
					temp += getElt(trans, i, k) * getElt(m, k, j);

				setElt(mTemp, i, j, temp);
			}
		deleteMatrix(trans);
		trans = mult_scal(1, mTemp);
	}

	deleteMatrix(mTemp);

	return trans;
}

/**
 * @brief Remontée d'un systèmes linéaire
 * @param Matrix A : une matrice
 * @param Matrix B : une matrice
 * @param Matrix X : une matrice
 * @returns void : 'A', 'B' et 'X' sont modifiées par effet de bord
 **/
void remontee(Matrix A, Matrix B, Matrix X)
{
	int i, j;
	for(i = B->nrows -1; i > -1; i--)
	{
		setElt(X, i, 0, getElt(B, i, 0));
		for(j = i + 1; j < B->nrows; j++)
			setElt(X, i, 0, getElt(X, i, 0) - getElt(A, i, j) * getElt(X, j, 0));
		setElt(X, i, 0, getElt(X, i, 0) / getElt(A, i, i));
	}
	return;
}

/**
 * @brief Ajout du multiple d'une ligne à une autre ligne
 * @param Matrix A : une matrice
 * @param Matrix B : une matrice
 * @param int i : un indice de ligne
 * @param int j : un indice de ligne
 * @param E c : un scalaire
 * @returns void : 'A' et 'B' sont modifiées par effet de bord
 **/
void addMultiple(Matrix A, Matrix B, int i, int j, E c)
{
	int k;
	for(k = 0; k < B->nrows; k++)
		setElt(A, i, k, getElt(A, i, k) + c * getElt(A, j, k));
	setElt(B, i, 0, getElt(B, i, 0) + c * getElt(B, j, 0));
	return;
}

/**
 * @brief Echange de deux lignes dans un système linéaire
 * @param Matrix A : une matrice
 * @param Matrix B : une matrice
 * @param int i : un indice de ligne
 * @param int j : un indice de ligne
 * @returns void : 'A' et 'B' sont modifiées par effet de bord
 **/
void echangeLigne(Matrix A, Matrix B, int i, int j)
{
	int k;
	E temp;
	if(i == j) return;
	for(k = 0; k < A->ncols; k++)
	{
		temp = getElt(A, i, k);
		setElt(A, i, k, getElt(A, j, k));
		setElt(A, j, k, temp);
	}
	temp = getElt(B, i, 0);
	setElt(B, i, 0, getElt(B, j, 0));
	setElt(B, j, 0, temp);
	return;
}

/**
 * @brief Triangularisation d'un système linéaire
 * @param Matrix A : une matrice
 * @param Matrix B : une matrice
 * @returns void : 'A' et 'B' sont modifiées par effet de bord
 **/
void triangulaire(Matrix A, Matrix B)
{
	int i, j;
	for(i = 0; i < A->nrows -1; i++)
	{
		j = choixPivot(A, i);
		echangeLigne(A, B, i, j);
		for(j = i + 1; j < A->nrows; j++)
			addMultiple(A, B, j, i, -getElt(A, j, i)/getElt(A, i, i));
	}
	return;
}

/**
 * @brief Solution d'un système linéaire à l'aide de l'algorithme de Gauss
 * @param Matrix A : une matrice
 * @param Matrix B : une matrice
 * @param Matrix X : une matrice
 * @returns void : 'A', 'B' et 'X' sont modifiées par effet de bord où 'X' contiendra les résultats
 **/
void gauss(Matrix A, Matrix B, Matrix X)
{
	triangulaire(A, B);
	remontee(A, B, X);
	return;
}

/**
 * @brief Détermine si une ligne de matrice est nulle ou non
 * @param Matrix A : une matrice
 * @param int line : un indice de ligne
 * @returns 1 : si la ligne est nulle
 * @returns 0 : si la ligne contient au moins un élément non-nul
 **/
int zero_row(Matrix A, int line)
{
	int i, j, k;

	for(j = 0; j < A->ncols; j++)
	{
			if(getElt(A, line, j) != 0.0)
				return 0;
	}

	return 1;
}

/**
 * @brief Rang d'une matrice
 * @param Matrix A : une matrice
 * @returns int : le rang de 'A'
 **/
int rank(Matrix A)
{
	Matrix r = copyMatrix(A);

	int i = 0, j = 0, k = 0;

	while( ( i < (r->nrows - 1) ) && ( (j = choixPivot(r, i)) != -1 ) )
	{
		swapLine(r, i, j);

		for(k=(i+1);k<r->nrows;k++)
		{
			if(k != i)
				combineLines(r, (-(getElt(r, k, i) / getElt(r, i, i))), i, 1, k);
		}

		i++;
	}

	k = 0;

	for(i = 0; i < r->nrows; i++)
	{
		if( zero_row(r, i) == 0 )
			k++;
	}

	deleteMatrix(r);

	return k;
}

/**
 * @brief Valeur absolue d'un scalaire
 * @param E val : un scalaire
 * @returns E : la valeur absolue de 'val'
 **/
E eabs(E val)
{
	if( val < 0.0 )
		return (-val);

	return val;
}

/**
 * @brief Inverse d'une matrice
 * @param Matrix A : une matrice
 * @returns Matrix : retourne l'inverse de 'A' si 'A' est inversible, sinon retourne la matrice identité
 **/
Matrix inverse(Matrix A)
{
	if( A->nrows != A->ncols )
	{
		printf("La matrice n'est pas inversible\n");
		return identite(A->nrows);
	}
	
	if( determinant(A) == 0.0 )
		return identite(A->nrows);

	Matrix r = copyMatrix(A);
	Matrix id = identite(A->nrows);

	int i = 0, j = 0, k = 0, p = 0, m = 0;
	int n = r->nrows;

	for(j = 0; j < n; j++)
	{
		int imax = choixPivot(r, j);

		E max = getElt(r, imax, j);
		if(getElt(r, imax, j) != 0.0)
		{
			for(m=0;m<n;m++)
			{
				setElt(r, imax, m, getElt(r, imax, m) / max);
				setElt(id, imax, m, getElt(id, imax, m) / max);
			}

			if( imax != k )
			{
				swapLine(r, imax, p);
				swapLine(id, imax, p);
			}

			for(i=0;i<n;i++)
			{
				if(i != p)
				{
					combineLines(id, -(getElt(r, i, j)), p, 1, i);
					combineLines(r, -(getElt(r, i, j)), p, 1, i);
				}
			}
			p++;
		}
	}

	deleteMatrix(r);

	return id;
}

/**
 * @brief Calcul des coefficients de la droite de régression linéaire et du vecteur des résidus
 * @param Matrix S : une matrice
 * @returns struct LEstimateCouple : le couple des vecteurs de solution (coefficients et résidus)
 **/
struct LEstimateCouple least_estimate(Matrix S)
{
	if( S->ncols != 2 )
	{
		printf("Les dimensions de la matrice sont incorrectes\n");
		return;
	}

	int i, j, n = S->nrows;

	E moyX = 0.0, moyY = 0.0;

	for(i = 0; i < n; i++)
	{
		moyX += getElt(S, i, 0);
		moyY += getElt(S, i, 1);
	}

	moyX = moyX / n;
	moyY = moyY / n;

	E somme1 = 0.0, somme2 = 0.0;

	for(i = 0; i < n; i++)
	{
		somme1 += ( (getElt(S, i, 0) - moyX) * (getElt(S, i, 1) - moyY) );
		somme2 += (getElt(S, i, 0) - moyX) * (getElt(S, i, 0) - moyX);
	}

	E alpha = somme1 / somme2;

	E beta = moyY - (alpha * moyX);

	Matrix coef = newMatrix(2, 1);

	setElt(coef, 0, 0, alpha);
	setElt(coef, 1, 0, beta);

	Matrix residus = newMatrix(n, 1);

	for(i=0;i<n;i++)
	{
		setElt(residus, i, 0, ( ( ( getElt(S, i, 0) * alpha ) + beta ) - getElt(S, i, 1) ) );
	}
	
	//Gnuplot
	FILE * lestimate_r, *abeta;
	
	lestimate_r = fopen(LESTFILE, "w+");
	
	for(i = 0; i < n; i++)
	{
		fprintf(lestimate_r, "%f %f\n", getElt(S, i, 0), getElt(S, i, 1));
	}
	
	fclose(lestimate_r);
	
	abeta = fopen(ALPHABETA, "w+");
	
	fprintf(abeta, "%f %f\n", alpha, beta);
	
	fclose(abeta);
	
	if( fork() == 0 )
	{
		execl("/usr/bin/gnuplot", "gnuplot", "lestimate.dat", (char *) NULL);
	}
	
	wait(NULL);
	
	struct LEstimateCouple r;
	
	r.coeff = coef;
	r.residus = residus;
	
	return r;
}

/**
 * @brief Calcul la valeur propre maximale et du vecteur propre d'une matrice
 * @param Matrix A : une matrice
 * @returns struct EigenCouple : le couple des solutions (valeur propre maximale et vectuer propre)
 **/
 struct EigenCouple eigenval(Matrix A)
{
	Matrix vect_u = aleatoire(A->nrows, 1, 0.0, 1.0);
	
	E eval = 0.0, epsilon = 1.0;
	while( eabs(epsilon) > 0.0001 )
	{
		Matrix temp = multiplication(A, vect_u);
		
		int i = 0;
		for(i = 0; i < vect_u->nrows; i++)
		{
			setElt(vect_u, i, 0, getElt(temp, i, 0));
		}
		
		deleteMatrix(temp);
		
		int j = 0;
		E max = eabs(getElt(vect_u, 0, 0));
		for(j=1;j<vect_u->nrows;j++)
		{
			if( getElt(vect_u, j, 0) > max )
				max = getElt(vect_u, j, 0);
		}
		epsilon = max - eval;
		
		eval = max;
		Matrix temp2 = mult_scal((1/eval), vect_u);
		for(i = 0; i < vect_u->nrows; i++)
		{
			setElt(vect_u, i, 0, getElt(temp2, i, 0));
		}
		
		deleteMatrix(temp2);
	}

	struct EigenCouple r;

	r.evect = vect_u;
	r.eval = eval;

	return r;
}
/**
 * @brief Transforme le nom d'une commande en une seule lettre
 * @param char * cmd : un nom de commande
 * @returns char : lettre correspondate à la commande si une telle commande existe
 * @returns 'O' : si la commande n'existe pas
 **/
char getcmd(char * cmd)
{
	if( ( cmd == NULL ) || ( strcmp(cmd, "") == 0 ) )
		return 'O';

	if( strcmp(cmd, "mult") == 0 )
		return 'M';

	if( strcmp(cmd, "addition") == 0 )
		return 'A';

	if( strcmp(cmd, "sub") == 0 )
		return 'S';
		
	if( strcmp(cmd, "transpose") == 0 )
		return 'T';
		
	if( strcmp(cmd, "exposant") == 0 )
		return 'X';
		
	if( strcmp(cmd, "determinant") == 0 )
		return 'D';
		
	if( strcmp(cmd, "eigen") == 0 )
		return 'E';
	
	if( strcmp(cmd, "invert") == 0 )
		return 'I';
		
	if( strcmp(cmd, "least_estimate") == 0 )
		return 'L';
		
	if( strcmp(cmd, "mult_scal") == 0 )
		return 'C';
		
	if( strcmp(cmd, "norme") == 0 )
		return 'N';
		
	if( strcmp(cmd, "rank") == 0 )
		return 'R';

	return 'O';
}

/**
 * @brief Calcul du temps d'exécution d'une commande
 * @param clock_t start : un temps
 * @param clock_t end : un temps
 * @returns float : le temps en secondes
 **/
float exec_time(clock_t start, clock_t end)
{
	clock_t diff = end - start;
	
	float result = (float) diff / CLOCKS_PER_SEC;
	
	return result;
}

/**
 * @brief Test de vitesse d'exécution d'une commande
 * @param char * cmd : une commande
 * @param int taille_min : taille minimale de matrice
 * @param int taille_max : taille maximale de matrice
 * @param int pas : pas de changement de taille
 * @param int sec : temps limite d'exécution (le test s'arrête si ce temps est dépassé)
 * @returns 0 : en cas de test réussi
 * @returns -1 : en cas d'erreur
 **/
int speedtest(char * cmd, int taille_min, int taille_max, int pas, int sec)
{
	FILE * s_results;
	
	char code = getcmd(cmd);
	
	switch( code )
	{
		case 'M' : {
			int i;
			clock_t start, end;
			
			s_results = fopen(SPTFILE, "w+");
			
			for( i = taille_min; i < taille_max; i += pas )
			{
				Matrix m1 = aleatoire(i, i, -10.0, 10.0);
				Matrix m2 = aleatoire(i, i, -10.0, 10.0);
				
				start = clock();
				
				Matrix r = multiplication(m1, m2);
				
				end = clock();
				
				float e_time = exec_time(start, end);
							
				fprintf(s_results, "%d %f\n", i, e_time);
				
				deleteMatrix(m1);
				deleteMatrix(m2);
				deleteMatrix(r);
				
				if( (int) e_time > sec )
				{
					fclose(s_results);
					
					if( fork() == 0 )
					{
						execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
					}
					
					wait(NULL);
					
					return 0;
				}	
			}
			
			fclose(s_results);
			
			if( fork() == 0 )
			{
				execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
			}
			
			wait(NULL);
			
			return 0;
		}
		
		case 'A' : {
			int i;
			clock_t start, end;
			
			s_results = fopen(SPTFILE, "w+");
			
			for( i = taille_min; i < taille_max; i += pas )
			{
				Matrix m1 = aleatoire(i, i, -10.0, 10.0);
				Matrix m2 = aleatoire(i, i, -10.0, 10.0);
				
				start = clock();
				
				Matrix r = addition(m1, m2);
				
				end = clock();
				
				float e_time = exec_time(start, end);
							
				fprintf(s_results, "%d %f\n", i, e_time);
				
				deleteMatrix(m1);
				deleteMatrix(m2);
				deleteMatrix(r);
				
				if( (int) e_time > sec )
				{
					fclose(s_results);
					
					if( fork() == 0 )
					{
						execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
					}
					
					wait(NULL);
					
					return 0;
				}	
			}
			
			fclose(s_results);
			
			if( fork() == 0 )
			{
				execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
			}
			
			wait(NULL);
			
			return 0;
		}
		
		case 'S' : {
			int i;
			clock_t start, end;
			
			s_results = fopen(SPTFILE, "w+");
			
			for( i = taille_min; i < taille_max; i += pas )
			{
				Matrix m1 = aleatoire(i, i, -10.0, 10.0);
				Matrix m2 = aleatoire(i, i, -10.0, 10.0);
				
				start = clock();
				
				Matrix r = soustraction(m1, m2);
				
				end = clock();
				
				float e_time = exec_time(start, end);
							
				fprintf(s_results, "%d %f\n", i, e_time);
				
				deleteMatrix(m1);
				deleteMatrix(m2);
				deleteMatrix(r);
				
				if( (int) e_time > sec )
				{
					fclose(s_results);
					
					if( fork() == 0 )
					{
						execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
					}
					
					wait(NULL);
					
					return 0;
				}	
			}
			
			fclose(s_results);
			
			if( fork() == 0 )
			{
				execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
			}
			
			wait(NULL);
			
			return 0;
		}
		
		case 'T' : {
			int i;
			clock_t start, end;
			
			s_results = fopen(SPTFILE, "w+");
			
			for( i = taille_min; i < taille_max; i += pas )
			{
				Matrix m = aleatoire(i, i, -10.0, 10.0);
				
				start = clock();
				
				Matrix r = transpose(m);
				
				end = clock();
				
				float e_time = exec_time(start, end);
							
				fprintf(s_results, "%d %f\n", i, e_time);
				
				deleteMatrix(m);
				deleteMatrix(r);
				
				if( (int) e_time > sec )
				{
					fclose(s_results);
					
					if( fork() == 0 )
					{
						execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
					}
					
					wait(NULL);
					
					return 0;
				}	
			}
			
			fclose(s_results);
			
			if( fork() == 0 )
			{
				execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
			}
			
			wait(NULL);
			
			return 0;
		}
		
		case 'X' : {
			int i;
			clock_t start, end;
			
			s_results = fopen(SPTFILE, "w+");
			
			for( i = taille_min; i < taille_max; i += pas )
			{
				Matrix m = aleatoire(i, i, -10.0, 10.0);
				
				start = clock();
				
				Matrix r = exposant(m, 3);
				
				end = clock();
				
				float e_time = exec_time(start, end);
							
				fprintf(s_results, "%d %f\n", i, e_time);
				
				deleteMatrix(m);
				deleteMatrix(r);
				
				if( (int) e_time > sec )
				{
					fclose(s_results);
					
					if( fork() == 0 )
					{
						execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
					}
					
					wait(NULL);
					
					return 0;
				}	
			}
			
			fclose(s_results);
			
			if( fork() == 0 )
			{
				execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
			}
			
			wait(NULL);
			
			return 0;
		}
		
		case 'D' : { //Déterminant
			int i;
			clock_t start, end;
			
			s_results = fopen(SPTFILE, "w+");
			
			for( i = taille_min; i < taille_max; i += pas )
			{
				Matrix m = aleatoire(i, i, -10.0, 10.0);
				
				start = clock();
				
				int det = determinant(m);
				
				end = clock();
				
				float e_time = exec_time(start, end);
							
				fprintf(s_results, "%d %f\n", i, e_time);
				
				deleteMatrix(m);
				
				if( (int) e_time > sec )
				{
					fclose(s_results);
					
					if( fork() == 0 )
					{
						execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
					}
					
					wait(NULL);
					
					return 0;
				}	
			}
			
			fclose(s_results);
			
			if( fork() == 0 )
			{
				execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
			}
			
			wait(NULL);
			
			return 0;
		}
		
		case 'E' : {
			int i;
			clock_t start, end;
			
			s_results = fopen(SPTFILE, "w+");
			
			for( i = taille_min; i < taille_max; i += pas )
			{				
				Matrix m = aleatoire(i, i, 0, 10);
				
				start = clock();
				
				struct EigenCouple r = eigenval(m);

				end = clock();
				float e_time = exec_time(start, end);
							
				fprintf(s_results, "%d %f\n", i, e_time);
				
				deleteMatrix(r.evect);
				
				deleteMatrix(m);
				
				if( (int) e_time > sec )
				{
					fclose(s_results);
					
					if( fork() == 0 )
					{
						execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
					}
					
					wait(NULL);
					
					return 0;
				}	
			}
			
			fclose(s_results);
			
			if( fork() == 0 )
			{
				execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
			}
			
			wait(NULL);
			
			return 0;
		}
		
		case 'I' : {
			int i;
			clock_t start, end;
			
			s_results = fopen(SPTFILE, "w+");
			
			for( i = taille_min; i < taille_max; i += pas )
			{
				Matrix m = aleatoire(i, i, -10.0, 10.0);
				
				start = clock();
				
				Matrix r = inverse(m);
				
				end = clock();
				
				float e_time = exec_time(start, end);
							
				fprintf(s_results, "%d %f\n", i, e_time);
				
				deleteMatrix(m);
				deleteMatrix(r);
				
				if( (int) e_time > sec )
				{
					fclose(s_results);
					
					if( fork() == 0 )
					{
						execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
					}
					
					wait(NULL);
					
					return 0;
				}	
			}
			
			fclose(s_results);
			
			if( fork() == 0 )
			{
				execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
			}
			
			wait(NULL);
			
			return 0;
		}
		
		case 'L' : {
			int i;
			clock_t start, end;
			
			s_results = fopen(SPTFILE, "w+");
			
			for( i = taille_min; i < taille_max; i += pas )
			{
				Matrix m = aleatoire(i, i, -10.0, 10.0);
				
				start = clock();
				
				struct LEstimateCouple r = least_estimate(m);
				
				end = clock();
				
				float e_time = exec_time(start, end);
							
				fprintf(s_results, "%d %f\n", i, e_time);
				
				deleteMatrix(m);
				
				if( (int) e_time > sec )
				{
					fclose(s_results);
					
					if( fork() == 0 )
					{
						execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
					}
					
					wait(NULL);
					
					return 0;
				}	
			}
			
			fclose(s_results);
			
			if( fork() == 0 )
			{
				execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
			}
			
			wait(NULL);
			
			return 0;
		}
		
		case 'C' : {
			int i;
			clock_t start, end;
			
			s_results = fopen(SPTFILE, "w+");
			
			for( i = taille_min; i < taille_max; i += pas )
			{
				Matrix m = aleatoire(i, i, -10.0, 10.0);
				E scal = 5.0;
				
				start = clock();
				
				Matrix r = mult_scal(scal, m);
				
				end = clock();
				
				float e_time = exec_time(start, end);
							
				fprintf(s_results, "%d %f\n", i, e_time);
				
				deleteMatrix(m);
				deleteMatrix(r);
				
				if( (int) e_time > sec )
				{
					fclose(s_results);
					
					if( fork() == 0 )
					{
						execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
					}
					
					wait(NULL);
					
					return 0;
				}	
			}
			
			fclose(s_results);
			
			if( fork() == 0 )
			{
				execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
			}
			
			wait(NULL);
			
			return 0;
		}
		
		case 'N' : {
			int i;
			clock_t start, end;
			
			s_results = fopen(SPTFILE, "w+");
			
			for( i = taille_min; i < taille_max; i += pas )
			{
				Matrix v = aleatoire(1, i, -10.0, 10.0);
				
				start = clock();
				
				E nv = norme(v);
				
				end = clock();
				
				float e_time = exec_time(start, end);
							
				fprintf(s_results, "%d %f\n", i, e_time);
				
				deleteMatrix(v);
				
				if( (int) e_time > sec )
				{
					fclose(s_results);
					
					if( fork() == 0 )
					{
						execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
					}
					
					wait(NULL);
					
					return 0;
				}	
			}
			
			fclose(s_results);
			
			if( fork() == 0 )
			{
				execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
			}
			
			wait(NULL);
			
			return 0;
		}
		
		case 'R' : {
			int i;
			clock_t start, end;
			
			s_results = fopen(SPTFILE, "w+");
			
			for( i = taille_min; i < taille_max; i += pas )
			{
				Matrix m = aleatoire(i, i, -10.0, 10.0);
				
				start = clock();
				
				int r = rank(m);
				
				end = clock();
				
				float e_time = exec_time(start, end);
							
				fprintf(s_results, "%d %f\n", i, e_time);
				
				deleteMatrix(m);
				
				if( (int) e_time > sec )
				{
					fclose(s_results);
					
					if( fork() == 0 )
					{
						execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
					}
					
					wait(NULL);
					
					return 0;
				}	
			}
			
			fclose(s_results);
			
			if( fork() == 0 )
			{
				execl("/usr/bin/gnuplot", "gnuplot", "speedtest.dat", (char *) NULL);
			}
			
			wait(NULL);
			
			return 0;
		}
		
		default:
			return -1;
	}
				
	return -1;			
}
