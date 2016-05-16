#include "swendsen_wang.h"

int properLabel(int i, int *labelLabel)
{
	while(labelLabel[i] != i)
		i = labelLabel[i];
	
	return i;
}

void swendsen_wang_step(double freezeProb, int **spin, int ***bonds, int **clusterLabel, gsl_rng *r)
{
	int *labelLabel;
	/*
	 * Forms "physical" bonds.
	 */ 
	for(int x = 0; x < XLENGTH; x++)
		for(int y = 0; y < YLENGTH; y++) 
		{
			int xNext = (x == XLENGTH - 1) ? 0 : x + 1;
			int yNext = (y == YLENGTH - 1) ? 0 : y + 1;
			
			bonds[x][y][0] = bonds[x][y][1] = 0;
			if(spin[x][y] == spin[xNext][y] && gsl_rng_uniform(r) < freezeProb)
				bonds[x][y][0] = 1;
			if(spin[x][y] == spin[x][yNext] && gsl_rng_uniform(r) < freezeProb)
				bonds[x][y][1] = 1;
		}
	/*
	 * identifies spin clusters
	 */
	labelLabel = hk_cluster(bonds, clusterLabel);
		
	int numClusters = 1;
	for(int x = 0; x < XLENGTH; x++)
		for(int y = 0; y < YLENGTH; y++)//relabel cluster labels to their proper label
		{
			clusterLabel[x][y] = properLabel(clusterLabel[x][y], labelLabel);
			if(clusterLabel[x][y] > numClusters)
				numClusters = clusterLabel[x][y] + 1;
		}
		
	/* CONDITIONAL JUMP & UNINITIALIZED STACK ALLOCATION ERROR HERE
	 * 
	 * randomly flips spin clusters
	 */ 
	 //1st index is the actual cluster spin, second index represents whether or not this cluster has been flipped
	int **clusterSpin = matrix_allocate_int(numClusters, 2);
	for(int x = 0; x < XLENGTH; x++)
		for(int y = 0; y < YLENGTH; y++) 
		{
			int c = clusterLabel[x][y];
			clusterSpin[c][0] = spin[x][y];
			clusterSpin[c][1] = 0;
		}
	for(int x = 0; x < XLENGTH; x++)
		for(int y = 0; y < YLENGTH; y++) 
		{
			int c = clusterLabel[x][y];
			if(!clusterSpin[c][1])//if this cluster has not been flipped yet
			{
				clusterSpin[c][0] = (gsl_rng_uniform(r) < 0.5) ? 1 : -1;//randomly flips cluster c (actual flipping of spins according to this line is done below)
				clusterSpin[c][1] = 1;//signifies that this cluster has been flipped
			}
			spin[x][y] = clusterSpin[c][0];
		}
	/*printf("%s\n", "Cluster Lattice:");
	for(int x = 0; x < XLENGTH; x++)
		for(int y = 0; y < YLENGTH; y++)
		{
			printf(" %d ", clusterLabel[x][y]);
			if(y == YLENGTH - 1)
				printf("\n");
		}*/
	matrix_free_int(clusterSpin);
	free(labelLabel);
}



int* hk_cluster(int ***bonds, int **clusterLabel)
{
	int amountOfBonds;
	int label = 0;
	int xBond[4], yBond[4];
	int *labelLabel = malloc((unsigned long) (XLENGTH*YLENGTH) * sizeof(int));
	for(int x = 0; x < XLENGTH; x++)
	{
		for(int y = 0; y < YLENGTH; y++)
		{	
			amountOfBonds = 0;
			//check neighbors for frozen bonds
			if(x > 0 && bonds[x - 1][y][0])//check previous x
			{
				xBond[amountOfBonds] = x - 1;
				yBond[amountOfBonds++] = y;
			}
			if(y > 0 && bonds[x][y - 1][1]) //check previous y
			{
				xBond[amountOfBonds] = x;
				yBond[amountOfBonds++] = y - 1;
			}
			
			//Periodic Boundary Conditions
			if(x == XLENGTH - 1 && bonds[x][y][0])
			{
				xBond[amountOfBonds] = 0;
				yBond[amountOfBonds++] = y;
			}
			if(y == YLENGTH - 1 && bonds[x][y][1])
			{
				xBond[amountOfBonds] = x;
				yBond[amountOfBonds++] = 0;
			}
			
			//creates new cluster
			if(amountOfBonds == 0)
			{
				clusterLabel[x][y] = label;
				labelLabel[label] = label;
				label++;
			}
			else//relabel spins in current cluster with smallest proper label
			{
				int minLabel = label;
				for(int b = 0; b < amountOfBonds; b++)
				{
					int propLabel = properLabel(clusterLabel[xBond[b]][yBond[b]], labelLabel);
					if (minLabel > propLabel)
						minLabel = propLabel;
				}
				clusterLabel[x][y] = minLabel;
				for(int b = 0; b < amountOfBonds; b++)
				{
					labelLabel[clusterLabel[xBond[b]][yBond[b]]] = minLabel;
					clusterLabel[xBond[b]][yBond[b]] = minLabel;
				}
			}
		}
	}
	
	
	return labelLabel;
}
