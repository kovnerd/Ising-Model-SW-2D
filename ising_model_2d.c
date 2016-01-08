#include <stdio.h>
#include "metropolis.c"
#include "matrixmem.c"

void coldStart(int**, int, int);


/* cold(): initializes spin[][] to all spins = +1.
 * 
 * spin[][]: array containing +/-1 to simulate a 2D configuration of spins
 * 
 * lx: horizontal length of spin[][]
 * 
 * ly: vertical length of spin[][]
 */
void coldStart(int **spin, int lx, int ly)
{   
	for(int x = 0; x < lx; x++)
	{
		for(int y = 0; y < ly; y++)
		{
			spin[x][y] = 1;
		}
	}
}

int main(void)
{
	int **spin = matrix_allocate_int(XLENGTH, YLENGTH);
	double **boltzProbs = matrix_allocate_double(17, 3);
	
	double J = 1.;
	double tmin = 1.;
	
	double tmax = 5.;
	int numPoints= 100;
	double tstep = (tmax - tmin)/numPoints;
	//TESTING
	
	
	int ensembleSize = 9000;
	double avEn = 0., magnetization = 0., avMag = 0., avMag2 = 0., avMagSus = 0.;
	int thermSteps = ensembleSize / 4;
  	FILE *fp;
		fp = fopen("results2D.dat", "w");
	for(double T = tmin; T < tmax; T += tstep)
	{
		probLookUp(T, J, boltzProbs); //updates lookup table for boltzmann probabilities
		coldStart(spin, XLENGTH, YLENGTH);
		
		for(int ts = 0; ts < thermSteps; ts++)//thermalizes configuration
		{
			mc_step_per_spin(spin, boltzProbs);
		}
		
		for(int n = 0; n < ensembleSize; n++)
		{
			mc_step_per_spin(spin, boltzProbs);
				
			avEn += (hamil(J, spin)/(XLENGTH*YLENGTH));
			magnetization = mag(spin);
			avMag += magnetization;
			avMag2 += (magnetization*magnetization);
			
		}
		
		avEn /= ensembleSize;
		avMag /= ensembleSize;
		avMag2 /= ensembleSize;
		
		avMagSus = (avMag2-(avMag*avMag))/T;
		fprintf(fp, "%f %f %f %f\n", T, avEn, avMag, avMagSus); //statement will grow
		printf("%f %f %f %f\n", T, avEn, avMag, avMagSus);
	}	
	
	matrix_free_int(spin);
	matrix_free_double(boltzProbs);
	fclose(fp);
	
	return 0;
}
