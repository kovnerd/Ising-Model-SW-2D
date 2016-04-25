#include "swendsen_wang.h"
//ready for TESTING-MAYBE

int properLabel(int i, int *labelLabel)
{
	while(i != labelLabel[i])
		i = labelLabel[i];
	return i;
}

void swendsen_wang_step_per_spin(double freezeProb, int **spin, int **clusterLabel, int ***bond, gsl_rng *r)
{
	for(int i = 0; i < XLENGTH*YLENGTH; i++)
		swendsen_wang_step(freezeProb, spin, clusterLabel, bond, r);
}

void swendsen_wang_step(double freezeProb, int **spin, int **clusterLabel, int ***bond, gsl_rng *r)
{
	//Forms "physical" bonds.
	for(int x = 0; x < XLENGTH; x++)
		for(int y = 0; y < YLENGTH; y++) 
		{
			int xPrev = (x == 0) ? XLENGTH - 1 : x - 1;
			int yPrev = (y == 0) ? YLENGTH - 1 : y - 1;
			
			if(spin[x][yPrev] == spin[xPrev][y] && gsl_rng_uniform(r) < freezeProb)
				bond[x][y][0] = 1;
			if(spin[x][yPrev] == spin[xPrev][y] && gsl_rng_uniform(r) < freezeProb)
				bond[x][y][1] = 1;
			else
				bond[x][y][0] = bond[x][y][1] = 0;
				
		}
		//identifies spin clusters
		int numClusters = hk_cluster(bond, clusterLabel);//FIX hk_cluster!!!
		
		printf("%s\n","Got here");
		/*
		//randomly flips spin clusters
		int clusterSpin[numClusters][2];//might have to dynamically allocate this  //1st index is the actual cluster spin, second index represents whether or not this cluster has been flipped
		int c = 0;
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
			}*/
			
}



int hk_cluster(int ***bond, int **clusterLabel)//NEEDS FIXING
{
	int amountOfBonds;
	int label = 0, minLabel = 0, propLabel = 0;
	int xBond[4], yBond[4];
	int labelLabel[XLENGTH*YLENGTH];
	
	
	for(int y = 0; y < YLENGTH; y++)
	{
		for(int x = 0; x < XLENGTH; x++)
		{	//check neighbors for frozen bonds
			amountOfBonds = 0;
			int xPrev = (x == 0) ? XLENGTH - 1 : x - 1;
			int yPrev = (y == 0) ? YLENGTH - 1 : y - 1;
			
			if(bond[xPrev][y][0] == 1)//check previous x
			{
				xBond[amountOfBonds] = xPrev;
				yBond[amountOfBonds] = y;
				amountOfBonds++;	
			}
			if(bond[x][yPrev][1] == 1) //check previous y
			{
				xBond[amountOfBonds] = x;
				yBond[amountOfBonds] = yPrev;
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
				minLabel = label;
				for(int b = 0; b < amountOfBonds; b++)//makes labels proper
				{
					propLabel = properLabel(clusterLabel[xBond[b]][yBond[b]], labelLabel);
					if (minLabel > propLabel)
						minLabel = propLabel;
				}
				printf("%d, %d: %d\n", x, y, clusterLabel[x][y]);
				clusterLabel[x][y] = minLabel;// SEG FAUT IS HAPPENING HERE
				
				for(int b = 0; b < amountOfBonds; b++)
				{
					labelLabel[clusterLabel[xBond[b]][yBond[b]]] = minLabel;
					clusterLabel[xBond[b]][yBond[b]] = minLabel;
				}
			}
		}
	}
	return label + 1;
}
