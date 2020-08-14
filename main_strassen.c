#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "matrixUtil.h"
#include "./strassen.h"
#include "msrUtil.c"

#define N_INDEX 1
#define M1_INDEX 2
#define M2_INDEX 3
#define ANSWER_INDEX 4
#define DEBUG_INDEX 5
#define NUM_THREADS 7 //change to 7

int main( int argc, char *argv[] )
{
	int N, correct, debug;
	double exetime;
	struct timeval start, end;

  // msr setup
  struct msr_batch_array read_batch,write_batch, zero_batch;
  struct msr_batch_op start_op[ NUM_READ_MSRS * NUM_THREADS ], stop_op[ NUM_READ_MSRS * NUM_THREADS ], write_op[ NUM_WRITE_MSRS * NUM_THREADS ], zero_op[ NUM_ZERO_MSRS * NUM_THREADS ];
  struct msr_deltas deltas[ NUM_THREADS ], avg;
  int fd = open_msr_fd();
  write_batch.numops = NUM_WRITE_MSRS * NUM_THREADS;
  write_batch.ops = write_op;

  read_batch.numops = NUM_READ_MSRS * NUM_THREADS;
  read_batch.ops = start_op;

  zero_batch.numops = NUM_ZERO_MSRS * NUM_THREADS;
  zero_batch.ops = zero_op;

  write_perf_count_off( fd, NUM_THREADS, &write_batch );
  zero_counter( fd, NUM_THREADS, &zero_batch );

	N = atoi( argv[ N_INDEX ] );

	double *a = ( double * ) malloc( N * N * sizeof( double ));
	double *b = ( double * ) malloc( N * N * sizeof( double ));
	double *c = ( double * ) malloc( N * N * sizeof( double ));
	double *answer = ( double * ) malloc( N * N * sizeof( double ));
	
	readMatrixFromFile( argv[ M1_INDEX ], a );
	readMatrixFromFile( argv[ M2_INDEX ], b );
	readMatrixFromFile( argv[ ANSWER_INDEX ], answer );

	debug = ( argc > 5 ) ? atoi( argv[ DEBUG_INDEX ] ) : 0 ;
	
	//gettimeofday( &start, NULL );
	write_perf_count_on( fd, NUM_THREADS, &write_batch );
  read_msrs( fd, NUM_THREADS, &read_batch);

	//strassen_thread_spawn( N, a, b, c );
	strassen_thread_spawn_intrinsics( N, a, b, c );
	//gettimeofday( &end, NULL );

  write_perf_count_off( fd, NUM_THREADS, &write_batch );
  read_batch.ops = stop_op;
  read_msrs( fd, NUM_THREADS, &read_batch );

  get_msrdata( NUM_THREADS, start_op, stop_op, deltas );
  //print_msrdelta( NUM_THREADS, deltas );
  msrdelta_avg( NUM_THREADS, deltas, &avg );
  print_avg( &avg );

	correct = checkAnswer( N, c, answer, debug );
//	printf( "Answer is (%d): %s\n", correct, (correct? "correct" : "incorrect") );
	exetime = ( end.tv_sec - start.tv_sec ) + ( end.tv_usec - start.tv_usec ) / 1000000.0;
//	printf( "Execution time is %.0f microseconds\n", exetime );
	//printf( "%d \n", correct );

	free( a );
	free( b );
	free( c );
	free( answer );
	return 0;
}
