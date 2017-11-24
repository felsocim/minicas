/**
 * @file matrix.h
 * @brief Définitions des types et des fonctions de base
 * @authors Marek Felsoci, Paul Viville
 **/ 
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

typedef float E;

typedef struct matrix {
	E * mat;
	int nrows, ncols;
} *Matrix;

E random_float(E a, E b);
Matrix newMatrix(int nbrows, int nbcolumns);
E getElt(Matrix m, int row, int column);
void setElt(Matrix m, int row, int column, E val);
void deleteMatrix(Matrix m);
void displayMatrix(Matrix m);
Matrix identite(int nbrows);
Matrix aleatoire(int nbrows, int nbcolumns, E minval, E maxval);
