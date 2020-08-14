#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <smmintrin.h>
#include <xmmintrin.h>

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

// with intrinsics try 1
void strassen4( int n, double *m1, double *m2, double *answer ) {

  // base case n = 1
  if( n == 1 ) {
    *answer = *m1 * *m2;
  } else if( n == 2 ) {
    __m128d addreg1, addreg2, addreg3, addreg4, addreg5, addreg6, subreg1, subreg2, subreg3, subreg4;
    __m128d mulreg1, mulreg2, mulreg3, mulreg4;
    double add1[2], add2[2], add3[2], add4[2], add5[2], add6[2], sub1[2], sub2[2], sub3[2], sub4[4];
    double mul1[2], mul2[2], mul3[2], mul4[2], t56[2];

    // load into arrays
    add1[0] = *m1; // a
    add1[1] = *( m1 + 2 ); // c

    add2[0] = *( m1 + 1 ); // b
    add2[1] = *( m1 + 3 ); // d

    add3[0] = *m1; // a
    add3[1] = *m2; //e

    add4[0] = *( m1 + 3 ); // d
    add4[1] = *( m2 + 3 ); // h

    add5[0] = *( m2 + 2 ); // g
    add5[1] = *m2; // e

    add6[0] = *( m2 + 3 ); // h
    add6[1] = *( m2 + 1 ); // f

    sub1[0] = *( m2 + 1 ); // f
    sub1[1] = *( m2 + 2 ); // g

    sub2[0] = *( m2 + 3 ); // h
    sub2[1] = *m2; // e

    sub3[0] = *( m1 + 1 ); // b
    sub3[1] = *m1; // a

    sub4[0] = *( m1 + 3 );
    sub4[1] = *( m1 + 2 );

    // load in registers
    addreg1 = _mm_load_pd( add1 );
    addreg2 = _mm_load_pd( add2 );
    addreg3 = _mm_load_pd( add3 );
    addreg4 = _mm_load_pd( add4 );
    addreg5 = _mm_load_pd( add5 );
    addreg6 = _mm_load_pd( add6 );

    subreg1 = _mm_load_pd( sub1 );
    subreg2 = _mm_load_pd( sub2 );
    subreg3 = _mm_load_pd( sub3 );
    subreg4 = _mm_load_pd( sub4 );

    // do add/sub
    addreg1 = _mm_add_pd( addreg1, addreg2 );
    addreg3 = _mm_add_pd( addreg3, addreg4 );
    addreg5 = _mm_add_pd( addreg5, addreg6 );

    subreg1 = _mm_sub_pd( subreg1, subreg2 );
    subreg3 = _mm_sub_pd( subreg3, subreg4 );

    // unload values
    _mm_store_pd( t56, addreg3 );

    // load extra mul arrays
    mul1[0] = *m1; // a
    mul1[1] = *( m1 + 3 ); // d

    mul2[0] = *( m2 + 3 ); // h
    mul2[1] = *m2; // e

    mul3[0] = t56[0]; // t5
    mul3[1] = 0;

    mul4[0] = t56[1]; // t6
    mul4[1] = 0;

    // load into registers
    mulreg1 = _mm_load_pd( mul1 );
    mulreg2 = _mm_load_pd( mul2 );
    mulreg3 = _mm_load_pd( mul3 );
    mulreg4 = _mm_load_pd( mul4 );

    // do multiplication
    mulreg1 = _mm_mul_pd( subreg1, mulreg1 ); // M1, M4
    mulreg2 = _mm_mul_pd( addreg1, mulreg2 ); // M2, M3
    mulreg3 = _mm_mul_pd( mulreg3, mulreg4 ); // M5
    mulreg4 = _mm_mul_pd( addreg5, subreg3 ); // M6, M7

    // unload into arrays
    _mm_store_pd( mul1, mulreg1 ); // M1, M4
    _mm_store_pd( mul2, mulreg2 ); // M2, M3
    _mm_store_pd( mul3, mulreg3 ); // M5
    _mm_store_pd( mul4, mulreg4 ); // M6, M7

    // combine into answer matrix
    *answer = mul3[0] + mul1[1] - mul2[0] + mul4[0];
    *( answer + 1 ) = mul1[0] + mul2[0];
    *( answer + 2 ) = mul2[1] + mul1[1];
    *( answer + 3 ) = mul1[0] + mul3[0] - mul2[1] - mul4[1];


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
    strassen4( n/2, a, inter0, p1 );
    strassen4( n/2, inter1, h, p2 );
    strassen4( n/2, inter2, e, p3 );
    strassen4( n/2, d, inter3, p4 );
    strassen4( n/2, inter4, inter5, p5 );
    strassen4( n/2, inter6, inter7, p6 );
    strassen4( n/2, inter8, inter9, p7 );

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

// UNUSABLE, intrinsics take 2, not helpful
void strassen5( int n, double *m1, double *m2, double *answer ) {

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
    double add1[2], add2[2], add3[2], add4[2];
    __m128d addreg1, addreg2, addreg3, addreg4, result;
    //subtractMatrix( n/2, f, h, inter0 );
    for( i = 0; i < n/2; i++ ) {
      if( n/4 >= 1) {
        for( j = 0; j < n/2; j+=4 ) {
          add1[0] = *( m2 + n * i + j + (n/2) );
          add1[1] = *( m2 + n * i + (j+1) + (n/2) );
          add3[0] = *( m2 + n * i + (j+2) + (n/2) );
          add3[1] = *( m2 + n * i + (j+3) + (n/2) );

          add2[0] = *( m2 + n * (i + n/2) + j + (n/2) );
          add2[1] = *( m2 + n * (i + n/2) + (j+1) + (n/2) );
          add4[0] = *( m2 + n * (i + n/2) + (j+2) + (n/2) );
          add4[1] = *( m2 + n * (i + n/2) + (j+3) + (n/2) );

          addreg1 = _mm_load_pd( add1 );
          addreg2 = _mm_load_pd( add2 );
          addreg3 = _mm_load_pd( add3 );
          addreg4 = _mm_load_pd( add4 );

          result = _mm_sub_pd( addreg1, addreg2 );
          _mm_store_pd( inter0 + (n/2) * i + j, result );

          result = _mm_sub_pd( addreg3, addreg4 );
          _mm_store_pd( inter0 + (n/2) * i + (j+2), result );
        }
      } else {
        for( j = 0; j < n/2; j++ ) 
          *( inter0 + (n/2) * i + j ) = *( m2 + n * i + j + (n/2) ) - *( m2 + n * (i + n/2) + j + (n/2) );
	    }
    }
    //addMatrix( n/2, a, b, inter1 );
    for( i = 0; i < n/2; i++ ) {
      if( n/4 >= 1) {
        for( j = 0; j < n/2; j+=4 ) {
          add1[0] = *( m1 + n * i + j );
          add1[1] = *( m1 + n * i + (j+1) );
          add3[0] = *( m1 + n * i + (j+2) );
          add3[1] = *( m1 + n * i + (j+3) );

          add2[0] = *( m1 + n * i + j + n/2 );
          add2[1] = *( m1 + n * i + (j+1) + n/2 );
          add4[0] = *( m1 + n * i + (j+2) + n/2 );
          add4[1] = *( m1 + n * i + (j+3) + n/2 );

          addreg1 = _mm_load_pd( add1 );
          addreg2 = _mm_load_pd( add2 );
          addreg3 = _mm_load_pd( add3 );
          addreg4 = _mm_load_pd( add4 );

          result = _mm_add_pd( addreg1, addreg2 );
          _mm_store_pd( inter1 + (n/2) * i + j, result );

          result = _mm_add_pd( addreg3, addreg4 );
          _mm_store_pd( inter1 + (n/2) * i + (j+2), result );
        }
      } else {
        for( j = 0; j < n/2; j++ ) 
		      *( inter1 + (n/2) * i + j ) = *( m1 + n * i + j ) + *( m1 + n * i + j + n/2 );
	    }
    }
    //addMatrix( n/2, c, d, inter2 );
    for( i = 0; i < n/2; i++ ) {
      if( n/4 >= 1) {
        for( j = 0; j < n/2; j+=4 ) {
          add1[0] = *( m1 + n * (i + n/2) + j );
          add1[1] = *( m1 + n * (i + n/2) + (j+1) );
          add3[0] = *( m1 + n * (i + n/2) + (j+2) );
          add3[1] = *( m1 + n * (i + n/2) + (j+3) );

          add2[0] = *( m1 + n * (i + n/2) + j + n/2 );
          add2[1] = *( m1 + n * (i + n/2) + (j+1) + n/2 );
          add4[0] = *( m1 + n * (i + n/2) + (j+2) + n/2 );
          add4[1] = *( m1 + n * (i + n/2) + (j+3) + n/2 );

          addreg1 = _mm_load_pd( add1 );
          addreg2 = _mm_load_pd( add2 );
          addreg3 = _mm_load_pd( add3 );
          addreg4 = _mm_load_pd( add4 );

          result = _mm_add_pd( addreg1, addreg2 );
          _mm_store_pd( inter2 + (n/2) * i + j, result );

          result = _mm_add_pd( addreg3, addreg4 );
          _mm_store_pd( inter2 + (n/2) * i + (j+2), result );
        }
      } else {
        for( j = 0; j < n/2; j++ ) 
		      *( inter2 + (n/2) * i + j ) = *( m1 + n * (i + n/2) + j ) + *( m1 + n * (i + n/2) + j + n/2 );
	    }
    }
    //subtractMatrix( n/2, g, e, inter3 );
    for( i = 0; i < n/2; i++ ) {
      if( n/4 >= 1) {
        for( j = 0; j < n/2; j+=4 ) {
          add1[0] = *( m2 + n * (i + n/2) + j );
          add1[1] = *( m2 + n * (i + n/2) + (j+1) );
          add3[0] = *( m2 + n * (i + n/2) + (j+2) );
          add3[1] = *( m2 + n * (i + n/2) + (j+3) );

          add2[0] = *( m2 + n * i + j );
          add2[1] = *( m2 + n * i + (j+1) );
          add4[0] = *( m2 + n * i + (j+2) );
          add4[1] = *( m2 + n * i + (j+3) );

          addreg1 = _mm_load_pd( add1 );
          addreg2 = _mm_load_pd( add2 );
          addreg3 = _mm_load_pd( add3 );
          addreg4 = _mm_load_pd( add4 );

          result = _mm_sub_pd( addreg1, addreg2 );
          _mm_store_pd( inter3 + (n/2) * i + j, result );

          result = _mm_sub_pd( addreg3, addreg4 );
          _mm_store_pd( inter3 + (n/2) * i + (j+2), result );
        }
      } else {
        for( j = 0; j < n/2; j++ ) 
		      *( inter3 + (n/2) * i + j ) = *( m2 + n * (i + n/2) + j ) - *( m2 + n * i + j );
	    }
    }
    //addMatrix( n/2, a, d, inter4 );
    for( i = 0; i < n/2; i++ ) {
      if( n/4 >= 1) {
        for( j = 0; j < n/2; j+=4 ) {
          add1[0] = *( m1 + n * i + j );
          add1[1] = *( m1 + n * i + (j+1) );
          add3[0] = *( m1 + n * i + (j+2) );
          add3[1] = *( m1 + n * i + (j+3) );

          add2[0] = *( m1 + n * (i + n/2) + j + n/2 );
          add2[1] = *( m1 + n * (i + n/2) + (j+1) + n/2 );
          add4[0] = *( m1 + n * (i + n/2) + (j+2) + n/2 );
          add4[1] = *( m1 + n * (i + n/2) + (j+3) + n/2 );

          addreg1 = _mm_load_pd( add1 );
          addreg2 = _mm_load_pd( add2 );
          addreg3 = _mm_load_pd( add3 );
          addreg4 = _mm_load_pd( add4 );

          result = _mm_add_pd( addreg1, addreg2 );
          _mm_store_pd( inter4 + (n/2) * i + j, result );

          result = _mm_add_pd( addreg3, addreg4 );
          _mm_store_pd( inter4 + (n/2) * i + (j+2), result );
        }
      } else {
        for( j = 0; j < n/2; j++ ) 
		      *( inter4 + (n/2) * i + j ) = *( m1 + n * i + j ) + *( m1 + n * (i + n/2) + j + n/2 );
	    }
    }
    //addMatrix( n/2, e, h, inter5 );
    for( i = 0; i < n/2; i++ ) {
      if( n/4 >= 1) {
        for( j = 0; j < n/2; j+=4 ) {
          add1[0] = *( m2 + n * i + j );
          add1[1] = *( m2 + n * i + (j+1) );
          add3[0] = *( m2 + n * i + (j+2) );
          add3[1] = *( m2 + n * i + (j+3) );

          add2[0] = *( m2 + n * (i + n/2) + j + n/2 );
          add2[1] = *( m2 + n * (i + n/2) + (j+1) + n/2 );
          add4[0] = *( m2 + n * (i + n/2) + (j+2) + n/2 );
          add4[1] = *( m2 + n * (i + n/2) + (j+3) + n/2 );

          addreg1 = _mm_load_pd( add1 );
          addreg2 = _mm_load_pd( add2 );
          addreg3 = _mm_load_pd( add3 );
          addreg4 = _mm_load_pd( add4 );

          result = _mm_add_pd( addreg1, addreg2 );
          _mm_store_pd( inter5 + (n/2) * i + j, result );

          result = _mm_add_pd( addreg3, addreg4 );
          _mm_store_pd( inter5 + (n/2) * i + (j+2), result );
        }
      } else {
        for( j = 0; j < n/2; j++ ) 
		      *( inter5 + (n/2) * i + j ) = *( m2 + n * i + j ) + *( m2 + n * (i + n/2) + j + n/2 );
	    }
    }
    //subtractMatrix( n/2, b, d, inter6 );
    for( i = 0; i < n/2; i++ ) {
      if( n/4 >= 1) {
        for( j = 0; j < n/2; j+=4 ) {
          add1[0] = *( m1 + n * i + j + n/2 );
          add1[1] = *( m1 + n * i + (j+1) + n/2 );
          add3[0] = *( m1 + n * i + (j+2) + n/2 );
          add3[1] = *( m1 + n * i + (j+3) + n/2 );

          add2[0] = *( m1 + n * (i + n/2) + j + n/2 );
          add2[1] = *( m1 + n * (i + n/2) + (j+1) + n/2 );
          add4[0] = *( m1 + n * (i + n/2) + (j+2) + n/2 );
          add4[1] = *( m1 + n * (i + n/2) + (j+3) + n/2 );

          addreg1 = _mm_load_pd( add1 );
          addreg2 = _mm_load_pd( add2 );
          addreg3 = _mm_load_pd( add3 );
          addreg4 = _mm_load_pd( add4 );

          result = _mm_sub_pd( addreg1, addreg2 );
          _mm_store_pd( inter6 + (n/2) * i + j, result );

          result = _mm_sub_pd( addreg3, addreg4 );
          _mm_store_pd( inter6 + (n/2) * i + (j+2), result );
        }
      } else {
        for( j = 0; j < n/2; j++ ) 
		      *( inter6 + (n/2) * i + j ) = *( m1 + n * i + j + n/2 ) - *( m1 + n * (i + n/2) + j + n/2 );
	    }
    }
    //addMatrix( n/2, g, h, inter7);
    for( i = 0; i < n/2; i++ ) {
      if( n/4 >= 1) {
        for( j = 0; j < n/2; j+=4 ) {
          add1[0] = *( m2 + n * (i + n/2) + j );
          add1[1] = *( m2 + n * (i + n/2) + (j+1) );
          add3[0] = *( m2 + n * (i + n/2) + (j+2) );
          add3[1] = *( m2 + n * (i + n/2) + (j+3) );

          add2[0] = *( m2 + n * (i + n/2) + j + n/2 );
          add2[1] = *( m2 + n * (i + n/2) + (j+1) + n/2 );
          add4[0] = *( m2 + n * (i + n/2) + (j+2) + n/2 );
          add4[1] = *( m2 + n * (i + n/2) + (j+3) + n/2 );

          addreg1 = _mm_load_pd( add1 );
          addreg2 = _mm_load_pd( add2 );
          addreg3 = _mm_load_pd( add3 );
          addreg4 = _mm_load_pd( add4 );

          result = _mm_add_pd( addreg1, addreg2 );
          _mm_store_pd( inter7 + (n/2) * i + j, result );

          result = _mm_add_pd( addreg3, addreg4 );
          _mm_store_pd( inter7 + (n/2) * i + (j+2), result );
        }
      } else {
        for( j = 0; j < n/2; j++ ) 
		      *( inter7 + (n/2) * i + j ) = *( m2 + n * (i + n/2) + j ) + *( m2 + n * (i + n/2) + j + n/2 );
	    }
    }
    //subtractMatrix( n/2, a, c, inter8 );
    for( i = 0; i < n/2; i++ ) {
      if( n/4 >= 1) {
        for( j = 0; j < n/2; j+=4 ) {
          add1[0] = *( m1 + n * i + j );
          add1[1] = *( m1 + n * i + (j+1) );
          add3[0] = *( m1 + n * i + (j+2) );
          add3[1] = *( m1 + n * i + (j+3) );

          add2[0] = *( m1 + n * (i + n/2) + j );
          add2[1] = *( m1 + n * (i + n/2) + (j+1) );
          add4[0] = *( m1 + n * (i + n/2) + (j+2) );
          add4[1] = *( m1 + n * (i + n/2) + (j+3) );

          addreg1 = _mm_load_pd( add1 );
          addreg2 = _mm_load_pd( add2 );
          addreg3 = _mm_load_pd( add3 );
          addreg4 = _mm_load_pd( add4 );

          result = _mm_sub_pd( addreg1, addreg2 );
          _mm_store_pd( inter8 + (n/2) * i + j, result );

          result = _mm_sub_pd( addreg3, addreg4 );
          _mm_store_pd( inter8 + (n/2) * i + (j+2), result );
        }
      } else {
        for( j = 0; j < n/2; j++ ) 
		      *( inter8 + (n/2) * i + j ) = *( m1 + n * i + j ) - *( m1 + n * (i + n/2) + j );
	    }
    }
    //addMatrix( n/2, e, f, inter9 );
    for( i = 0; i < n/2; i++ ) {
      if( n/4 >= 1) {
        for( j = 0; j < n/2; j+=4 ) {
          add1[0] = *( m2 + n * i + j );
          add1[1] = *( m2 + n * i + (j+1) );
          add3[0] = *( m2 + n * i + (j+2) );
          add3[1] = *( m2 + n * i + (j+3) );

          add2[0] = *( m2 + n * i + j + n/2 );
          add2[1] = *( m2 + n * i + (j+1) + n/2 );
          add4[0] = *( m2 + n * i + (j+2) + n/2 );
          add4[1] = *( m2 + n * i + (j+3) + n/2 );

          addreg1 = _mm_load_pd( add1 );
          addreg2 = _mm_load_pd( add2 );
          addreg3 = _mm_load_pd( add3 );
          addreg4 = _mm_load_pd( add4 );

          result = _mm_add_pd( addreg1, addreg2 );
          _mm_store_pd( inter9 + (n/2) * i + j, result );

          result = _mm_add_pd( addreg3, addreg4 );
          _mm_store_pd( inter9 + (n/2) * i + (j+2), result );
        }
      } else {
        for( j = 0; j < n/2; j++ ) 
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
    strassen5( n/2, a, inter0, p1 );
    strassen5( n/2, inter1, h, p2 );
    strassen5( n/2, inter2, e, p3 );
    strassen5( n/2, d, inter3, p4 );
    strassen5( n/2, inter4, inter5, p5 );
    strassen5( n/2, inter6, inter7, p6 );
    strassen5( n/2, inter8, inter9, p7 );

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

void strassen6( int n, double *m1, double *m2, double *answer ) {

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
    double x[10], y[10], z[2];
    __m128d reg1, reg2, result;
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
        //subtractMatrix( n/2, f, h, inter0 );
		    //*( inter0 + (n/2) * i + j ) = *( m2 + n * i + j + (n/2) ) - *( m2 + n * (i + n/2) + j + (n/2) );
        //subtractMatrix( n/2, g, e, inter3 );
		    //*( inter3 + (n/2) * i + j ) = *( m2 + n * (i + n/2) + j ) - *( m2 + n * i + j );
        x[0] = *( m2 + n * i + j + (n/2) );
        x[1] = *( m2 + n * (i + n/2) + j );
        y[0] = *( m2 + n * (i + n/2) + j + (n/2) );
        y[1] = *( m2 + n * i + j );
        

        //addMatrix( n/2, a, b, inter1 );
		    //*( inter1 + (n/2) * i + j ) = *( m1 + n * i + j ) + *( m1 + n * i + j + n/2 );
        //addMatrix( n/2, c, d, inter2 );
		    //*( inter2 + (n/2) * i + j ) = *( m1 + n * (i + n/2) + j ) + *( m1 + n * (i + n/2) + j + n/2 );
        x[2] = *( m1 + n * i + j );
        x[3] = *( m1 + n * (i + n/2) + j ); 
        y[2] = *( m1 + n * i + j + n/2 );
        y[3] = *( m1 + n * (i + n/2) + j + n/2 );


        //addMatrix( n/2, a, d, inter4 );
		    //*( inter4 + (n/2) * i + j ) = *( m1 + n * i + j ) + *( m1 + n * (i + n/2) + j + n/2 );
        //addMatrix( n/2, e, h, inter5 );
		    //*( inter5 + (n/2) * i + j ) = *( m2 + n * i + j ) + *( m2 + n * (i + n/2) + j + n/2 );
        x[4] = *( m1 + n * i + j );
        x[5] = *( m2 + n * i + j );
        y[4] = *( m1 + n * (i + n/2) + j + n/2 );
        y[5] = *( m2 + n * (i + n/2) + j + n/2 );


        //subtractMatrix( n/2, b, d, inter6 );
		    //*( inter6 + (n/2) * i + j ) = *( m1 + n * i + j + n/2 ) - *( m1 + n * (i + n/2) + j + n/2 );
        //subtractMatrix( n/2, a, c, inter8 );
		    //*( inter8 + (n/2) * i + j ) = *( m1 + n * i + j ) - *( m1 + n * (i + n/2) + j );
        x[6] = *( m1 + n * i + j + n/2 );
        x[7] = *( m1 + n * i + j );
        y[6] = *( m1 + n * (i + n/2) + j + n/2 );
        y[7] = *( m1 + n * (i + n/2) + j );


        //addMatrix( n/2, g, h, inter7);
		    //*( inter7 + (n/2) * i + j ) = *( m2 + n * (i + n/2) + j ) + *( m2 + n * (i + n/2) + j + n/2 );
        //addMatrix( n/2, e, f, inter9 );
		    //*( inter9 + (n/2) * i + j ) = *( m2 + n * i + j ) + *( m2 + n * i + j + n/2 );
        x[8] = *( m2 + n * (i + n/2) + j );
        x[9] = *( m2 + n * i + j );
        y[8] = *( m2 + n * (i + n/2) + j + n/2 );
        y[9] = *( m2 + n * i + j + n/2 );


        reg1 = _mm_load_pd( x );
        reg2 = _mm_load_pd( y );
        result = _mm_sub_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter0 + (n/2) * i + j ) =  z[0];
        *( inter3 + (n/2) * i + j ) =  z[1];

        reg1 = _mm_load_pd( x+2 );
        reg2 = _mm_load_pd( y+2 );
        result = _mm_add_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter1 + (n/2) * i + j ) =  z[0];
        *( inter2 + (n/2) * i + j ) =  z[1];

        reg1 = _mm_load_pd( x+4 );
        reg2 = _mm_load_pd( y+4 );
        result = _mm_add_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter4 + (n/2) * i + j ) =  z[0];
        *( inter5 + (n/2) * i + j ) =  z[1];

        reg1 = _mm_load_pd( x+6 );
        reg2 = _mm_load_pd( y+6 );
        result = _mm_sub_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter6 + (n/2) * i + j ) =  z[0];
        *( inter8 + (n/2) * i + j ) =  z[1];
        
        reg1 = _mm_load_pd( x+8 );
        reg2 = _mm_load_pd( y+8 );
        result = _mm_add_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter7 + (n/2) * i + j ) =  z[0];
        *( inter9 + (n/2) * i + j ) =  z[1];
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
    strassen6( n/2, a, inter0, p1 );
    strassen6( n/2, inter1, h, p2 );
    strassen6( n/2, inter2, e, p3 );
    strassen6( n/2, d, inter3, p4 );
    strassen6( n/2, inter4, inter5, p5 );
    strassen6( n/2, inter6, inter7, p6 );
    strassen6( n/2, inter8, inter9, p7 );

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
    /*
    addMatrix( n/2, p5, p4, a );
    subtractMatrix( n/2, a, p2, a );
    addMatrix( n/2, a, p6, a );

    addMatrix( n/2, p1, p2, h );

    addMatrix( n/2, p3, p4, e );

    addMatrix( n/2, p1, p5, d );
    subtractMatrix( n/2, d, p3, d );
    subtractMatrix( n/2, d, p7, d );
    */
    /*
    for( i = 0; i < n * n / 4; i++ ) {
      *( a + i ) = *( p5 + i ) + *( p4 + i ) - *( p2 + i ) + *( p6 + i );     
      *( h + i ) = *( p1 + i ) + *( p2 + i );
      *( e + i ) = *( p3 + i ) + *( p4 + i );
      *( d + i ) = *( p5 + i ) + *( p1 + i ) - *( p3 + i ) - *( p7 + i );
    }
    */
    __m128d regs[6];
    double s[6], t[6], u[2];
    for( i = 0; i < n * n / 4; i++ ) {
      /*
      *( a + i ) = *( p5 + i ) + *( p4 + i ) - *( p2 + i ) + *( p6 + i );     
      *( h + i ) = *( p1 + i ) + *( p2 + i );
      *( e + i ) = *( p3 + i ) + *( p4 + i );
      *( d + i ) = *( p5 + i ) + *( p1 + i ) - *( p3 + i ) - *( p7 + i );
      */

      // p5 + p4, p5 + p1
      s[0] = *( p5 + i );
      t[0] = *( p4 + i );
      s[1] = *( p5 + i );
      t[1] = *( p1 + i );

      // p6 - p2, -p3 - p7
      s[2] = *( p6 + i );
      t[2] = *( p2 + i );
      s[3] = -*( p3 + i );
      t[3] = *( p7 + i );

      // p1 + p2, p3 + p4
      s[4] = *( p1 + i );
      t[4] = *( p2 + i );
      s[5] = *( p3 + i );
      t[5] = *( p4 + i );

      regs[0] = _mm_load_pd( s );
      regs[1] = _mm_load_pd( t );
      regs[1] = _mm_add_pd( regs[0], regs[1] );

      regs[2] = _mm_load_pd( s+2 );
      regs[3] = _mm_load_pd( t+2 );
      regs[3] = _mm_sub_pd( regs[2], regs[3] );

      regs[4] = _mm_load_pd( s+4 );
      regs[5] = _mm_load_pd( t+4 );
      regs[5] = _mm_add_pd( regs[4], regs[5] );

      regs[1] = _mm_add_pd( regs[1], regs[3] );

      _mm_store_pd( u, regs[1] );
      *( a + i ) = u[0];
      *( d + i ) = u[1];
      
      _mm_store_pd( u, regs[5] );
      *( h + i ) = u[0];
      *( e + i ) = u[1];

    }

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
    pthread_exit( NULL );
  }
}

