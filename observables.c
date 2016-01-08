#include "averages.h"
#include "observables.h"

//===================================HAMILTONIAN=====================================
/*
 * hamil(): calculates the energy of the spin configuration
 * 
 * PARAMETERS:
 * 
 * J: interaction energy
 * spin[][]: array containing +/-1 to simulate a 2D configuration of spins 
 */
//===================================================================================
double hamil(double J, int **spin)
{
    double spinProducts = 0.0;
    
    for(int x = 0; x < XLENGTH; x++)
	{
		for(int y = 0; y < YLENGTH; y++)
		{
			int xAdj = (x == XLENGTH - 1) ? 0 : x + 1; //adjacent lattice site in the +x direction*
			int yAdj = (y == YLENGTH - 1) ? 0 : y + 1; //adjacent lattice site in the +y direction*
			
			spinProducts += spin[x][y] * (spin[xAdj][y] + spin[x][yAdj]);
			
		}
    }
	
    return -J*spinProducts;
}



//===================================MAGNETIZATION=====================================
/*
mag(): calculates the magnetization of the spin configuration.

spin[][]: array containing +/-1 to simulate a 2D configuration of spins

*/
//=====================================================================================
double mag(int **spin)
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


