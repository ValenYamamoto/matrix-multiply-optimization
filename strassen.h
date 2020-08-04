void strassen( int n, double *m1, double *m2, double *answer );

void strassen2( int n, double *m1, double *m2, double *answer );

void strassen3( int n, double *m1, double *m2, double *answer );

void strassen4( int n, double *m1, double *m2, double *answer );

void *strassen_parallel_thread_func( void *thread_args );

void strassen_thread_spawn( int n, double *m1, double *m2, double *answer );
