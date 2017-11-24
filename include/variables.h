#pragma once

#include "parseurs.h"

//Définition du type variable
typedef struct{
  char* name;
  char type;
  void* ptr;
} var;

//Définition d'un tableau de variables utilisé pour l'interpreteur
typedef struct{
  var * tab;
  int size;
} *Vars;

var nouvelleVar(char * name, char type, void* ptr);
Vars nouvelleVars();
void agrandir(Vars vs);
int recherchePos(Vars vs, char * s);
int rechercheVar(Vars vs, char * s);
void ajouterVar(Vars vs, var v);
void printElement(var v);
void printAllElements(Vars vs);
Matrix createMatrix(Vars vs, char** elements, int lines, int cols);
void eraseAll(Vars vs);