void strassen7( int n, double *m1, double *m2, double *answer ) {

  // base case n = 1
  if( n == 1 ) {
    *answer = *m1 * *m2;
  } else if( n == 2 ) {
    __m128d addreg1, addreg2, addreg3, addreg4, addreg5, addreg6, subreg1, subreg2, subreg3, subreg4;
    __m128d mulreg1, mulreg2, mulreg3, mulreg4;
    double add1[2], add2[2], add3[2], add4[2], add5[2], add6[2], sub1[2], sub2[2], sub3[2], sub4[4];
    double mul1[2], mul2[2], mul3[2], mul4[2], t56[2];

    // load into arrays
    add1[0] = *m1; // a
    add1[1] = *( m1 + 2 ); // c

    add2[0] = *( m1 + 1 ); // b
    add2[1] = *( m1 + 3 ); // d

    add3[0] = *m1; // a
    add3[1] = *m2; //e

    add4[0] = *( m1 + 3 ); // d
    add4[1] = *( m2 + 3 ); // h

    add5[0] = *( m2 + 2 ); // g
    add5[1] = *m2; // e

    add6[0] = *( m2 + 3 ); // h
    add6[1] = *( m2 + 1 ); // f

    sub1[0] = *( m2 + 1 ); // f
    sub1[1] = *( m2 + 2 ); // g

    sub2[0] = *( m2 + 3 ); // h
    sub2[1] = *m2; // e

    sub3[0] = *( m1 + 1 ); // b
    sub3[1] = *m1; // a

    sub4[0] = *( m1 + 3 );
    sub4[1] = *( m1 + 2 );

    // load in registers
    addreg1 = _mm_load_pd( add1 );
    addreg2 = _mm_load_pd( add2 );
    addreg3 = _mm_load_pd( add3 );
    addreg4 = _mm_load_pd( add4 );
    addreg5 = _mm_load_pd( add5 );
    addreg6 = _mm_load_pd( add6 );

    subreg1 = _mm_load_pd( sub1 );
    subreg2 = _mm_load_pd( sub2 );
    subreg3 = _mm_load_pd( sub3 );
    subreg4 = _mm_load_pd( sub4 );

    // do add/sub
    addreg1 = _mm_add_pd( addreg1, addreg2 );
    addreg3 = _mm_add_pd( addreg3, addreg4 );
    addreg5 = _mm_add_pd( addreg5, addreg6 );

    subreg1 = _mm_sub_pd( subreg1, subreg2 );
    subreg3 = _mm_sub_pd( subreg3, subreg4 );

    // unload values
    _mm_store_pd( t56, addreg3 );

    // load extra mul arrays
    mul1[0] = *m1; // a
    mul1[1] = *( m1 + 3 ); // d

    mul2[0] = *( m2 + 3 ); // h
    mul2[1] = *m2; // e

    mul3[0] = t56[0]; // t5
    mul3[1] = 0;

    mul4[0] = t56[1]; // t6
    mul4[1] = 0;

    // load into registers
    mulreg1 = _mm_load_pd( mul1 );
    mulreg2 = _mm_load_pd( mul2 );
    mulreg3 = _mm_load_pd( mul3 );
    mulreg4 = _mm_load_pd( mul4 );

    // do multiplication
    mulreg1 = _mm_mul_pd( subreg1, mulreg1 ); // M1, M4
    mulreg2 = _mm_mul_pd( addreg1, mulreg2 ); // M2, M3
    mulreg3 = _mm_mul_pd( mulreg3, mulreg4 ); // M5
    mulreg4 = _mm_mul_pd( addreg5, subreg3 ); // M6, M7

    // unload into arrays
    _mm_store_pd( mul1, mulreg1 ); // M1, M4
    _mm_store_pd( mul2, mulreg2 ); // M2, M3
    _mm_store_pd( mul3, mulreg3 ); // M5
    _mm_store_pd( mul4, mulreg4 ); // M6, M7

    // combine into answer matrix
    *answer = mul3[0] + mul1[1] - mul2[0] + mul4[0];
    *( answer + 1 ) = mul1[0] + mul2[0];
    *( answer + 2 ) = mul2[1] + mul1[1];
    *( answer + 3 ) = mul1[0] + mul3[0] - mul2[1] - mul4[1];

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
    double x[10], y[10], z[2];
    __m128d reg1, reg2, result;
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
        //subtractMatrix( n/2, f, h, inter0 );
		    //*( inter0 + (n/2) * i + j ) = *( m2 + n * i + j + (n/2) ) - *( m2 + n * (i + n/2) + j + (n/2) );
        //subtractMatrix( n/2, g, e, inter3 );
		    //*( inter3 + (n/2) * i + j ) = *( m2 + n * (i + n/2) + j ) - *( m2 + n * i + j );
        x[0] = *( m2 + n * i + j + (n/2) );
        x[1] = *( m2 + n * (i + n/2) + j );
        y[0] = *( m2 + n * (i + n/2) + j + (n/2) );
        y[1] = *( m2 + n * i + j );
        

        //addMatrix( n/2, a, b, inter1 );
		    //*( inter1 + (n/2) * i + j ) = *( m1 + n * i + j ) + *( m1 + n * i + j + n/2 );
        //addMatrix( n/2, c, d, inter2 );
		    //*( inter2 + (n/2) * i + j ) = *( m1 + n * (i + n/2) + j ) + *( m1 + n * (i + n/2) + j + n/2 );
        x[2] = *( m1 + n * i + j );
        x[3] = *( m1 + n * (i + n/2) + j ); 
        y[2] = *( m1 + n * i + j + n/2 );
        y[3] = *( m1 + n * (i + n/2) + j + n/2 );


        //addMatrix( n/2, a, d, inter4 );
		    //*( inter4 + (n/2) * i + j ) = *( m1 + n * i + j ) + *( m1 + n * (i + n/2) + j + n/2 );
        //addMatrix( n/2, e, h, inter5 );
		    //*( inter5 + (n/2) * i + j ) = *( m2 + n * i + j ) + *( m2 + n * (i + n/2) + j + n/2 );
        x[4] = *( m1 + n * i + j );
        x[5] = *( m2 + n * i + j );
        y[4] = *( m1 + n * (i + n/2) + j + n/2 );
        y[5] = *( m2 + n * (i + n/2) + j + n/2 );


        //subtractMatrix( n/2, b, d, inter6 );
		    //*( inter6 + (n/2) * i + j ) = *( m1 + n * i + j + n/2 ) - *( m1 + n * (i + n/2) + j + n/2 );
        //subtractMatrix( n/2, a, c, inter8 );
		    //*( inter8 + (n/2) * i + j ) = *( m1 + n * i + j ) - *( m1 + n * (i + n/2) + j );
        x[6] = *( m1 + n * i + j + n/2 );
        x[7] = *( m1 + n * i + j );
        y[6] = *( m1 + n * (i + n/2) + j + n/2 );
        y[7] = *( m1 + n * (i + n/2) + j );


        //addMatrix( n/2, g, h, inter7);
		    //*( inter7 + (n/2) * i + j ) = *( m2 + n * (i + n/2) + j ) + *( m2 + n * (i + n/2) + j + n/2 );
        //addMatrix( n/2, e, f, inter9 );
		    //*( inter9 + (n/2) * i + j ) = *( m2 + n * i + j ) + *( m2 + n * i + j + n/2 );
        x[8] = *( m2 + n * (i + n/2) + j );
        x[9] = *( m2 + n * i + j );
        y[8] = *( m2 + n * (i + n/2) + j + n/2 );
        y[9] = *( m2 + n * i + j + n/2 );


        reg1 = _mm_load_pd( x );
        reg2 = _mm_load_pd( y );
        result = _mm_sub_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter0 + (n/2) * i + j ) =  z[0];
        *( inter3 + (n/2) * i + j ) =  z[1];

        reg1 = _mm_load_pd( x+2 );
        reg2 = _mm_load_pd( y+2 );
        result = _mm_add_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter1 + (n/2) * i + j ) =  z[0];
        *( inter2 + (n/2) * i + j ) =  z[1];

        reg1 = _mm_load_pd( x+4 );
        reg2 = _mm_load_pd( y+4 );
        result = _mm_add_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter4 + (n/2) * i + j ) =  z[0];
        *( inter5 + (n/2) * i + j ) =  z[1];

        reg1 = _mm_load_pd( x+6 );
        reg2 = _mm_load_pd( y+6 );
        result = _mm_sub_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter6 + (n/2) * i + j ) =  z[0];
        *( inter8 + (n/2) * i + j ) =  z[1];
        
        reg1 = _mm_load_pd( x+8 );
        reg2 = _mm_load_pd( y+8 );
        result = _mm_add_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter7 + (n/2) * i + j ) =  z[0];
        *( inter9 + (n/2) * i + j ) =  z[1];
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
    strassen7( n/2, a, inter0, p1 );
    strassen7( n/2, inter1, h, p2 );
    strassen7( n/2, inter2, e, p3 );
    strassen7( n/2, d, inter3, p4 );
    strassen7( n/2, inter4, inter5, p5 );
    strassen7( n/2, inter6, inter7, p6 );
    strassen7( n/2, inter8, inter9, p7 );

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
    __m128d regs[6];
    double s[6], t[6], u[2];
    for( i = 0; i < n * n / 4; i++ ) {
      /*
      *( a + i ) = *( p5 + i ) + *( p4 + i ) - *( p2 + i ) + *( p6 + i );     
      *( h + i ) = *( p1 + i ) + *( p2 + i );
      *( e + i ) = *( p3 + i ) + *( p4 + i );
      *( d + i ) = *( p5 + i ) + *( p1 + i ) - *( p3 + i ) - *( p7 + i );
      */

      // p5 + p4, p5 + p1
      s[0] = *( p5 + i );
      t[0] = *( p4 + i );
      s[1] = *( p5 + i );
      t[1] = *( p1 + i );

      // p6 - p2, -p3 - p7
      s[2] = *( p6 + i );
      t[2] = *( p2 + i );
      s[3] = -*( p3 + i );
      t[3] = *( p7 + i );

      // p1 + p2, p3 + p4
      s[4] = *( p1 + i );
      t[4] = *( p2 + i );
      s[5] = *( p3 + i );
      t[5] = *( p4 + i );

      regs[0] = _mm_load_pd( s );
      regs[1] = _mm_load_pd( t );
      regs[1] = _mm_add_pd( regs[0], regs[1] );

      regs[2] = _mm_load_pd( s+2 );
      regs[3] = _mm_load_pd( t+2 );
      regs[3] = _mm_sub_pd( regs[2], regs[3] );

      regs[4] = _mm_load_pd( s+4 );
      regs[5] = _mm_load_pd( t+4 );
      regs[5] = _mm_add_pd( regs[4], regs[5] );

      regs[1] = _mm_add_pd( regs[1], regs[3] );

      _mm_store_pd( u, regs[1] );
      *( a + i ) = u[0];
      *( d + i ) = u[1];
      
      _mm_store_pd( u, regs[5] );
      *( h + i ) = u[0];
      *( e + i ) = u[1];

    }
    //addMatrix( n/2, p5, p4, a );
    //subtractMatrix( n/2, a, p2, a );
    //addMatrix( n/2, a, p6, a );

    //addMatrix( n/2, p1, p2, h );

    //addMatrix( n/2, p3, p4, e );

    //addMatrix( n/2, p1, p5, d );
    //subtractMatrix( n/2, d, p3, d );
    //subtractMatrix( n/2, d, p7, d );

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

