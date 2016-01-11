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
	unsigned long seed = ((unsigned long) time(NULL));
	gsl_rng *r = gsl_rng_alloc(gsl_rng_taus2); //allocates memory for random number generator
	gsl_rng_set(r, seed); //seeds random number generator
	
	double J = 1.;
	double tmin = 2.;
	
	double tmax = 3.;
	int numPoints= 250;
	double tstep = (tmax - tmin)/numPoints;
	//TESTING
	
	
	int ensembleSize = 1024*128;
	double energy = 0., magnetization = 0., avEn = 0., avEn2 = 0., avMag = 0., avMag2 = 0., avMagSus = 0., avSpecHeat = 0.;
	int thermSteps = ensembleSize / 4;
  	FILE *fp;
		fp = fopen("2DSquareModelResults50x50.dat", "w");
	for(double T = tmin; T < tmax; T += tstep)
	{
		probLookUp(T, J, boltzProbs); //updates lookup table for boltzmann probabilities
		coldStart(spin, XLENGTH, YLENGTH);
		
		for(int ts = 0; ts < thermSteps; ts++)//thermalizes configuration
		{
			mc_step_per_spin(spin, boltzProbs, r);
		}
		
		for(int n = 0; n < ensembleSize; n++)
		{
			mc_step_per_spin(spin, boltzProbs, r);
			energy = hamil(J, spin)/(XLENGTH*YLENGTH);
			magnetization = mag(spin);
			
			avEn += energy;
			avEn2 += (energy * energy);
			avMag += fabs(magnetization);
			avMag2 += (magnetization * magnetization);
			
		}
		
		avEn /= ensembleSize;
		avEn2 /= ensembleSize;
		avMag /= ensembleSize;
		avMag2 /= ensembleSize;
		
		avMagSus = (avMag2 - avMag * avMag)/T;
		avSpecHeat = (avEn2 - avEn*avEn)/(T * T);
		
		fprintf(fp, "%f %f %f %f\n", T, avEn, avMag, avMagSus); //statement will grow
		printf("%f %f %f %f\n", T, avEn, avMag, avMagSus);
	}	
	gsl_rng_free(r);
	matrix_free_int(spin);
	matrix_free_double(boltzProbs);
	fclose(fp);
	
	return 0;
}
