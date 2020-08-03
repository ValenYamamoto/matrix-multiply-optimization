#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "./matrixUtil.h"
#include "./strassen.h"

#define DEBUG_SPLIT 0
#define DEBUG_INTER 0
#define DEBUG_RECUR 0
#define DEBUG_COMBINE 0

void strassen( int n, double *m1, double *m2, double *answer ) {

  // base case n = 1
  if( n == 1 ) {
    *answer = *m1 * *m2;
  } else {
    // split each into four mini matrices
    double *a = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *b = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *c = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *d = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *e = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *f = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *g = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *h = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    split( n, 1, m1, a );
    split( n, 2, m1, b );
    split( n, 3, m1, c );
    split( n, 4, m1, d );
    split( n, 1, m2, e );
    split( n, 2, m2, f );
    split( n, 3, m2, g );
    split( n, 4, m2, h );

    if ( DEBUG_SPLIT ) {
      printMatrix( n/2, a );
      printMatrix( n/2, b );
      printMatrix( n/2, c );
      printMatrix( n/2, d );
    }

    // intermediate products and recursive calls
    double *p1 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p2 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p3 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p4 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p5 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p6 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p7 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    double *inter0 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter1 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter2 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter3 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter4 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter5 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter6 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter7 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter8 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter9 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    subtractMatrix( n/2, f, h, inter0 );
    addMatrix( n/2, a, b, inter1 );
    addMatrix( n/2, c, d, inter2 );
    subtractMatrix( n/2, g, e, inter3 );
    addMatrix( n/2, a, d, inter4 );
    addMatrix( n/2, e, h, inter5 );
    subtractMatrix( n/2, b, d, inter6 );
    addMatrix( n/2, g, h, inter7);
    subtractMatrix( n/2, a, c, inter8 );
    addMatrix( n/2, e, f, inter9 );

    if ( DEBUG_INTER ) {
      printMatrix( n/2, inter0 );
      printMatrix( n/2, inter1 );
      printMatrix( n/2, inter2 );
      printMatrix( n/2, inter3 );
      printMatrix( n/2, inter4 );
      printMatrix( n/2, inter5 );
      printMatrix( n/2, inter6 );
      printMatrix( n/2, inter7 );
      printMatrix( n/2, inter8 );
      printMatrix( n/2, inter9 );
    }
    strassen( n/2, a, inter0, p1 );
    strassen( n/2, inter1, h, p2 );
    strassen( n/2, inter2, e, p3 );
    strassen( n/2, d, inter3, p4 );
    strassen( n/2, inter4, inter5, p5 );
    strassen( n/2, inter6, inter7, p6 );
    strassen( n/2, inter8, inter9, p7 );

    if ( DEBUG_RECUR ) {
      printMatrix(n/2, p1 );
      printMatrix(n/2, p2 );
      printMatrix(n/2, p3 );
      printMatrix(n/2, p4 );
      printMatrix(n/2, p5 );
      printMatrix(n/2, p6 );
      printMatrix(n/2, p7 );
    }

    // combine into four mini matrices
    addMatrix( n/2, p5, p4, a );
    subtractMatrix( n/2, a, p2, a );
    addMatrix( n/2, a, p6, a );

    addMatrix( n/2, p1, p2, b );

    addMatrix( n/2, p3, p4, c );

    addMatrix( n/2, p1, p5, d );
    subtractMatrix( n/2, d, p3, d );
    subtractMatrix( n/2, d, p7, d );

    combine( n, a, b, c, d, answer );

    free( a );
    free( b );
    free( c );
    free( d );
    free( e );
    free( f );
    free( g );
    free( h );

    free( p1 );
    free( p2 );
    free( p3 );
    free( p4 );
    free( p5 );
    free( p6 );
    free( p7 );

    free( inter0 );
    free( inter1 );
    free( inter2 );
    free( inter3 );
    free( inter4 );
    free( inter5 );
    free( inter6 );
    free( inter7 );
    free( inter8 );
    free( inter9 );
  }
}