void strassen_thread_spawn_intrinsics( int n, double *m1, double *m2, double *answer ) {

  // base case n = 1
  if( n == 1 ) {
    *answer = *m1 * *m2;
  } else {
    // setup for threads
    pthread_t threads[ 7 ]; // seven for now
    struct strassen_args args_array[ 7 ];
    pthread_attr_t attr;
    void *status;
    int rc, thread_num;

    pthread_attr_init( &attr );
    pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );

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
    double x[10], y[10], z[2];
    __m128d reg1, reg2, result;
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
        //subtractMatrix( n/2, f, h, inter0 );
		    //*( inter0 + (n/2) * i + j ) = *( m2 + n * i + j + (n/2) ) - *( m2 + n * (i + n/2) + j + (n/2) );
        //subtractMatrix( n/2, g, e, inter3 );
		    //*( inter3 + (n/2) * i + j ) = *( m2 + n * (i + n/2) + j ) - *( m2 + n * i + j );
        x[0] = *( m2 + n * i + j + (n/2) );
        x[1] = *( m2 + n * (i + n/2) + j );
        y[0] = *( m2 + n * (i + n/2) + j + (n/2) );
        y[1] = *( m2 + n * i + j );
        

        //addMatrix( n/2, a, b, inter1 );
		    //*( inter1 + (n/2) * i + j ) = *( m1 + n * i + j ) + *( m1 + n * i + j + n/2 );
        //addMatrix( n/2, c, d, inter2 );
		    //*( inter2 + (n/2) * i + j ) = *( m1 + n * (i + n/2) + j ) + *( m1 + n * (i + n/2) + j + n/2 );
        x[2] = *( m1 + n * i + j );
        x[3] = *( m1 + n * (i + n/2) + j ); 
        y[2] = *( m1 + n * i + j + n/2 );
        y[3] = *( m1 + n * (i + n/2) + j + n/2 );


        //addMatrix( n/2, a, d, inter4 );
		    //*( inter4 + (n/2) * i + j ) = *( m1 + n * i + j ) + *( m1 + n * (i + n/2) + j + n/2 );
        //addMatrix( n/2, e, h, inter5 );
		    //*( inter5 + (n/2) * i + j ) = *( m2 + n * i + j ) + *( m2 + n * (i + n/2) + j + n/2 );
        x[4] = *( m1 + n * i + j );
        x[5] = *( m2 + n * i + j );
        y[4] = *( m1 + n * (i + n/2) + j + n/2 );
        y[5] = *( m2 + n * (i + n/2) + j + n/2 );


        //subtractMatrix( n/2, b, d, inter6 );
		    //*( inter6 + (n/2) * i + j ) = *( m1 + n * i + j + n/2 ) - *( m1 + n * (i + n/2) + j + n/2 );
        //subtractMatrix( n/2, a, c, inter8 );
		    //*( inter8 + (n/2) * i + j ) = *( m1 + n * i + j ) - *( m1 + n * (i + n/2) + j );
        x[6] = *( m1 + n * i + j + n/2 );
        x[7] = *( m1 + n * i + j );
        y[6] = *( m1 + n * (i + n/2) + j + n/2 );
        y[7] = *( m1 + n * (i + n/2) + j );


        //addMatrix( n/2, g, h, inter7);
		    //*( inter7 + (n/2) * i + j ) = *( m2 + n * (i + n/2) + j ) + *( m2 + n * (i + n/2) + j + n/2 );
        //addMatrix( n/2, e, f, inter9 );
		    //*( inter9 + (n/2) * i + j ) = *( m2 + n * i + j ) + *( m2 + n * i + j + n/2 );
        x[8] = *( m2 + n * (i + n/2) + j );
        x[9] = *( m2 + n * i + j );
        y[8] = *( m2 + n * (i + n/2) + j + n/2 );
        y[9] = *( m2 + n * i + j + n/2 );


        reg1 = _mm_load_pd( x );
        reg2 = _mm_load_pd( y );
        result = _mm_sub_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter0 + (n/2) * i + j ) =  z[0];
        *( inter3 + (n/2) * i + j ) =  z[1];

        reg1 = _mm_load_pd( x+2 );
        reg2 = _mm_load_pd( y+2 );
        result = _mm_add_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter1 + (n/2) * i + j ) =  z[0];
        *( inter2 + (n/2) * i + j ) =  z[1];

        reg1 = _mm_load_pd( x+4 );
        reg2 = _mm_load_pd( y+4 );
        result = _mm_add_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter4 + (n/2) * i + j ) =  z[0];
        *( inter5 + (n/2) * i + j ) =  z[1];

        reg1 = _mm_load_pd( x+6 );
        reg2 = _mm_load_pd( y+6 );
        result = _mm_sub_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter6 + (n/2) * i + j ) =  z[0];
        *( inter8 + (n/2) * i + j ) =  z[1];
        
        reg1 = _mm_load_pd( x+8 );
        reg2 = _mm_load_pd( y+8 );
        result = _mm_add_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter7 + (n/2) * i + j ) =  z[0];
        *( inter9 + (n/2) * i + j ) =  z[1];
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
    // Recursive Calls
    args_array[ 0 ].n = n/2;
    args_array[ 0 ].m1 = a;
    args_array[ 0 ].m2 = inter0;
    args_array[ 0 ].answer = p1;
    rc = pthread_create( &threads[ 0 ], &attr, strassen_parallel_thread_func_intrinsics, ( void * ) &args_array[ 0 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    args_array[ 1 ].n = n/2;
    args_array[ 1 ].m1 = inter1;
    args_array[ 1 ].m2 = h;
    args_array[ 1 ].answer = p2;
    rc = pthread_create( &threads[ 1 ], &attr, strassen_parallel_thread_func_intrinsics, ( void * ) &args_array[ 1 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    args_array[ 2 ].n = n/2;
    args_array[ 2 ].m1 = inter2;
    args_array[ 2 ].m2 = e;
    args_array[ 2 ].answer = p3;
    rc = pthread_create( &threads[ 2 ], &attr, strassen_parallel_thread_func_intrinsics, ( void * ) &args_array[ 2 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    args_array[ 3 ].n = n/2;
    args_array[ 3 ].m1 = d;
    args_array[ 3 ].m2 = inter3;
    args_array[ 3 ].answer = p4;
    rc = pthread_create( &threads[ 3 ], &attr, strassen_parallel_thread_func_intrinsics, ( void * ) &args_array[ 3 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    args_array[ 4 ].n = n/2;
    args_array[ 4 ].m1 = inter4;
    args_array[ 4 ].m2 = inter5;
    args_array[ 4 ].answer = p5;
    rc = pthread_create( &threads[ 4 ], &attr, strassen_parallel_thread_func_intrinsics, ( void * ) &args_array[ 4 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    args_array[ 5 ].n = n/2;
    args_array[ 5 ].m1 = inter6;
    args_array[ 5 ].m2 = inter7;
    args_array[ 5 ].answer = p6;
    rc = pthread_create( &threads[ 5 ], &attr, strassen_parallel_thread_func_intrinsics, ( void * ) &args_array[ 5 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    args_array[ 6 ].n = n/2;
    args_array[ 6 ].m1 = inter8;
    args_array[ 6 ].m2 = inter9;
    args_array[ 6 ].answer = p7;
    rc = pthread_create( &threads[ 6 ], &attr, strassen_parallel_thread_func_intrinsics, ( void * ) &args_array[ 6 ] );
    if (rc) {
      printf( "ERROR; return code from pthread_create is %d\n", rc );
      exit( -1 );
    }

    for ( thread_num = 0; thread_num < 7; thread_num++ ) {
      rc = pthread_join( threads[ thread_num ], &status );
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
    __m128d regs[6];
    double s[6], t[6], u[2];
    for( i = 0; i < n * n / 4; i++ ) {
      // p5 + p4, p5 + p1
      s[0] = *( p5 + i );
      t[0] = *( p4 + i );
      s[1] = *( p5 + i );
      t[1] = *( p1 + i );

      // p6 - p2, -p3 - p7
      s[2] = *( p6 + i );
      t[2] = *( p2 + i );
      s[3] = -*( p3 + i );
      t[3] = *( p7 + i );

      // p1 + p2, p3 + p4
      s[4] = *( p1 + i );
      t[4] = *( p2 + i );
      s[5] = *( p3 + i );
      t[5] = *( p4 + i );

      regs[0] = _mm_load_pd( s );
      regs[1] = _mm_load_pd( t );
      regs[1] = _mm_add_pd( regs[0], regs[1] );

      regs[2] = _mm_load_pd( s+2 );
      regs[3] = _mm_load_pd( t+2 );
      regs[3] = _mm_sub_pd( regs[2], regs[3] );

      regs[4] = _mm_load_pd( s+4 );
      regs[5] = _mm_load_pd( t+4 );
      regs[5] = _mm_add_pd( regs[4], regs[5] );

      regs[1] = _mm_add_pd( regs[1], regs[3] );

      _mm_store_pd( u, regs[1] );
      *( a + i ) = u[0];
      *( d + i ) = u[1];
      
      _mm_store_pd( u, regs[5] );
      *( h + i ) = u[0];
      *( e + i ) = u[1];

    }

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

void *strassen_parallel_thread_func_intrinsics( void *thread_args ) {

  struct strassen_args *args = ( struct strassen_args * ) thread_args;
  int n = args->n;
  double *m1 = args->m1;
  double *m2 = args->m2;
  double *answer = args->answer;

  // base case n = 1
  if( n == 1 ) {
    *answer = *m1 * *m2;
  } else if( n == 2 ) {
    __m128d addreg1, addreg2, addreg3, addreg4, addreg5, addreg6, subreg1, subreg2, subreg3, subreg4;
    __m128d mulreg1, mulreg2, mulreg3, mulreg4;
    double add1[2], add2[2], add3[2], add4[2], add5[2], add6[2], sub1[2], sub2[2], sub3[2], sub4[4];
    double mul1[2], mul2[2], mul3[2], mul4[2], t56[2];

    // load into arrays
    add1[0] = *m1; // a
    add1[1] = *( m1 + 2 ); // c

    add2[0] = *( m1 + 1 ); // b
    add2[1] = *( m1 + 3 ); // d

    add3[0] = *m1; // a
    add3[1] = *m2; //e

    add4[0] = *( m1 + 3 ); // d
    add4[1] = *( m2 + 3 ); // h

    add5[0] = *( m2 + 2 ); // g
    add5[1] = *m2; // e

    add6[0] = *( m2 + 3 ); // h
    add6[1] = *( m2 + 1 ); // f

    sub1[0] = *( m2 + 1 ); // f
    sub1[1] = *( m2 + 2 ); // g

    sub2[0] = *( m2 + 3 ); // h
    sub2[1] = *m2; // e

    sub3[0] = *( m1 + 1 ); // b
    sub3[1] = *m1; // a

    sub4[0] = *( m1 + 3 );
    sub4[1] = *( m1 + 2 );

    // load in registers
    addreg1 = _mm_load_pd( add1 );
    addreg2 = _mm_load_pd( add2 );
    addreg3 = _mm_load_pd( add3 );
    addreg4 = _mm_load_pd( add4 );
    addreg5 = _mm_load_pd( add5 );
    addreg6 = _mm_load_pd( add6 );

    subreg1 = _mm_load_pd( sub1 );
    subreg2 = _mm_load_pd( sub2 );
    subreg3 = _mm_load_pd( sub3 );
    subreg4 = _mm_load_pd( sub4 );

    // do add/sub
    addreg1 = _mm_add_pd( addreg1, addreg2 );
    addreg3 = _mm_add_pd( addreg3, addreg4 );
    addreg5 = _mm_add_pd( addreg5, addreg6 );

    subreg1 = _mm_sub_pd( subreg1, subreg2 );
    subreg3 = _mm_sub_pd( subreg3, subreg4 );

    // unload values
    _mm_store_pd( t56, addreg3 );

    // load extra mul arrays
    mul1[0] = *m1; // a
    mul1[1] = *( m1 + 3 ); // d

    mul2[0] = *( m2 + 3 ); // h
    mul2[1] = *m2; // e

    mul3[0] = t56[0]; // t5
    mul3[1] = 0;

    mul4[0] = t56[1]; // t6
    mul4[1] = 0;

    // load into registers
    mulreg1 = _mm_load_pd( mul1 );
    mulreg2 = _mm_load_pd( mul2 );
    mulreg3 = _mm_load_pd( mul3 );
    mulreg4 = _mm_load_pd( mul4 );

    // do multiplication
    mulreg1 = _mm_mul_pd( subreg1, mulreg1 ); // M1, M4
    mulreg2 = _mm_mul_pd( addreg1, mulreg2 ); // M2, M3
    mulreg3 = _mm_mul_pd( mulreg3, mulreg4 ); // M5
    mulreg4 = _mm_mul_pd( addreg5, subreg3 ); // M6, M7

    // unload into arrays
    _mm_store_pd( mul1, mulreg1 ); // M1, M4
    _mm_store_pd( mul2, mulreg2 ); // M2, M3
    _mm_store_pd( mul3, mulreg3 ); // M5
    _mm_store_pd( mul4, mulreg4 ); // M6, M7

    // combine into answer matrix
    *answer = mul3[0] + mul1[1] - mul2[0] + mul4[0];
    *( answer + 1 ) = mul1[0] + mul2[0];
    *( answer + 2 ) = mul2[1] + mul1[1];
    *( answer + 3 ) = mul1[0] + mul3[0] - mul2[1] - mul4[1];

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
    double x[10], y[10], z[2];
    __m128d reg1, reg2, result;
    for( i = 0; i < n/2; i++ ) {
	    for( j = 0; j < n/2; j++ ) {
        //subtractMatrix( n/2, f, h, inter0 );
		    //*( inter0 + (n/2) * i + j ) = *( m2 + n * i + j + (n/2) ) - *( m2 + n * (i + n/2) + j + (n/2) );
        //subtractMatrix( n/2, g, e, inter3 );
		    //*( inter3 + (n/2) * i + j ) = *( m2 + n * (i + n/2) + j ) - *( m2 + n * i + j );
        x[0] = *( m2 + n * i + j + (n/2) );
        x[1] = *( m2 + n * (i + n/2) + j );
        y[0] = *( m2 + n * (i + n/2) + j + (n/2) );
        y[1] = *( m2 + n * i + j );
        

        //addMatrix( n/2, a, b, inter1 );
		    //*( inter1 + (n/2) * i + j ) = *( m1 + n * i + j ) + *( m1 + n * i + j + n/2 );
        //addMatrix( n/2, c, d, inter2 );
		    //*( inter2 + (n/2) * i + j ) = *( m1 + n * (i + n/2) + j ) + *( m1 + n * (i + n/2) + j + n/2 );
        x[2] = *( m1 + n * i + j );
        x[3] = *( m1 + n * (i + n/2) + j ); 
        y[2] = *( m1 + n * i + j + n/2 );
        y[3] = *( m1 + n * (i + n/2) + j + n/2 );


        //addMatrix( n/2, a, d, inter4 );
		    //*( inter4 + (n/2) * i + j ) = *( m1 + n * i + j ) + *( m1 + n * (i + n/2) + j + n/2 );
        //addMatrix( n/2, e, h, inter5 );
		    //*( inter5 + (n/2) * i + j ) = *( m2 + n * i + j ) + *( m2 + n * (i + n/2) + j + n/2 );
        x[4] = *( m1 + n * i + j );
        x[5] = *( m2 + n * i + j );
        y[4] = *( m1 + n * (i + n/2) + j + n/2 );
        y[5] = *( m2 + n * (i + n/2) + j + n/2 );


        //subtractMatrix( n/2, b, d, inter6 );
		    //*( inter6 + (n/2) * i + j ) = *( m1 + n * i + j + n/2 ) - *( m1 + n * (i + n/2) + j + n/2 );
        //subtractMatrix( n/2, a, c, inter8 );
		    //*( inter8 + (n/2) * i + j ) = *( m1 + n * i + j ) - *( m1 + n * (i + n/2) + j );
        x[6] = *( m1 + n * i + j + n/2 );
        x[7] = *( m1 + n * i + j );
        y[6] = *( m1 + n * (i + n/2) + j + n/2 );
        y[7] = *( m1 + n * (i + n/2) + j );


        //addMatrix( n/2, g, h, inter7);
		    //*( inter7 + (n/2) * i + j ) = *( m2 + n * (i + n/2) + j ) + *( m2 + n * (i + n/2) + j + n/2 );
        //addMatrix( n/2, e, f, inter9 );
		    //*( inter9 + (n/2) * i + j ) = *( m2 + n * i + j ) + *( m2 + n * i + j + n/2 );
        x[8] = *( m2 + n * (i + n/2) + j );
        x[9] = *( m2 + n * i + j );
        y[8] = *( m2 + n * (i + n/2) + j + n/2 );
        y[9] = *( m2 + n * i + j + n/2 );


        reg1 = _mm_load_pd( x );
        reg2 = _mm_load_pd( y );
        result = _mm_sub_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter0 + (n/2) * i + j ) =  z[0];
        *( inter3 + (n/2) * i + j ) =  z[1];

        reg1 = _mm_load_pd( x+2 );
        reg2 = _mm_load_pd( y+2 );
        result = _mm_add_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter1 + (n/2) * i + j ) =  z[0];
        *( inter2 + (n/2) * i + j ) =  z[1];

        reg1 = _mm_load_pd( x+4 );
        reg2 = _mm_load_pd( y+4 );
        result = _mm_add_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter4 + (n/2) * i + j ) =  z[0];
        *( inter5 + (n/2) * i + j ) =  z[1];

        reg1 = _mm_load_pd( x+6 );
        reg2 = _mm_load_pd( y+6 );
        result = _mm_sub_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter6 + (n/2) * i + j ) =  z[0];
        *( inter8 + (n/2) * i + j ) =  z[1];
        
        reg1 = _mm_load_pd( x+8 );
        reg2 = _mm_load_pd( y+8 );
        result = _mm_add_pd( reg1, reg2 );
        _mm_store_pd( z, result );
        *( inter7 + (n/2) * i + j ) =  z[0];
        *( inter9 + (n/2) * i + j ) =  z[1];
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
    strassen7( n/2, a, inter0, p1 );
    strassen7( n/2, inter1, h, p2 );
    strassen7( n/2, inter2, e, p3 );
    strassen7( n/2, d, inter3, p4 );
    strassen7( n/2, inter4, inter5, p5 );
    strassen7( n/2, inter6, inter7, p6 );
    strassen7( n/2, inter8, inter9, p7 );

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
    __m128d regs[6];
    double s[6], t[6], u[2];
    for( i = 0; i < n * n / 4; i++ ) {
      /*
      *( a + i ) = *( p5 + i ) + *( p4 + i ) - *( p2 + i ) + *( p6 + i );     
      *( h + i ) = *( p1 + i ) + *( p2 + i );
      *( e + i ) = *( p3 + i ) + *( p4 + i );
      *( d + i ) = *( p5 + i ) + *( p1 + i ) - *( p3 + i ) - *( p7 + i );
      */

      // p5 + p4, p5 + p1
      s[0] = *( p5 + i );
      t[0] = *( p4 + i );
      s[1] = *( p5 + i );
      t[1] = *( p1 + i );

      // p6 - p2, -p3 - p7
      s[2] = *( p6 + i );
      t[2] = *( p2 + i );
      s[3] = -*( p3 + i );
      t[3] = *( p7 + i );

      // p1 + p2, p3 + p4
      s[4] = *( p1 + i );
      t[4] = *( p2 + i );
      s[5] = *( p3 + i );
      t[5] = *( p4 + i );

      regs[0] = _mm_load_pd( s );
      regs[1] = _mm_load_pd( t );
      regs[1] = _mm_add_pd( regs[0], regs[1] );

      regs[2] = _mm_load_pd( s+2 );
      regs[3] = _mm_load_pd( t+2 );
      regs[3] = _mm_sub_pd( regs[2], regs[3] );

      regs[4] = _mm_load_pd( s+4 );
      regs[5] = _mm_load_pd( t+4 );
      regs[5] = _mm_add_pd( regs[4], regs[5] );

      regs[1] = _mm_add_pd( regs[1], regs[3] );

      _mm_store_pd( u, regs[1] );
      *( a + i ) = u[0];
      *( d + i ) = u[1];
      
      _mm_store_pd( u, regs[5] );
      *( h + i ) = u[0];
      *( e + i ) = u[1];

    }
    //addMatrix( n/2, p5, p4, a );
    //subtractMatrix( n/2, a, p2, a );
    //addMatrix( n/2, a, p6, a );

    //addMatrix( n/2, p1, p2, h );

    //addMatrix( n/2, p3, p4, e );

    //addMatrix( n/2, p1, p5, d );
    //subtractMatrix( n/2, d, p3, d );
    //subtractMatrix( n/2, d, p7, d );

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
  pthread_exit( NULL );
}
