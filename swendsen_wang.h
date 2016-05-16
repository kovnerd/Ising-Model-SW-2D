#include <gsl/gsl_rng.h>
#include <math.h>
#include <time.h>

void swendsen_wang_step(double, int **, int ***, int **, int*, gsl_rng *);
void hk_cluster(int ***, int**, int*);
int properLabel(int, int *);
