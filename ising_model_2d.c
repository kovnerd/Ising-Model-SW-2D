#include <stdio.h>
#include "metropolis.c"
#include "matrixmem.c"
#include "queuearray.c"

void coldStart(int**, int, int);

void hotStart(int**, int, int);

void probLookUp(double, double, double**);


/* coldStart(): initializes spin[][] to all spins = +1.
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


/* hotStart(): initializes spin[][] to all spins = +/-1 randomly.
 * 
 * spin[][]: array containing +/-1 to simulate a 2D configuration of spins
 * 
 * lx: horizontal length of spin[][]
 * 
 * ly: vertical length of spin[][]
 */ 
void hotStart(int **spin, int lx, int ly)
{   
	gsl_rng *r = gsl_rng_alloc(gsl_rng_taus2);
	unsigned long seed = ((unsigned long) time(NULL));
	gsl_rng_set(r, seed);
	
	double randNum = 0.;
	for(int x = 0; x < lx; x++)
	{
		for(int y = 0; y < ly; y++)
		{
			randNum = gsl_rng_uniform(r);
			spin[x][y] = (randNum < 0.5) ? 1 : -1;
		}
	}
	
	gsl_rng_free(r);
}

/*
 * Creates look-up table for boltzmann probabilities for spin-flips for 2D square lattice
 */
void probLookUp(double T, double J, double **probs)
{
	for(int i = -8; i <= 8; i += 4)
	{
		probs[i + 8][0] = exp(-(i * J)/T);
		probs[i + 8][2] = exp(-(i * J)/T);
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
	int numPoints= 100;
	double tstep = (tmax - tmin)/numPoints;
	int ensembleSize = 1024*128; 
	
	double energy = 0., magnetization = 0., mags = 0., avEn = 0., avEn2 = 0., avMag = 0., avMag2 = 0., magSus = 0., specHeat = 0., avMagLast10 = 0.;
	int thermSteps = ensembleSize/2;
	Queue *magLast10;
	magLast10 = newQueue();
	
  	FILE *fp;
		fp = fopen("2DSquareModelResults5x5.dat", "w");
	for(double T = tmin; T < tmax; T += tstep)	 
	{ 
		probLookUp(T, J, boltzProbs); //updates lookup table for boltzmann probabilities
		if(!isEmpty(magLast10) && avMagLast10 < 0.2)//decides whether or not to hotstart or coldstart the initial spin configuration
				hotStart(spin, XLENGTH, YLENGTH);
		else
			coldStart(spin, XLENGTH, YLENGTH);
		
		for(int ts = 0; ts < thermSteps; ts++)//thermalizes configuration 
			mc_step_per_spin(spin, boltzProbs, r);
		 
		for(int n = 0; n < ensembleSize; n++)//does metropolis sweeps when configuration is in thermal equilibrium
		{
			mc_step_per_spin(spin, boltzProbs, r);
			energy = hamil(J, spin);
			mags = mag(spin);
			magnetization = fabs(mags);
			avEn += energy;
			avEn2 += (energy * energy);
			avMag += magnetization;
			avMag2 += (magnetization * magnetization);	
		}
		
		avEn /= ensembleSize;
		avEn2 /= ensembleSize;
		avMag /= ensembleSize;
		avMag2 /= ensembleSize;
		
		magSus = 2*(avMag2 - avMag * avMag)/T;
		specHeat = (avEn2 - avEn * avEn)/(T * T);
		
		if(magLast10->size == 10)
			avMagLast10 -= dequeue(magLast10);
			
		enqueue(magLast10, magSus);
		avMagLast10 += avMag;
		
		fprintf(fp, "%f %f %f %f %f\n", T/2.269185, avEn/(XLENGTH*YLENGTH), avMag/(XLENGTH*YLENGTH), magSus/(XLENGTH*YLENGTH), specHeat/(XLENGTH*YLENGTH));
		printf("%f %f %f %f %f\n", T/2.269185, avEn/(XLENGTH*YLENGTH), avMag/(XLENGTH*YLENGTH), magSus/(XLENGTH*YLENGTH), specHeat/(XLENGTH*YLENGTH));
			
	}	
	gsl_rng_free(r);
	matrix_free_int(spin);
	matrix_free_double(boltzProbs);
	free(magLast10);
	fclose(fp);
	
	return 0;
}
