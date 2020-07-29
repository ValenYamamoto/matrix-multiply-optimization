#include "../msr-safe/msr_safe.h"

#define NUM_READ_MSRS 5
#define NUM_WRITE_MSRS 4
#define NUM_ZERO_MSRS 3

struct msr_deltas {
  uint64_t retired_instruct;
  uint64_t cache_access;
  uint64_t cache_miss;
  uint64_t aperf;
  uint64_t mperf;
};

__u32 READ_MSRS[] = { 0x309, 0xC1, 0xC2, 0x30A, 0x30B }; // FIXED_CTR0, PMC0, PMC1, APERF, MPERF

__u32 WRITE_MSRS_ON[] = { 0x38D, 0x38F, 0x186, 0x187 }; // FIXED_CTR_CTRL, PERF_GLOBAL_CTRL, PERFEVTSEL0, PERFEVTSEL1
__u64 WRITE_ON_VALUES[] = { 0x222, 0x0000000700000003, 0x0434F2E, 0x043412E };
__u64 WRITE_ON_MASKS[] = { 0xbbb, 0x0000000700000003, 0x00000000ffffffff, 0x00000000ffffffff };

__u64 WRITE_MSRS_OFF[] = { 0x38D, 0x38F, 0x186, 0x187 };
__u64 WRITE_OFF_MASKS[] = { 0xbbb, 0x0000000700000003, 0x00000000ffffffff, 0x0 };

__u32 ZERO_MSRS[] = { 0x309, 0xC1, 0xC2 }; // FIXED_CTR0, PMC0, PMC1

void read_msrs( int fd, int num_cpus, struct msr_batch_array *batch );

void write_perf_count_on( int fd, int num_cpus, struct msr_batch_array *batch );

void write_perf_count_off( int fd, int num_cpus, struct msr_batch_array *batch );

void zero_counter( int fd, int num_cpus, struct msr_batch_array *batch );
