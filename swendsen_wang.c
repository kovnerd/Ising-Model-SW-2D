#include "swendsen_wang.h"
//ready for TESTING-MAYBE

int properLabel(int i, int *labelLabel)
{
	while(i != labelLabel[i])
		i = labelLabel[i];
	return i;
}

void swendsen_wang_step_per_spin

void swendsen_wang_step(int **probs, int **spin, int ***bond, gsl_rng *r)
{
	
	int **clusterLabel = matrix_allocate_int(XLENGTH,YLENGTH);
	double freezeProb = 1-probs[10][0]; //aka 1-exp(-2J/(kT))
	
	//Forms "physical" bonds.
	for(int x = 0; x < XLENGTH, x++)
		for(int y = 0; y < YLENGTH; y++) 
		{
			int xPrev = (x == 0) ? XLENGTH - 1 : x - 1;
			int yPrev = (y == 0) ? YLENGTH - 1 : y - 1;
			
			bond[x][y][0] = bond[x][y][1] = 0;
			
			if(spin[x][yPrev] == spin[xPrev][y] && gsl_rng_uniform() < freezeProb)
				bond[x][y][0] == 1;
			if(spin[x][yPrev] == spin[xPrev][y] && gsl_rng_uniform() < freezeProb)
				bond[x][y][1] == 1;
		}
		
		//identifies spin clusters
		numClusters = hk-cluster(bond, clusterLabel);
		
		//randomly flips spin clusters
		int clusterSpin[numClusters][2];//might have to dynamically allocate this  //1st index is the actual cluster spin, second index represents whether or not this cluster has been flipped
		
		for(int x = 0; x < XLENGTH; x++)
			for(int y = 0; y < YLENGTH; y++) 
			{
				c = clusterLabel[x][y];
				if(!clusterSpin[c][1])//if this cluster has not been flipped yet
				{
					clusterSpin[c][0] = (gsl_rng_uniform(r) < 0.5) ? 1 : -1;//randomly flips cluster c (actual flipping of spins according to this line is done below)
					clusterSpin[c][1] = 1;//signifies that this cluster has been flipped
				}
				spin[x][y] = clusterSpin[c][0];//actually does the spin-flipping
			}
		matrix_free_int(clusterLabel);
		
}



int hk-cluster(int ***bond, int **clusterLabel)
{
	int amountOfBonds = 0;
	int label = 0, minLabel = 0, propLabel = 0;
	int xBond[4], yBond[4];
	int labelLabel[XLENGTH*YLENGTH]
	for(x = 0; x < XLENGTH, x++)
	{
		for(y = 0; y < YLENGTH, y++)
		{	//check neighbors for frozen bonds
			int xPrev = (x == 0) ? XLENGTH - 1 : x - 1;
			int yPrev = (y == 0) ? YLENGTH - 1 : y - 1;
			
			if(bond[xPrev][y][0] == 1)//check previous x
			{
				xBond[amountOfBonds] = xDwn;
				yBond[amountOfBonds] = y;
				amountOfBonds++;	
			}
			if(bond[x][yPrev][1] == 1) //check previous y
			{
				xBond[amountOfBonds] = x;
				yBond[amountOfBonds] = yDwn;
				amountOfBonds++; 
			}
			if(amountOfBonds == 0)//create new cluster
			{
				clusterLabel[x][y] = label;
				labelLabel[label] = label;
				label++; //eventually represents number of clusters
			}
			else//relabel spins with proper (aka minimum) cluster label
			{
				for(int b = 0; b < amountOfbonds; b++)
				{
					propLabel = properLabel(clusterLabel[xBond[b]][yBond[b]], labelLabel);
					if (minLabel > propLabel)
						minLabel = propLabel;
				}
				
				clusterLabel[x][y] = minLabel;
				
				for(int b = 0; b < amountOfBonds; b++)
				{
					iLabel = clusterLabel[xBond[b]][yBond[b]];
					labelLabel[iLabel] = minLabel;
					clusterLabel[xBond[b]][yBond[b]] = minLabel;
				}
			}
		}
	}	
	return label + 1;																																																																																					`
}