// second pass
void strassen2( int n, double *m1, double *m2, double *answer ) {

  // base case n = 1
  if( n == 1 ) {
    *answer = *m1 * *m2;
  } else {
    // split each into four mini matrices
    double *a = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *b = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *c = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *d = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *e = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *f = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *g = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *h = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    split( n, 1, m1, a );
    split( n, 2, m1, b );
    split( n, 3, m1, c );
    split( n, 4, m1, d );
    split( n, 1, m2, e );
    split( n, 2, m2, f );
    split( n, 3, m2, g );
    split( n, 4, m2, h );

    if ( DEBUG_SPLIT ) {
      printMatrix( n/2, e );
      printMatrix( n/2, f );
      printMatrix( n/2, g );
      printMatrix( n/2, h );
    }

    // intermediate products and recursive calls
    double *p2 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p5 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p6 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    double *inter = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    addMatrix( n/2, a, b, inter );
    strassen2( n/2, inter, h, p2 );

    addMatrix( n/2, g, h, inter );
    subtractMatrix( n/2, b, d, b );
    strassen2( n/2, b, inter, p6 );

    subtractMatrix( n/2, g, e, g );
    strassen2( n/2, d, g, b );

    subtractMatrix( n/2, f, h, inter );
    strassen2( n/2, a, inter, g);

    addMatrix( n/2, a, d, inter );
    addMatrix( n/2, e, h , h );
    strassen2( n/2, inter, h, p5 );

    addMatrix( n/2, c, d, inter );
    strassen2( n/2, inter, e, h );

    subtractMatrix( n/2, a, c, a );
    addMatrix( n/2, e, f, e );
    strassen2( n/2, a, e, d );

    if ( DEBUG_RECUR ) {
      printMatrix(n/2, b );
      printf("\n");
      printMatrix(n/2, p2 );
      printf("\n");
      printMatrix(n/2, h );
      printf("\n");
      printMatrix(n/2, b );
      printf("\n");
      printMatrix(n/2, p5 );
      printf("\n");
      printMatrix(n/2, p6 );
      printf("\n");
      printMatrix(n/2, d );
      printf("\n");
    }

    // combine into four mini matrices
    addMatrix( n/2, p5, b, a );
    subtractMatrix( n/2, a, p2, a );
    addMatrix( n/2, a, p6, a );

    addMatrix( n/2, g, p2, c );

    addMatrix( n/2, h, b, e );

    addMatrix( n/2, g, p5, f );
    subtractMatrix( n/2, f, h, f );
    subtractMatrix( n/2, f, d, f );

    if ( DEBUG_COMBINE ) {
      printMatrix( n/2, a );
      printf("\n");
      printMatrix( n/2, c );
      printf("\n");
      printMatrix( n/2, e );
      printf("\n");
      printMatrix( n/2, f );
      printf("\n");
    }
    combine( n, a, c, e, f, answer );

    free( a );
    free( b );
    free( c );
    free( d );
    free( e );
    free( f );
    free( g );
    free( h );

    free( p2 );
    free( p5 );
    free( p6 );

    free( inter );
  }
}

