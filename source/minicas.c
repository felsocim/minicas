#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../include/variables.h"

int runVar(char * line, Vars vs){
	int dp = rechercheChar(line, ':');
	int par = rechercheChar(line, '(');
	int declarVar = 0;
	char ** tab1;
	char ** tab;
	char * nom;
	size_t length = strlen(line);

	if(length < 2) {
		return -1;
	}

	line[length - 1] = '\0';

	if(par + dp){
		line = epurer(line);
		if(dp){
			tab1 = split(line, ":");
			nom = tab1[0];
			if(par)
				tab = split(tab1[1], "(");
			else
				tab = split(tab1[1], " ");
			declarVar = 1;
		}
		else{
			tab = split(line, "(");
			declarVar = 0;
		}
	}
	else
		tab = split(line, " ");

	if(!strcmp(tab[0], "quit")){
		free(tab);
		return 1;	
	}
	if(tab[0] != NULL && isNumber(tab[0][0])){
		float * ptr = malloc(sizeof(float));
		*ptr = (float) atof(tab[0]);
		printf("\t%1.2f\n", *ptr);
		if(declarVar){
			var v = nouvelleVar(nom, 'f', ptr);
			ajouterVar(vs, v);
		}
		free(tab);
		return 0;
	}
	if(!strcmp(tab[0], "speedtest")){
		if(tab[1] == NULL || tab[2] == NULL || tab[3] == NULL || tab[4] == NULL || tab[5] == NULL) return 0;
		int success;
		success = speedtest(tab[1], atoi(tab[2]), atoi(tab[3]), atoi(tab[4]), atoi(tab[5]));
		if(!success)
			printf("\tspeedtest effectué\n");
		else
			printf("\techec du speedtest\n");
		free(tab);
		return 0;
	}
	if(!strcmp(tab[0], "matrix")){
		if(tab[1] == NULL) return -1;
		int crochet = compteur(tab[1], '[');
		char ** lignes = split(tab[1], "[");
		if(lignes[0] == NULL) return -1;
		int virgules = compteur(lignes[0], ',');
		virgules ++;
		Matrix m = createMatrix(vs, lignes, crochet, virgules);
		displayMatrix(m);
		if(declarVar){
			var v = nouvelleVar(nom, 'm', m);
			ajouterVar(vs, v);
		}
		else
			deleteMatrix(m);
		free(tab);
		return 0;
	}
	if(!strcmp(tab[0], "addition")){
		if(tab[1] == NULL) return -1;
		char **args = split(tab[1], ",");
		if(args[0] == NULL|| args [1] == NULL) return -2;
		int arg1 = rechercheVar(vs, args[0]);
		int arg2 = rechercheVar(vs, args[1]);
		if(arg1 == -1 || arg2 == -1) return -2;
		Matrix m = addition((Matrix) vs->tab[arg1].ptr, (Matrix) vs->tab[arg2].ptr);
		displayMatrix(m);
		if(declarVar){
			var v = nouvelleVar(nom, 'm', m);
			ajouterVar(vs, v);
		}
		else
			deleteMatrix(m);
		free(tab);
		return 0;
	}
	if(!strcmp(tab[0], "sub")){
		if(tab[1] == NULL) return -1;
		char **args = split(tab[1], ",");
		if(args[0] == NULL|| args [1] == NULL) return -2;
		int arg1 = rechercheVar(vs, args[0]);
		int arg2 = rechercheVar(vs, args[1]);
		if(arg1 == -1 || arg2 == -1) return -2;
		Matrix m = soustraction((Matrix) vs->tab[arg1].ptr, (Matrix) vs->tab[arg2].ptr);
		displayMatrix(m);
		if(declarVar){
			var v = nouvelleVar(nom, 'm', m);
			ajouterVar(vs, v);
			return 0;
		}
		else
			deleteMatrix(m);
		free(tab);
		return 0;
	}
	if(!strcmp(tab[0], "mult")){
		if(tab[1] == NULL) return -1;
		char **args = split(tab[1], ",");
		if(args[0] == NULL|| args [1] == NULL) return -2;
		int arg1 = rechercheVar(vs, args[0]);
		int arg2 = rechercheVar(vs, args[1]);
		if(arg1 == -1 || arg2 == -1) return -2;
		Matrix m = multiplication((Matrix) vs->tab[arg1].ptr, (Matrix) vs->tab[arg2].ptr);
		displayMatrix(m);
		if(declarVar){
			var v = nouvelleVar(nom, 'm', m);
			ajouterVar(vs, v);
		}
		else
			deleteMatrix(m);
		free(tab);
		return 0;
	}
	if(!strcmp(tab[0], "mult_scal")){
		if(tab[1] == NULL) return -1;
		char **args = split(tab[1], ",");
		if(args[0] == NULL|| args [1] == NULL) return -2;
		int arg1 = rechercheVar(vs, args[0]);
		float arg2;
		if(arg1 == -1) return -2;
		if(!isNumber(args[1][0])){
			int pos = rechercheVar(vs, args[1]);
			if(pos == -1) return -2;
			arg2 = *(float*) vs->tab[pos].ptr;
		}
		else arg2 = (float) atof(args[1]);
		Matrix m = mult_scal(arg2, (Matrix) vs->tab[arg1].ptr);
		displayMatrix(m);
		if(declarVar){
			var v = nouvelleVar(nom, 'm', m);
			ajouterVar(vs, v);
		}
		else
			deleteMatrix(m);
		free(tab);
		return 0;
	}
	if(!strcmp(tab[0], "expo")){
		if(tab[1] == NULL) return -1;
		char **args = split(tab[1], ",");
		if(args[0] == NULL|| args [1] == NULL) return -2;
		int arg1 = rechercheVar(vs, args[0]);
		int arg2 = atoi(args[1]);
		if(arg1 == -1) return -2;
		Matrix m = exposant((Matrix) vs->tab[arg1].ptr, arg2);
		displayMatrix(m);
		if(declarVar){
			var v = nouvelleVar(nom, 'm', m);
			ajouterVar(vs, v);
		}
		else
			deleteMatrix(m);
		free(tab);
		return 0;
	}
	if(!strcmp(tab[0], "transpose")){
		if(tab[1] == NULL) return -1;
		char *args = tab[1];
		int arg1 = rechercheVar(vs, args);
		if(arg1 == -1) return -2;
		Matrix m = transpose((Matrix) vs->tab[arg1].ptr);
		displayMatrix(m);
		if(declarVar){
			var v = nouvelleVar(nom, 'm', m);
			ajouterVar(vs, v);
		}
		else
			deleteMatrix(m);
		free(tab);
		return 0;
	}
	if(!strcmp(tab[0], "determinant")){
		if(tab[1] == NULL) return -1;
    	char *args = tab[1];
    	int arg1 = rechercheVar(vs, args);
    	if(arg1 == -1) return -2;
   		float * det = malloc(sizeof(float));
    	*det = determinant((Matrix) vs->tab[arg1].ptr);
    	printf("\t%1.2f\n", *det);
    	if(declarVar){
			var v = nouvelleVar(nom, 'f', det);
			ajouterVar(vs, v);
		}
		else
			free(det);
		free(tab);
    	return 0;
  	}
	if(!strcmp(tab[0], "solve")){
		if(tab[1] == NULL) return -1;
		char **args = split(tab[1], ",");
		int arg1 = rechercheVar(vs, args[0]);
		int arg2 = rechercheVar(vs, args[1]);
		if(arg1 == -1 || arg2 == -1 || determinant((Matrix) vs->tab[arg1].ptr) == 0) return -2;
		Matrix m = newMatrix(((Matrix) vs->tab[arg1].ptr)->nrows, 1);
		gauss((Matrix) vs->tab[arg1].ptr, (Matrix) vs->tab[arg2].ptr, m);
		displayMatrix(m);
		if(declarVar){
			var v = nouvelleVar(nom, 'm', m);
			ajouterVar(vs, v);
		}
		else
			deleteMatrix(m);
		free(tab);
		return 0;
	}
	if(!strcmp(tab[0], "rank")){
		if(tab[1] == NULL) return -1;
    	char *args = tab[1];
    	int arg1 = rechercheVar(vs, args);
    	if(arg1 == -1) return -2;
   		float * r = malloc(sizeof(float));
    	*r = (float) rank((Matrix) vs->tab[arg1].ptr);
    	printf("\t%1.0f\n", *r);
    	if(declarVar){
			var v = nouvelleVar(nom, 'f', r);
			ajouterVar(vs, v);
		}
		else
			free(r);
		free(tab);
    	return 0;
  	}
  	if(!strcmp(tab[0], "invert")){
		if(tab[1] == NULL) return -1;
		char *args = tab[1];
		int arg1 = rechercheVar(vs, args);
		if(arg1 == -1) return -2;
		Matrix m = inverse((Matrix) vs->tab[arg1].ptr);
		displayMatrix(m);
		if(declarVar){
			var v = nouvelleVar(nom, 'm', m);
			ajouterVar(vs, v);
		}
		else
			deleteMatrix(m);
		free(tab);
		return 0;
	}
	if(!strcmp(tab[0], "eigen")){
		if(tab[1] == NULL) return -1;
		char *args = tab[1];
		int arg1 = rechercheVar(vs, args);
		if(arg1 == -1) return -2;
		struct EigenCouple eiv;
		eiv = eigenval((Matrix) vs->tab[arg1].ptr);
		printf("eigen val: %1.2f\n", eiv.eval);
		printf("\nvect_u:\n");
		displayMatrix(eiv.evect);
		deleteMatrix(eiv.evect);
		free(tab);
		return 0;
	}
	if(!strcmp(tab[0], "least_estimate")){
		if(tab[1] == NULL) return -1;
		char *args = tab[1];
		int arg1 = rechercheVar(vs, args);
		if(arg1 == -1) return -2;
		struct LEstimateCouple r = least_estimate((Matrix) vs->tab[arg1].ptr);
		printf("Alhpa-Beta:\n");
		displayMatrix(r.coeff);
		displayMatrix(r.residus);
		deleteMatrix(r.coeff);
		deleteMatrix(r.residus);
		free(tab);
		return 0;
	}
  	else
  		if(tab[0] != NULL)
    		printf("%s : function not implemented yet\n", tab[0]);

	return 0;
}

int main(int argc, char **argv) {
	FILE *f_in;
	int file = 0;
	if(argc == 2){
		file = 1;
		f_in = fopen(argv[1], "r");
	}
	else
		f_in = fdopen(0, "r");
	char *line;
	size_t n=0;
	int statut = 0;
	Vars vs = nouvelleVars();

	printf("prompt>");
	line=NULL;
	
	while (statut == 0 && getline(&line, &n, f_in)!= -1) {
		if(!strcmp(line, "\n")) continue;
		if(file) printf("%s", line);
		statut = runVar(line, vs);
		free(line);
		line=NULL;
		if(statut == -1){
			printf("erreur de syntaxe\n\n");
			statut = 0;
		}
		if(statut == -2){
			printf("erreur d'argument(s)\n\n");
			statut = 0;
		}
		if(statut == 0) 
			printf("prompt>");
	}
	fclose(f_in);
	printf("\n");
	eraseAll(vs);
	return 0;   
}