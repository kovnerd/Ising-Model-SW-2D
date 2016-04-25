#include <stdlib.h>

int **matrix_allocate_int(int, int);
int ***matrix3d_allocate_int(int, int, int);//??????
double **matrix_allocate_double(int, int);
void matrix_free_int(int**);
void matrix_free_double(double**);
void matrix3d_free_int(int***, int, int);//??????
