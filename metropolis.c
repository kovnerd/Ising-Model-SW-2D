#include "metropolis.h"
#include <math.h>

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

/*
 * Does 1 monte-carlo step per spin; performs 1 iteration of the Metropolis-Hastings algorithm
 * 
 * 
 * 
*/
void mc_step_per_spin(int **spin, double **probs)
{
	double prob;
	
	unsigned long seed = 1UL;
	
	
	
	for(int x = 0; x < XLENGTH; x++)
	{
		for(int y = 0; y < YLENGTH; y++)
		{
			//==========Periodic-Boundary-Conditions==========
			int xUp = (x == XLENGTH - 1) ? 0 : x + 1;
			int xDwn = (x == 0) ? XLENGTH - 1 : x - 1;
			int yUp = (y == YLENGTH - 1) ? 0 : y - 1;
			int yDwn = (y == 0) ? YLENGTH - 1: y - 1;
			
			int deltaH = (int)(2 * spin[x][y] * (spin[xUp][y] + spin[xDwn][y] + spin[x][yUp] + spin[x][yDwn]));
			prob = probs[8 + deltaH][1 + spin[x][y]]; //access look-up table
			
			gsl_rng *r = gsl_rng_alloc(gsl_rng_taus2); //allocates memory for random number generator
			gsl_rng_set(r, seed); //seeds random number generator
			
			double randNum = gsl_rng_uniform(r); 
			
			if(deltaH < 0 || prob < randNum)
			{
				spin[x][y] *= -1;
			}
			
			gsl_rng_free(r);
		}
	}
}	
