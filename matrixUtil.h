#define EPSILON 1E-7

struct thread_info {
	long size;
	double *m1;
	double *m2;
	double *answer;
	int start;
	int end;
};

void readMatrixFromFile( char *filepath, double *m );

int checkAnswer( int n, double *result, double *answer, int debug );

void generateMatrix( int n, double *m );

void addMatrix( int n, double *m1, double *m2, double *answer );

void subtractMatrix( int n, double *m1, double *m2, double *answer );

void split( int n, int quadrant, double *m, double *result );

void combine( int n, double *a, double *b, double *c, double *d, double *result );

void printMatrix( int n, double *m );