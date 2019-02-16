/**
 * @file main.c
 * @brief Jeux d'essai
 * @author Marek Felsoci
 **/ 
#include "../include/resol.h"

int main(void)
{
	srand(time(NULL));

	Matrix mi = identite(5);

	Matrix ma = aleatoire(6,9,1.5,10.3);

	printf("Matrix mi:\n");

	displayMatrix(mi);

	printf("Matrix ma:\n");

	displayMatrix(ma);

	Matrix cp = copyMatrix(ma);

	Matrix mult = mult_scal(2.0, cp);

	printf("Matrix cp:\n");

	displayMatrix(cp);

	printf("Matrix mult:\n");

	displayMatrix(mult);

	deleteMatrix(ma);

	deleteMatrix(mi);

	deleteMatrix(cp);

	deleteMatrix(mult);

	Matrix col = aleatoire(5, 1, 1.0, 5.0);

	printf("Matrix col:\n");

	displayMatrix(col);

	printf("Norme vecteur: %f\n", norme(col));
	
	deleteMatrix(col);


	Matrix m = aleatoire(4, 2, 1.0, 9.0);

	displayMatrix(m);

	printf("\nRang m : %d\n\n", rank(m));

	deleteMatrix(m);

	Matrix tr = newMatrix(3, 3);

	setElt(tr, 0, 0, -3.0);
	setElt(tr, 0, 1, 5.0);
	setElt(tr, 0, 2, 6.0);

	setElt(tr, 1, 0, -1.0);
	setElt(tr, 1, 1, 2.0);
	setElt(tr, 1, 2, 2.0);

	setElt(tr, 2, 0, 1.0);
	setElt(tr, 2, 1, -1.0);
	setElt(tr, 2, 2, -1.0);

	displayMatrix(tr);

	printf("\nRang m : %d\n\n", rank(tr));

	printf("det tr: %f\n", determinant(tr));

	Matrix er = inverse(tr);

	printf("\nInv tr : \n");

	displayMatrix(er);

	deleteMatrix(er);

	deleteMatrix(tr);


	Matrix toi = newMatrix(3, 3);

	setElt(toi, 0, 0, 1.0);
	setElt(toi, 0, 1, 2.0);
	setElt(toi, 0, 2, 1.0);

	setElt(toi, 1, 0, 4.0);
	setElt(toi, 1, 1, 2.0);
	setElt(toi, 1, 2, 6.0);

	setElt(toi, 2, 0, 2.0);
	setElt(toi, 2, 1, 3.0);
	setElt(toi, 2, 2, 1.0);

	printf("\nMatrix toi: \n");

	displayMatrix(toi);

	Matrix rtoi = inverse(toi);

	printf("\nInv toi : \n");

	displayMatrix(rtoi);

	printf("\nDet toi: %f\n", determinant(toi));

	deleteMatrix(toi);
	deleteMatrix(rtoi);

	printf("\nTeste moindres carrres\n");

	Matrix S = newMatrix(5, 2);

	setElt(S, 0, 0, 2.0);
	setElt(S, 0, 1, 3.7);

	setElt(S, 1, 0, 7.0);
	setElt(S, 1, 1, 12.6);

	setElt(S, 2, 0, 5.3);
	setElt(S, 2, 1, 7.3);

	setElt(S, 3, 0, 3.0);
	setElt(S, 3, 1, 0.8);

	setElt(S, 4, 0, 5.2);
	setElt(S, 4, 1, 7.1);

	printf("Source Matrix:\n");

	displayMatrix(S);

	struct LEstimateCouple r = least_estimate(S);

	printf("Alhpa-Beta:\n");

	displayMatrix(r.coeff);
	displayMatrix(r.residus);

	deleteMatrix(S);

	Matrix vp = newMatrix(2, 2);
	struct EigenCouple eiv;

	setElt(vp, 0, 0, 3.0);
	setElt(vp, 0, 1, -2.0);

	setElt(vp, 1, 0, 1.0);
	setElt(vp, 1, 1, 0.0);

	printf("\nvp matrix:\n");

	displayMatrix(vp);
	
	eiv = eigenval(vp);

	printf("eigen val: %f\n", eiv.eval);
	
	printf("\nvect_u:\n");

	displayMatrix(eiv.evect);

	deleteMatrix(vp);
	

	Matrix m1 = newMatrix(2,2);
	
	setElt(m1, 0, 0, 3.0);
	setElt(m1, 0, 1, -2.0);

	setElt(m1, 1, 0, 1.0);
	setElt(m1, 1, 1, 0.0);
	
	printf("Det m1 : %f\n", determinant(m1));
	
	speedtest("det", 1, 101, 1, 20);

	return 0;
}
