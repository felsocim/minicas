#include "../include/parseurs.h"

int countChar(char * ligne){
  unsigned int cpt = 0, i;
  if (!ligne)
   return 0;
  for(i = 0; i < strlen(ligne); i++){
    if(ligne[i] != ' ' && ligne[i] != '\t' && ligne[i] != '\n' && ligne[i] != ')' && ligne[i] != ']')
      cpt++;
  }
  return cpt;
}

char * epurer(char * ligne){
  unsigned int cpt = countChar(ligne);
  char * pure;
  if(cpt == 0)
    return NULL;
  pure = malloc(cpt + 1);
  unsigned int i, j = 0;
  for(i = 0; i < strlen(ligne); i++){
    if(ligne[i] != ' ' && ligne[i] != '\t' && ligne[i] != '\n' && ligne[i] != ')' && ligne[i] != ']'){
      pure[j] = ligne[i];
      j++;
    }
  }
  pure[j] = '\0';
  return pure;
}

int compteur(char * ligne, char compt){
  unsigned int i = 0, cpt = 0;
  while(i < strlen(ligne)){
    if(ligne[i] == compt){
      cpt++;
    }
    i++;
  }
  return cpt;
}

char **split(char * ligne, char * delim){
  char **tab = malloc(sizeof(char*));
  int i = 0;
  if(!ligne)
    return NULL;
  tab[i] = strtok(ligne, delim);
  while(tab[i] != NULL)
  {
    i++;
    tab = realloc(tab, sizeof(char*) * (i + 1));
    tab[i] = strtok(NULL, delim);
  }
  return tab;
}

void displayTab(char ** tab){
  int i = 0;
  if(tab == NULL) return;
  while(tab[i] != NULL){
    printf("token %d : %s\n",i, tab[i]);
    i++;
  }
}

int rechercheChar(char* ligne, char c){
	unsigned int i;
	for(i = 0; i < strlen(ligne); i++){
    if(ligne[i] == c) return 1;
  	}
  return 0;
}

int isNumber(char car){
  if ((car <= 71 && car >= 48) || car == '-')
    return 1;
  return 0;
}