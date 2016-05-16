#include "metropolis.h"
void mc_step_per_spin(int **spin, double **probs, gsl_rng *r)
{	
	for(int x = 0; x < XLENGTH; x++)
	{
		for(int y = 0; y < YLENGTH; y++)
		{
			//==========Periodic-Boundary-Conditions==========
			int xUp = (x == XLENGTH - 1) ? 0 : x + 1;
			int yUp = (y == YLENGTH - 1) ? 0 : y + 1;
			int xDwn = (x == 0) ? XLENGTH - 1 : x - 1;
			int yDwn = (y == 0) ? YLENGTH - 1: y - 1;
			
			int deltaSpinProd = 2 * spin[x][y] * (spin[xUp][y] + spin[xDwn][y] + spin[x][yUp] + spin[x][yDwn]);
			double prob = probs[8 + deltaSpinProd][1 + spin[x][y]]; //access look-up table
				
			double randNum = gsl_rng_uniform(r);
			
			spin[x][y] *= (prob > randNum) ? -1 : 1;
			
		}
	}
}
