void naiveMultiply( int n, double *m1, double *m2, double *result );

void naiveMultiply_float( int n, float *m1, float *m2, float *result );

void *naiveMultiply_parallel( void *thread_args );

void *naiveMultiply_parallel_better( void *thread_args );

void *naiveMultiply_parallel_float( void *thread_args );

void* naiveMultiply_parallel_intrinsics( void *thread_args );

void* naiveMultiply_parallel_intrinsics_better( void *thread_args );
