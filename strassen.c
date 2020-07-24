#include <stdlib.h>

#include "./matrixUtil.h"
#include "./strassen.h"

#define DEBUG_SPLIT 0
#define DEBUG_INTER 0
#define DEBUG_RECUR 0

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


