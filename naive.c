#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


void naiveMultiply( int n, float *m1, float *m2, float *result );


int main(int argc, char *argv[])
{

	int i, j, N;
	float exetime;
	struct timeval start, end;
        
	if ( argc == 1 ) 
		N = 4; // default matrix size to 4
	else
		N = atoi(argv[1]);

	float *a = ( float * ) malloc( N * N * sizeof( float ));
	float *b = ( float * ) malloc( N * N * sizeof( float ));
	float *c = ( float * ) malloc( N * N * sizeof( float ));

	srand(1); // for testing purposes

	for ( i = 0; i < N * N; i++ ) {
		*(a + i) = rand() % 50; // mod 50 just for testing purposes
		*(b + i) = rand() % 50;
	}

	printf( "arrays A and B\n" );
	for ( i = 0; i < N * N; i++ ) 
		printf( "%.0f	%.0f\n", *(a+i), *(b+i) );

	gettimeofday(&start, NULL);
	naiveMultiply( N, a, b, c );
	gettimeofday(&end, NULL);

	printf( "Array C\n" );
	for ( i = 0; i < N; i++ )
		for ( j = 0; j < N; j++ )
			printf( "%.0f\n",  *( c + N * i + j) );

	exetime = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
	printf( "Execution time is: %f microseconds\n", exetime );

	free(a);
	free(b);
	free(c);
	return 0;
}

// multiply two nxn matrices together
void naiveMultiply( int n, float *m1, float *m2, float *result )
{
	int i, j, k;
	float sum;

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

