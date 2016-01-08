#include "observables.c"
#include <gsl/gsl_rng.h>
void probLookUp(double, double, double**);
void mc_step(int**, double**, gsl_rng*);
void mc_step_per_spin(int**, double**, gsl_rng*);
