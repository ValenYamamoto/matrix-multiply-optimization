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
