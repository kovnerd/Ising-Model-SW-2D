#include <math.h>
#include <stdlib.h>
#include "metropolis.h"

//=====================================================================================
/*
mc_step(): does 1 monte-carlo step per spin; performs 1 iteration of the Metropolis-Hastings algorithm


*/
//=====================================================================================
void metro_sweep(double J, double T, int spin[XLENGTH][YLENGTH])
{
	int xUp = 0 , xDwn = 0, yUp = 0, yDwn = 0;
	for(int x = 0; x < XLENGTH; x++)
	{
		for(int y = 0; y < YLENGTH; y++)
		{
			//==========Periodic-Boundary-Conditions==========
            if (x < XLENGTH - 1)
				xUp = x + 1;
			else
				xUp = 0;
			
			if (x == 0)
				xDwn = XLENGTH - 1;
			else
				xDwn = x - 1;
			
			if (y < YLENGTH - 1)
				yDwn = y + 1;
			else
				yDwn = 0;

			if (y == 0)
				yUp = YLENGTH - 1;
			else
				yUp = y - 1;
				
			//not sure if postFlipE should be multiplied by 0.5 or not
			double postFlipE = J*((spin[x][y]*spin[xUp][y]) + (spin[x][y]*spin[xDwn][y]) + (spin[x][y]*spin[x][yUp]) + (spin[x][y]*spin[x][yDwn]));
			double deltaH = 2* postFlipE;
			double prob = exp(-deltaH/T);
			double randNum = (double)rand()/((double)RAND_MAX);
			if(deltaH < 0 || prob < randNum)
			{
				spin[x][y] *= -1;
			}
		}
	}
}	
