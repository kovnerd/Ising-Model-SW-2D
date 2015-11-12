#define XLENGTH 5
#define YLENGTH 5

double hamil(double J, int spin[XLENGTH][YLENGTH]);
double mag(int spin[XLENGTH][YLENGTH]);
double magSus(int ensembleSize, double mag[ensembleSize], double T);
