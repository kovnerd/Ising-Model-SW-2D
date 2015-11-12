#include "averages.h"
#include "observables.h"

//===================================HAMILTONIAN=====================================
/*
hamil(): calculates the energy of the spin configuration
J: interaction energy

spin[][]: array containing +/-1 to simulate a 2D configuration of spins

xUp: variable determining the PBC at the right end of the lattice

yUp: variable determining the PBC at the top of the lattice

xDwn: variable determining the PBC at the left end of the lattice

yDwn: variable determining the PBC at the bottom of the lattice


* = may be changed/removed

*/
//===================================================================================
double hamil(double J, int spin[XLENGTH][YLENGTH])
{
    double spinProducts = 0.0;
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

			spinProducts += (spin[x][y]*spin[xUp][y]) + (spin[x][y]*spin[xDwn][y]) + (spin[x][y]*spin[x][yUp]) + (spin[x][y]*spin[x][yDwn]);
                }
        }
	
        return -J*spinProducts*0.5;
}



//===================================MAGNETIZATION=====================================
/*
mag(): calculates the magnetization of the spin configuration.

spin[][]: array containing +/-1 to simulate a 2D configuration of spins

*/
//=====================================================================================
double mag(int spin[XLENGTH][YLENGTH])
{
        double netSpin = 0;
        for(int x = 0; x < XLENGTH; x++)
        {
                for(int y = 0; y < YLENGTH; y++)
                {
                        netSpin += spin[x][y];
                }
        }
        return netSpin/((double)(XLENGTH*YLENGTH));
}


//=====================================================================================
/*
 magSus(): calculates magentic susceptibility
 
 mag[n]: list of magnetizations for each configuration of ensemble size n
 
 T: temperature 
 
  
*/
//=====================================================================================
double magSus(int ensembleSize, double mag[ensembleSize], double T)
{
	double avMag = average(ensembleSize, mag);
	double avMagSquared = average2(ensembleSize, mag);
	double magsus = (avMagSquared - (avMag*avMag))/T;
	
	return magsus;
}

