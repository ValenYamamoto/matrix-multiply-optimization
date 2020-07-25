#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "matrixUtil.h"
#include "./strassen.h"

#define N_INDEX 1
#define M1_INDEX 2
#define M2_INDEX 3
#define ANSWER_INDEX 4
#define DEBUG_INDEX 5

int main( int argc, char *argv[] )
{
	int N, correct, debug;
	double exetime;
	struct timeval start, end;

	N = atoi( argv[ N_INDEX ] );

	double *a = ( double * ) malloc( N * N * sizeof( double ));
	double *b = ( double * ) malloc( N * N * sizeof( double ));
	double *c = ( double * ) malloc( N * N * sizeof( double ));
	double *answer = ( double * ) malloc( N * N * sizeof( double ));
	
	readMatrixFromFile( argv[ M1_INDEX ], a );
	readMatrixFromFile( argv[ M2_INDEX ], b );
	readMatrixFromFile( argv[ ANSWER_INDEX ], answer );

	debug = ( argc > 5 ) ? atoi( argv[ DEBUG_INDEX ] ) : 0 ;
	
	gettimeofday( &start, NULL );
	strassen2( N, a, b, c );
	gettimeofday( &end, NULL );

	correct = checkAnswer( N, c, answer, debug );
//	printf( "Answer is (%d): %s\n", correct, (correct? "correct" : "incorrect") );
	exetime = ( end.tv_sec - start.tv_sec ) + ( end.tv_usec - start.tv_usec ) / 1000000.0;
//	printf( "Execution time is %.0f microseconds\n", exetime );
	printf( "%d %.6f\n", correct, exetime );

	free( a );
	free( b );
	free( c );
	free( answer );
	return 0;
}