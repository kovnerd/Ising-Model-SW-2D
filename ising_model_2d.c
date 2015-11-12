#include <stdio.h>
#include <time.h>
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_rng.h>
#include "observables.h"
#include "metropolis.h"

void initialize(int spin[XLENGTH][YLENGTH]);
//========================================================================
/*
initialize(): initializes spin[] with periodic boundary conditions.

spin[][]: array containing +/-1 to simulate a 2D configuration of spins

CHANGE SPIN TO BE 1D ARRAY, MAKE LIFE EASIER
*/
//===================================INITIAL-CONDITIONS==============================
void initialize(int spin[XLENGTH][YLENGTH])
{
	for(int x = 0; x < XLENGTH; x++)
	{
		for(int y = 0; y < YLENGTH; y++)
		{
			spin[x][y] = 1;
		}
	}
}

int main(void)
{
	int spin[XLENGTH][YLENGTH];
	double J = 1.;
	int ensembleSize = 9000;
	double energy[ensembleSize], mags[ensembleSize];
	double avEn = 0., avMag = 0., avMagSus = 0.;
	srand(time(NULL));
  	FILE *fp;
		fp = fopen("results2D.dat", "w");
	for(double T = 1; T < 5; T += 0.1)
	{
		for(int n = 0; n < ensembleSize; n++)
		{
			initialize(spin);
			metro_sweep(J, T, spin);
			energy[n] = hamil(J, spin)/(XLENGTH*YLENGTH);
			mags[n] = mag(spin);
		}
		avEn = gsl_stats_mean(energy, 1, ensembleSize);
		avMag = gsl_stats_mean(mags, 1, ensembleSize);
		avMagSus = magSus(ensembleSize, mags, T);
		fprintf(fp, "%f %f %f %f\n", T, avEn, avMag, avMagSus); //statement will grow
	}	
	
	return 0;
}
