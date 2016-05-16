#include <gsl/gsl_rng.h>
#include <math.h>
#include <time.h>

void swendsen_wang_step(double, int **, int ***, int **, gsl_rng *);
int* hk_cluster(int ***, int**);
int properLabel(int, int *);
