#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "../msr-safe/msr_safe.h"

#define PRINTED_FREQ 2.6
#define NUM_READ_MSRS 5
#define NUM_WRITE_MSRS 4
#define NUM_ZERO_MSRS 5

struct msr_deltas {
  uint64_t retired_instruct;
  uint64_t cache_access;
  uint64_t cache_miss;
  uint64_t aperf;
  uint64_t mperf;
  double instruct_per_cycle;
  double cache_miss_per_instruct;
  double freq;
  double time;
};


int open_msr_fd(); 

void read_msrs( int fd, int num_cpus, struct msr_batch_array *batch );

void write_perf_count_on( int fd, int num_cpus, struct msr_batch_array *batch );

void write_perf_count_off( int fd, int num_cpus, struct msr_batch_array *batch );

void zero_counter( int fd, int num_cpus, struct msr_batch_array *batch );

void get_msrdata( int num_cpus, struct msr_batch_op begin[], struct msr_batch_op end[], struct msr_deltas delta[]); 

void print_msrdelta( int num_cpus, struct msr_deltas delta[] ); 

void print_debug( int num_cpus, struct msr_batch_op start[], struct msr_batch_op stop[] ); 