void strassen3( int n, double *m1, double *m2, double *answer ) {

  // base case n = 1
  if( n == 1 ) {
    *answer = *m1 * *m2;
  } else {
    // split each into four mini matrices
    double *a = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *d = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *e = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *h = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    split( n, 1, m1, a );
    split( n, 4, m1, d );
    split( n, 1, m2, e );
    split( n, 4, m2, h );

    if ( DEBUG_SPLIT ) {
      printMatrix( n/2, a );
      printMatrix( n/2, d );
      printMatrix( n/2, e );
      printMatrix( n/2, h );
    }

    // intermediate products and recursive calls
    double *p1 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p2 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p3 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p4 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p5 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p6 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p7 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    double *inter0 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter1 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter2 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter3 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter4 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter5 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter6 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter7 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter8 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter9 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    int i, j;
    //subtractMatrix( n/2, f, h, inter0 );
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
		    *( inter0 + (n/2) * i + j ) = *( m2 + n * i + j + (n/2) ) - *( m2 + n * (i + n/2) + j + (n/2) );
	    }
    }
    //addMatrix( n/2, a, b, inter1 );
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
		    *( inter1 + (n/2) * i + j ) = *( m1 + n * i + j ) + *( m1 + n * i + j + n/2 );
	    }
    }
    //addMatrix( n/2, c, d, inter2 );
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
		    *( inter2 + (n/2) * i + j ) = *( m1 + n * (i + n/2) + j ) + *( m1 + n * (i + n/2) + j + n/2 );
	    }
    }
    //subtractMatrix( n/2, g, e, inter3 );
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
		    *( inter3 + (n/2) * i + j ) = *( m2 + n * (i + n/2) + j ) - *( m2 + n * i + j );
	    }
    }
    //addMatrix( n/2, a, d, inter4 );
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
		    *( inter4 + (n/2) * i + j ) = *( m1 + n * i + j ) + *( m1 + n * (i + n/2) + j + n/2 );
	    }
    }
    //addMatrix( n/2, e, h, inter5 );
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
		    *( inter5 + (n/2) * i + j ) = *( m2 + n * i + j ) + *( m2 + n * (i + n/2) + j + n/2 );
	    }
    }
    //subtractMatrix( n/2, b, d, inter6 );
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
		    *( inter6 + (n/2) * i + j ) = *( m1 + n * i + j + n/2 ) - *( m1 + n * (i + n/2) + j + n/2 );
	    }
    }
    //addMatrix( n/2, g, h, inter7);
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
		    *( inter7 + (n/2) * i + j ) = *( m2 + n * (i + n/2) + j ) + *( m2 + n * (i + n/2) + j + n/2 );
	    }
    }
    //subtractMatrix( n/2, a, c, inter8 );
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
		    *( inter8 + (n/2) * i + j ) = *( m1 + n * i + j ) - *( m1 + n * (i + n/2) + j );
	    }
    }
    //addMatrix( n/2, e, f, inter9 );
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
		    *( inter9 + (n/2) * i + j ) = *( m2 + n * i + j ) + *( m2 + n * i + j + n/2 );
	    }
    }

    if ( DEBUG_INTER ) {
      printMatrix( n/2, inter0 );
      printMatrix( n/2, inter1 );
      printMatrix( n/2, inter2 );
      printMatrix( n/2, inter3 );
      printMatrix( n/2, inter4 );
      printMatrix( n/2, inter5 );
      printMatrix( n/2, inter6 );
      printMatrix( n/2, inter7 );
      printMatrix( n/2, inter8 );
      printMatrix( n/2, inter9 );
    }
    strassen( n/2, a, inter0, p1 );
    strassen( n/2, inter1, h, p2 );
    strassen( n/2, inter2, e, p3 );
    strassen( n/2, d, inter3, p4 );
    strassen( n/2, inter4, inter5, p5 );
    strassen( n/2, inter6, inter7, p6 );
    strassen( n/2, inter8, inter9, p7 );

    if ( DEBUG_RECUR ) {
      printMatrix(n/2, p1 );
      printMatrix(n/2, p2 );
      printMatrix(n/2, p3 );
      printMatrix(n/2, p4 );
      printMatrix(n/2, p5 );
      printMatrix(n/2, p6 );
      printMatrix(n/2, p7 );
    }

    // combine into four mini matrices
    addMatrix( n/2, p5, p4, a );
    subtractMatrix( n/2, a, p2, a );
    addMatrix( n/2, a, p6, a );

    addMatrix( n/2, p1, p2, h );

    addMatrix( n/2, p3, p4, e );

    addMatrix( n/2, p1, p5, d );
    subtractMatrix( n/2, d, p3, d );
    subtractMatrix( n/2, d, p7, d );

    combine( n, a, h, e, d, answer );

    free( a );
    free( d );
    free( e );
    free( h );

    free( p1 );
    free( p2 );
    free( p3 );
    free( p4 );
    free( p5 );
    free( p6 );
    free( p7 );

    free( inter0 );
    free( inter1 );
    free( inter2 );
    free( inter3 );
    free( inter4 );
    free( inter5 );
    free( inter6 );
    free( inter7 );
    free( inter8 );
    free( inter9 );
  }
}

