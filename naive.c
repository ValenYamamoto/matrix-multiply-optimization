#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <smmintrin.h>
#include <xmmintrin.h>

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

void naiveMultiply_float( int n, float *m1, float *m2, float *result )
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

// better?
void* naiveMultiply_parallel_better( void *thread_args )
{
	int i, j, k, start, end;

	struct thread_info *args = ( struct thread_info * ) thread_args;
	double *m1 = args->m1;
	double *m2 = args->m2;
	double *result = args->answer;

	long n = args->size;
	start = args->start;
	end = args->end;

	double a0, a1, a2, a3;


	for ( i = start; i < end; i++ ) 
	{
		for ( k = 0; k < n; k+=4 ) 
		{
			a0 = *( m1 + n * i + k );
			if ( k + 1 < n) { 
				a1 = *( m1 + n * i + (k+1) );
			} else {
				a1 = 0;
			}
			if ( k + 2 < n) { 
				a2 = *( m1 + n * i + (k+2) );
			} else {
				a2 = 0;
			}
			if ( k + 3 < n) { 
				a3 = *( m1 + n * i + (k+3) );
			} else {
				a3 = 0;
			}
			for ( j = 0; j < n; j++ )
			{
				*( result + n * i + j ) += a0 * *( m2 + n * k + j ); 
				if ( k + 1 < n ) {
					*( result + n * i + j ) += a1 * *( m2 + n * (k+1) + j ) 
				}
				if( k + 2 < n ) {
					*( result + n * i + j ) += a2 * *( m2 + n * (k+2) + j ) 
				}
				if( k + 3 < n ) {
					*( result + n * i + j ) += a3 * *( m2 + n * (k+3) + j );
				}
			}
		}
	}
	pthread_exit( NULL );
}

void* naiveMultiply_parallel_float( void *thread_args )
{
	int i, j, k, start, end;
	float sum;

	struct thread_info_float *args = ( struct thread_info_float * ) thread_args;
	float *m1 = args->m1;
	float *m2 = args->m2;
	float *result = args->answer;

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

void* naiveMultiply_parallel_intrinsics( void *thread_args )
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

  double a[2], b[2], c[2];

	for ( i = start; i < end; i++ ) 
	{
		for ( j = 0; j < n; j++ ) 
		{
			sum = 0;
			for ( k = 0; k < n; k+=2 )
			{
				//sum += *( m1 + n * i + k ) * *( m2 + n * k + j );
        a[0] = *( m1 + n * i + k ); 
        b[0] = *( m2 + n * k + j );
        if( k + 1 < n ) {
          a[1] = *( m1 + n * i + (k+1) ); 
          b[1] = *( m2 + n * (k+1) + j );
        } else {
          a[1] = 0;
          b[1] = 0;
        }
        dp_double( a, b, c );
        sum += c[0];
			}
			*( result + n * i + j) = sum;
		}
	}
	pthread_exit( NULL );
}
//better? i little i guess
void* naiveMultiply_parallel_intrinsics_better( void *thread_args )
{
	int i, j, k, start, end;

	struct thread_info *args = ( struct thread_info * ) thread_args;
	double *m1 = args->m1;
	double *m2 = args->m2;
	double *result = args->answer;

	long n = args->size;
	start = args->start;
	end = args->end;

  double a1[2], a2[2], b1[2], b2[2], c[2];

  __m128d t0, t1, t2, t3;

  j = 0;
	for ( i = start; i < end; i++ ) 
	{
		for ( k = 0; k < n; k+=4 ) 
		{
			//sum = 0;
      a1[0] = *( m1 + n * i + k ); 
      if( k + 1 < n ) {
        a1[1] = *( m1 + n * i + (k+1) ); 
      } else {
        a1[1] = 0;
      }
      if( k + 2 < n ) {
        a2[0] = *( m1 + n * i + (k+2) ); 
      } else {
        a2[0] = 0;
      }
      if( k + 3 < n ) {
        a2[1] = *( m1 + n * i + (k+3) ); 
      } else {
        a2[1] = 0;
      }
      t0 = _mm_load_pd( a1 );
      t2 = _mm_load_pd( a2 );
			for ( j = 0; j < n; j++ )
			{
        b1[0] = *( m2 + n * k + j );
        if( k + 1 < n ) {
          b1[1] = *( m2 + n * (k+1) + j );
        } else {
          b1[1] = 0;
        }
        if( k + 2 < n ) {
          b2[0] = *( m2 + n * (k+2) + j );
        } else {
          b2[0] = 0;
        }
        if( k + 3 < n ) {
          b2[1] = *( m2 + n * (k+3) + j );
        } else {
          b2[1] = 0;
        }
        t1 = _mm_load_pd(b1);
        t3 = _mm_load_pd(b2);
        t1 = _mm_dp_pd(t0, t1, 0xff);
        t3 = _mm_dp_pd(t2, t3, 0xff);

        _mm_store_pd(c, t1);
        *( result + n * i + j ) += c[0];

        _mm_store_pd(c, t3);
        *( result + n * i + j ) += c[0];
			}
			//*( result + n * i + j) = sum;
		}
	}
	pthread_exit( NULL );
}
