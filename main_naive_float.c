#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>

#include "matrixUtil.h"
#include "naive.h"
#include "msrUtil.h"

#define N_INDEX 1
#define M1_INDEX 2
#define M2_INDEX 3
#define ANSWER_INDEX 4
#define DEBUG_INDEX 6
#define NUM_THREADS_INDEX 5


int main( int argc, char *argv[] )
{
	int N, correct, debug, num_threads, step;
	long t;
	double exetime;
	struct timeval start, end;
	void *status;

	N = atoi( argv[ N_INDEX ] );

  // pthreads setup
	num_threads = atoi( argv[ NUM_THREADS_INDEX ] );
	pthread_t threads[ num_threads ];
	struct thread_info_float thread_info_array[ num_threads ];
	pthread_attr_t attr;
	int rc;

  // msr setup
  struct msr_batch_array read_batch,write_batch, zero_batch;
  struct msr_batch_op start_op[ NUM_READ_MSRS * num_threads ], stop_op[ NUM_READ_MSRS * num_threads ], write_op[ NUM_WRITE_MSRS * num_threads ], zero_op[ NUM_ZERO_MSRS * num_threads ];
  struct msr_deltas deltas[ num_threads ];
  int fd = open_msr_fd();
  write_batch.numops = NUM_WRITE_MSRS * num_threads;
  write_batch.ops = write_op;

  read_batch.numops = NUM_READ_MSRS * num_threads;
  read_batch.ops = start_op;

  zero_batch.numops = NUM_ZERO_MSRS * num_threads;
  zero_batch.ops = zero_op;

  write_perf_count_off( fd, num_threads, &write_batch );
  zero_counter( fd, num_threads, &zero_batch );

	float *a = ( float * ) malloc( N * N * sizeof( float ));
	float *b = ( float * ) malloc( N * N * sizeof( float ));
	float *c = ( float * ) malloc( N * N * sizeof( float ));
	float *answer = ( float * ) malloc( N * N * sizeof( float ));
	
	readMatrixFromFile_float( argv[ M1_INDEX ], a );
	readMatrixFromFile_float( argv[ M2_INDEX ], b );
	readMatrixFromFile_float( argv[ ANSWER_INDEX ], answer );

	debug = ( argc > 6 ) ? atoi( argv[ DEBUG_INDEX ] ) : 0 ;

	pthread_attr_init( &attr );
	pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
	
	//gettimeofday( &start, NULL );
	write_perf_count_on( fd, num_threads, &write_batch );
  read_msrs( fd, num_threads, &read_batch);

	step = ceil( N / ( double ) num_threads );

	for( t = 0; t < num_threads; t++ ) {
		thread_info_array[t].size = N;
		thread_info_array[t].m1 = a;
	        thread_info_array[t].m2 = b;
		thread_info_array[t].answer = c;
		thread_info_array[t].start = step * t;
		thread_info_array[t].end = ( t != num_threads - 1) ? ( step * ( t + 1 ) ) : N ;	
//		printf( "Thread t=%ld	start=%d 	end=%d", t, thread_info_array[t].start, thread_info_array[t].end );
		rc = pthread_create( &threads[t], &attr, naiveMultiply_parallel_float, (void *)&thread_info_array[t] );
		if (rc) {
			printf( "ERROR; return code from pthread_craete() is %d\n", rc );
			exit( -1 );
		}
	}

	for( t = 0; t < num_threads; t++ ) {
		rc = pthread_join( threads[t], &status);
		if (rc) {
			printf( "ERROR; return code from pthread_join() is %d\n", rc );
			exit( -1 );
		}
	}

	//gettimeofday( &end, NULL );
  write_perf_count_off( fd, num_threads, &write_batch );
  read_batch.ops = stop_op;
  read_msrs( fd, num_threads, &read_batch );

  get_msrdata( num_threads, start_op, stop_op, deltas );
  print_msrdelta( num_threads, deltas );

	pthread_attr_destroy( &attr );

	correct = checkAnswer_float( N, c, answer, debug );
//	printf( "Answer is (%d): %s\n", correct, (correct? "correct" : "incorrect") );
	//exetime = ( end.tv_sec - start.tv_sec ) + ( end.tv_usec - start.tv_usec ) / 1000000.0;
//	printf( "Execution time is %.0f microseconds\n", exetime );
	//printf( "%d %.6f\n", correct, exetime );
	printf( "%d\n", correct );

	free( a );
	free( b );
	free( c );
	free( answer );
	return 0;
}
