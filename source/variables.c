#include "../include/variables.h"

/**
 * @brief crée une nouvelle variable
 * @param char * name : nom de la variable 
 * @param char type : 'f' ou 'm' type float ou matrix
 * @param void* ptr : pointeur vers le float ou la matrix
 * @returns var : renvoie la variable créée
**/
var nouvelleVar(char * name, char type, void* ptr){
  var newVar;
  newVar.name = malloc(strlen(name)+1);
  strcpy(newVar.name,name);
  free(name);
  newVar.type = type;
  newVar.ptr = ptr;
  return newVar;
}

/**
 * @brief crée une Vars
 * @returns Vars : retourne le tableau créé
 **/
Vars nouvelleVars(){
  Vars newV = malloc(sizeof(*newV));
  newV->size = 16;
  var * new = malloc(16*sizeof(var));
  newV->tab = new;
  int i;
  for(i = 0; i < 16; i++){
    new[i].name = NULL;
    new[i].type = 'n';
}
return newV;
}

/**
 * @brief Agrandir le tableau de variables d'une case
 * @param Vars vs: tableau de variable
 * @returns void : 'vs' est modifiée par effet de bord
 **/
void agrandir(Vars vs){
  int taille = vs->size;
  vs->tab = realloc(vs->tab, (taille + 16) * sizeof(var));
  int i;
  for(i = taille; i < taille + 16; i++){
    vs->tab[i].name = NULL;
    vs->tab[i].type = 'n';
} 
vs->size += 16;
return;
}

/**
 * @brief Cherche une position de variable dans le tableau en fonction du nom
 * @param Vars vs: tableau de variable
 * @param char * s : nom de la variable
 * @returns int : la position de la variable dans le tableau si elle existe -1 sinon
 **/
int rechercheVar(Vars vs, char * s){
  int i;
  for(i = 0; i < vs->size; i++){
    if(vs->tab[i].name == NULL)
      return -1;
    if(strcmp(s, vs->tab[i].name) == 0)
      return i;
  }
return -1;
}

/**
 * @brief Cherche une position d'insertion de variable dans le tableau en fonction du nom
 * @param Vars vs: tableau de variable
 * @param char * s : nom de la variable
 * @returns int : la position de la variable dans le tableau si elle existe -1 sinon
 **/
int recherchePos(Vars vs, char * s){
  int i;
  for(i = 0; i < vs->size; i++){
    if(vs->tab[i].name == NULL)
      return i;
    if(strcmp(s, vs->tab[i].name) == 0)
      return i;
  }
return -1;
}

/**
 * @brief ajoute une variable au tableau
 * @param Vars vs: tableau de variable
 * @param var v : variable a ajouter
 * @returns void : 'vs' est modifiée par effet de bord
 **/
void ajouterVar(Vars vs, var v){
  int pos = recherchePos(vs, v.name);
  if(pos == -1){
    pos = vs->size;
    agrandir(vs);
}
if(vs->tab[pos].name != NULL){
  if(vs->tab[pos].type == 'f')
    free((float*) vs->tab[pos].ptr);
  else
    deleteMatrix((Matrix)vs->tab[pos].ptr);
}
vs->tab[pos].name = v.name;
vs->tab[pos].type = v.type;
vs->tab[pos].ptr = v.ptr;
return;
}

/**
 * @brief affiche une variable
 * @param var v : variable a afficher
 * @returns void : aucune modification
 **/
void printElement(var v){
  printf("%s :\n", v.name);
  if(v.type == 'm'){
    displayMatrix((Matrix) v.ptr);
}
else
    printf("\t%f\n\n", *((float*)v.ptr));
return;
}

/**
 * @brief affiche un tableau de variable
 * @param Vars vs : tableau de variables a afficher
 * @returns void : aucune modification
 **/
void printAllElements(Vars vs){
  int i = 0;
  while(vs->tab[i].name != NULL){
    printElement(vs->tab[i]);
    i++;
}
return;
}

/**
 * @brief crée une nouvelle matrix
 * @param Vars vs : tableau de variables pour des recherches
 * @param char ** elements : tableau des elements de la matrix 
 * @param int lines : nombre de lignes de la matrix
 * @param int cols : nombre de colonnes de la matrix
 * @returns Matrix: renvoie la matrice créée
**/
Matrix createMatrix(Vars vs, char** elements, int lines, int cols){
    Matrix new = newMatrix(lines, cols);
    char **args;
    int i, j;
    float val;
    for(i = 0; i < lines; i++){
        args = split(elements[i], ",");
        for(j = 0; j < cols; j++){
            if(args[j] != NULL){
                if(isNumber(args[j][0]))
                    val = (float) atof(args[j]);
                else{
                    int pos = recherchePos(vs, args[j]);
                    if(pos == -1)
                        val = 0;
                    else
                        val = *(float*) vs->tab[pos].ptr;
                }
                setElt(new, i, j, val);
            }
        }
    }
    free(args);
    return new;
}

/**
 * @brief supprime un tableau de variable
 * @param Vars vs : tableau de variables a supprimer
 * @returns void : rien à renvoyer
 **/
void eraseAll(Vars vs){
    int i = 0;
    while(i < vs->size && vs->tab[i].name != NULL){
      free(vs->tab[i].name);
        if(vs->tab[i].type == 'f'){
            free((float*)vs->tab[i].ptr);
        }
        else{
          deleteMatrix((Matrix)vs->tab[i].ptr);
        }
        i++;
    }
    free(vs->tab);
    free(vs);
    return;
}