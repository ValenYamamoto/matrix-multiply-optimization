#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "msrUtil.h"

#define DEBUG 0

void get_msrdata( int num_cpus, struct msr_batch_op begin[], struct msr_batch_op end[], struct msr_deltas delta[]) {
  int i;
  for( i = 0; i < num_cpus; i++ ) {
    delta[i].retired_instruct = end[ NUM_READ_MSRS * i ] - begin[ NUM_READ_MSRS * i ];
    delta[i].cache_access = end[ NUM_READ_MSRS * i + 1] - begin[ NUM_READ_MSRS * i + 1 ];
    delta[i].cache_miss = end[ NUM_READ_MSRS * i + 2] - begin[ NUM_READ_MSRS * i + 2];
    delta[i].aperf = end[ NUM_READ_MSRS * i + 3 ] - begin[ NUM_READ_MSRS * i + 3 ];
    delta[i].mperf = end[ NUM_READ_MSRS * i + 4] - begin[ NUM_READ_MSRS * i + 4 ];

}

void read_msrs( int fd, int num_cpus, struct msr_batch_array *batch ) {
  struct msr_batch_op op[ num_cpus * NUM_READ_MSRS ];
  batch->ops = op; 
  batch->numops = num_cpus * NUM_READ_MSRS;
  int i, j, rc;
	for( i=0; i<num_cpus; i++ ){
    for ( j = 0; j < NUM_READ_MSRS; j++ ) {
      batch->ops[NUM_READ_MSRS*i+j].cpu = i;	
      batch->ops[NUM_READ_MSRS*i+j].isrdmsr = 1;	
      batch->ops[NUM_READ_MSRS*i+j].err = 0;	
      batch->ops[NUM_READ_MSRS*i+j].msr = READ_MSRS[ j ];	
      batch->ops[NUM_READ_MSRS*i+j].msrdata = 0;	
      batch->ops[NUM_READ_MSRS*i+j].wmask = 0;	
    }
	}
	rc = ioctl( fd, X86_IOC_MSR_BATCH, batch );
	assert( rc != -1 );
}

void write_perf_count_on( int fd, int num_cpus, struct msr_batch_array *batch ) {
  struct msr_batch_op op[ num_cpus * NUM_WRITE_MSRS ];
  batch->ops = op; 
  batch->numops = num_cpus * NUM_WRITE_MSRS;
  int i, j, rc;
	for( i=0; i<num_cpus; i++ ){
    for ( j = 0; j < NUM_WRITE_MSRS; j++ ) {
      batch->ops[NUM_WRITE_MSRS*i+j].cpu = i;	
      batch->ops[NUM_WRITE_MSRS*i+j].isrdmsr = 0;	
      batch->ops[NUM_WRITE_MSRS*i+j].err = 0;	
      batch->ops[NUM_WRITE_MSRS*i+j].msr = WRITE_MSRS_ON[ j ];	
      batch->ops[NUM_WRITE_MSRS*i+j].msrdata = WRITE_ON_VALUES[ j ];	
      batch->ops[NUM_WRITE_MSRS*i+j].wmask = WRITE_ON_MASKS[ j ];	
    }
	}
	rc = ioctl( fd, X86_IOC_MSR_BATCH, batch );
	assert( rc != -1 );
}

void write_perf_count_off( int fd, int num_cpus, struct msr_batch_array *batch ) {

  struct msr_batch_op op[ num_cpus * NUM_WRITE_MSRS ];
  batch->ops = op; 
  batch->numops = num_cpus * NUM_WRITE_MSRS;
  int i, j, rc;
	for( i=0; i<num_cpus; i++ ){
    for ( j = 0; j < NUM_WRITE_MSRS; j++ ) {
      batch->ops[NUM_WRITE_MSRS*i+j].cpu = i;	
      batch->ops[NUM_WRITE_MSRS*i+j].isrdmsr = 0;	
      batch->ops[NUM_WRITE_MSRS*i+j].err = 0;	
      batch->ops[NUM_WRITE_MSRS*i+j].msr = WRITE_MSRS_OFF[ j ];	
      batch->ops[NUM_WRITE_MSRS*i+j].msrdata = 0x0000000000000000;	
      batch->ops[NUM_WRITE_MSRS*i+j].wmask = WRITE_OFF_MASKS[ j ];	
    }
	}
	rc = ioctl( fd, X86_IOC_MSR_BATCH, batch );
	assert( rc != -1 );
}

void zero_counter( int fd, int num_cpus, struct msr_batch_array *batch ) {
  struct msr_batch_op op[ num_cpus * NUM_ZERO_MSRS ];
  batch->ops = op; 
  batch->numops = num_cpus * NUM_ZERO_MSRS;
  int i, j, rc;
	for( i=0; i<num_cpus; i++ ){
    for ( j = 0; j < NUM_ZERO_MSRS; j++ ) {
      batch->ops[NUM_ZERO_MSRS*i+j].cpu = i;	
      batch->ops[NUM_ZERO_MSRS*i+j].isrdmsr = 0;	
      batch->ops[NUM_ZERO_MSRS*i+j].err = 0;	
      batch->ops[NUM_ZERO_MSRS*i+j].msr = ZERO_MSRS[ j ];	
      batch->ops[NUM_ZERO_MSRS*i+j].msrdata = 0;	
      batch->ops[NUM_ZERO_MSRS*i+j].wmask = 0;	
    }
	}
	rc = ioctl( fd, X86_IOC_MSR_BATCH, batch );
	assert( rc != -1 );
}

int main() {
  return 0;
}
