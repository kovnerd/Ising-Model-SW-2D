#include "observables.c"
#include <gsl/gsl_rng.h>
#include <math.h>
#include <time.h>
void probLookUp(double, double, double**);
void mc_step_per_spin(int**, double**, gsl_rng*);
