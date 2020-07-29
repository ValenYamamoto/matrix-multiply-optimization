#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "matrixUtil.h"
#include "naive.h"
#include "msrUtil.h"

#define N_INDEX 1
#define M1_INDEX 2
#define M2_INDEX 3
#define ANSWER_INDEX 4
#define DEBUG_INDEX 5

int main( int argc, char *argv[] )
{
	int N, correct, debug, fd;
	//double exetime;
	//struct timeval start, end;
  struct msr_batch_array read_batch, write_batch, zero_batch;
  struct msr_batch_op start_op[ NUM_READ_MSRS ], stop_op[ NUM_READ_MSRS ], write_op[ NUM_WRITE_MSRS ], zero_op[ NUM_ZERO_MSRS ];
  struct msr_deltas deltas[1];

	N = atoi( argv[ N_INDEX ] );

	double *a = ( double * ) malloc( N * N * sizeof( double ));
	double *b = ( double * ) malloc( N * N * sizeof( double ));
	double *c = ( double * ) malloc( N * N * sizeof( double ));
	double *answer = ( double * ) malloc( N * N * sizeof( double ));
	
	readMatrixFromFile( argv[ M1_INDEX ], a );
	readMatrixFromFile( argv[ M2_INDEX ], b );
	readMatrixFromFile( argv[ ANSWER_INDEX ], answer );

	debug = ( argc > 5 ) ? atoi( argv[ DEBUG_INDEX ] ) : 0 ;
	
  // msr setup
  fd = open_msr_fd();
  write_batch.numops = NUM_WRITE_MSRS;
  write_batch.ops = write_op;

  read_batch.numops = NUM_READ_MSRS;
  read_batch.ops = start_op;

  zero_batch.numops = NUM_ZERO_MSRS;
  zero_batch.ops = zero_op;

  write_perf_count_off( fd, 1, &write_batch ); 
  zero_counter( fd, 1, &zero_batch );
  write_perf_count_on( fd, 1, &write_batch ); 
  read_msrs( fd, 1, &read_batch );

	//gettimeofday( &start, NULL );
	naiveMultiply( N, a, b, c );
	//gettimeofday( &end, NULL );

  write_perf_count_off( fd, 1, &write_batch );
  read_batch.ops = stop_op;
  read_msrs( fd, 1, &read_batch );

  get_msrdata( 1, start_op, stop_op, deltas );
  print_msrdelta( 1, deltas );
  //print_debug( 1, start_op, stop_op );

	correct = checkAnswer( N, c, answer, debug );
//	printf( "Answer is (%d): %s\n", correct, (correct? "correct" : "incorrect") );
	//exetime = ( end.tv_sec * 1000000 + end.tv_usec ) - ( start.tv_sec * 1000000 + start.tv_usec );
//	printf( "Execution time is %.0f microseconds\n", exetime );

	free( a );
	free( b );
	free( c );
	free( answer );
	return 0;
}
