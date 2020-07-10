#define EPSILON 1E-7

void readMatrixFromFile( char *filepath, double *m );

int checkAnswer( int n, double *result, double *answer, int debug );

void generateMatrix( int n, double *m );
