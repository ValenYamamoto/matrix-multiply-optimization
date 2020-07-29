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


static __u32 READ_MSRS[] = { 0x309, 0xC1, 0xC2, 0x30A, 0x30B }; // FIXED_CTR0, PMC0, PMC1, APERF, MPERF

static __u32 WRITE_MSRS_ON[] = { 0x38D, 0x38F, 0x186, 0x187 }; // FIXED_CTR_CTRL, PERF_GLOBAL_CTRL, PERFEVTSEL0, PERFEVTSEL1
static __u64 WRITE_ON_VALUES[] = { 0x222, 0x0000000700000003, 0x0434F2E, 0x043412E };
static __u64 WRITE_ON_MASKS[] = { 0xbbb, 0x0000000700000003, 0x00000000ffffffff, 0x00000000ffffffff };

static __u64 WRITE_MSRS_OFF[] = { 0x38D, 0x38F, 0x186, 0x187 };
static __u64 WRITE_OFF_MASKS[] = { 0xbbb, 0x0000000700000003, 0x00000000ffffffff, 0x0 };

static __u32 ZERO_MSRS[] = { 0x309, 0xC1, 0xC2, 0x30A, 0x30B }; // FIXED_CTR0, PMC0, PMC1, FIXED_CTR1, FIRXED_CTR2


int open_msr_fd() {
  return open( "/dev/cpu/msr_batch", O_RDWR );
}

void get_msrdata( int num_cpus, struct msr_batch_op begin[], struct msr_batch_op end[], struct msr_deltas delta[]) {
  int i;
  for( i = 0; i < num_cpus; i++ ) {
    delta[i].retired_instruct = (uint64_t)end[ NUM_READ_MSRS * i ].msrdata - (uint64_t)begin[ NUM_READ_MSRS * i ].msrdata;
    delta[i].cache_access = (uint64_t)end[ NUM_READ_MSRS * i + 1].msrdata - (uint64_t)begin[ NUM_READ_MSRS * i + 1 ].msrdata;
    delta[i].cache_miss = (uint64_t)end[ NUM_READ_MSRS * i + 2].msrdata - (uint64_t)begin[ NUM_READ_MSRS * i + 2].msrdata;
    delta[i].aperf = (uint64_t)end[ NUM_READ_MSRS * i + 3 ].msrdata - (uint64_t)begin[ NUM_READ_MSRS * i + 3 ].msrdata;
    delta[i].mperf = (uint64_t)end[ NUM_READ_MSRS * i + 4].msrdata - (uint64_t)begin[ NUM_READ_MSRS * i + 4 ].msrdata;
    delta[i].instruct_per_cycle = delta[i].retired_instruct / (double) delta[i].aperf;
    delta[i].cache_miss_per_instruct = delta[i].cache_miss / (double) delta[i].retired_instruct;
    delta[i].freq = PRINTED_FREQ * delta[i].aperf / (double) delta[i].mperf;
    delta[i].time = delta[i].aperf / delta[i].freq / 1E9;
  }
}

void print_msrdelta( int num_cpus, struct msr_deltas delta[] ) {
  int i;
  for( i = 0; i < num_cpus; i++ ) {
    printf( "CPU: %2d   %25s: %" PRIu64 "\n", i, "Retired Instructions", delta[i].retired_instruct );
    printf( "          %25s: %" PRIu64 "\n", "Cache access", delta[i].cache_access );
    printf( "          %25s: %" PRIu64 "\n", "Cache Misses", delta[i].cache_miss );
    printf( "          %25s: %" PRIu64 "\n", "APERF", delta[i].aperf );
    printf( "          %25s: %" PRIu64 "\n", "MPERF", delta[i].mperf );
    printf( "          %25s: %.6lf\n", "Instruction / cycle", delta[i].instruct_per_cycle );
    printf( "          %25s: %.6lf\n", "Cache miss / instruction", delta[i].cache_miss_per_instruct );
    printf( "          %25s: %.6lf\n", "Freq", delta[i].freq );
    printf( "          %25s: %.6lf\n", "Time", delta[i].time );
    printf( "\n" );
  }
}

void print_debug( int num_cpus, struct msr_batch_op start[], struct msr_batch_op stop[] ) {
  int i;
  for( i = 0; i < num_cpus; i++ ) {
    printf( "CPU: %2d   %20s: %" PRIu64 "   %" PRIu64 "\n", i, "Retired Instructions", (uint64_t)start[i].msrdata, (uint64_t)stop[i].msrdata );
    printf( "          %20s: %" PRIu64 "    %" PRIu64 "\n", "Cache access", (uint64_t)start[i+1].msrdata, (uint64_t)stop[i+1].msrdata );
    printf( "          %20s: %" PRIu64 "    %" PRIu64 "\n", "Cache Misses", (uint64_t)start[i+2].msrdata, (uint64_t)stop[i+2].msrdata );
    printf( "          %20s: %" PRIu64 "    %" PRIu64 "\n", "APERF", (uint64_t)start[i+3].msrdata, (uint64_t)stop[i+3].msrdata );
    printf( "          %20s: %" PRIu64 "    %" PRIu64 "\n", "MPERF", (uint64_t)start[i+4].msrdata, (uint64_t)stop[i+4].msrdata );
    printf( "\n" );
  }
}

void read_msrs( int fd, int num_cpus, struct msr_batch_array *batch ) {
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
  if (DEBUG) {
    print_debug(1, batch->ops, batch->ops );
  }
}

void write_perf_count_on( int fd, int num_cpus, struct msr_batch_array *batch ) {
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

#if DEBUG  
int main() {
  int i, j;
  struct msr_batch_array batch;
  struct msr_batch_op start[ NUM_READ_MSRS ], stop[ NUM_READ_MSRS ], write[ NUM_WRITE_MSRS ], zero[ NUM_ZERO_MSRS ];
  struct msr_deltas delta[1];

  int fd = open( "/dev/cpu/msr_batch", O_RDWR );

  batch.ops = write;
  batch.numops = NUM_WRITE_MSRS;
  write_perf_count_off( fd, 1, &batch );

  batch.ops = zero;
  batch.numops = NUM_ZERO_MSRS;
  zero_counter( fd, 1, &batch );

  batch.ops = write;
  batch.numops = NUM_WRITE_MSRS;
  write_perf_count_on( fd, 1, &batch );

  batch.ops = start;
  batch.numops = NUM_READ_MSRS;
  read_msrs( fd, 1, &batch );

  for (i = 0; i < 10000; i++ )  {
    j ++;
  }

  batch.ops = write;
  batch.numops = NUM_WRITE_MSRS;
  write_perf_count_off( fd, 1, &batch );
  batch.ops = stop;
  batch.numops = NUM_READ_MSRS;
  read_msrs( fd, 1, &batch );

  get_msrdata( 1, start, stop, delta );
  print_msrdelta( 1, delta );

  return 0;
}
#endif
