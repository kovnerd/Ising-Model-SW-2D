/*
 * Allocate (and free) two-dimensional array.
 * 
 * Credits to the folowing sites for inspiration:
 * 		http://c-faq.com/aryptr/dynmuldimary.html
 * 		https://mycodelog.com/2010/05/21/array3d/
 */

#include <stdlib.h>
#include "matrixmem.h"

int **matrix_allocate_int (int lx, int ly)
{
    int **s = malloc((unsigned long) lx * sizeof(int *));
    if (s == NULL)
        return s;

    s[0] = malloc((unsigned long) (lx * ly) * sizeof(int));
    if (s[0] == NULL)
        return NULL;
        
    for (int i = 1; i < lx; i++)
        s[i] = s[0] + i*ly;
    return s;
}

int ***matrix3d_allocate_int(int lx, int ly, int lz)//???????
{
	int ***s = malloc((unsigned long) lx * sizeof(int **));
	for(int i = 0; i < lx; i++)
	{
		s[i] = malloc((unsigned long) ly * sizeof(int *));
		for(int j = 0; j < ly; j++)
			 s[i][j] = malloc((unsigned long)lz * sizeof(int));
	}
	
	return s;
}


double **matrix_allocate_double (int lx, int ly)
{
    double **s = (double **) malloc((unsigned long) lx * sizeof(double *));
    if (s == NULL)
    {
        return s;
    }

    s[0] = (double *) malloc((unsigned long) (lx * ly) * sizeof(double));
    if (s[0] == NULL)
    {
        return NULL;
    }

    for (int i = 1; i < lx; i++)
    {
        s[i] = s[0] + i*ly;
    }
    return s;
}

void matrix_free_int (int **s)
{
    free (s[0]);
    free (s);
}

void matrix3d_free_int(int ***s, int lx, int ly)
{
	for(int i = 0; i < lx; i++)
	{
		for(int j = 0; j < ly; j++)
			free(s[i][j]);
		free(s[i]);
	}
	free(s);
	
}
void matrix_free_double (double **s)
{
    free (s[0]);
    free (s);
}
