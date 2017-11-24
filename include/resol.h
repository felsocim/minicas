/**
 * @file resol.h
 * @brief Définitions des fonctions avancées
 * @authors Marek Felsoci, Paul Viville
 **/ 
#pragma once

#include "matrix.h"

//Fichier temporarie de sauvegarde des résultats de speedtest
#define SPTFILE "tmp/speedtest-results.txt"

//Fichier temporarie de sauvegarde des résultats de 'least_estimate'
#define LESTFILE "tmp/lestimate-results.txt"
#define ALPHABETA "tmp/alpha-beta.txt"

//Définition du type de retour pour la fonction 'eigenval' qui calcule 
//la valeur et le vecteur propre
struct EigenCouple {
	Matrix evect;
	E eval;
};

//Définition du type de retour pour la fonction 'least_estimate' qui calcule 
//les coefficients de la droite de régression linéaires et le vecteur des résidus
struct LEstimateCouple {
	Matrix coeff;
	Matrix residus;
};

Matrix copyMatrix(const Matrix m);
Matrix mult_scal(E v, const Matrix m);
E norme(const Matrix V);
Matrix addition(Matrix m1, Matrix m2);
Matrix soustraction(Matrix m1, Matrix m2);
Matrix multiplication(Matrix m1, Matrix m2);
void swapLine(Matrix m, int l1, int l2);
void combineLines(Matrix m, E c1, int l1, E c2, int l2);
int choixPivot(Matrix A, int l);
E determinant(Matrix X);
Matrix transpose(Matrix m);
Matrix exposant(Matrix m, int exp);
void remontee(Matrix A, Matrix B, Matrix X);
void addMultiple(Matrix A, Matrix B, int i, int j, E c);
void echangeLigne(Matrix A, Matrix B, int i, int j);
void triangulaire(Matrix A, Matrix B);
void gauss(Matrix A, Matrix B, Matrix X);
int zero_row(Matrix A, int line);
int rank(Matrix A);
E eabs(E val);
Matrix inverse(Matrix A);
struct LEstimateCouple least_estimate(Matrix S);
struct EigenCouple eigenval(Matrix A);
char getcmd(char * cmd);
float exec_time(clock_t start, clock_t end);
int speedtest(char * cmd, int taille_min, int taille_max, int pas, int sec);

