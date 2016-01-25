#include "metropolis.h"

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

void mc_step_per_spin(int **spin, double **probs, gsl_rng *r)
{	
	for(int x = 0; x < XLENGTH; x++)
	{
		for(int y = 0; y < YLENGTH; y++)
		{
			//==========Periodic-Boundary-Conditions==========
			int xUp = (x == XLENGTH - 1) ? 0 : x + 1;
			int xDwn = (x == 0) ? XLENGTH - 1 : x - 1;
			int yUp = (y == YLENGTH - 1) ? 0 : y + 1;
			int yDwn = (y == 0) ? YLENGTH - 1: y - 1;
			
			int deltaSpinProd = 2 * spin[x][y] * (spin[xUp][y] + spin[xDwn][y] + spin[x][yUp] + spin[x][yDwn]);
			double prob = probs[8 + deltaSpinProd][1 + spin[x][y]]; //access look-up table
				
			double randNum = gsl_rng_uniform(r);
			if(prob > randNum)
			{
				spin[x][y] *= -1;
				//printf("In mc_step: spin flip successful!\n");
			}
		}
	}
}
