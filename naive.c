#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

#include "matrixUtil.h"



#if 0
// argv: [1] = N, [2] = a file, [3] = b file, [4] = answer file
int main(int argc, char *argv[])
{

	int i, j, N;
	double exetime;
	struct timeval start, end;
        
	if ( argc == 1 ) 
		N = 4; // default matrix size to 4
	else
		N = atoi(argv[1]);

	double *a = ( double * ) malloc( N * N * sizeof( double ));
	double *b = ( double * ) malloc( N * N * sizeof( double ));
	double *c = ( double * ) malloc( N * N * sizeof( double ));

//	srand(time(0));
		
//	generateMatrix( N, a );
//	generateMatrix( N, b );
	readMatrixFile( argv[2], a );
	readMatrixFile( argv[2], a );
	readMatrixFile( argv[2], a );
	/*
	printf( "arrays A and B\n" );
	for ( i = 0; i < N * N; i++ ) 
		printf( "%.0f	%.0f\n", *(a+i), *(b+i) );
	*/

	gettimeofday(&start, NULL);
	naiveMultiply( N, a, b, c );
	gettimeofday(&end, NULL);

	/*
	printf( "Array C\n" );
	for ( i = 0; i < N; i++ )
		for ( j = 0; j < N; j++ )
			printf( "%.0f\n",  *( c + N * i + j) );
	*/

	exetime = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
	printf( "Execution time is: %f microseconds\n", exetime );

	free(a);
	free(b);
	free(c);
	return 0;
}
#endif
// multiply two nxn matrices together
void naiveMultiply( int n, double *m1, double *m2, double *result )
{
	int i, j, k;
	double sum;

	for ( i = 0; i < n; i++ ) 
	{
		for ( j = 0; j < n; j++ ) 
		{
			sum = 0;
			for ( k = 0; k < n; k++ )
			{
				sum += *( m1 + n * i + k ) * *( m2 + n * k + j );
			}
			*( result + n * i + j) = sum;
		}
	}
}


void* naiveMultiply_parallel( void *thread_args )
{
	int i, j, k, start, end;
	double sum;

	struct thread_info *args = ( struct thread_info * ) thread_args;
	double *m1 = args->m1;
	double *m2 = args->m2;
	double *result = args->answer;

	long n = args->size;
	start = args->start;
	end = args->end;


	for ( i = start; i < end; i++ ) 
	{
		for ( j = 0; j < n; j++ ) 
		{
			sum = 0;
			for ( k = 0; k < n; k++ )
			{
				sum += *( m1 + n * i + k ) * *( m2 + n * k + j );
			}
			*( result + n * i + j) = sum;
		}
	}
	pthread_exit( NULL );
}