// to spawn seven threads
void strassen_thread_spawn( int n, double *m1, double *m2, double *answer ) {

  // base case n = 1
  if( n == 1 ) {
    *answer = *m1 * *m2;
  } else {
    // setup for threads
    pthread_t threads[ 7 ]; // seven for now
    struct strassen_args args_array[ 7 ];
    pthread_attr_t attr;
    void *status;
    int rc, t;

    pthread_attr_init( &attr );
    pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );

    // split each into four mini matrices
    double *a = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *b = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *c = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *d = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *e = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *f = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *g = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *h = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    split( n, 1, m1, a );
    split( n, 2, m1, b );
    split( n, 3, m1, c );
    split( n, 4, m1, d );
    split( n, 1, m2, e );
    split( n, 2, m2, f );
    split( n, 3, m2, g );
    split( n, 4, m2, h );

    if ( DEBUG_SPLIT ) {
      printMatrix( n/2, a );
      printMatrix( n/2, b );
      printMatrix( n/2, c );
      printMatrix( n/2, d );
    }

    // intermediate products and recursive calls
    double *p1 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p2 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p3 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p4 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p5 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p6 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p7 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    double *inter0 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter1 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter2 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter3 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter4 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter5 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter6 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter7 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter8 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter9 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    subtractMatrix( n/2, f, h, inter0 );
    addMatrix( n/2, a, b, inter1 );
    addMatrix( n/2, c, d, inter2 );
    subtractMatrix( n/2, g, e, inter3 );
    addMatrix( n/2, a, d, inter4 );
    addMatrix( n/2, e, h, inter5 );
    subtractMatrix( n/2, b, d, inter6 );
    addMatrix( n/2, g, h, inter7);
    subtractMatrix( n/2, a, c, inter8 );
    addMatrix( n/2, e, f, inter9 );

    if ( DEBUG_INTER ) {
      printMatrix( n/2, inter0 );
      printMatrix( n/2, inter1 );
      printMatrix( n/2, inter2 );
      printMatrix( n/2, inter3 );
      printMatrix( n/2, inter4 );
      printMatrix( n/2, inter5 );
      printMatrix( n/2, inter6 );
      printMatrix( n/2, inter7 );
      printMatrix( n/2, inter8 );
      printMatrix( n/2, inter9 );
    }
    // Recursive Calls
    args_array[ 0 ].n = n/2;
    args_array[ 0 ].m1 = a;
    args_array[ 0 ].m2 = inter0;
    args_array[ 0 ].answer = p1;
    rc = pthread_create( &threads[ 0 ], &attr, strassen_parallel_thread_func, ( void * ) &args_array[ 0 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    args_array[ 1 ].n = n/2;
    args_array[ 1 ].m1 = inter1;
    args_array[ 1 ].m2 = h;
    args_array[ 1 ].answer = p2;
    rc = pthread_create( &threads[ 1 ], &attr, strassen_parallel_thread_func, ( void * ) &args_array[ 1 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    args_array[ 2 ].n = n/2;
    args_array[ 2 ].m1 = inter2;
    args_array[ 2 ].m2 = e;
    args_array[ 2 ].answer = p3;
    rc = pthread_create( &threads[ 2 ], &attr, strassen_parallel_thread_func, ( void * ) &args_array[ 2 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    args_array[ 3 ].n = n/2;
    args_array[ 3 ].m1 = d;
    args_array[ 3 ].m2 = inter3;
    args_array[ 3 ].answer = p4;
    rc = pthread_create( &threads[ 3 ], &attr, strassen_parallel_thread_func, ( void * ) &args_array[ 3 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    args_array[ 4 ].n = n/2;
    args_array[ 4 ].m1 = inter4;
    args_array[ 4 ].m2 = inter5;
    args_array[ 4 ].answer = p5;
    rc = pthread_create( &threads[ 4 ], &attr, strassen_parallel_thread_func, ( void * ) &args_array[ 4 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    args_array[ 5 ].n = n/2;
    args_array[ 5 ].m1 = inter6;
    args_array[ 5 ].m2 = inter7;
    args_array[ 5 ].answer = p6;
    rc = pthread_create( &threads[ 5 ], &attr, strassen_parallel_thread_func, ( void * ) &args_array[ 5 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    args_array[ 6 ].n = n/2;
    args_array[ 6 ].m1 = inter8;
    args_array[ 6 ].m2 = inter9;
    args_array[ 6 ].answer = p7;
    rc = pthread_create( &threads[ 6 ], &attr, strassen_parallel_thread_func, ( void * ) &args_array[ 6 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    for ( t = 0; t < 7; t++ ) {
      rc = pthread_join( threads[ t ], &status );
      if (rc) {
        printf( "ERROR; return code from pthread_create is %d\n", rc );
        exit( -1 );
      }
    }
    pthread_attr_destroy( &attr );

    if ( DEBUG_RECUR ) {
      printMatrix(n/2, p1 );
      printMatrix(n/2, p2 );
      printMatrix(n/2, p3 );
      printMatrix(n/2, p4 );
      printMatrix(n/2, p5 );
      printMatrix(n/2, p6 );
      printMatrix(n/2, p7 );
    }

    // combine into four mini matrices
    addMatrix( n/2, p5, p4, a );
    subtractMatrix( n/2, a, p2, a );
    addMatrix( n/2, a, p6, a );

    addMatrix( n/2, p1, p2, b );

    addMatrix( n/2, p3, p4, c );

    addMatrix( n/2, p1, p5, d );
    subtractMatrix( n/2, d, p3, d );
    subtractMatrix( n/2, d, p7, d );

    combine( n, a, b, c, d, answer );

    free( a );
    free( b );
    free( c );
    free( d );
    free( e );
    free( f );
    free( g );
    free( h );

    free( p1 );
    free( p2 );
    free( p3 );
    free( p4 );
    free( p5 );
    free( p6 );
    free( p7 );

    free( inter0 );
    free( inter1 );
    free( inter2 );
    free( inter3 );
    free( inter4 );
    free( inter5 );
    free( inter6 );
    free( inter7 );
    free( inter8 );
    free( inter9 );
  }
}
// for seven threads
void *strassen_parallel_thread_func( void *thread_args ) {
  // Unpack args
  // int n, double *m1, double *m2, double *answer
  struct strassen_args *args = ( struct strassen_args * ) thread_args;
  int n = args->n;
  double *m1 = args->m1;
  double *m2 = args->m2;
  double *answer = args->answer;

  // base case n = 1
  if( n == 1 ) {
    *answer = *m1 * *m2;
  } else {
    // split each into four mini matrices
    double *a = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *b = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *c = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *d = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *e = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *f = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *g = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *h = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    split( n, 1, m1, a );
    split( n, 2, m1, b );
    split( n, 3, m1, c );
    split( n, 4, m1, d );
    split( n, 1, m2, e );
    split( n, 2, m2, f );
    split( n, 3, m2, g );
    split( n, 4, m2, h );

    if ( DEBUG_SPLIT ) {
      printMatrix( n/2, a );
      printMatrix( n/2, b );
      printMatrix( n/2, c );
      printMatrix( n/2, d );
    }

    // intermediate products and recursive calls
    double *p1 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p2 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p3 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p4 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p5 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p6 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *p7 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    double *inter0 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter1 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter2 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter3 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter4 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter5 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter6 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter7 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter8 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *inter9 = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    subtractMatrix( n/2, f, h, inter0 );
    addMatrix( n/2, a, b, inter1 );
    addMatrix( n/2, c, d, inter2 );
    subtractMatrix( n/2, g, e, inter3 );
    addMatrix( n/2, a, d, inter4 );
    addMatrix( n/2, e, h, inter5 );
    subtractMatrix( n/2, b, d, inter6 );
    addMatrix( n/2, g, h, inter7);
    subtractMatrix( n/2, a, c, inter8 );
    addMatrix( n/2, e, f, inter9 );

    if ( DEBUG_INTER ) {
      printMatrix( n/2, inter0 );
      printMatrix( n/2, inter1 );
      printMatrix( n/2, inter2 );
      printMatrix( n/2, inter3 );
      printMatrix( n/2, inter4 );
      printMatrix( n/2, inter5 );
      printMatrix( n/2, inter6 );
      printMatrix( n/2, inter7 );
      printMatrix( n/2, inter8 );
      printMatrix( n/2, inter9 );
    }
    strassen( n/2, a, inter0, p1 );
    strassen( n/2, inter1, h, p2 );
    strassen( n/2, inter2, e, p3 );
    strassen( n/2, d, inter3, p4 );
    strassen( n/2, inter4, inter5, p5 );
    strassen( n/2, inter6, inter7, p6 );
    strassen( n/2, inter8, inter9, p7 );

    if ( DEBUG_RECUR ) {
      printMatrix(n/2, p1 );
      printMatrix(n/2, p2 );
      printMatrix(n/2, p3 );
      printMatrix(n/2, p4 );
      printMatrix(n/2, p5 );
      printMatrix(n/2, p6 );
      printMatrix(n/2, p7 );
    }

    // combine into four mini matrices
    addMatrix( n/2, p5, p4, a );
    subtractMatrix( n/2, a, p2, a );
    addMatrix( n/2, a, p6, a );

    addMatrix( n/2, p1, p2, b );

    addMatrix( n/2, p3, p4, c );

    addMatrix( n/2, p1, p5, d );
    subtractMatrix( n/2, d, p3, d );
    subtractMatrix( n/2, d, p7, d );

    combine( n, a, b, c, d, answer );

    free( a );
    free( b );
    free( c );
    free( d );
    free( e );
    free( f );
    free( g );
    free( h );

    free( p1 );
    free( p2 );
    free( p3 );
    free( p4 );
    free( p5 );
    free( p6 );
    free( p7 );

    free( inter0 );
    free( inter1 );
    free( inter2 );
    free( inter3 );
    free( inter4 );
    free( inter5 );
    free( inter6 );
    free( inter7 );
    free( inter8 );
    free( inter9 );
    pthread_exit( NULL );
  }
}
