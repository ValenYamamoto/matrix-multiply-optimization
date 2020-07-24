#include "./matrixUtil.h"

void strassen( int n, double *m1, double *m2, double *answer ) {

  // base case n = 1
  if( n == 1 ) {
    *answer = *m1 * *m2;
  } else if {
    // split each into four mini matrices
    double *a = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *b = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *c = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *d = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *e = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *f = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *g = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );
    double *h = ( double * ) malloc ( ( n * n / 4 ) * sizeof( double ) );

    split( n, m1, a );
    split( n, m1, b );
    split( n, m1, c );
    split( n, m1, d );
    split( n, m2, e );
    split( n, m2, f );
    split( n, m2, g );
    split( n, m2, h );

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
    subractMatrix( n/2, b, d, inter6 );
    addMatrix( n/2, g, h, inter7);
    subtractMatrix( n/2, a, c, inter8 );
    subractMatrix( n/2, e, f, inter9 );

    strassen( n/2, a, inter0, p1 );
    strassen( n/2, inter1, h, p2 );
    strassen( n/2, inter2, e, p3 );
    strassen( n/2, d, inter3, p4 );
    strassen( n/2, inter4, inter5, p5 );
    strassen( n/2, inter6, inter7, p6 );
    strassen( n/2, inter8, inter9, p7 );

    // combine into four mini matrices
    a = p5 + p4 - p2 + p6;
    b = p1 + p2;
    c = p3 + p4;
    d = p1 + p5 - p3 - p7;

    combine( n, a, b, c, d, answer );
  }
}


