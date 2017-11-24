#pragma once

#include "resol.h"
#include "string.h"

int countChar(char * ligne);
char * epurer(char * ligne);
int compteur(char * ligne, char compt);
char **split(char * ligne, char * delim);
void displayTab(char ** tab);
int rechercheChar(char* ligne, char c);
int isNumber(char car);