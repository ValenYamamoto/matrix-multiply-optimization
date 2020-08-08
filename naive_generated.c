#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <smmintrin.h>
#include <xmmintrin.h>

#include "matrixUtil.h"

void* naiveMultiply_parallel_intrinsics_6( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=6 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_8( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=8 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_16( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2], a7[2], b7[2], a8[2], b8[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=16 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     if( k + 12 < n ) {
       a7[0] = *( m1 + n * i + (k+12) );
     } else {
       a7[0] = 0;
     }
     if( k + 13 < n ) {
       a7[1] = *( m1 + n * i + (k+13) );
     } else {
       a7[1] = 0;
     }
     if( k + 14 < n ) {
       a8[0] = *( m1 + n * i + (k+14) );
     } else {
       a8[0] = 0;
     }
     if( k + 15 < n ) {
       a8[1] = *( m1 + n * i + (k+15) );
     } else {
       a8[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );
     t12 = _mm_load_pd( a7 );
     t14 = _mm_load_pd( a8 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       if( k + 12 < n ) {
         b7[0] = *( m2 + n * (k+12) + j );
       } else {
         b7[0] = 0;
       }
      if( k + 13 < n ) {
        b7[1] = *( m2 + n * (k+13) + j );
      } else {
        b7[1] = 0;
      }
       if( k + 14 < n ) {
         b8[0] = *( m2 + n * (k+14) + j );
       } else {
         b8[0] = 0;
       }
      if( k + 15 < n ) {
        b8[1] = *( m2 + n * (k+15) + j );
      } else {
        b8[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t13 = _mm_load_pd( b7 );
       t15 = _mm_load_pd( b8 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );
       t13 = _mm_dp_pd( t12, t13, 0xff );
       t15 = _mm_dp_pd( t14, t15, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t13 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t15 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_32( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2], a7[2], b7[2], a8[2], b8[2], a9[2], b9[2], a10[2], b10[2], a11[2], b11[2], a12[2], b12[2], a13[2], b13[2], a14[2], b14[2], a15[2], b15[2], a16[2], b16[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=32 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     if( k + 12 < n ) {
       a7[0] = *( m1 + n * i + (k+12) );
     } else {
       a7[0] = 0;
     }
     if( k + 13 < n ) {
       a7[1] = *( m1 + n * i + (k+13) );
     } else {
       a7[1] = 0;
     }
     if( k + 14 < n ) {
       a8[0] = *( m1 + n * i + (k+14) );
     } else {
       a8[0] = 0;
     }
     if( k + 15 < n ) {
       a8[1] = *( m1 + n * i + (k+15) );
     } else {
       a8[1] = 0;
     }
     if( k + 16 < n ) {
       a9[0] = *( m1 + n * i + (k+16) );
     } else {
       a9[0] = 0;
     }
     if( k + 17 < n ) {
       a9[1] = *( m1 + n * i + (k+17) );
     } else {
       a9[1] = 0;
     }
     if( k + 18 < n ) {
       a10[0] = *( m1 + n * i + (k+18) );
     } else {
       a10[0] = 0;
     }
     if( k + 19 < n ) {
       a10[1] = *( m1 + n * i + (k+19) );
     } else {
       a10[1] = 0;
     }
     if( k + 20 < n ) {
       a11[0] = *( m1 + n * i + (k+20) );
     } else {
       a11[0] = 0;
     }
     if( k + 21 < n ) {
       a11[1] = *( m1 + n * i + (k+21) );
     } else {
       a11[1] = 0;
     }
     if( k + 22 < n ) {
       a12[0] = *( m1 + n * i + (k+22) );
     } else {
       a12[0] = 0;
     }
     if( k + 23 < n ) {
       a12[1] = *( m1 + n * i + (k+23) );
     } else {
       a12[1] = 0;
     }
     if( k + 24 < n ) {
       a13[0] = *( m1 + n * i + (k+24) );
     } else {
       a13[0] = 0;
     }
     if( k + 25 < n ) {
       a13[1] = *( m1 + n * i + (k+25) );
     } else {
       a13[1] = 0;
     }
     if( k + 26 < n ) {
       a14[0] = *( m1 + n * i + (k+26) );
     } else {
       a14[0] = 0;
     }
     if( k + 27 < n ) {
       a14[1] = *( m1 + n * i + (k+27) );
     } else {
       a14[1] = 0;
     }
     if( k + 28 < n ) {
       a15[0] = *( m1 + n * i + (k+28) );
     } else {
       a15[0] = 0;
     }
     if( k + 29 < n ) {
       a15[1] = *( m1 + n * i + (k+29) );
     } else {
       a15[1] = 0;
     }
     if( k + 30 < n ) {
       a16[0] = *( m1 + n * i + (k+30) );
     } else {
       a16[0] = 0;
     }
     if( k + 31 < n ) {
       a16[1] = *( m1 + n * i + (k+31) );
     } else {
       a16[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );
     t12 = _mm_load_pd( a7 );
     t14 = _mm_load_pd( a8 );
     t16 = _mm_load_pd( a9 );
     t18 = _mm_load_pd( a10 );
     t20 = _mm_load_pd( a11 );
     t22 = _mm_load_pd( a12 );
     t24 = _mm_load_pd( a13 );
     t26 = _mm_load_pd( a14 );
     t28 = _mm_load_pd( a15 );
     t30 = _mm_load_pd( a16 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       if( k + 12 < n ) {
         b7[0] = *( m2 + n * (k+12) + j );
       } else {
         b7[0] = 0;
       }
      if( k + 13 < n ) {
        b7[1] = *( m2 + n * (k+13) + j );
      } else {
        b7[1] = 0;
      }
       if( k + 14 < n ) {
         b8[0] = *( m2 + n * (k+14) + j );
       } else {
         b8[0] = 0;
       }
      if( k + 15 < n ) {
        b8[1] = *( m2 + n * (k+15) + j );
      } else {
        b8[1] = 0;
      }
       if( k + 16 < n ) {
         b9[0] = *( m2 + n * (k+16) + j );
       } else {
         b9[0] = 0;
       }
      if( k + 17 < n ) {
        b9[1] = *( m2 + n * (k+17) + j );
      } else {
        b9[1] = 0;
      }
       if( k + 18 < n ) {
         b10[0] = *( m2 + n * (k+18) + j );
       } else {
         b10[0] = 0;
       }
      if( k + 19 < n ) {
        b10[1] = *( m2 + n * (k+19) + j );
      } else {
        b10[1] = 0;
      }
       if( k + 20 < n ) {
         b11[0] = *( m2 + n * (k+20) + j );
       } else {
         b11[0] = 0;
       }
      if( k + 21 < n ) {
        b11[1] = *( m2 + n * (k+21) + j );
      } else {
        b11[1] = 0;
      }
       if( k + 22 < n ) {
         b12[0] = *( m2 + n * (k+22) + j );
       } else {
         b12[0] = 0;
       }
      if( k + 23 < n ) {
        b12[1] = *( m2 + n * (k+23) + j );
      } else {
        b12[1] = 0;
      }
       if( k + 24 < n ) {
         b13[0] = *( m2 + n * (k+24) + j );
       } else {
         b13[0] = 0;
       }
      if( k + 25 < n ) {
        b13[1] = *( m2 + n * (k+25) + j );
      } else {
        b13[1] = 0;
      }
       if( k + 26 < n ) {
         b14[0] = *( m2 + n * (k+26) + j );
       } else {
         b14[0] = 0;
       }
      if( k + 27 < n ) {
        b14[1] = *( m2 + n * (k+27) + j );
      } else {
        b14[1] = 0;
      }
       if( k + 28 < n ) {
         b15[0] = *( m2 + n * (k+28) + j );
       } else {
         b15[0] = 0;
       }
      if( k + 29 < n ) {
        b15[1] = *( m2 + n * (k+29) + j );
      } else {
        b15[1] = 0;
      }
       if( k + 30 < n ) {
         b16[0] = *( m2 + n * (k+30) + j );
       } else {
         b16[0] = 0;
       }
      if( k + 31 < n ) {
        b16[1] = *( m2 + n * (k+31) + j );
      } else {
        b16[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t13 = _mm_load_pd( b7 );
       t15 = _mm_load_pd( b8 );
       t17 = _mm_load_pd( b9 );
       t19 = _mm_load_pd( b10 );
       t21 = _mm_load_pd( b11 );
       t23 = _mm_load_pd( b12 );
       t25 = _mm_load_pd( b13 );
       t27 = _mm_load_pd( b14 );
       t29 = _mm_load_pd( b15 );
       t31 = _mm_load_pd( b16 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );
       t13 = _mm_dp_pd( t12, t13, 0xff );
       t15 = _mm_dp_pd( t14, t15, 0xff );
       t17 = _mm_dp_pd( t16, t17, 0xff );
       t19 = _mm_dp_pd( t18, t19, 0xff );
       t21 = _mm_dp_pd( t20, t21, 0xff );
       t23 = _mm_dp_pd( t22, t23, 0xff );
       t25 = _mm_dp_pd( t24, t25, 0xff );
       t27 = _mm_dp_pd( t26, t27, 0xff );
       t29 = _mm_dp_pd( t28, t29, 0xff );
       t31 = _mm_dp_pd( t30, t31, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t13 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t15 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t17 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t19 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t21 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t23 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t25 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t27 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t29 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t31 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_10( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=10 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_12( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=12 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_14( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2], a7[2], b7[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=14 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     if( k + 12 < n ) {
       a7[0] = *( m1 + n * i + (k+12) );
     } else {
       a7[0] = 0;
     }
     if( k + 13 < n ) {
       a7[1] = *( m1 + n * i + (k+13) );
     } else {
       a7[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );
     t12 = _mm_load_pd( a7 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       if( k + 12 < n ) {
         b7[0] = *( m2 + n * (k+12) + j );
       } else {
         b7[0] = 0;
       }
      if( k + 13 < n ) {
        b7[1] = *( m2 + n * (k+13) + j );
      } else {
        b7[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t13 = _mm_load_pd( b7 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );
       t13 = _mm_dp_pd( t12, t13, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t13 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_18( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2], a7[2], b7[2], a8[2], b8[2], a9[2], b9[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=18 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     if( k + 12 < n ) {
       a7[0] = *( m1 + n * i + (k+12) );
     } else {
       a7[0] = 0;
     }
     if( k + 13 < n ) {
       a7[1] = *( m1 + n * i + (k+13) );
     } else {
       a7[1] = 0;
     }
     if( k + 14 < n ) {
       a8[0] = *( m1 + n * i + (k+14) );
     } else {
       a8[0] = 0;
     }
     if( k + 15 < n ) {
       a8[1] = *( m1 + n * i + (k+15) );
     } else {
       a8[1] = 0;
     }
     if( k + 16 < n ) {
       a9[0] = *( m1 + n * i + (k+16) );
     } else {
       a9[0] = 0;
     }
     if( k + 17 < n ) {
       a9[1] = *( m1 + n * i + (k+17) );
     } else {
       a9[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );
     t12 = _mm_load_pd( a7 );
     t14 = _mm_load_pd( a8 );
     t16 = _mm_load_pd( a9 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       if( k + 12 < n ) {
         b7[0] = *( m2 + n * (k+12) + j );
       } else {
         b7[0] = 0;
       }
      if( k + 13 < n ) {
        b7[1] = *( m2 + n * (k+13) + j );
      } else {
        b7[1] = 0;
      }
       if( k + 14 < n ) {
         b8[0] = *( m2 + n * (k+14) + j );
       } else {
         b8[0] = 0;
       }
      if( k + 15 < n ) {
        b8[1] = *( m2 + n * (k+15) + j );
      } else {
        b8[1] = 0;
      }
       if( k + 16 < n ) {
         b9[0] = *( m2 + n * (k+16) + j );
       } else {
         b9[0] = 0;
       }
      if( k + 17 < n ) {
        b9[1] = *( m2 + n * (k+17) + j );
      } else {
        b9[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t13 = _mm_load_pd( b7 );
       t15 = _mm_load_pd( b8 );
       t17 = _mm_load_pd( b9 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );
       t13 = _mm_dp_pd( t12, t13, 0xff );
       t15 = _mm_dp_pd( t14, t15, 0xff );
       t17 = _mm_dp_pd( t16, t17, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t13 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t15 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t17 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_20( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2], a7[2], b7[2], a8[2], b8[2], a9[2], b9[2], a10[2], b10[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=20 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     if( k + 12 < n ) {
       a7[0] = *( m1 + n * i + (k+12) );
     } else {
       a7[0] = 0;
     }
     if( k + 13 < n ) {
       a7[1] = *( m1 + n * i + (k+13) );
     } else {
       a7[1] = 0;
     }
     if( k + 14 < n ) {
       a8[0] = *( m1 + n * i + (k+14) );
     } else {
       a8[0] = 0;
     }
     if( k + 15 < n ) {
       a8[1] = *( m1 + n * i + (k+15) );
     } else {
       a8[1] = 0;
     }
     if( k + 16 < n ) {
       a9[0] = *( m1 + n * i + (k+16) );
     } else {
       a9[0] = 0;
     }
     if( k + 17 < n ) {
       a9[1] = *( m1 + n * i + (k+17) );
     } else {
       a9[1] = 0;
     }
     if( k + 18 < n ) {
       a10[0] = *( m1 + n * i + (k+18) );
     } else {
       a10[0] = 0;
     }
     if( k + 19 < n ) {
       a10[1] = *( m1 + n * i + (k+19) );
     } else {
       a10[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );
     t12 = _mm_load_pd( a7 );
     t14 = _mm_load_pd( a8 );
     t16 = _mm_load_pd( a9 );
     t18 = _mm_load_pd( a10 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       if( k + 12 < n ) {
         b7[0] = *( m2 + n * (k+12) + j );
       } else {
         b7[0] = 0;
       }
      if( k + 13 < n ) {
        b7[1] = *( m2 + n * (k+13) + j );
      } else {
        b7[1] = 0;
      }
       if( k + 14 < n ) {
         b8[0] = *( m2 + n * (k+14) + j );
       } else {
         b8[0] = 0;
       }
      if( k + 15 < n ) {
        b8[1] = *( m2 + n * (k+15) + j );
      } else {
        b8[1] = 0;
      }
       if( k + 16 < n ) {
         b9[0] = *( m2 + n * (k+16) + j );
       } else {
         b9[0] = 0;
       }
      if( k + 17 < n ) {
        b9[1] = *( m2 + n * (k+17) + j );
      } else {
        b9[1] = 0;
      }
       if( k + 18 < n ) {
         b10[0] = *( m2 + n * (k+18) + j );
       } else {
         b10[0] = 0;
       }
      if( k + 19 < n ) {
        b10[1] = *( m2 + n * (k+19) + j );
      } else {
        b10[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t13 = _mm_load_pd( b7 );
       t15 = _mm_load_pd( b8 );
       t17 = _mm_load_pd( b9 );
       t19 = _mm_load_pd( b10 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );
       t13 = _mm_dp_pd( t12, t13, 0xff );
       t15 = _mm_dp_pd( t14, t15, 0xff );
       t17 = _mm_dp_pd( t16, t17, 0xff );
       t19 = _mm_dp_pd( t18, t19, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t13 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t15 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t17 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t19 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_22( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2], a7[2], b7[2], a8[2], b8[2], a9[2], b9[2], a10[2], b10[2], a11[2], b11[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=22 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     if( k + 12 < n ) {
       a7[0] = *( m1 + n * i + (k+12) );
     } else {
       a7[0] = 0;
     }
     if( k + 13 < n ) {
       a7[1] = *( m1 + n * i + (k+13) );
     } else {
       a7[1] = 0;
     }
     if( k + 14 < n ) {
       a8[0] = *( m1 + n * i + (k+14) );
     } else {
       a8[0] = 0;
     }
     if( k + 15 < n ) {
       a8[1] = *( m1 + n * i + (k+15) );
     } else {
       a8[1] = 0;
     }
     if( k + 16 < n ) {
       a9[0] = *( m1 + n * i + (k+16) );
     } else {
       a9[0] = 0;
     }
     if( k + 17 < n ) {
       a9[1] = *( m1 + n * i + (k+17) );
     } else {
       a9[1] = 0;
     }
     if( k + 18 < n ) {
       a10[0] = *( m1 + n * i + (k+18) );
     } else {
       a10[0] = 0;
     }
     if( k + 19 < n ) {
       a10[1] = *( m1 + n * i + (k+19) );
     } else {
       a10[1] = 0;
     }
     if( k + 20 < n ) {
       a11[0] = *( m1 + n * i + (k+20) );
     } else {
       a11[0] = 0;
     }
     if( k + 21 < n ) {
       a11[1] = *( m1 + n * i + (k+21) );
     } else {
       a11[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );
     t12 = _mm_load_pd( a7 );
     t14 = _mm_load_pd( a8 );
     t16 = _mm_load_pd( a9 );
     t18 = _mm_load_pd( a10 );
     t20 = _mm_load_pd( a11 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       if( k + 12 < n ) {
         b7[0] = *( m2 + n * (k+12) + j );
       } else {
         b7[0] = 0;
       }
      if( k + 13 < n ) {
        b7[1] = *( m2 + n * (k+13) + j );
      } else {
        b7[1] = 0;
      }
       if( k + 14 < n ) {
         b8[0] = *( m2 + n * (k+14) + j );
       } else {
         b8[0] = 0;
       }
      if( k + 15 < n ) {
        b8[1] = *( m2 + n * (k+15) + j );
      } else {
        b8[1] = 0;
      }
       if( k + 16 < n ) {
         b9[0] = *( m2 + n * (k+16) + j );
       } else {
         b9[0] = 0;
       }
      if( k + 17 < n ) {
        b9[1] = *( m2 + n * (k+17) + j );
      } else {
        b9[1] = 0;
      }
       if( k + 18 < n ) {
         b10[0] = *( m2 + n * (k+18) + j );
       } else {
         b10[0] = 0;
       }
      if( k + 19 < n ) {
        b10[1] = *( m2 + n * (k+19) + j );
      } else {
        b10[1] = 0;
      }
       if( k + 20 < n ) {
         b11[0] = *( m2 + n * (k+20) + j );
       } else {
         b11[0] = 0;
       }
      if( k + 21 < n ) {
        b11[1] = *( m2 + n * (k+21) + j );
      } else {
        b11[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t13 = _mm_load_pd( b7 );
       t15 = _mm_load_pd( b8 );
       t17 = _mm_load_pd( b9 );
       t19 = _mm_load_pd( b10 );
       t21 = _mm_load_pd( b11 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );
       t13 = _mm_dp_pd( t12, t13, 0xff );
       t15 = _mm_dp_pd( t14, t15, 0xff );
       t17 = _mm_dp_pd( t16, t17, 0xff );
       t19 = _mm_dp_pd( t18, t19, 0xff );
       t21 = _mm_dp_pd( t20, t21, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t13 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t15 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t17 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t19 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t21 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_64( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2], a7[2], b7[2], a8[2], b8[2], a9[2], b9[2], a10[2], b10[2], a11[2], b11[2], a12[2], b12[2], a13[2], b13[2], a14[2], b14[2], a15[2], b15[2], a16[2], b16[2], a17[2], b17[2], a18[2], b18[2], a19[2], b19[2], a20[2], b20[2], a21[2], b21[2], a22[2], b22[2], a23[2], b23[2], a24[2], b24[2], a25[2], b25[2], a26[2], b26[2], a27[2], b27[2], a28[2], b28[2], a29[2], b29[2], a30[2], b30[2], a31[2], b31[2], a32[2], b32[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61, t62, t63;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=64 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     if( k + 12 < n ) {
       a7[0] = *( m1 + n * i + (k+12) );
     } else {
       a7[0] = 0;
     }
     if( k + 13 < n ) {
       a7[1] = *( m1 + n * i + (k+13) );
     } else {
       a7[1] = 0;
     }
     if( k + 14 < n ) {
       a8[0] = *( m1 + n * i + (k+14) );
     } else {
       a8[0] = 0;
     }
     if( k + 15 < n ) {
       a8[1] = *( m1 + n * i + (k+15) );
     } else {
       a8[1] = 0;
     }
     if( k + 16 < n ) {
       a9[0] = *( m1 + n * i + (k+16) );
     } else {
       a9[0] = 0;
     }
     if( k + 17 < n ) {
       a9[1] = *( m1 + n * i + (k+17) );
     } else {
       a9[1] = 0;
     }
     if( k + 18 < n ) {
       a10[0] = *( m1 + n * i + (k+18) );
     } else {
       a10[0] = 0;
     }
     if( k + 19 < n ) {
       a10[1] = *( m1 + n * i + (k+19) );
     } else {
       a10[1] = 0;
     }
     if( k + 20 < n ) {
       a11[0] = *( m1 + n * i + (k+20) );
     } else {
       a11[0] = 0;
     }
     if( k + 21 < n ) {
       a11[1] = *( m1 + n * i + (k+21) );
     } else {
       a11[1] = 0;
     }
     if( k + 22 < n ) {
       a12[0] = *( m1 + n * i + (k+22) );
     } else {
       a12[0] = 0;
     }
     if( k + 23 < n ) {
       a12[1] = *( m1 + n * i + (k+23) );
     } else {
       a12[1] = 0;
     }
     if( k + 24 < n ) {
       a13[0] = *( m1 + n * i + (k+24) );
     } else {
       a13[0] = 0;
     }
     if( k + 25 < n ) {
       a13[1] = *( m1 + n * i + (k+25) );
     } else {
       a13[1] = 0;
     }
     if( k + 26 < n ) {
       a14[0] = *( m1 + n * i + (k+26) );
     } else {
       a14[0] = 0;
     }
     if( k + 27 < n ) {
       a14[1] = *( m1 + n * i + (k+27) );
     } else {
       a14[1] = 0;
     }
     if( k + 28 < n ) {
       a15[0] = *( m1 + n * i + (k+28) );
     } else {
       a15[0] = 0;
     }
     if( k + 29 < n ) {
       a15[1] = *( m1 + n * i + (k+29) );
     } else {
       a15[1] = 0;
     }
     if( k + 30 < n ) {
       a16[0] = *( m1 + n * i + (k+30) );
     } else {
       a16[0] = 0;
     }
     if( k + 31 < n ) {
       a16[1] = *( m1 + n * i + (k+31) );
     } else {
       a16[1] = 0;
     }
     if( k + 32 < n ) {
       a17[0] = *( m1 + n * i + (k+32) );
     } else {
       a17[0] = 0;
     }
     if( k + 33 < n ) {
       a17[1] = *( m1 + n * i + (k+33) );
     } else {
       a17[1] = 0;
     }
     if( k + 34 < n ) {
       a18[0] = *( m1 + n * i + (k+34) );
     } else {
       a18[0] = 0;
     }
     if( k + 35 < n ) {
       a18[1] = *( m1 + n * i + (k+35) );
     } else {
       a18[1] = 0;
     }
     if( k + 36 < n ) {
       a19[0] = *( m1 + n * i + (k+36) );
     } else {
       a19[0] = 0;
     }
     if( k + 37 < n ) {
       a19[1] = *( m1 + n * i + (k+37) );
     } else {
       a19[1] = 0;
     }
     if( k + 38 < n ) {
       a20[0] = *( m1 + n * i + (k+38) );
     } else {
       a20[0] = 0;
     }
     if( k + 39 < n ) {
       a20[1] = *( m1 + n * i + (k+39) );
     } else {
       a20[1] = 0;
     }
     if( k + 40 < n ) {
       a21[0] = *( m1 + n * i + (k+40) );
     } else {
       a21[0] = 0;
     }
     if( k + 41 < n ) {
       a21[1] = *( m1 + n * i + (k+41) );
     } else {
       a21[1] = 0;
     }
     if( k + 42 < n ) {
       a22[0] = *( m1 + n * i + (k+42) );
     } else {
       a22[0] = 0;
     }
     if( k + 43 < n ) {
       a22[1] = *( m1 + n * i + (k+43) );
     } else {
       a22[1] = 0;
     }
     if( k + 44 < n ) {
       a23[0] = *( m1 + n * i + (k+44) );
     } else {
       a23[0] = 0;
     }
     if( k + 45 < n ) {
       a23[1] = *( m1 + n * i + (k+45) );
     } else {
       a23[1] = 0;
     }
     if( k + 46 < n ) {
       a24[0] = *( m1 + n * i + (k+46) );
     } else {
       a24[0] = 0;
     }
     if( k + 47 < n ) {
       a24[1] = *( m1 + n * i + (k+47) );
     } else {
       a24[1] = 0;
     }
     if( k + 48 < n ) {
       a25[0] = *( m1 + n * i + (k+48) );
     } else {
       a25[0] = 0;
     }
     if( k + 49 < n ) {
       a25[1] = *( m1 + n * i + (k+49) );
     } else {
       a25[1] = 0;
     }
     if( k + 50 < n ) {
       a26[0] = *( m1 + n * i + (k+50) );
     } else {
       a26[0] = 0;
     }
     if( k + 51 < n ) {
       a26[1] = *( m1 + n * i + (k+51) );
     } else {
       a26[1] = 0;
     }
     if( k + 52 < n ) {
       a27[0] = *( m1 + n * i + (k+52) );
     } else {
       a27[0] = 0;
     }
     if( k + 53 < n ) {
       a27[1] = *( m1 + n * i + (k+53) );
     } else {
       a27[1] = 0;
     }
     if( k + 54 < n ) {
       a28[0] = *( m1 + n * i + (k+54) );
     } else {
       a28[0] = 0;
     }
     if( k + 55 < n ) {
       a28[1] = *( m1 + n * i + (k+55) );
     } else {
       a28[1] = 0;
     }
     if( k + 56 < n ) {
       a29[0] = *( m1 + n * i + (k+56) );
     } else {
       a29[0] = 0;
     }
     if( k + 57 < n ) {
       a29[1] = *( m1 + n * i + (k+57) );
     } else {
       a29[1] = 0;
     }
     if( k + 58 < n ) {
       a30[0] = *( m1 + n * i + (k+58) );
     } else {
       a30[0] = 0;
     }
     if( k + 59 < n ) {
       a30[1] = *( m1 + n * i + (k+59) );
     } else {
       a30[1] = 0;
     }
     if( k + 60 < n ) {
       a31[0] = *( m1 + n * i + (k+60) );
     } else {
       a31[0] = 0;
     }
     if( k + 61 < n ) {
       a31[1] = *( m1 + n * i + (k+61) );
     } else {
       a31[1] = 0;
     }
     if( k + 62 < n ) {
       a32[0] = *( m1 + n * i + (k+62) );
     } else {
       a32[0] = 0;
     }
     if( k + 63 < n ) {
       a32[1] = *( m1 + n * i + (k+63) );
     } else {
       a32[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );
     t12 = _mm_load_pd( a7 );
     t14 = _mm_load_pd( a8 );
     t16 = _mm_load_pd( a9 );
     t18 = _mm_load_pd( a10 );
     t20 = _mm_load_pd( a11 );
     t22 = _mm_load_pd( a12 );
     t24 = _mm_load_pd( a13 );
     t26 = _mm_load_pd( a14 );
     t28 = _mm_load_pd( a15 );
     t30 = _mm_load_pd( a16 );
     t32 = _mm_load_pd( a17 );
     t34 = _mm_load_pd( a18 );
     t36 = _mm_load_pd( a19 );
     t38 = _mm_load_pd( a20 );
     t40 = _mm_load_pd( a21 );
     t42 = _mm_load_pd( a22 );
     t44 = _mm_load_pd( a23 );
     t46 = _mm_load_pd( a24 );
     t48 = _mm_load_pd( a25 );
     t50 = _mm_load_pd( a26 );
     t52 = _mm_load_pd( a27 );
     t54 = _mm_load_pd( a28 );
     t56 = _mm_load_pd( a29 );
     t58 = _mm_load_pd( a30 );
     t60 = _mm_load_pd( a31 );
     t62 = _mm_load_pd( a32 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       if( k + 12 < n ) {
         b7[0] = *( m2 + n * (k+12) + j );
       } else {
         b7[0] = 0;
       }
      if( k + 13 < n ) {
        b7[1] = *( m2 + n * (k+13) + j );
      } else {
        b7[1] = 0;
      }
       if( k + 14 < n ) {
         b8[0] = *( m2 + n * (k+14) + j );
       } else {
         b8[0] = 0;
       }
      if( k + 15 < n ) {
        b8[1] = *( m2 + n * (k+15) + j );
      } else {
        b8[1] = 0;
      }
       if( k + 16 < n ) {
         b9[0] = *( m2 + n * (k+16) + j );
       } else {
         b9[0] = 0;
       }
      if( k + 17 < n ) {
        b9[1] = *( m2 + n * (k+17) + j );
      } else {
        b9[1] = 0;
      }
       if( k + 18 < n ) {
         b10[0] = *( m2 + n * (k+18) + j );
       } else {
         b10[0] = 0;
       }
      if( k + 19 < n ) {
        b10[1] = *( m2 + n * (k+19) + j );
      } else {
        b10[1] = 0;
      }
       if( k + 20 < n ) {
         b11[0] = *( m2 + n * (k+20) + j );
       } else {
         b11[0] = 0;
       }
      if( k + 21 < n ) {
        b11[1] = *( m2 + n * (k+21) + j );
      } else {
        b11[1] = 0;
      }
       if( k + 22 < n ) {
         b12[0] = *( m2 + n * (k+22) + j );
       } else {
         b12[0] = 0;
       }
      if( k + 23 < n ) {
        b12[1] = *( m2 + n * (k+23) + j );
      } else {
        b12[1] = 0;
      }
       if( k + 24 < n ) {
         b13[0] = *( m2 + n * (k+24) + j );
       } else {
         b13[0] = 0;
       }
      if( k + 25 < n ) {
        b13[1] = *( m2 + n * (k+25) + j );
      } else {
        b13[1] = 0;
      }
       if( k + 26 < n ) {
         b14[0] = *( m2 + n * (k+26) + j );
       } else {
         b14[0] = 0;
       }
      if( k + 27 < n ) {
        b14[1] = *( m2 + n * (k+27) + j );
      } else {
        b14[1] = 0;
      }
       if( k + 28 < n ) {
         b15[0] = *( m2 + n * (k+28) + j );
       } else {
         b15[0] = 0;
       }
      if( k + 29 < n ) {
        b15[1] = *( m2 + n * (k+29) + j );
      } else {
        b15[1] = 0;
      }
       if( k + 30 < n ) {
         b16[0] = *( m2 + n * (k+30) + j );
       } else {
         b16[0] = 0;
       }
      if( k + 31 < n ) {
        b16[1] = *( m2 + n * (k+31) + j );
      } else {
        b16[1] = 0;
      }
       if( k + 32 < n ) {
         b17[0] = *( m2 + n * (k+32) + j );
       } else {
         b17[0] = 0;
       }
      if( k + 33 < n ) {
        b17[1] = *( m2 + n * (k+33) + j );
      } else {
        b17[1] = 0;
      }
       if( k + 34 < n ) {
         b18[0] = *( m2 + n * (k+34) + j );
       } else {
         b18[0] = 0;
       }
      if( k + 35 < n ) {
        b18[1] = *( m2 + n * (k+35) + j );
      } else {
        b18[1] = 0;
      }
       if( k + 36 < n ) {
         b19[0] = *( m2 + n * (k+36) + j );
       } else {
         b19[0] = 0;
       }
      if( k + 37 < n ) {
        b19[1] = *( m2 + n * (k+37) + j );
      } else {
        b19[1] = 0;
      }
       if( k + 38 < n ) {
         b20[0] = *( m2 + n * (k+38) + j );
       } else {
         b20[0] = 0;
       }
      if( k + 39 < n ) {
        b20[1] = *( m2 + n * (k+39) + j );
      } else {
        b20[1] = 0;
      }
       if( k + 40 < n ) {
         b21[0] = *( m2 + n * (k+40) + j );
       } else {
         b21[0] = 0;
       }
      if( k + 41 < n ) {
        b21[1] = *( m2 + n * (k+41) + j );
      } else {
        b21[1] = 0;
      }
       if( k + 42 < n ) {
         b22[0] = *( m2 + n * (k+42) + j );
       } else {
         b22[0] = 0;
       }
      if( k + 43 < n ) {
        b22[1] = *( m2 + n * (k+43) + j );
      } else {
        b22[1] = 0;
      }
       if( k + 44 < n ) {
         b23[0] = *( m2 + n * (k+44) + j );
       } else {
         b23[0] = 0;
       }
      if( k + 45 < n ) {
        b23[1] = *( m2 + n * (k+45) + j );
      } else {
        b23[1] = 0;
      }
       if( k + 46 < n ) {
         b24[0] = *( m2 + n * (k+46) + j );
       } else {
         b24[0] = 0;
       }
      if( k + 47 < n ) {
        b24[1] = *( m2 + n * (k+47) + j );
      } else {
        b24[1] = 0;
      }
       if( k + 48 < n ) {
         b25[0] = *( m2 + n * (k+48) + j );
       } else {
         b25[0] = 0;
       }
      if( k + 49 < n ) {
        b25[1] = *( m2 + n * (k+49) + j );
      } else {
        b25[1] = 0;
      }
       if( k + 50 < n ) {
         b26[0] = *( m2 + n * (k+50) + j );
       } else {
         b26[0] = 0;
       }
      if( k + 51 < n ) {
        b26[1] = *( m2 + n * (k+51) + j );
      } else {
        b26[1] = 0;
      }
       if( k + 52 < n ) {
         b27[0] = *( m2 + n * (k+52) + j );
       } else {
         b27[0] = 0;
       }
      if( k + 53 < n ) {
        b27[1] = *( m2 + n * (k+53) + j );
      } else {
        b27[1] = 0;
      }
       if( k + 54 < n ) {
         b28[0] = *( m2 + n * (k+54) + j );
       } else {
         b28[0] = 0;
       }
      if( k + 55 < n ) {
        b28[1] = *( m2 + n * (k+55) + j );
      } else {
        b28[1] = 0;
      }
       if( k + 56 < n ) {
         b29[0] = *( m2 + n * (k+56) + j );
       } else {
         b29[0] = 0;
       }
      if( k + 57 < n ) {
        b29[1] = *( m2 + n * (k+57) + j );
      } else {
        b29[1] = 0;
      }
       if( k + 58 < n ) {
         b30[0] = *( m2 + n * (k+58) + j );
       } else {
         b30[0] = 0;
       }
      if( k + 59 < n ) {
        b30[1] = *( m2 + n * (k+59) + j );
      } else {
        b30[1] = 0;
      }
       if( k + 60 < n ) {
         b31[0] = *( m2 + n * (k+60) + j );
       } else {
         b31[0] = 0;
       }
      if( k + 61 < n ) {
        b31[1] = *( m2 + n * (k+61) + j );
      } else {
        b31[1] = 0;
      }
       if( k + 62 < n ) {
         b32[0] = *( m2 + n * (k+62) + j );
       } else {
         b32[0] = 0;
       }
      if( k + 63 < n ) {
        b32[1] = *( m2 + n * (k+63) + j );
      } else {
        b32[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t13 = _mm_load_pd( b7 );
       t15 = _mm_load_pd( b8 );
       t17 = _mm_load_pd( b9 );
       t19 = _mm_load_pd( b10 );
       t21 = _mm_load_pd( b11 );
       t23 = _mm_load_pd( b12 );
       t25 = _mm_load_pd( b13 );
       t27 = _mm_load_pd( b14 );
       t29 = _mm_load_pd( b15 );
       t31 = _mm_load_pd( b16 );
       t33 = _mm_load_pd( b17 );
       t35 = _mm_load_pd( b18 );
       t37 = _mm_load_pd( b19 );
       t39 = _mm_load_pd( b20 );
       t41 = _mm_load_pd( b21 );
       t43 = _mm_load_pd( b22 );
       t45 = _mm_load_pd( b23 );
       t47 = _mm_load_pd( b24 );
       t49 = _mm_load_pd( b25 );
       t51 = _mm_load_pd( b26 );
       t53 = _mm_load_pd( b27 );
       t55 = _mm_load_pd( b28 );
       t57 = _mm_load_pd( b29 );
       t59 = _mm_load_pd( b30 );
       t61 = _mm_load_pd( b31 );
       t63 = _mm_load_pd( b32 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );
       t13 = _mm_dp_pd( t12, t13, 0xff );
       t15 = _mm_dp_pd( t14, t15, 0xff );
       t17 = _mm_dp_pd( t16, t17, 0xff );
       t19 = _mm_dp_pd( t18, t19, 0xff );
       t21 = _mm_dp_pd( t20, t21, 0xff );
       t23 = _mm_dp_pd( t22, t23, 0xff );
       t25 = _mm_dp_pd( t24, t25, 0xff );
       t27 = _mm_dp_pd( t26, t27, 0xff );
       t29 = _mm_dp_pd( t28, t29, 0xff );
       t31 = _mm_dp_pd( t30, t31, 0xff );
       t33 = _mm_dp_pd( t32, t33, 0xff );
       t35 = _mm_dp_pd( t34, t35, 0xff );
       t37 = _mm_dp_pd( t36, t37, 0xff );
       t39 = _mm_dp_pd( t38, t39, 0xff );
       t41 = _mm_dp_pd( t40, t41, 0xff );
       t43 = _mm_dp_pd( t42, t43, 0xff );
       t45 = _mm_dp_pd( t44, t45, 0xff );
       t47 = _mm_dp_pd( t46, t47, 0xff );
       t49 = _mm_dp_pd( t48, t49, 0xff );
       t51 = _mm_dp_pd( t50, t51, 0xff );
       t53 = _mm_dp_pd( t52, t53, 0xff );
       t55 = _mm_dp_pd( t54, t55, 0xff );
       t57 = _mm_dp_pd( t56, t57, 0xff );
       t59 = _mm_dp_pd( t58, t59, 0xff );
       t61 = _mm_dp_pd( t60, t61, 0xff );
       t63 = _mm_dp_pd( t62, t63, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t13 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t15 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t17 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t19 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t21 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t23 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t25 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t27 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t29 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t31 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t33 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t35 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t37 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t39 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t41 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t43 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t45 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t47 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t49 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t51 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t53 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t55 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t57 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t59 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t61 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t63 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_128( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2], a7[2], b7[2], a8[2], b8[2], a9[2], b9[2], a10[2], b10[2], a11[2], b11[2], a12[2], b12[2], a13[2], b13[2], a14[2], b14[2], a15[2], b15[2], a16[2], b16[2], a17[2], b17[2], a18[2], b18[2], a19[2], b19[2], a20[2], b20[2], a21[2], b21[2], a22[2], b22[2], a23[2], b23[2], a24[2], b24[2], a25[2], b25[2], a26[2], b26[2], a27[2], b27[2], a28[2], b28[2], a29[2], b29[2], a30[2], b30[2], a31[2], b31[2], a32[2], b32[2], a33[2], b33[2], a34[2], b34[2], a35[2], b35[2], a36[2], b36[2], a37[2], b37[2], a38[2], b38[2], a39[2], b39[2], a40[2], b40[2], a41[2], b41[2], a42[2], b42[2], a43[2], b43[2], a44[2], b44[2], a45[2], b45[2], a46[2], b46[2], a47[2], b47[2], a48[2], b48[2], a49[2], b49[2], a50[2], b50[2], a51[2], b51[2], a52[2], b52[2], a53[2], b53[2], a54[2], b54[2], a55[2], b55[2], a56[2], b56[2], a57[2], b57[2], a58[2], b58[2], a59[2], b59[2], a60[2], b60[2], a61[2], b61[2], a62[2], b62[2], a63[2], b63[2], a64[2], b64[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95, t96, t97, t98, t99, t100, t101, t102, t103, t104, t105, t106, t107, t108, t109, t110, t111, t112, t113, t114, t115, t116, t117, t118, t119, t120, t121, t122, t123, t124, t125, t126, t127;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=128 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     if( k + 12 < n ) {
       a7[0] = *( m1 + n * i + (k+12) );
     } else {
       a7[0] = 0;
     }
     if( k + 13 < n ) {
       a7[1] = *( m1 + n * i + (k+13) );
     } else {
       a7[1] = 0;
     }
     if( k + 14 < n ) {
       a8[0] = *( m1 + n * i + (k+14) );
     } else {
       a8[0] = 0;
     }
     if( k + 15 < n ) {
       a8[1] = *( m1 + n * i + (k+15) );
     } else {
       a8[1] = 0;
     }
     if( k + 16 < n ) {
       a9[0] = *( m1 + n * i + (k+16) );
     } else {
       a9[0] = 0;
     }
     if( k + 17 < n ) {
       a9[1] = *( m1 + n * i + (k+17) );
     } else {
       a9[1] = 0;
     }
     if( k + 18 < n ) {
       a10[0] = *( m1 + n * i + (k+18) );
     } else {
       a10[0] = 0;
     }
     if( k + 19 < n ) {
       a10[1] = *( m1 + n * i + (k+19) );
     } else {
       a10[1] = 0;
     }
     if( k + 20 < n ) {
       a11[0] = *( m1 + n * i + (k+20) );
     } else {
       a11[0] = 0;
     }
     if( k + 21 < n ) {
       a11[1] = *( m1 + n * i + (k+21) );
     } else {
       a11[1] = 0;
     }
     if( k + 22 < n ) {
       a12[0] = *( m1 + n * i + (k+22) );
     } else {
       a12[0] = 0;
     }
     if( k + 23 < n ) {
       a12[1] = *( m1 + n * i + (k+23) );
     } else {
       a12[1] = 0;
     }
     if( k + 24 < n ) {
       a13[0] = *( m1 + n * i + (k+24) );
     } else {
       a13[0] = 0;
     }
     if( k + 25 < n ) {
       a13[1] = *( m1 + n * i + (k+25) );
     } else {
       a13[1] = 0;
     }
     if( k + 26 < n ) {
       a14[0] = *( m1 + n * i + (k+26) );
     } else {
       a14[0] = 0;
     }
     if( k + 27 < n ) {
       a14[1] = *( m1 + n * i + (k+27) );
     } else {
       a14[1] = 0;
     }
     if( k + 28 < n ) {
       a15[0] = *( m1 + n * i + (k+28) );
     } else {
       a15[0] = 0;
     }
     if( k + 29 < n ) {
       a15[1] = *( m1 + n * i + (k+29) );
     } else {
       a15[1] = 0;
     }
     if( k + 30 < n ) {
       a16[0] = *( m1 + n * i + (k+30) );
     } else {
       a16[0] = 0;
     }
     if( k + 31 < n ) {
       a16[1] = *( m1 + n * i + (k+31) );
     } else {
       a16[1] = 0;
     }
     if( k + 32 < n ) {
       a17[0] = *( m1 + n * i + (k+32) );
     } else {
       a17[0] = 0;
     }
     if( k + 33 < n ) {
       a17[1] = *( m1 + n * i + (k+33) );
     } else {
       a17[1] = 0;
     }
     if( k + 34 < n ) {
       a18[0] = *( m1 + n * i + (k+34) );
     } else {
       a18[0] = 0;
     }
     if( k + 35 < n ) {
       a18[1] = *( m1 + n * i + (k+35) );
     } else {
       a18[1] = 0;
     }
     if( k + 36 < n ) {
       a19[0] = *( m1 + n * i + (k+36) );
     } else {
       a19[0] = 0;
     }
     if( k + 37 < n ) {
       a19[1] = *( m1 + n * i + (k+37) );
     } else {
       a19[1] = 0;
     }
     if( k + 38 < n ) {
       a20[0] = *( m1 + n * i + (k+38) );
     } else {
       a20[0] = 0;
     }
     if( k + 39 < n ) {
       a20[1] = *( m1 + n * i + (k+39) );
     } else {
       a20[1] = 0;
     }
     if( k + 40 < n ) {
       a21[0] = *( m1 + n * i + (k+40) );
     } else {
       a21[0] = 0;
     }
     if( k + 41 < n ) {
       a21[1] = *( m1 + n * i + (k+41) );
     } else {
       a21[1] = 0;
     }
     if( k + 42 < n ) {
       a22[0] = *( m1 + n * i + (k+42) );
     } else {
       a22[0] = 0;
     }
     if( k + 43 < n ) {
       a22[1] = *( m1 + n * i + (k+43) );
     } else {
       a22[1] = 0;
     }
     if( k + 44 < n ) {
       a23[0] = *( m1 + n * i + (k+44) );
     } else {
       a23[0] = 0;
     }
     if( k + 45 < n ) {
       a23[1] = *( m1 + n * i + (k+45) );
     } else {
       a23[1] = 0;
     }
     if( k + 46 < n ) {
       a24[0] = *( m1 + n * i + (k+46) );
     } else {
       a24[0] = 0;
     }
     if( k + 47 < n ) {
       a24[1] = *( m1 + n * i + (k+47) );
     } else {
       a24[1] = 0;
     }
     if( k + 48 < n ) {
       a25[0] = *( m1 + n * i + (k+48) );
     } else {
       a25[0] = 0;
     }
     if( k + 49 < n ) {
       a25[1] = *( m1 + n * i + (k+49) );
     } else {
       a25[1] = 0;
     }
     if( k + 50 < n ) {
       a26[0] = *( m1 + n * i + (k+50) );
     } else {
       a26[0] = 0;
     }
     if( k + 51 < n ) {
       a26[1] = *( m1 + n * i + (k+51) );
     } else {
       a26[1] = 0;
     }
     if( k + 52 < n ) {
       a27[0] = *( m1 + n * i + (k+52) );
     } else {
       a27[0] = 0;
     }
     if( k + 53 < n ) {
       a27[1] = *( m1 + n * i + (k+53) );
     } else {
       a27[1] = 0;
     }
     if( k + 54 < n ) {
       a28[0] = *( m1 + n * i + (k+54) );
     } else {
       a28[0] = 0;
     }
     if( k + 55 < n ) {
       a28[1] = *( m1 + n * i + (k+55) );
     } else {
       a28[1] = 0;
     }
     if( k + 56 < n ) {
       a29[0] = *( m1 + n * i + (k+56) );
     } else {
       a29[0] = 0;
     }
     if( k + 57 < n ) {
       a29[1] = *( m1 + n * i + (k+57) );
     } else {
       a29[1] = 0;
     }
     if( k + 58 < n ) {
       a30[0] = *( m1 + n * i + (k+58) );
     } else {
       a30[0] = 0;
     }
     if( k + 59 < n ) {
       a30[1] = *( m1 + n * i + (k+59) );
     } else {
       a30[1] = 0;
     }
     if( k + 60 < n ) {
       a31[0] = *( m1 + n * i + (k+60) );
     } else {
       a31[0] = 0;
     }
     if( k + 61 < n ) {
       a31[1] = *( m1 + n * i + (k+61) );
     } else {
       a31[1] = 0;
     }
     if( k + 62 < n ) {
       a32[0] = *( m1 + n * i + (k+62) );
     } else {
       a32[0] = 0;
     }
     if( k + 63 < n ) {
       a32[1] = *( m1 + n * i + (k+63) );
     } else {
       a32[1] = 0;
     }
     if( k + 64 < n ) {
       a33[0] = *( m1 + n * i + (k+64) );
     } else {
       a33[0] = 0;
     }
     if( k + 65 < n ) {
       a33[1] = *( m1 + n * i + (k+65) );
     } else {
       a33[1] = 0;
     }
     if( k + 66 < n ) {
       a34[0] = *( m1 + n * i + (k+66) );
     } else {
       a34[0] = 0;
     }
     if( k + 67 < n ) {
       a34[1] = *( m1 + n * i + (k+67) );
     } else {
       a34[1] = 0;
     }
     if( k + 68 < n ) {
       a35[0] = *( m1 + n * i + (k+68) );
     } else {
       a35[0] = 0;
     }
     if( k + 69 < n ) {
       a35[1] = *( m1 + n * i + (k+69) );
     } else {
       a35[1] = 0;
     }
     if( k + 70 < n ) {
       a36[0] = *( m1 + n * i + (k+70) );
     } else {
       a36[0] = 0;
     }
     if( k + 71 < n ) {
       a36[1] = *( m1 + n * i + (k+71) );
     } else {
       a36[1] = 0;
     }
     if( k + 72 < n ) {
       a37[0] = *( m1 + n * i + (k+72) );
     } else {
       a37[0] = 0;
     }
     if( k + 73 < n ) {
       a37[1] = *( m1 + n * i + (k+73) );
     } else {
       a37[1] = 0;
     }
     if( k + 74 < n ) {
       a38[0] = *( m1 + n * i + (k+74) );
     } else {
       a38[0] = 0;
     }
     if( k + 75 < n ) {
       a38[1] = *( m1 + n * i + (k+75) );
     } else {
       a38[1] = 0;
     }
     if( k + 76 < n ) {
       a39[0] = *( m1 + n * i + (k+76) );
     } else {
       a39[0] = 0;
     }
     if( k + 77 < n ) {
       a39[1] = *( m1 + n * i + (k+77) );
     } else {
       a39[1] = 0;
     }
     if( k + 78 < n ) {
       a40[0] = *( m1 + n * i + (k+78) );
     } else {
       a40[0] = 0;
     }
     if( k + 79 < n ) {
       a40[1] = *( m1 + n * i + (k+79) );
     } else {
       a40[1] = 0;
     }
     if( k + 80 < n ) {
       a41[0] = *( m1 + n * i + (k+80) );
     } else {
       a41[0] = 0;
     }
     if( k + 81 < n ) {
       a41[1] = *( m1 + n * i + (k+81) );
     } else {
       a41[1] = 0;
     }
     if( k + 82 < n ) {
       a42[0] = *( m1 + n * i + (k+82) );
     } else {
       a42[0] = 0;
     }
     if( k + 83 < n ) {
       a42[1] = *( m1 + n * i + (k+83) );
     } else {
       a42[1] = 0;
     }
     if( k + 84 < n ) {
       a43[0] = *( m1 + n * i + (k+84) );
     } else {
       a43[0] = 0;
     }
     if( k + 85 < n ) {
       a43[1] = *( m1 + n * i + (k+85) );
     } else {
       a43[1] = 0;
     }
     if( k + 86 < n ) {
       a44[0] = *( m1 + n * i + (k+86) );
     } else {
       a44[0] = 0;
     }
     if( k + 87 < n ) {
       a44[1] = *( m1 + n * i + (k+87) );
     } else {
       a44[1] = 0;
     }
     if( k + 88 < n ) {
       a45[0] = *( m1 + n * i + (k+88) );
     } else {
       a45[0] = 0;
     }
     if( k + 89 < n ) {
       a45[1] = *( m1 + n * i + (k+89) );
     } else {
       a45[1] = 0;
     }
     if( k + 90 < n ) {
       a46[0] = *( m1 + n * i + (k+90) );
     } else {
       a46[0] = 0;
     }
     if( k + 91 < n ) {
       a46[1] = *( m1 + n * i + (k+91) );
     } else {
       a46[1] = 0;
     }
     if( k + 92 < n ) {
       a47[0] = *( m1 + n * i + (k+92) );
     } else {
       a47[0] = 0;
     }
     if( k + 93 < n ) {
       a47[1] = *( m1 + n * i + (k+93) );
     } else {
       a47[1] = 0;
     }
     if( k + 94 < n ) {
       a48[0] = *( m1 + n * i + (k+94) );
     } else {
       a48[0] = 0;
     }
     if( k + 95 < n ) {
       a48[1] = *( m1 + n * i + (k+95) );
     } else {
       a48[1] = 0;
     }
     if( k + 96 < n ) {
       a49[0] = *( m1 + n * i + (k+96) );
     } else {
       a49[0] = 0;
     }
     if( k + 97 < n ) {
       a49[1] = *( m1 + n * i + (k+97) );
     } else {
       a49[1] = 0;
     }
     if( k + 98 < n ) {
       a50[0] = *( m1 + n * i + (k+98) );
     } else {
       a50[0] = 0;
     }
     if( k + 99 < n ) {
       a50[1] = *( m1 + n * i + (k+99) );
     } else {
       a50[1] = 0;
     }
     if( k + 100 < n ) {
       a51[0] = *( m1 + n * i + (k+100) );
     } else {
       a51[0] = 0;
     }
     if( k + 101 < n ) {
       a51[1] = *( m1 + n * i + (k+101) );
     } else {
       a51[1] = 0;
     }
     if( k + 102 < n ) {
       a52[0] = *( m1 + n * i + (k+102) );
     } else {
       a52[0] = 0;
     }
     if( k + 103 < n ) {
       a52[1] = *( m1 + n * i + (k+103) );
     } else {
       a52[1] = 0;
     }
     if( k + 104 < n ) {
       a53[0] = *( m1 + n * i + (k+104) );
     } else {
       a53[0] = 0;
     }
     if( k + 105 < n ) {
       a53[1] = *( m1 + n * i + (k+105) );
     } else {
       a53[1] = 0;
     }
     if( k + 106 < n ) {
       a54[0] = *( m1 + n * i + (k+106) );
     } else {
       a54[0] = 0;
     }
     if( k + 107 < n ) {
       a54[1] = *( m1 + n * i + (k+107) );
     } else {
       a54[1] = 0;
     }
     if( k + 108 < n ) {
       a55[0] = *( m1 + n * i + (k+108) );
     } else {
       a55[0] = 0;
     }
     if( k + 109 < n ) {
       a55[1] = *( m1 + n * i + (k+109) );
     } else {
       a55[1] = 0;
     }
     if( k + 110 < n ) {
       a56[0] = *( m1 + n * i + (k+110) );
     } else {
       a56[0] = 0;
     }
     if( k + 111 < n ) {
       a56[1] = *( m1 + n * i + (k+111) );
     } else {
       a56[1] = 0;
     }
     if( k + 112 < n ) {
       a57[0] = *( m1 + n * i + (k+112) );
     } else {
       a57[0] = 0;
     }
     if( k + 113 < n ) {
       a57[1] = *( m1 + n * i + (k+113) );
     } else {
       a57[1] = 0;
     }
     if( k + 114 < n ) {
       a58[0] = *( m1 + n * i + (k+114) );
     } else {
       a58[0] = 0;
     }
     if( k + 115 < n ) {
       a58[1] = *( m1 + n * i + (k+115) );
     } else {
       a58[1] = 0;
     }
     if( k + 116 < n ) {
       a59[0] = *( m1 + n * i + (k+116) );
     } else {
       a59[0] = 0;
     }
     if( k + 117 < n ) {
       a59[1] = *( m1 + n * i + (k+117) );
     } else {
       a59[1] = 0;
     }
     if( k + 118 < n ) {
       a60[0] = *( m1 + n * i + (k+118) );
     } else {
       a60[0] = 0;
     }
     if( k + 119 < n ) {
       a60[1] = *( m1 + n * i + (k+119) );
     } else {
       a60[1] = 0;
     }
     if( k + 120 < n ) {
       a61[0] = *( m1 + n * i + (k+120) );
     } else {
       a61[0] = 0;
     }
     if( k + 121 < n ) {
       a61[1] = *( m1 + n * i + (k+121) );
     } else {
       a61[1] = 0;
     }
     if( k + 122 < n ) {
       a62[0] = *( m1 + n * i + (k+122) );
     } else {
       a62[0] = 0;
     }
     if( k + 123 < n ) {
       a62[1] = *( m1 + n * i + (k+123) );
     } else {
       a62[1] = 0;
     }
     if( k + 124 < n ) {
       a63[0] = *( m1 + n * i + (k+124) );
     } else {
       a63[0] = 0;
     }
     if( k + 125 < n ) {
       a63[1] = *( m1 + n * i + (k+125) );
     } else {
       a63[1] = 0;
     }
     if( k + 126 < n ) {
       a64[0] = *( m1 + n * i + (k+126) );
     } else {
       a64[0] = 0;
     }
     if( k + 127 < n ) {
       a64[1] = *( m1 + n * i + (k+127) );
     } else {
       a64[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );
     t12 = _mm_load_pd( a7 );
     t14 = _mm_load_pd( a8 );
     t16 = _mm_load_pd( a9 );
     t18 = _mm_load_pd( a10 );
     t20 = _mm_load_pd( a11 );
     t22 = _mm_load_pd( a12 );
     t24 = _mm_load_pd( a13 );
     t26 = _mm_load_pd( a14 );
     t28 = _mm_load_pd( a15 );
     t30 = _mm_load_pd( a16 );
     t32 = _mm_load_pd( a17 );
     t34 = _mm_load_pd( a18 );
     t36 = _mm_load_pd( a19 );
     t38 = _mm_load_pd( a20 );
     t40 = _mm_load_pd( a21 );
     t42 = _mm_load_pd( a22 );
     t44 = _mm_load_pd( a23 );
     t46 = _mm_load_pd( a24 );
     t48 = _mm_load_pd( a25 );
     t50 = _mm_load_pd( a26 );
     t52 = _mm_load_pd( a27 );
     t54 = _mm_load_pd( a28 );
     t56 = _mm_load_pd( a29 );
     t58 = _mm_load_pd( a30 );
     t60 = _mm_load_pd( a31 );
     t62 = _mm_load_pd( a32 );
     t64 = _mm_load_pd( a33 );
     t66 = _mm_load_pd( a34 );
     t68 = _mm_load_pd( a35 );
     t70 = _mm_load_pd( a36 );
     t72 = _mm_load_pd( a37 );
     t74 = _mm_load_pd( a38 );
     t76 = _mm_load_pd( a39 );
     t78 = _mm_load_pd( a40 );
     t80 = _mm_load_pd( a41 );
     t82 = _mm_load_pd( a42 );
     t84 = _mm_load_pd( a43 );
     t86 = _mm_load_pd( a44 );
     t88 = _mm_load_pd( a45 );
     t90 = _mm_load_pd( a46 );
     t92 = _mm_load_pd( a47 );
     t94 = _mm_load_pd( a48 );
     t96 = _mm_load_pd( a49 );
     t98 = _mm_load_pd( a50 );
     t100 = _mm_load_pd( a51 );
     t102 = _mm_load_pd( a52 );
     t104 = _mm_load_pd( a53 );
     t106 = _mm_load_pd( a54 );
     t108 = _mm_load_pd( a55 );
     t110 = _mm_load_pd( a56 );
     t112 = _mm_load_pd( a57 );
     t114 = _mm_load_pd( a58 );
     t116 = _mm_load_pd( a59 );
     t118 = _mm_load_pd( a60 );
     t120 = _mm_load_pd( a61 );
     t122 = _mm_load_pd( a62 );
     t124 = _mm_load_pd( a63 );
     t126 = _mm_load_pd( a64 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       if( k + 12 < n ) {
         b7[0] = *( m2 + n * (k+12) + j );
       } else {
         b7[0] = 0;
       }
      if( k + 13 < n ) {
        b7[1] = *( m2 + n * (k+13) + j );
      } else {
        b7[1] = 0;
      }
       if( k + 14 < n ) {
         b8[0] = *( m2 + n * (k+14) + j );
       } else {
         b8[0] = 0;
       }
      if( k + 15 < n ) {
        b8[1] = *( m2 + n * (k+15) + j );
      } else {
        b8[1] = 0;
      }
       if( k + 16 < n ) {
         b9[0] = *( m2 + n * (k+16) + j );
       } else {
         b9[0] = 0;
       }
      if( k + 17 < n ) {
        b9[1] = *( m2 + n * (k+17) + j );
      } else {
        b9[1] = 0;
      }
       if( k + 18 < n ) {
         b10[0] = *( m2 + n * (k+18) + j );
       } else {
         b10[0] = 0;
       }
      if( k + 19 < n ) {
        b10[1] = *( m2 + n * (k+19) + j );
      } else {
        b10[1] = 0;
      }
       if( k + 20 < n ) {
         b11[0] = *( m2 + n * (k+20) + j );
       } else {
         b11[0] = 0;
       }
      if( k + 21 < n ) {
        b11[1] = *( m2 + n * (k+21) + j );
      } else {
        b11[1] = 0;
      }
       if( k + 22 < n ) {
         b12[0] = *( m2 + n * (k+22) + j );
       } else {
         b12[0] = 0;
       }
      if( k + 23 < n ) {
        b12[1] = *( m2 + n * (k+23) + j );
      } else {
        b12[1] = 0;
      }
       if( k + 24 < n ) {
         b13[0] = *( m2 + n * (k+24) + j );
       } else {
         b13[0] = 0;
       }
      if( k + 25 < n ) {
        b13[1] = *( m2 + n * (k+25) + j );
      } else {
        b13[1] = 0;
      }
       if( k + 26 < n ) {
         b14[0] = *( m2 + n * (k+26) + j );
       } else {
         b14[0] = 0;
       }
      if( k + 27 < n ) {
        b14[1] = *( m2 + n * (k+27) + j );
      } else {
        b14[1] = 0;
      }
       if( k + 28 < n ) {
         b15[0] = *( m2 + n * (k+28) + j );
       } else {
         b15[0] = 0;
       }
      if( k + 29 < n ) {
        b15[1] = *( m2 + n * (k+29) + j );
      } else {
        b15[1] = 0;
      }
       if( k + 30 < n ) {
         b16[0] = *( m2 + n * (k+30) + j );
       } else {
         b16[0] = 0;
       }
      if( k + 31 < n ) {
        b16[1] = *( m2 + n * (k+31) + j );
      } else {
        b16[1] = 0;
      }
       if( k + 32 < n ) {
         b17[0] = *( m2 + n * (k+32) + j );
       } else {
         b17[0] = 0;
       }
      if( k + 33 < n ) {
        b17[1] = *( m2 + n * (k+33) + j );
      } else {
        b17[1] = 0;
      }
       if( k + 34 < n ) {
         b18[0] = *( m2 + n * (k+34) + j );
       } else {
         b18[0] = 0;
       }
      if( k + 35 < n ) {
        b18[1] = *( m2 + n * (k+35) + j );
      } else {
        b18[1] = 0;
      }
       if( k + 36 < n ) {
         b19[0] = *( m2 + n * (k+36) + j );
       } else {
         b19[0] = 0;
       }
      if( k + 37 < n ) {
        b19[1] = *( m2 + n * (k+37) + j );
      } else {
        b19[1] = 0;
      }
       if( k + 38 < n ) {
         b20[0] = *( m2 + n * (k+38) + j );
       } else {
         b20[0] = 0;
       }
      if( k + 39 < n ) {
        b20[1] = *( m2 + n * (k+39) + j );
      } else {
        b20[1] = 0;
      }
       if( k + 40 < n ) {
         b21[0] = *( m2 + n * (k+40) + j );
       } else {
         b21[0] = 0;
       }
      if( k + 41 < n ) {
        b21[1] = *( m2 + n * (k+41) + j );
      } else {
        b21[1] = 0;
      }
       if( k + 42 < n ) {
         b22[0] = *( m2 + n * (k+42) + j );
       } else {
         b22[0] = 0;
       }
      if( k + 43 < n ) {
        b22[1] = *( m2 + n * (k+43) + j );
      } else {
        b22[1] = 0;
      }
       if( k + 44 < n ) {
         b23[0] = *( m2 + n * (k+44) + j );
       } else {
         b23[0] = 0;
       }
      if( k + 45 < n ) {
        b23[1] = *( m2 + n * (k+45) + j );
      } else {
        b23[1] = 0;
      }
       if( k + 46 < n ) {
         b24[0] = *( m2 + n * (k+46) + j );
       } else {
         b24[0] = 0;
       }
      if( k + 47 < n ) {
        b24[1] = *( m2 + n * (k+47) + j );
      } else {
        b24[1] = 0;
      }
       if( k + 48 < n ) {
         b25[0] = *( m2 + n * (k+48) + j );
       } else {
         b25[0] = 0;
       }
      if( k + 49 < n ) {
        b25[1] = *( m2 + n * (k+49) + j );
      } else {
        b25[1] = 0;
      }
       if( k + 50 < n ) {
         b26[0] = *( m2 + n * (k+50) + j );
       } else {
         b26[0] = 0;
       }
      if( k + 51 < n ) {
        b26[1] = *( m2 + n * (k+51) + j );
      } else {
        b26[1] = 0;
      }
       if( k + 52 < n ) {
         b27[0] = *( m2 + n * (k+52) + j );
       } else {
         b27[0] = 0;
       }
      if( k + 53 < n ) {
        b27[1] = *( m2 + n * (k+53) + j );
      } else {
        b27[1] = 0;
      }
       if( k + 54 < n ) {
         b28[0] = *( m2 + n * (k+54) + j );
       } else {
         b28[0] = 0;
       }
      if( k + 55 < n ) {
        b28[1] = *( m2 + n * (k+55) + j );
      } else {
        b28[1] = 0;
      }
       if( k + 56 < n ) {
         b29[0] = *( m2 + n * (k+56) + j );
       } else {
         b29[0] = 0;
       }
      if( k + 57 < n ) {
        b29[1] = *( m2 + n * (k+57) + j );
      } else {
        b29[1] = 0;
      }
       if( k + 58 < n ) {
         b30[0] = *( m2 + n * (k+58) + j );
       } else {
         b30[0] = 0;
       }
      if( k + 59 < n ) {
        b30[1] = *( m2 + n * (k+59) + j );
      } else {
        b30[1] = 0;
      }
       if( k + 60 < n ) {
         b31[0] = *( m2 + n * (k+60) + j );
       } else {
         b31[0] = 0;
       }
      if( k + 61 < n ) {
        b31[1] = *( m2 + n * (k+61) + j );
      } else {
        b31[1] = 0;
      }
       if( k + 62 < n ) {
         b32[0] = *( m2 + n * (k+62) + j );
       } else {
         b32[0] = 0;
       }
      if( k + 63 < n ) {
        b32[1] = *( m2 + n * (k+63) + j );
      } else {
        b32[1] = 0;
      }
       if( k + 64 < n ) {
         b33[0] = *( m2 + n * (k+64) + j );
       } else {
         b33[0] = 0;
       }
      if( k + 65 < n ) {
        b33[1] = *( m2 + n * (k+65) + j );
      } else {
        b33[1] = 0;
      }
       if( k + 66 < n ) {
         b34[0] = *( m2 + n * (k+66) + j );
       } else {
         b34[0] = 0;
       }
      if( k + 67 < n ) {
        b34[1] = *( m2 + n * (k+67) + j );
      } else {
        b34[1] = 0;
      }
       if( k + 68 < n ) {
         b35[0] = *( m2 + n * (k+68) + j );
       } else {
         b35[0] = 0;
       }
      if( k + 69 < n ) {
        b35[1] = *( m2 + n * (k+69) + j );
      } else {
        b35[1] = 0;
      }
       if( k + 70 < n ) {
         b36[0] = *( m2 + n * (k+70) + j );
       } else {
         b36[0] = 0;
       }
      if( k + 71 < n ) {
        b36[1] = *( m2 + n * (k+71) + j );
      } else {
        b36[1] = 0;
      }
       if( k + 72 < n ) {
         b37[0] = *( m2 + n * (k+72) + j );
       } else {
         b37[0] = 0;
       }
      if( k + 73 < n ) {
        b37[1] = *( m2 + n * (k+73) + j );
      } else {
        b37[1] = 0;
      }
       if( k + 74 < n ) {
         b38[0] = *( m2 + n * (k+74) + j );
       } else {
         b38[0] = 0;
       }
      if( k + 75 < n ) {
        b38[1] = *( m2 + n * (k+75) + j );
      } else {
        b38[1] = 0;
      }
       if( k + 76 < n ) {
         b39[0] = *( m2 + n * (k+76) + j );
       } else {
         b39[0] = 0;
       }
      if( k + 77 < n ) {
        b39[1] = *( m2 + n * (k+77) + j );
      } else {
        b39[1] = 0;
      }
       if( k + 78 < n ) {
         b40[0] = *( m2 + n * (k+78) + j );
       } else {
         b40[0] = 0;
       }
      if( k + 79 < n ) {
        b40[1] = *( m2 + n * (k+79) + j );
      } else {
        b40[1] = 0;
      }
       if( k + 80 < n ) {
         b41[0] = *( m2 + n * (k+80) + j );
       } else {
         b41[0] = 0;
       }
      if( k + 81 < n ) {
        b41[1] = *( m2 + n * (k+81) + j );
      } else {
        b41[1] = 0;
      }
       if( k + 82 < n ) {
         b42[0] = *( m2 + n * (k+82) + j );
       } else {
         b42[0] = 0;
       }
      if( k + 83 < n ) {
        b42[1] = *( m2 + n * (k+83) + j );
      } else {
        b42[1] = 0;
      }
       if( k + 84 < n ) {
         b43[0] = *( m2 + n * (k+84) + j );
       } else {
         b43[0] = 0;
       }
      if( k + 85 < n ) {
        b43[1] = *( m2 + n * (k+85) + j );
      } else {
        b43[1] = 0;
      }
       if( k + 86 < n ) {
         b44[0] = *( m2 + n * (k+86) + j );
       } else {
         b44[0] = 0;
       }
      if( k + 87 < n ) {
        b44[1] = *( m2 + n * (k+87) + j );
      } else {
        b44[1] = 0;
      }
       if( k + 88 < n ) {
         b45[0] = *( m2 + n * (k+88) + j );
       } else {
         b45[0] = 0;
       }
      if( k + 89 < n ) {
        b45[1] = *( m2 + n * (k+89) + j );
      } else {
        b45[1] = 0;
      }
       if( k + 90 < n ) {
         b46[0] = *( m2 + n * (k+90) + j );
       } else {
         b46[0] = 0;
       }
      if( k + 91 < n ) {
        b46[1] = *( m2 + n * (k+91) + j );
      } else {
        b46[1] = 0;
      }
       if( k + 92 < n ) {
         b47[0] = *( m2 + n * (k+92) + j );
       } else {
         b47[0] = 0;
       }
      if( k + 93 < n ) {
        b47[1] = *( m2 + n * (k+93) + j );
      } else {
        b47[1] = 0;
      }
       if( k + 94 < n ) {
         b48[0] = *( m2 + n * (k+94) + j );
       } else {
         b48[0] = 0;
       }
      if( k + 95 < n ) {
        b48[1] = *( m2 + n * (k+95) + j );
      } else {
        b48[1] = 0;
      }
       if( k + 96 < n ) {
         b49[0] = *( m2 + n * (k+96) + j );
       } else {
         b49[0] = 0;
       }
      if( k + 97 < n ) {
        b49[1] = *( m2 + n * (k+97) + j );
      } else {
        b49[1] = 0;
      }
       if( k + 98 < n ) {
         b50[0] = *( m2 + n * (k+98) + j );
       } else {
         b50[0] = 0;
       }
      if( k + 99 < n ) {
        b50[1] = *( m2 + n * (k+99) + j );
      } else {
        b50[1] = 0;
      }
       if( k + 100 < n ) {
         b51[0] = *( m2 + n * (k+100) + j );
       } else {
         b51[0] = 0;
       }
      if( k + 101 < n ) {
        b51[1] = *( m2 + n * (k+101) + j );
      } else {
        b51[1] = 0;
      }
       if( k + 102 < n ) {
         b52[0] = *( m2 + n * (k+102) + j );
       } else {
         b52[0] = 0;
       }
      if( k + 103 < n ) {
        b52[1] = *( m2 + n * (k+103) + j );
      } else {
        b52[1] = 0;
      }
       if( k + 104 < n ) {
         b53[0] = *( m2 + n * (k+104) + j );
       } else {
         b53[0] = 0;
       }
      if( k + 105 < n ) {
        b53[1] = *( m2 + n * (k+105) + j );
      } else {
        b53[1] = 0;
      }
       if( k + 106 < n ) {
         b54[0] = *( m2 + n * (k+106) + j );
       } else {
         b54[0] = 0;
       }
      if( k + 107 < n ) {
        b54[1] = *( m2 + n * (k+107) + j );
      } else {
        b54[1] = 0;
      }
       if( k + 108 < n ) {
         b55[0] = *( m2 + n * (k+108) + j );
       } else {
         b55[0] = 0;
       }
      if( k + 109 < n ) {
        b55[1] = *( m2 + n * (k+109) + j );
      } else {
        b55[1] = 0;
      }
       if( k + 110 < n ) {
         b56[0] = *( m2 + n * (k+110) + j );
       } else {
         b56[0] = 0;
       }
      if( k + 111 < n ) {
        b56[1] = *( m2 + n * (k+111) + j );
      } else {
        b56[1] = 0;
      }
       if( k + 112 < n ) {
         b57[0] = *( m2 + n * (k+112) + j );
       } else {
         b57[0] = 0;
       }
      if( k + 113 < n ) {
        b57[1] = *( m2 + n * (k+113) + j );
      } else {
        b57[1] = 0;
      }
       if( k + 114 < n ) {
         b58[0] = *( m2 + n * (k+114) + j );
       } else {
         b58[0] = 0;
       }
      if( k + 115 < n ) {
        b58[1] = *( m2 + n * (k+115) + j );
      } else {
        b58[1] = 0;
      }
       if( k + 116 < n ) {
         b59[0] = *( m2 + n * (k+116) + j );
       } else {
         b59[0] = 0;
       }
      if( k + 117 < n ) {
        b59[1] = *( m2 + n * (k+117) + j );
      } else {
        b59[1] = 0;
      }
       if( k + 118 < n ) {
         b60[0] = *( m2 + n * (k+118) + j );
       } else {
         b60[0] = 0;
       }
      if( k + 119 < n ) {
        b60[1] = *( m2 + n * (k+119) + j );
      } else {
        b60[1] = 0;
      }
       if( k + 120 < n ) {
         b61[0] = *( m2 + n * (k+120) + j );
       } else {
         b61[0] = 0;
       }
      if( k + 121 < n ) {
        b61[1] = *( m2 + n * (k+121) + j );
      } else {
        b61[1] = 0;
      }
       if( k + 122 < n ) {
         b62[0] = *( m2 + n * (k+122) + j );
       } else {
         b62[0] = 0;
       }
      if( k + 123 < n ) {
        b62[1] = *( m2 + n * (k+123) + j );
      } else {
        b62[1] = 0;
      }
       if( k + 124 < n ) {
         b63[0] = *( m2 + n * (k+124) + j );
       } else {
         b63[0] = 0;
       }
      if( k + 125 < n ) {
        b63[1] = *( m2 + n * (k+125) + j );
      } else {
        b63[1] = 0;
      }
       if( k + 126 < n ) {
         b64[0] = *( m2 + n * (k+126) + j );
       } else {
         b64[0] = 0;
       }
      if( k + 127 < n ) {
        b64[1] = *( m2 + n * (k+127) + j );
      } else {
        b64[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t13 = _mm_load_pd( b7 );
       t15 = _mm_load_pd( b8 );
       t17 = _mm_load_pd( b9 );
       t19 = _mm_load_pd( b10 );
       t21 = _mm_load_pd( b11 );
       t23 = _mm_load_pd( b12 );
       t25 = _mm_load_pd( b13 );
       t27 = _mm_load_pd( b14 );
       t29 = _mm_load_pd( b15 );
       t31 = _mm_load_pd( b16 );
       t33 = _mm_load_pd( b17 );
       t35 = _mm_load_pd( b18 );
       t37 = _mm_load_pd( b19 );
       t39 = _mm_load_pd( b20 );
       t41 = _mm_load_pd( b21 );
       t43 = _mm_load_pd( b22 );
       t45 = _mm_load_pd( b23 );
       t47 = _mm_load_pd( b24 );
       t49 = _mm_load_pd( b25 );
       t51 = _mm_load_pd( b26 );
       t53 = _mm_load_pd( b27 );
       t55 = _mm_load_pd( b28 );
       t57 = _mm_load_pd( b29 );
       t59 = _mm_load_pd( b30 );
       t61 = _mm_load_pd( b31 );
       t63 = _mm_load_pd( b32 );
       t65 = _mm_load_pd( b33 );
       t67 = _mm_load_pd( b34 );
       t69 = _mm_load_pd( b35 );
       t71 = _mm_load_pd( b36 );
       t73 = _mm_load_pd( b37 );
       t75 = _mm_load_pd( b38 );
       t77 = _mm_load_pd( b39 );
       t79 = _mm_load_pd( b40 );
       t81 = _mm_load_pd( b41 );
       t83 = _mm_load_pd( b42 );
       t85 = _mm_load_pd( b43 );
       t87 = _mm_load_pd( b44 );
       t89 = _mm_load_pd( b45 );
       t91 = _mm_load_pd( b46 );
       t93 = _mm_load_pd( b47 );
       t95 = _mm_load_pd( b48 );
       t97 = _mm_load_pd( b49 );
       t99 = _mm_load_pd( b50 );
       t101 = _mm_load_pd( b51 );
       t103 = _mm_load_pd( b52 );
       t105 = _mm_load_pd( b53 );
       t107 = _mm_load_pd( b54 );
       t109 = _mm_load_pd( b55 );
       t111 = _mm_load_pd( b56 );
       t113 = _mm_load_pd( b57 );
       t115 = _mm_load_pd( b58 );
       t117 = _mm_load_pd( b59 );
       t119 = _mm_load_pd( b60 );
       t121 = _mm_load_pd( b61 );
       t123 = _mm_load_pd( b62 );
       t125 = _mm_load_pd( b63 );
       t127 = _mm_load_pd( b64 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );
       t13 = _mm_dp_pd( t12, t13, 0xff );
       t15 = _mm_dp_pd( t14, t15, 0xff );
       t17 = _mm_dp_pd( t16, t17, 0xff );
       t19 = _mm_dp_pd( t18, t19, 0xff );
       t21 = _mm_dp_pd( t20, t21, 0xff );
       t23 = _mm_dp_pd( t22, t23, 0xff );
       t25 = _mm_dp_pd( t24, t25, 0xff );
       t27 = _mm_dp_pd( t26, t27, 0xff );
       t29 = _mm_dp_pd( t28, t29, 0xff );
       t31 = _mm_dp_pd( t30, t31, 0xff );
       t33 = _mm_dp_pd( t32, t33, 0xff );
       t35 = _mm_dp_pd( t34, t35, 0xff );
       t37 = _mm_dp_pd( t36, t37, 0xff );
       t39 = _mm_dp_pd( t38, t39, 0xff );
       t41 = _mm_dp_pd( t40, t41, 0xff );
       t43 = _mm_dp_pd( t42, t43, 0xff );
       t45 = _mm_dp_pd( t44, t45, 0xff );
       t47 = _mm_dp_pd( t46, t47, 0xff );
       t49 = _mm_dp_pd( t48, t49, 0xff );
       t51 = _mm_dp_pd( t50, t51, 0xff );
       t53 = _mm_dp_pd( t52, t53, 0xff );
       t55 = _mm_dp_pd( t54, t55, 0xff );
       t57 = _mm_dp_pd( t56, t57, 0xff );
       t59 = _mm_dp_pd( t58, t59, 0xff );
       t61 = _mm_dp_pd( t60, t61, 0xff );
       t63 = _mm_dp_pd( t62, t63, 0xff );
       t65 = _mm_dp_pd( t64, t65, 0xff );
       t67 = _mm_dp_pd( t66, t67, 0xff );
       t69 = _mm_dp_pd( t68, t69, 0xff );
       t71 = _mm_dp_pd( t70, t71, 0xff );
       t73 = _mm_dp_pd( t72, t73, 0xff );
       t75 = _mm_dp_pd( t74, t75, 0xff );
       t77 = _mm_dp_pd( t76, t77, 0xff );
       t79 = _mm_dp_pd( t78, t79, 0xff );
       t81 = _mm_dp_pd( t80, t81, 0xff );
       t83 = _mm_dp_pd( t82, t83, 0xff );
       t85 = _mm_dp_pd( t84, t85, 0xff );
       t87 = _mm_dp_pd( t86, t87, 0xff );
       t89 = _mm_dp_pd( t88, t89, 0xff );
       t91 = _mm_dp_pd( t90, t91, 0xff );
       t93 = _mm_dp_pd( t92, t93, 0xff );
       t95 = _mm_dp_pd( t94, t95, 0xff );
       t97 = _mm_dp_pd( t96, t97, 0xff );
       t99 = _mm_dp_pd( t98, t99, 0xff );
       t101 = _mm_dp_pd( t100, t101, 0xff );
       t103 = _mm_dp_pd( t102, t103, 0xff );
       t105 = _mm_dp_pd( t104, t105, 0xff );
       t107 = _mm_dp_pd( t106, t107, 0xff );
       t109 = _mm_dp_pd( t108, t109, 0xff );
       t111 = _mm_dp_pd( t110, t111, 0xff );
       t113 = _mm_dp_pd( t112, t113, 0xff );
       t115 = _mm_dp_pd( t114, t115, 0xff );
       t117 = _mm_dp_pd( t116, t117, 0xff );
       t119 = _mm_dp_pd( t118, t119, 0xff );
       t121 = _mm_dp_pd( t120, t121, 0xff );
       t123 = _mm_dp_pd( t122, t123, 0xff );
       t125 = _mm_dp_pd( t124, t125, 0xff );
       t127 = _mm_dp_pd( t126, t127, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t13 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t15 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t17 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t19 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t21 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t23 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t25 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t27 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t29 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t31 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t33 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t35 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t37 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t39 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t41 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t43 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t45 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t47 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t49 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t51 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t53 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t55 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t57 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t59 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t61 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t63 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t65 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t67 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t69 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t71 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t73 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t75 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t77 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t79 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t81 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t83 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t85 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t87 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t89 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t91 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t93 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t95 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t97 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t99 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t101 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t103 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t105 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t107 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t109 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t111 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t113 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t115 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t117 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t119 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t121 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t123 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t125 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t127 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_256( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2], a7[2], b7[2], a8[2], b8[2], a9[2], b9[2], a10[2], b10[2], a11[2], b11[2], a12[2], b12[2], a13[2], b13[2], a14[2], b14[2], a15[2], b15[2], a16[2], b16[2], a17[2], b17[2], a18[2], b18[2], a19[2], b19[2], a20[2], b20[2], a21[2], b21[2], a22[2], b22[2], a23[2], b23[2], a24[2], b24[2], a25[2], b25[2], a26[2], b26[2], a27[2], b27[2], a28[2], b28[2], a29[2], b29[2], a30[2], b30[2], a31[2], b31[2], a32[2], b32[2], a33[2], b33[2], a34[2], b34[2], a35[2], b35[2], a36[2], b36[2], a37[2], b37[2], a38[2], b38[2], a39[2], b39[2], a40[2], b40[2], a41[2], b41[2], a42[2], b42[2], a43[2], b43[2], a44[2], b44[2], a45[2], b45[2], a46[2], b46[2], a47[2], b47[2], a48[2], b48[2], a49[2], b49[2], a50[2], b50[2], a51[2], b51[2], a52[2], b52[2], a53[2], b53[2], a54[2], b54[2], a55[2], b55[2], a56[2], b56[2], a57[2], b57[2], a58[2], b58[2], a59[2], b59[2], a60[2], b60[2], a61[2], b61[2], a62[2], b62[2], a63[2], b63[2], a64[2], b64[2], a65[2], b65[2], a66[2], b66[2], a67[2], b67[2], a68[2], b68[2], a69[2], b69[2], a70[2], b70[2], a71[2], b71[2], a72[2], b72[2], a73[2], b73[2], a74[2], b74[2], a75[2], b75[2], a76[2], b76[2], a77[2], b77[2], a78[2], b78[2], a79[2], b79[2], a80[2], b80[2], a81[2], b81[2], a82[2], b82[2], a83[2], b83[2], a84[2], b84[2], a85[2], b85[2], a86[2], b86[2], a87[2], b87[2], a88[2], b88[2], a89[2], b89[2], a90[2], b90[2], a91[2], b91[2], a92[2], b92[2], a93[2], b93[2], a94[2], b94[2], a95[2], b95[2], a96[2], b96[2], a97[2], b97[2], a98[2], b98[2], a99[2], b99[2], a100[2], b100[2], a101[2], b101[2], a102[2], b102[2], a103[2], b103[2], a104[2], b104[2], a105[2], b105[2], a106[2], b106[2], a107[2], b107[2], a108[2], b108[2], a109[2], b109[2], a110[2], b110[2], a111[2], b111[2], a112[2], b112[2], a113[2], b113[2], a114[2], b114[2], a115[2], b115[2], a116[2], b116[2], a117[2], b117[2], a118[2], b118[2], a119[2], b119[2], a120[2], b120[2], a121[2], b121[2], a122[2], b122[2], a123[2], b123[2], a124[2], b124[2], a125[2], b125[2], a126[2], b126[2], a127[2], b127[2], a128[2], b128[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95, t96, t97, t98, t99, t100, t101, t102, t103, t104, t105, t106, t107, t108, t109, t110, t111, t112, t113, t114, t115, t116, t117, t118, t119, t120, t121, t122, t123, t124, t125, t126, t127, t128, t129, t130, t131, t132, t133, t134, t135, t136, t137, t138, t139, t140, t141, t142, t143, t144, t145, t146, t147, t148, t149, t150, t151, t152, t153, t154, t155, t156, t157, t158, t159, t160, t161, t162, t163, t164, t165, t166, t167, t168, t169, t170, t171, t172, t173, t174, t175, t176, t177, t178, t179, t180, t181, t182, t183, t184, t185, t186, t187, t188, t189, t190, t191, t192, t193, t194, t195, t196, t197, t198, t199, t200, t201, t202, t203, t204, t205, t206, t207, t208, t209, t210, t211, t212, t213, t214, t215, t216, t217, t218, t219, t220, t221, t222, t223, t224, t225, t226, t227, t228, t229, t230, t231, t232, t233, t234, t235, t236, t237, t238, t239, t240, t241, t242, t243, t244, t245, t246, t247, t248, t249, t250, t251, t252, t253, t254, t255;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=256 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     if( k + 12 < n ) {
       a7[0] = *( m1 + n * i + (k+12) );
     } else {
       a7[0] = 0;
     }
     if( k + 13 < n ) {
       a7[1] = *( m1 + n * i + (k+13) );
     } else {
       a7[1] = 0;
     }
     if( k + 14 < n ) {
       a8[0] = *( m1 + n * i + (k+14) );
     } else {
       a8[0] = 0;
     }
     if( k + 15 < n ) {
       a8[1] = *( m1 + n * i + (k+15) );
     } else {
       a8[1] = 0;
     }
     if( k + 16 < n ) {
       a9[0] = *( m1 + n * i + (k+16) );
     } else {
       a9[0] = 0;
     }
     if( k + 17 < n ) {
       a9[1] = *( m1 + n * i + (k+17) );
     } else {
       a9[1] = 0;
     }
     if( k + 18 < n ) {
       a10[0] = *( m1 + n * i + (k+18) );
     } else {
       a10[0] = 0;
     }
     if( k + 19 < n ) {
       a10[1] = *( m1 + n * i + (k+19) );
     } else {
       a10[1] = 0;
     }
     if( k + 20 < n ) {
       a11[0] = *( m1 + n * i + (k+20) );
     } else {
       a11[0] = 0;
     }
     if( k + 21 < n ) {
       a11[1] = *( m1 + n * i + (k+21) );
     } else {
       a11[1] = 0;
     }
     if( k + 22 < n ) {
       a12[0] = *( m1 + n * i + (k+22) );
     } else {
       a12[0] = 0;
     }
     if( k + 23 < n ) {
       a12[1] = *( m1 + n * i + (k+23) );
     } else {
       a12[1] = 0;
     }
     if( k + 24 < n ) {
       a13[0] = *( m1 + n * i + (k+24) );
     } else {
       a13[0] = 0;
     }
     if( k + 25 < n ) {
       a13[1] = *( m1 + n * i + (k+25) );
     } else {
       a13[1] = 0;
     }
     if( k + 26 < n ) {
       a14[0] = *( m1 + n * i + (k+26) );
     } else {
       a14[0] = 0;
     }
     if( k + 27 < n ) {
       a14[1] = *( m1 + n * i + (k+27) );
     } else {
       a14[1] = 0;
     }
     if( k + 28 < n ) {
       a15[0] = *( m1 + n * i + (k+28) );
     } else {
       a15[0] = 0;
     }
     if( k + 29 < n ) {
       a15[1] = *( m1 + n * i + (k+29) );
     } else {
       a15[1] = 0;
     }
     if( k + 30 < n ) {
       a16[0] = *( m1 + n * i + (k+30) );
     } else {
       a16[0] = 0;
     }
     if( k + 31 < n ) {
       a16[1] = *( m1 + n * i + (k+31) );
     } else {
       a16[1] = 0;
     }
     if( k + 32 < n ) {
       a17[0] = *( m1 + n * i + (k+32) );
     } else {
       a17[0] = 0;
     }
     if( k + 33 < n ) {
       a17[1] = *( m1 + n * i + (k+33) );
     } else {
       a17[1] = 0;
     }
     if( k + 34 < n ) {
       a18[0] = *( m1 + n * i + (k+34) );
     } else {
       a18[0] = 0;
     }
     if( k + 35 < n ) {
       a18[1] = *( m1 + n * i + (k+35) );
     } else {
       a18[1] = 0;
     }
     if( k + 36 < n ) {
       a19[0] = *( m1 + n * i + (k+36) );
     } else {
       a19[0] = 0;
     }
     if( k + 37 < n ) {
       a19[1] = *( m1 + n * i + (k+37) );
     } else {
       a19[1] = 0;
     }
     if( k + 38 < n ) {
       a20[0] = *( m1 + n * i + (k+38) );
     } else {
       a20[0] = 0;
     }
     if( k + 39 < n ) {
       a20[1] = *( m1 + n * i + (k+39) );
     } else {
       a20[1] = 0;
     }
     if( k + 40 < n ) {
       a21[0] = *( m1 + n * i + (k+40) );
     } else {
       a21[0] = 0;
     }
     if( k + 41 < n ) {
       a21[1] = *( m1 + n * i + (k+41) );
     } else {
       a21[1] = 0;
     }
     if( k + 42 < n ) {
       a22[0] = *( m1 + n * i + (k+42) );
     } else {
       a22[0] = 0;
     }
     if( k + 43 < n ) {
       a22[1] = *( m1 + n * i + (k+43) );
     } else {
       a22[1] = 0;
     }
     if( k + 44 < n ) {
       a23[0] = *( m1 + n * i + (k+44) );
     } else {
       a23[0] = 0;
     }
     if( k + 45 < n ) {
       a23[1] = *( m1 + n * i + (k+45) );
     } else {
       a23[1] = 0;
     }
     if( k + 46 < n ) {
       a24[0] = *( m1 + n * i + (k+46) );
     } else {
       a24[0] = 0;
     }
     if( k + 47 < n ) {
       a24[1] = *( m1 + n * i + (k+47) );
     } else {
       a24[1] = 0;
     }
     if( k + 48 < n ) {
       a25[0] = *( m1 + n * i + (k+48) );
     } else {
       a25[0] = 0;
     }
     if( k + 49 < n ) {
       a25[1] = *( m1 + n * i + (k+49) );
     } else {
       a25[1] = 0;
     }
     if( k + 50 < n ) {
       a26[0] = *( m1 + n * i + (k+50) );
     } else {
       a26[0] = 0;
     }
     if( k + 51 < n ) {
       a26[1] = *( m1 + n * i + (k+51) );
     } else {
       a26[1] = 0;
     }
     if( k + 52 < n ) {
       a27[0] = *( m1 + n * i + (k+52) );
     } else {
       a27[0] = 0;
     }
     if( k + 53 < n ) {
       a27[1] = *( m1 + n * i + (k+53) );
     } else {
       a27[1] = 0;
     }
     if( k + 54 < n ) {
       a28[0] = *( m1 + n * i + (k+54) );
     } else {
       a28[0] = 0;
     }
     if( k + 55 < n ) {
       a28[1] = *( m1 + n * i + (k+55) );
     } else {
       a28[1] = 0;
     }
     if( k + 56 < n ) {
       a29[0] = *( m1 + n * i + (k+56) );
     } else {
       a29[0] = 0;
     }
     if( k + 57 < n ) {
       a29[1] = *( m1 + n * i + (k+57) );
     } else {
       a29[1] = 0;
     }
     if( k + 58 < n ) {
       a30[0] = *( m1 + n * i + (k+58) );
     } else {
       a30[0] = 0;
     }
     if( k + 59 < n ) {
       a30[1] = *( m1 + n * i + (k+59) );
     } else {
       a30[1] = 0;
     }
     if( k + 60 < n ) {
       a31[0] = *( m1 + n * i + (k+60) );
     } else {
       a31[0] = 0;
     }
     if( k + 61 < n ) {
       a31[1] = *( m1 + n * i + (k+61) );
     } else {
       a31[1] = 0;
     }
     if( k + 62 < n ) {
       a32[0] = *( m1 + n * i + (k+62) );
     } else {
       a32[0] = 0;
     }
     if( k + 63 < n ) {
       a32[1] = *( m1 + n * i + (k+63) );
     } else {
       a32[1] = 0;
     }
     if( k + 64 < n ) {
       a33[0] = *( m1 + n * i + (k+64) );
     } else {
       a33[0] = 0;
     }
     if( k + 65 < n ) {
       a33[1] = *( m1 + n * i + (k+65) );
     } else {
       a33[1] = 0;
     }
     if( k + 66 < n ) {
       a34[0] = *( m1 + n * i + (k+66) );
     } else {
       a34[0] = 0;
     }
     if( k + 67 < n ) {
       a34[1] = *( m1 + n * i + (k+67) );
     } else {
       a34[1] = 0;
     }
     if( k + 68 < n ) {
       a35[0] = *( m1 + n * i + (k+68) );
     } else {
       a35[0] = 0;
     }
     if( k + 69 < n ) {
       a35[1] = *( m1 + n * i + (k+69) );
     } else {
       a35[1] = 0;
     }
     if( k + 70 < n ) {
       a36[0] = *( m1 + n * i + (k+70) );
     } else {
       a36[0] = 0;
     }
     if( k + 71 < n ) {
       a36[1] = *( m1 + n * i + (k+71) );
     } else {
       a36[1] = 0;
     }
     if( k + 72 < n ) {
       a37[0] = *( m1 + n * i + (k+72) );
     } else {
       a37[0] = 0;
     }
     if( k + 73 < n ) {
       a37[1] = *( m1 + n * i + (k+73) );
     } else {
       a37[1] = 0;
     }
     if( k + 74 < n ) {
       a38[0] = *( m1 + n * i + (k+74) );
     } else {
       a38[0] = 0;
     }
     if( k + 75 < n ) {
       a38[1] = *( m1 + n * i + (k+75) );
     } else {
       a38[1] = 0;
     }
     if( k + 76 < n ) {
       a39[0] = *( m1 + n * i + (k+76) );
     } else {
       a39[0] = 0;
     }
     if( k + 77 < n ) {
       a39[1] = *( m1 + n * i + (k+77) );
     } else {
       a39[1] = 0;
     }
     if( k + 78 < n ) {
       a40[0] = *( m1 + n * i + (k+78) );
     } else {
       a40[0] = 0;
     }
     if( k + 79 < n ) {
       a40[1] = *( m1 + n * i + (k+79) );
     } else {
       a40[1] = 0;
     }
     if( k + 80 < n ) {
       a41[0] = *( m1 + n * i + (k+80) );
     } else {
       a41[0] = 0;
     }
     if( k + 81 < n ) {
       a41[1] = *( m1 + n * i + (k+81) );
     } else {
       a41[1] = 0;
     }
     if( k + 82 < n ) {
       a42[0] = *( m1 + n * i + (k+82) );
     } else {
       a42[0] = 0;
     }
     if( k + 83 < n ) {
       a42[1] = *( m1 + n * i + (k+83) );
     } else {
       a42[1] = 0;
     }
     if( k + 84 < n ) {
       a43[0] = *( m1 + n * i + (k+84) );
     } else {
       a43[0] = 0;
     }
     if( k + 85 < n ) {
       a43[1] = *( m1 + n * i + (k+85) );
     } else {
       a43[1] = 0;
     }
     if( k + 86 < n ) {
       a44[0] = *( m1 + n * i + (k+86) );
     } else {
       a44[0] = 0;
     }
     if( k + 87 < n ) {
       a44[1] = *( m1 + n * i + (k+87) );
     } else {
       a44[1] = 0;
     }
     if( k + 88 < n ) {
       a45[0] = *( m1 + n * i + (k+88) );
     } else {
       a45[0] = 0;
     }
     if( k + 89 < n ) {
       a45[1] = *( m1 + n * i + (k+89) );
     } else {
       a45[1] = 0;
     }
     if( k + 90 < n ) {
       a46[0] = *( m1 + n * i + (k+90) );
     } else {
       a46[0] = 0;
     }
     if( k + 91 < n ) {
       a46[1] = *( m1 + n * i + (k+91) );
     } else {
       a46[1] = 0;
     }
     if( k + 92 < n ) {
       a47[0] = *( m1 + n * i + (k+92) );
     } else {
       a47[0] = 0;
     }
     if( k + 93 < n ) {
       a47[1] = *( m1 + n * i + (k+93) );
     } else {
       a47[1] = 0;
     }
     if( k + 94 < n ) {
       a48[0] = *( m1 + n * i + (k+94) );
     } else {
       a48[0] = 0;
     }
     if( k + 95 < n ) {
       a48[1] = *( m1 + n * i + (k+95) );
     } else {
       a48[1] = 0;
     }
     if( k + 96 < n ) {
       a49[0] = *( m1 + n * i + (k+96) );
     } else {
       a49[0] = 0;
     }
     if( k + 97 < n ) {
       a49[1] = *( m1 + n * i + (k+97) );
     } else {
       a49[1] = 0;
     }
     if( k + 98 < n ) {
       a50[0] = *( m1 + n * i + (k+98) );
     } else {
       a50[0] = 0;
     }
     if( k + 99 < n ) {
       a50[1] = *( m1 + n * i + (k+99) );
     } else {
       a50[1] = 0;
     }
     if( k + 100 < n ) {
       a51[0] = *( m1 + n * i + (k+100) );
     } else {
       a51[0] = 0;
     }
     if( k + 101 < n ) {
       a51[1] = *( m1 + n * i + (k+101) );
     } else {
       a51[1] = 0;
     }
     if( k + 102 < n ) {
       a52[0] = *( m1 + n * i + (k+102) );
     } else {
       a52[0] = 0;
     }
     if( k + 103 < n ) {
       a52[1] = *( m1 + n * i + (k+103) );
     } else {
       a52[1] = 0;
     }
     if( k + 104 < n ) {
       a53[0] = *( m1 + n * i + (k+104) );
     } else {
       a53[0] = 0;
     }
     if( k + 105 < n ) {
       a53[1] = *( m1 + n * i + (k+105) );
     } else {
       a53[1] = 0;
     }
     if( k + 106 < n ) {
       a54[0] = *( m1 + n * i + (k+106) );
     } else {
       a54[0] = 0;
     }
     if( k + 107 < n ) {
       a54[1] = *( m1 + n * i + (k+107) );
     } else {
       a54[1] = 0;
     }
     if( k + 108 < n ) {
       a55[0] = *( m1 + n * i + (k+108) );
     } else {
       a55[0] = 0;
     }
     if( k + 109 < n ) {
       a55[1] = *( m1 + n * i + (k+109) );
     } else {
       a55[1] = 0;
     }
     if( k + 110 < n ) {
       a56[0] = *( m1 + n * i + (k+110) );
     } else {
       a56[0] = 0;
     }
     if( k + 111 < n ) {
       a56[1] = *( m1 + n * i + (k+111) );
     } else {
       a56[1] = 0;
     }
     if( k + 112 < n ) {
       a57[0] = *( m1 + n * i + (k+112) );
     } else {
       a57[0] = 0;
     }
     if( k + 113 < n ) {
       a57[1] = *( m1 + n * i + (k+113) );
     } else {
       a57[1] = 0;
     }
     if( k + 114 < n ) {
       a58[0] = *( m1 + n * i + (k+114) );
     } else {
       a58[0] = 0;
     }
     if( k + 115 < n ) {
       a58[1] = *( m1 + n * i + (k+115) );
     } else {
       a58[1] = 0;
     }
     if( k + 116 < n ) {
       a59[0] = *( m1 + n * i + (k+116) );
     } else {
       a59[0] = 0;
     }
     if( k + 117 < n ) {
       a59[1] = *( m1 + n * i + (k+117) );
     } else {
       a59[1] = 0;
     }
     if( k + 118 < n ) {
       a60[0] = *( m1 + n * i + (k+118) );
     } else {
       a60[0] = 0;
     }
     if( k + 119 < n ) {
       a60[1] = *( m1 + n * i + (k+119) );
     } else {
       a60[1] = 0;
     }
     if( k + 120 < n ) {
       a61[0] = *( m1 + n * i + (k+120) );
     } else {
       a61[0] = 0;
     }
     if( k + 121 < n ) {
       a61[1] = *( m1 + n * i + (k+121) );
     } else {
       a61[1] = 0;
     }
     if( k + 122 < n ) {
       a62[0] = *( m1 + n * i + (k+122) );
     } else {
       a62[0] = 0;
     }
     if( k + 123 < n ) {
       a62[1] = *( m1 + n * i + (k+123) );
     } else {
       a62[1] = 0;
     }
     if( k + 124 < n ) {
       a63[0] = *( m1 + n * i + (k+124) );
     } else {
       a63[0] = 0;
     }
     if( k + 125 < n ) {
       a63[1] = *( m1 + n * i + (k+125) );
     } else {
       a63[1] = 0;
     }
     if( k + 126 < n ) {
       a64[0] = *( m1 + n * i + (k+126) );
     } else {
       a64[0] = 0;
     }
     if( k + 127 < n ) {
       a64[1] = *( m1 + n * i + (k+127) );
     } else {
       a64[1] = 0;
     }
     if( k + 128 < n ) {
       a65[0] = *( m1 + n * i + (k+128) );
     } else {
       a65[0] = 0;
     }
     if( k + 129 < n ) {
       a65[1] = *( m1 + n * i + (k+129) );
     } else {
       a65[1] = 0;
     }
     if( k + 130 < n ) {
       a66[0] = *( m1 + n * i + (k+130) );
     } else {
       a66[0] = 0;
     }
     if( k + 131 < n ) {
       a66[1] = *( m1 + n * i + (k+131) );
     } else {
       a66[1] = 0;
     }
     if( k + 132 < n ) {
       a67[0] = *( m1 + n * i + (k+132) );
     } else {
       a67[0] = 0;
     }
     if( k + 133 < n ) {
       a67[1] = *( m1 + n * i + (k+133) );
     } else {
       a67[1] = 0;
     }
     if( k + 134 < n ) {
       a68[0] = *( m1 + n * i + (k+134) );
     } else {
       a68[0] = 0;
     }
     if( k + 135 < n ) {
       a68[1] = *( m1 + n * i + (k+135) );
     } else {
       a68[1] = 0;
     }
     if( k + 136 < n ) {
       a69[0] = *( m1 + n * i + (k+136) );
     } else {
       a69[0] = 0;
     }
     if( k + 137 < n ) {
       a69[1] = *( m1 + n * i + (k+137) );
     } else {
       a69[1] = 0;
     }
     if( k + 138 < n ) {
       a70[0] = *( m1 + n * i + (k+138) );
     } else {
       a70[0] = 0;
     }
     if( k + 139 < n ) {
       a70[1] = *( m1 + n * i + (k+139) );
     } else {
       a70[1] = 0;
     }
     if( k + 140 < n ) {
       a71[0] = *( m1 + n * i + (k+140) );
     } else {
       a71[0] = 0;
     }
     if( k + 141 < n ) {
       a71[1] = *( m1 + n * i + (k+141) );
     } else {
       a71[1] = 0;
     }
     if( k + 142 < n ) {
       a72[0] = *( m1 + n * i + (k+142) );
     } else {
       a72[0] = 0;
     }
     if( k + 143 < n ) {
       a72[1] = *( m1 + n * i + (k+143) );
     } else {
       a72[1] = 0;
     }
     if( k + 144 < n ) {
       a73[0] = *( m1 + n * i + (k+144) );
     } else {
       a73[0] = 0;
     }
     if( k + 145 < n ) {
       a73[1] = *( m1 + n * i + (k+145) );
     } else {
       a73[1] = 0;
     }
     if( k + 146 < n ) {
       a74[0] = *( m1 + n * i + (k+146) );
     } else {
       a74[0] = 0;
     }
     if( k + 147 < n ) {
       a74[1] = *( m1 + n * i + (k+147) );
     } else {
       a74[1] = 0;
     }
     if( k + 148 < n ) {
       a75[0] = *( m1 + n * i + (k+148) );
     } else {
       a75[0] = 0;
     }
     if( k + 149 < n ) {
       a75[1] = *( m1 + n * i + (k+149) );
     } else {
       a75[1] = 0;
     }
     if( k + 150 < n ) {
       a76[0] = *( m1 + n * i + (k+150) );
     } else {
       a76[0] = 0;
     }
     if( k + 151 < n ) {
       a76[1] = *( m1 + n * i + (k+151) );
     } else {
       a76[1] = 0;
     }
     if( k + 152 < n ) {
       a77[0] = *( m1 + n * i + (k+152) );
     } else {
       a77[0] = 0;
     }
     if( k + 153 < n ) {
       a77[1] = *( m1 + n * i + (k+153) );
     } else {
       a77[1] = 0;
     }
     if( k + 154 < n ) {
       a78[0] = *( m1 + n * i + (k+154) );
     } else {
       a78[0] = 0;
     }
     if( k + 155 < n ) {
       a78[1] = *( m1 + n * i + (k+155) );
     } else {
       a78[1] = 0;
     }
     if( k + 156 < n ) {
       a79[0] = *( m1 + n * i + (k+156) );
     } else {
       a79[0] = 0;
     }
     if( k + 157 < n ) {
       a79[1] = *( m1 + n * i + (k+157) );
     } else {
       a79[1] = 0;
     }
     if( k + 158 < n ) {
       a80[0] = *( m1 + n * i + (k+158) );
     } else {
       a80[0] = 0;
     }
     if( k + 159 < n ) {
       a80[1] = *( m1 + n * i + (k+159) );
     } else {
       a80[1] = 0;
     }
     if( k + 160 < n ) {
       a81[0] = *( m1 + n * i + (k+160) );
     } else {
       a81[0] = 0;
     }
     if( k + 161 < n ) {
       a81[1] = *( m1 + n * i + (k+161) );
     } else {
       a81[1] = 0;
     }
     if( k + 162 < n ) {
       a82[0] = *( m1 + n * i + (k+162) );
     } else {
       a82[0] = 0;
     }
     if( k + 163 < n ) {
       a82[1] = *( m1 + n * i + (k+163) );
     } else {
       a82[1] = 0;
     }
     if( k + 164 < n ) {
       a83[0] = *( m1 + n * i + (k+164) );
     } else {
       a83[0] = 0;
     }
     if( k + 165 < n ) {
       a83[1] = *( m1 + n * i + (k+165) );
     } else {
       a83[1] = 0;
     }
     if( k + 166 < n ) {
       a84[0] = *( m1 + n * i + (k+166) );
     } else {
       a84[0] = 0;
     }
     if( k + 167 < n ) {
       a84[1] = *( m1 + n * i + (k+167) );
     } else {
       a84[1] = 0;
     }
     if( k + 168 < n ) {
       a85[0] = *( m1 + n * i + (k+168) );
     } else {
       a85[0] = 0;
     }
     if( k + 169 < n ) {
       a85[1] = *( m1 + n * i + (k+169) );
     } else {
       a85[1] = 0;
     }
     if( k + 170 < n ) {
       a86[0] = *( m1 + n * i + (k+170) );
     } else {
       a86[0] = 0;
     }
     if( k + 171 < n ) {
       a86[1] = *( m1 + n * i + (k+171) );
     } else {
       a86[1] = 0;
     }
     if( k + 172 < n ) {
       a87[0] = *( m1 + n * i + (k+172) );
     } else {
       a87[0] = 0;
     }
     if( k + 173 < n ) {
       a87[1] = *( m1 + n * i + (k+173) );
     } else {
       a87[1] = 0;
     }
     if( k + 174 < n ) {
       a88[0] = *( m1 + n * i + (k+174) );
     } else {
       a88[0] = 0;
     }
     if( k + 175 < n ) {
       a88[1] = *( m1 + n * i + (k+175) );
     } else {
       a88[1] = 0;
     }
     if( k + 176 < n ) {
       a89[0] = *( m1 + n * i + (k+176) );
     } else {
       a89[0] = 0;
     }
     if( k + 177 < n ) {
       a89[1] = *( m1 + n * i + (k+177) );
     } else {
       a89[1] = 0;
     }
     if( k + 178 < n ) {
       a90[0] = *( m1 + n * i + (k+178) );
     } else {
       a90[0] = 0;
     }
     if( k + 179 < n ) {
       a90[1] = *( m1 + n * i + (k+179) );
     } else {
       a90[1] = 0;
     }
     if( k + 180 < n ) {
       a91[0] = *( m1 + n * i + (k+180) );
     } else {
       a91[0] = 0;
     }
     if( k + 181 < n ) {
       a91[1] = *( m1 + n * i + (k+181) );
     } else {
       a91[1] = 0;
     }
     if( k + 182 < n ) {
       a92[0] = *( m1 + n * i + (k+182) );
     } else {
       a92[0] = 0;
     }
     if( k + 183 < n ) {
       a92[1] = *( m1 + n * i + (k+183) );
     } else {
       a92[1] = 0;
     }
     if( k + 184 < n ) {
       a93[0] = *( m1 + n * i + (k+184) );
     } else {
       a93[0] = 0;
     }
     if( k + 185 < n ) {
       a93[1] = *( m1 + n * i + (k+185) );
     } else {
       a93[1] = 0;
     }
     if( k + 186 < n ) {
       a94[0] = *( m1 + n * i + (k+186) );
     } else {
       a94[0] = 0;
     }
     if( k + 187 < n ) {
       a94[1] = *( m1 + n * i + (k+187) );
     } else {
       a94[1] = 0;
     }
     if( k + 188 < n ) {
       a95[0] = *( m1 + n * i + (k+188) );
     } else {
       a95[0] = 0;
     }
     if( k + 189 < n ) {
       a95[1] = *( m1 + n * i + (k+189) );
     } else {
       a95[1] = 0;
     }
     if( k + 190 < n ) {
       a96[0] = *( m1 + n * i + (k+190) );
     } else {
       a96[0] = 0;
     }
     if( k + 191 < n ) {
       a96[1] = *( m1 + n * i + (k+191) );
     } else {
       a96[1] = 0;
     }
     if( k + 192 < n ) {
       a97[0] = *( m1 + n * i + (k+192) );
     } else {
       a97[0] = 0;
     }
     if( k + 193 < n ) {
       a97[1] = *( m1 + n * i + (k+193) );
     } else {
       a97[1] = 0;
     }
     if( k + 194 < n ) {
       a98[0] = *( m1 + n * i + (k+194) );
     } else {
       a98[0] = 0;
     }
     if( k + 195 < n ) {
       a98[1] = *( m1 + n * i + (k+195) );
     } else {
       a98[1] = 0;
     }
     if( k + 196 < n ) {
       a99[0] = *( m1 + n * i + (k+196) );
     } else {
       a99[0] = 0;
     }
     if( k + 197 < n ) {
       a99[1] = *( m1 + n * i + (k+197) );
     } else {
       a99[1] = 0;
     }
     if( k + 198 < n ) {
       a100[0] = *( m1 + n * i + (k+198) );
     } else {
       a100[0] = 0;
     }
     if( k + 199 < n ) {
       a100[1] = *( m1 + n * i + (k+199) );
     } else {
       a100[1] = 0;
     }
     if( k + 200 < n ) {
       a101[0] = *( m1 + n * i + (k+200) );
     } else {
       a101[0] = 0;
     }
     if( k + 201 < n ) {
       a101[1] = *( m1 + n * i + (k+201) );
     } else {
       a101[1] = 0;
     }
     if( k + 202 < n ) {
       a102[0] = *( m1 + n * i + (k+202) );
     } else {
       a102[0] = 0;
     }
     if( k + 203 < n ) {
       a102[1] = *( m1 + n * i + (k+203) );
     } else {
       a102[1] = 0;
     }
     if( k + 204 < n ) {
       a103[0] = *( m1 + n * i + (k+204) );
     } else {
       a103[0] = 0;
     }
     if( k + 205 < n ) {
       a103[1] = *( m1 + n * i + (k+205) );
     } else {
       a103[1] = 0;
     }
     if( k + 206 < n ) {
       a104[0] = *( m1 + n * i + (k+206) );
     } else {
       a104[0] = 0;
     }
     if( k + 207 < n ) {
       a104[1] = *( m1 + n * i + (k+207) );
     } else {
       a104[1] = 0;
     }
     if( k + 208 < n ) {
       a105[0] = *( m1 + n * i + (k+208) );
     } else {
       a105[0] = 0;
     }
     if( k + 209 < n ) {
       a105[1] = *( m1 + n * i + (k+209) );
     } else {
       a105[1] = 0;
     }
     if( k + 210 < n ) {
       a106[0] = *( m1 + n * i + (k+210) );
     } else {
       a106[0] = 0;
     }
     if( k + 211 < n ) {
       a106[1] = *( m1 + n * i + (k+211) );
     } else {
       a106[1] = 0;
     }
     if( k + 212 < n ) {
       a107[0] = *( m1 + n * i + (k+212) );
     } else {
       a107[0] = 0;
     }
     if( k + 213 < n ) {
       a107[1] = *( m1 + n * i + (k+213) );
     } else {
       a107[1] = 0;
     }
     if( k + 214 < n ) {
       a108[0] = *( m1 + n * i + (k+214) );
     } else {
       a108[0] = 0;
     }
     if( k + 215 < n ) {
       a108[1] = *( m1 + n * i + (k+215) );
     } else {
       a108[1] = 0;
     }
     if( k + 216 < n ) {
       a109[0] = *( m1 + n * i + (k+216) );
     } else {
       a109[0] = 0;
     }
     if( k + 217 < n ) {
       a109[1] = *( m1 + n * i + (k+217) );
     } else {
       a109[1] = 0;
     }
     if( k + 218 < n ) {
       a110[0] = *( m1 + n * i + (k+218) );
     } else {
       a110[0] = 0;
     }
     if( k + 219 < n ) {
       a110[1] = *( m1 + n * i + (k+219) );
     } else {
       a110[1] = 0;
     }
     if( k + 220 < n ) {
       a111[0] = *( m1 + n * i + (k+220) );
     } else {
       a111[0] = 0;
     }
     if( k + 221 < n ) {
       a111[1] = *( m1 + n * i + (k+221) );
     } else {
       a111[1] = 0;
     }
     if( k + 222 < n ) {
       a112[0] = *( m1 + n * i + (k+222) );
     } else {
       a112[0] = 0;
     }
     if( k + 223 < n ) {
       a112[1] = *( m1 + n * i + (k+223) );
     } else {
       a112[1] = 0;
     }
     if( k + 224 < n ) {
       a113[0] = *( m1 + n * i + (k+224) );
     } else {
       a113[0] = 0;
     }
     if( k + 225 < n ) {
       a113[1] = *( m1 + n * i + (k+225) );
     } else {
       a113[1] = 0;
     }
     if( k + 226 < n ) {
       a114[0] = *( m1 + n * i + (k+226) );
     } else {
       a114[0] = 0;
     }
     if( k + 227 < n ) {
       a114[1] = *( m1 + n * i + (k+227) );
     } else {
       a114[1] = 0;
     }
     if( k + 228 < n ) {
       a115[0] = *( m1 + n * i + (k+228) );
     } else {
       a115[0] = 0;
     }
     if( k + 229 < n ) {
       a115[1] = *( m1 + n * i + (k+229) );
     } else {
       a115[1] = 0;
     }
     if( k + 230 < n ) {
       a116[0] = *( m1 + n * i + (k+230) );
     } else {
       a116[0] = 0;
     }
     if( k + 231 < n ) {
       a116[1] = *( m1 + n * i + (k+231) );
     } else {
       a116[1] = 0;
     }
     if( k + 232 < n ) {
       a117[0] = *( m1 + n * i + (k+232) );
     } else {
       a117[0] = 0;
     }
     if( k + 233 < n ) {
       a117[1] = *( m1 + n * i + (k+233) );
     } else {
       a117[1] = 0;
     }
     if( k + 234 < n ) {
       a118[0] = *( m1 + n * i + (k+234) );
     } else {
       a118[0] = 0;
     }
     if( k + 235 < n ) {
       a118[1] = *( m1 + n * i + (k+235) );
     } else {
       a118[1] = 0;
     }
     if( k + 236 < n ) {
       a119[0] = *( m1 + n * i + (k+236) );
     } else {
       a119[0] = 0;
     }
     if( k + 237 < n ) {
       a119[1] = *( m1 + n * i + (k+237) );
     } else {
       a119[1] = 0;
     }
     if( k + 238 < n ) {
       a120[0] = *( m1 + n * i + (k+238) );
     } else {
       a120[0] = 0;
     }
     if( k + 239 < n ) {
       a120[1] = *( m1 + n * i + (k+239) );
     } else {
       a120[1] = 0;
     }
     if( k + 240 < n ) {
       a121[0] = *( m1 + n * i + (k+240) );
     } else {
       a121[0] = 0;
     }
     if( k + 241 < n ) {
       a121[1] = *( m1 + n * i + (k+241) );
     } else {
       a121[1] = 0;
     }
     if( k + 242 < n ) {
       a122[0] = *( m1 + n * i + (k+242) );
     } else {
       a122[0] = 0;
     }
     if( k + 243 < n ) {
       a122[1] = *( m1 + n * i + (k+243) );
     } else {
       a122[1] = 0;
     }
     if( k + 244 < n ) {
       a123[0] = *( m1 + n * i + (k+244) );
     } else {
       a123[0] = 0;
     }
     if( k + 245 < n ) {
       a123[1] = *( m1 + n * i + (k+245) );
     } else {
       a123[1] = 0;
     }
     if( k + 246 < n ) {
       a124[0] = *( m1 + n * i + (k+246) );
     } else {
       a124[0] = 0;
     }
     if( k + 247 < n ) {
       a124[1] = *( m1 + n * i + (k+247) );
     } else {
       a124[1] = 0;
     }
     if( k + 248 < n ) {
       a125[0] = *( m1 + n * i + (k+248) );
     } else {
       a125[0] = 0;
     }
     if( k + 249 < n ) {
       a125[1] = *( m1 + n * i + (k+249) );
     } else {
       a125[1] = 0;
     }
     if( k + 250 < n ) {
       a126[0] = *( m1 + n * i + (k+250) );
     } else {
       a126[0] = 0;
     }
     if( k + 251 < n ) {
       a126[1] = *( m1 + n * i + (k+251) );
     } else {
       a126[1] = 0;
     }
     if( k + 252 < n ) {
       a127[0] = *( m1 + n * i + (k+252) );
     } else {
       a127[0] = 0;
     }
     if( k + 253 < n ) {
       a127[1] = *( m1 + n * i + (k+253) );
     } else {
       a127[1] = 0;
     }
     if( k + 254 < n ) {
       a128[0] = *( m1 + n * i + (k+254) );
     } else {
       a128[0] = 0;
     }
     if( k + 255 < n ) {
       a128[1] = *( m1 + n * i + (k+255) );
     } else {
       a128[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );
     t12 = _mm_load_pd( a7 );
     t14 = _mm_load_pd( a8 );
     t16 = _mm_load_pd( a9 );
     t18 = _mm_load_pd( a10 );
     t20 = _mm_load_pd( a11 );
     t22 = _mm_load_pd( a12 );
     t24 = _mm_load_pd( a13 );
     t26 = _mm_load_pd( a14 );
     t28 = _mm_load_pd( a15 );
     t30 = _mm_load_pd( a16 );
     t32 = _mm_load_pd( a17 );
     t34 = _mm_load_pd( a18 );
     t36 = _mm_load_pd( a19 );
     t38 = _mm_load_pd( a20 );
     t40 = _mm_load_pd( a21 );
     t42 = _mm_load_pd( a22 );
     t44 = _mm_load_pd( a23 );
     t46 = _mm_load_pd( a24 );
     t48 = _mm_load_pd( a25 );
     t50 = _mm_load_pd( a26 );
     t52 = _mm_load_pd( a27 );
     t54 = _mm_load_pd( a28 );
     t56 = _mm_load_pd( a29 );
     t58 = _mm_load_pd( a30 );
     t60 = _mm_load_pd( a31 );
     t62 = _mm_load_pd( a32 );
     t64 = _mm_load_pd( a33 );
     t66 = _mm_load_pd( a34 );
     t68 = _mm_load_pd( a35 );
     t70 = _mm_load_pd( a36 );
     t72 = _mm_load_pd( a37 );
     t74 = _mm_load_pd( a38 );
     t76 = _mm_load_pd( a39 );
     t78 = _mm_load_pd( a40 );
     t80 = _mm_load_pd( a41 );
     t82 = _mm_load_pd( a42 );
     t84 = _mm_load_pd( a43 );
     t86 = _mm_load_pd( a44 );
     t88 = _mm_load_pd( a45 );
     t90 = _mm_load_pd( a46 );
     t92 = _mm_load_pd( a47 );
     t94 = _mm_load_pd( a48 );
     t96 = _mm_load_pd( a49 );
     t98 = _mm_load_pd( a50 );
     t100 = _mm_load_pd( a51 );
     t102 = _mm_load_pd( a52 );
     t104 = _mm_load_pd( a53 );
     t106 = _mm_load_pd( a54 );
     t108 = _mm_load_pd( a55 );
     t110 = _mm_load_pd( a56 );
     t112 = _mm_load_pd( a57 );
     t114 = _mm_load_pd( a58 );
     t116 = _mm_load_pd( a59 );
     t118 = _mm_load_pd( a60 );
     t120 = _mm_load_pd( a61 );
     t122 = _mm_load_pd( a62 );
     t124 = _mm_load_pd( a63 );
     t126 = _mm_load_pd( a64 );
     t128 = _mm_load_pd( a65 );
     t130 = _mm_load_pd( a66 );
     t132 = _mm_load_pd( a67 );
     t134 = _mm_load_pd( a68 );
     t136 = _mm_load_pd( a69 );
     t138 = _mm_load_pd( a70 );
     t140 = _mm_load_pd( a71 );
     t142 = _mm_load_pd( a72 );
     t144 = _mm_load_pd( a73 );
     t146 = _mm_load_pd( a74 );
     t148 = _mm_load_pd( a75 );
     t150 = _mm_load_pd( a76 );
     t152 = _mm_load_pd( a77 );
     t154 = _mm_load_pd( a78 );
     t156 = _mm_load_pd( a79 );
     t158 = _mm_load_pd( a80 );
     t160 = _mm_load_pd( a81 );
     t162 = _mm_load_pd( a82 );
     t164 = _mm_load_pd( a83 );
     t166 = _mm_load_pd( a84 );
     t168 = _mm_load_pd( a85 );
     t170 = _mm_load_pd( a86 );
     t172 = _mm_load_pd( a87 );
     t174 = _mm_load_pd( a88 );
     t176 = _mm_load_pd( a89 );
     t178 = _mm_load_pd( a90 );
     t180 = _mm_load_pd( a91 );
     t182 = _mm_load_pd( a92 );
     t184 = _mm_load_pd( a93 );
     t186 = _mm_load_pd( a94 );
     t188 = _mm_load_pd( a95 );
     t190 = _mm_load_pd( a96 );
     t192 = _mm_load_pd( a97 );
     t194 = _mm_load_pd( a98 );
     t196 = _mm_load_pd( a99 );
     t198 = _mm_load_pd( a100 );
     t200 = _mm_load_pd( a101 );
     t202 = _mm_load_pd( a102 );
     t204 = _mm_load_pd( a103 );
     t206 = _mm_load_pd( a104 );
     t208 = _mm_load_pd( a105 );
     t210 = _mm_load_pd( a106 );
     t212 = _mm_load_pd( a107 );
     t214 = _mm_load_pd( a108 );
     t216 = _mm_load_pd( a109 );
     t218 = _mm_load_pd( a110 );
     t220 = _mm_load_pd( a111 );
     t222 = _mm_load_pd( a112 );
     t224 = _mm_load_pd( a113 );
     t226 = _mm_load_pd( a114 );
     t228 = _mm_load_pd( a115 );
     t230 = _mm_load_pd( a116 );
     t232 = _mm_load_pd( a117 );
     t234 = _mm_load_pd( a118 );
     t236 = _mm_load_pd( a119 );
     t238 = _mm_load_pd( a120 );
     t240 = _mm_load_pd( a121 );
     t242 = _mm_load_pd( a122 );
     t244 = _mm_load_pd( a123 );
     t246 = _mm_load_pd( a124 );
     t248 = _mm_load_pd( a125 );
     t250 = _mm_load_pd( a126 );
     t252 = _mm_load_pd( a127 );
     t254 = _mm_load_pd( a128 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       if( k + 12 < n ) {
         b7[0] = *( m2 + n * (k+12) + j );
       } else {
         b7[0] = 0;
       }
      if( k + 13 < n ) {
        b7[1] = *( m2 + n * (k+13) + j );
      } else {
        b7[1] = 0;
      }
       if( k + 14 < n ) {
         b8[0] = *( m2 + n * (k+14) + j );
       } else {
         b8[0] = 0;
       }
      if( k + 15 < n ) {
        b8[1] = *( m2 + n * (k+15) + j );
      } else {
        b8[1] = 0;
      }
       if( k + 16 < n ) {
         b9[0] = *( m2 + n * (k+16) + j );
       } else {
         b9[0] = 0;
       }
      if( k + 17 < n ) {
        b9[1] = *( m2 + n * (k+17) + j );
      } else {
        b9[1] = 0;
      }
       if( k + 18 < n ) {
         b10[0] = *( m2 + n * (k+18) + j );
       } else {
         b10[0] = 0;
       }
      if( k + 19 < n ) {
        b10[1] = *( m2 + n * (k+19) + j );
      } else {
        b10[1] = 0;
      }
       if( k + 20 < n ) {
         b11[0] = *( m2 + n * (k+20) + j );
       } else {
         b11[0] = 0;
       }
      if( k + 21 < n ) {
        b11[1] = *( m2 + n * (k+21) + j );
      } else {
        b11[1] = 0;
      }
       if( k + 22 < n ) {
         b12[0] = *( m2 + n * (k+22) + j );
       } else {
         b12[0] = 0;
       }
      if( k + 23 < n ) {
        b12[1] = *( m2 + n * (k+23) + j );
      } else {
        b12[1] = 0;
      }
       if( k + 24 < n ) {
         b13[0] = *( m2 + n * (k+24) + j );
       } else {
         b13[0] = 0;
       }
      if( k + 25 < n ) {
        b13[1] = *( m2 + n * (k+25) + j );
      } else {
        b13[1] = 0;
      }
       if( k + 26 < n ) {
         b14[0] = *( m2 + n * (k+26) + j );
       } else {
         b14[0] = 0;
       }
      if( k + 27 < n ) {
        b14[1] = *( m2 + n * (k+27) + j );
      } else {
        b14[1] = 0;
      }
       if( k + 28 < n ) {
         b15[0] = *( m2 + n * (k+28) + j );
       } else {
         b15[0] = 0;
       }
      if( k + 29 < n ) {
        b15[1] = *( m2 + n * (k+29) + j );
      } else {
        b15[1] = 0;
      }
       if( k + 30 < n ) {
         b16[0] = *( m2 + n * (k+30) + j );
       } else {
         b16[0] = 0;
       }
      if( k + 31 < n ) {
        b16[1] = *( m2 + n * (k+31) + j );
      } else {
        b16[1] = 0;
      }
       if( k + 32 < n ) {
         b17[0] = *( m2 + n * (k+32) + j );
       } else {
         b17[0] = 0;
       }
      if( k + 33 < n ) {
        b17[1] = *( m2 + n * (k+33) + j );
      } else {
        b17[1] = 0;
      }
       if( k + 34 < n ) {
         b18[0] = *( m2 + n * (k+34) + j );
       } else {
         b18[0] = 0;
       }
      if( k + 35 < n ) {
        b18[1] = *( m2 + n * (k+35) + j );
      } else {
        b18[1] = 0;
      }
       if( k + 36 < n ) {
         b19[0] = *( m2 + n * (k+36) + j );
       } else {
         b19[0] = 0;
       }
      if( k + 37 < n ) {
        b19[1] = *( m2 + n * (k+37) + j );
      } else {
        b19[1] = 0;
      }
       if( k + 38 < n ) {
         b20[0] = *( m2 + n * (k+38) + j );
       } else {
         b20[0] = 0;
       }
      if( k + 39 < n ) {
        b20[1] = *( m2 + n * (k+39) + j );
      } else {
        b20[1] = 0;
      }
       if( k + 40 < n ) {
         b21[0] = *( m2 + n * (k+40) + j );
       } else {
         b21[0] = 0;
       }
      if( k + 41 < n ) {
        b21[1] = *( m2 + n * (k+41) + j );
      } else {
        b21[1] = 0;
      }
       if( k + 42 < n ) {
         b22[0] = *( m2 + n * (k+42) + j );
       } else {
         b22[0] = 0;
       }
      if( k + 43 < n ) {
        b22[1] = *( m2 + n * (k+43) + j );
      } else {
        b22[1] = 0;
      }
       if( k + 44 < n ) {
         b23[0] = *( m2 + n * (k+44) + j );
       } else {
         b23[0] = 0;
       }
      if( k + 45 < n ) {
        b23[1] = *( m2 + n * (k+45) + j );
      } else {
        b23[1] = 0;
      }
       if( k + 46 < n ) {
         b24[0] = *( m2 + n * (k+46) + j );
       } else {
         b24[0] = 0;
       }
      if( k + 47 < n ) {
        b24[1] = *( m2 + n * (k+47) + j );
      } else {
        b24[1] = 0;
      }
       if( k + 48 < n ) {
         b25[0] = *( m2 + n * (k+48) + j );
       } else {
         b25[0] = 0;
       }
      if( k + 49 < n ) {
        b25[1] = *( m2 + n * (k+49) + j );
      } else {
        b25[1] = 0;
      }
       if( k + 50 < n ) {
         b26[0] = *( m2 + n * (k+50) + j );
       } else {
         b26[0] = 0;
       }
      if( k + 51 < n ) {
        b26[1] = *( m2 + n * (k+51) + j );
      } else {
        b26[1] = 0;
      }
       if( k + 52 < n ) {
         b27[0] = *( m2 + n * (k+52) + j );
       } else {
         b27[0] = 0;
       }
      if( k + 53 < n ) {
        b27[1] = *( m2 + n * (k+53) + j );
      } else {
        b27[1] = 0;
      }
       if( k + 54 < n ) {
         b28[0] = *( m2 + n * (k+54) + j );
       } else {
         b28[0] = 0;
       }
      if( k + 55 < n ) {
        b28[1] = *( m2 + n * (k+55) + j );
      } else {
        b28[1] = 0;
      }
       if( k + 56 < n ) {
         b29[0] = *( m2 + n * (k+56) + j );
       } else {
         b29[0] = 0;
       }
      if( k + 57 < n ) {
        b29[1] = *( m2 + n * (k+57) + j );
      } else {
        b29[1] = 0;
      }
       if( k + 58 < n ) {
         b30[0] = *( m2 + n * (k+58) + j );
       } else {
         b30[0] = 0;
       }
      if( k + 59 < n ) {
        b30[1] = *( m2 + n * (k+59) + j );
      } else {
        b30[1] = 0;
      }
       if( k + 60 < n ) {
         b31[0] = *( m2 + n * (k+60) + j );
       } else {
         b31[0] = 0;
       }
      if( k + 61 < n ) {
        b31[1] = *( m2 + n * (k+61) + j );
      } else {
        b31[1] = 0;
      }
       if( k + 62 < n ) {
         b32[0] = *( m2 + n * (k+62) + j );
       } else {
         b32[0] = 0;
       }
      if( k + 63 < n ) {
        b32[1] = *( m2 + n * (k+63) + j );
      } else {
        b32[1] = 0;
      }
       if( k + 64 < n ) {
         b33[0] = *( m2 + n * (k+64) + j );
       } else {
         b33[0] = 0;
       }
      if( k + 65 < n ) {
        b33[1] = *( m2 + n * (k+65) + j );
      } else {
        b33[1] = 0;
      }
       if( k + 66 < n ) {
         b34[0] = *( m2 + n * (k+66) + j );
       } else {
         b34[0] = 0;
       }
      if( k + 67 < n ) {
        b34[1] = *( m2 + n * (k+67) + j );
      } else {
        b34[1] = 0;
      }
       if( k + 68 < n ) {
         b35[0] = *( m2 + n * (k+68) + j );
       } else {
         b35[0] = 0;
       }
      if( k + 69 < n ) {
        b35[1] = *( m2 + n * (k+69) + j );
      } else {
        b35[1] = 0;
      }
       if( k + 70 < n ) {
         b36[0] = *( m2 + n * (k+70) + j );
       } else {
         b36[0] = 0;
       }
      if( k + 71 < n ) {
        b36[1] = *( m2 + n * (k+71) + j );
      } else {
        b36[1] = 0;
      }
       if( k + 72 < n ) {
         b37[0] = *( m2 + n * (k+72) + j );
       } else {
         b37[0] = 0;
       }
      if( k + 73 < n ) {
        b37[1] = *( m2 + n * (k+73) + j );
      } else {
        b37[1] = 0;
      }
       if( k + 74 < n ) {
         b38[0] = *( m2 + n * (k+74) + j );
       } else {
         b38[0] = 0;
       }
      if( k + 75 < n ) {
        b38[1] = *( m2 + n * (k+75) + j );
      } else {
        b38[1] = 0;
      }
       if( k + 76 < n ) {
         b39[0] = *( m2 + n * (k+76) + j );
       } else {
         b39[0] = 0;
       }
      if( k + 77 < n ) {
        b39[1] = *( m2 + n * (k+77) + j );
      } else {
        b39[1] = 0;
      }
       if( k + 78 < n ) {
         b40[0] = *( m2 + n * (k+78) + j );
       } else {
         b40[0] = 0;
       }
      if( k + 79 < n ) {
        b40[1] = *( m2 + n * (k+79) + j );
      } else {
        b40[1] = 0;
      }
       if( k + 80 < n ) {
         b41[0] = *( m2 + n * (k+80) + j );
       } else {
         b41[0] = 0;
       }
      if( k + 81 < n ) {
        b41[1] = *( m2 + n * (k+81) + j );
      } else {
        b41[1] = 0;
      }
       if( k + 82 < n ) {
         b42[0] = *( m2 + n * (k+82) + j );
       } else {
         b42[0] = 0;
       }
      if( k + 83 < n ) {
        b42[1] = *( m2 + n * (k+83) + j );
      } else {
        b42[1] = 0;
      }
       if( k + 84 < n ) {
         b43[0] = *( m2 + n * (k+84) + j );
       } else {
         b43[0] = 0;
       }
      if( k + 85 < n ) {
        b43[1] = *( m2 + n * (k+85) + j );
      } else {
        b43[1] = 0;
      }
       if( k + 86 < n ) {
         b44[0] = *( m2 + n * (k+86) + j );
       } else {
         b44[0] = 0;
       }
      if( k + 87 < n ) {
        b44[1] = *( m2 + n * (k+87) + j );
      } else {
        b44[1] = 0;
      }
       if( k + 88 < n ) {
         b45[0] = *( m2 + n * (k+88) + j );
       } else {
         b45[0] = 0;
       }
      if( k + 89 < n ) {
        b45[1] = *( m2 + n * (k+89) + j );
      } else {
        b45[1] = 0;
      }
       if( k + 90 < n ) {
         b46[0] = *( m2 + n * (k+90) + j );
       } else {
         b46[0] = 0;
       }
      if( k + 91 < n ) {
        b46[1] = *( m2 + n * (k+91) + j );
      } else {
        b46[1] = 0;
      }
       if( k + 92 < n ) {
         b47[0] = *( m2 + n * (k+92) + j );
       } else {
         b47[0] = 0;
       }
      if( k + 93 < n ) {
        b47[1] = *( m2 + n * (k+93) + j );
      } else {
        b47[1] = 0;
      }
       if( k + 94 < n ) {
         b48[0] = *( m2 + n * (k+94) + j );
       } else {
         b48[0] = 0;
       }
      if( k + 95 < n ) {
        b48[1] = *( m2 + n * (k+95) + j );
      } else {
        b48[1] = 0;
      }
       if( k + 96 < n ) {
         b49[0] = *( m2 + n * (k+96) + j );
       } else {
         b49[0] = 0;
       }
      if( k + 97 < n ) {
        b49[1] = *( m2 + n * (k+97) + j );
      } else {
        b49[1] = 0;
      }
       if( k + 98 < n ) {
         b50[0] = *( m2 + n * (k+98) + j );
       } else {
         b50[0] = 0;
       }
      if( k + 99 < n ) {
        b50[1] = *( m2 + n * (k+99) + j );
      } else {
        b50[1] = 0;
      }
       if( k + 100 < n ) {
         b51[0] = *( m2 + n * (k+100) + j );
       } else {
         b51[0] = 0;
       }
      if( k + 101 < n ) {
        b51[1] = *( m2 + n * (k+101) + j );
      } else {
        b51[1] = 0;
      }
       if( k + 102 < n ) {
         b52[0] = *( m2 + n * (k+102) + j );
       } else {
         b52[0] = 0;
       }
      if( k + 103 < n ) {
        b52[1] = *( m2 + n * (k+103) + j );
      } else {
        b52[1] = 0;
      }
       if( k + 104 < n ) {
         b53[0] = *( m2 + n * (k+104) + j );
       } else {
         b53[0] = 0;
       }
      if( k + 105 < n ) {
        b53[1] = *( m2 + n * (k+105) + j );
      } else {
        b53[1] = 0;
      }
       if( k + 106 < n ) {
         b54[0] = *( m2 + n * (k+106) + j );
       } else {
         b54[0] = 0;
       }
      if( k + 107 < n ) {
        b54[1] = *( m2 + n * (k+107) + j );
      } else {
        b54[1] = 0;
      }
       if( k + 108 < n ) {
         b55[0] = *( m2 + n * (k+108) + j );
       } else {
         b55[0] = 0;
       }
      if( k + 109 < n ) {
        b55[1] = *( m2 + n * (k+109) + j );
      } else {
        b55[1] = 0;
      }
       if( k + 110 < n ) {
         b56[0] = *( m2 + n * (k+110) + j );
       } else {
         b56[0] = 0;
       }
      if( k + 111 < n ) {
        b56[1] = *( m2 + n * (k+111) + j );
      } else {
        b56[1] = 0;
      }
       if( k + 112 < n ) {
         b57[0] = *( m2 + n * (k+112) + j );
       } else {
         b57[0] = 0;
       }
      if( k + 113 < n ) {
        b57[1] = *( m2 + n * (k+113) + j );
      } else {
        b57[1] = 0;
      }
       if( k + 114 < n ) {
         b58[0] = *( m2 + n * (k+114) + j );
       } else {
         b58[0] = 0;
       }
      if( k + 115 < n ) {
        b58[1] = *( m2 + n * (k+115) + j );
      } else {
        b58[1] = 0;
      }
       if( k + 116 < n ) {
         b59[0] = *( m2 + n * (k+116) + j );
       } else {
         b59[0] = 0;
       }
      if( k + 117 < n ) {
        b59[1] = *( m2 + n * (k+117) + j );
      } else {
        b59[1] = 0;
      }
       if( k + 118 < n ) {
         b60[0] = *( m2 + n * (k+118) + j );
       } else {
         b60[0] = 0;
       }
      if( k + 119 < n ) {
        b60[1] = *( m2 + n * (k+119) + j );
      } else {
        b60[1] = 0;
      }
       if( k + 120 < n ) {
         b61[0] = *( m2 + n * (k+120) + j );
       } else {
         b61[0] = 0;
       }
      if( k + 121 < n ) {
        b61[1] = *( m2 + n * (k+121) + j );
      } else {
        b61[1] = 0;
      }
       if( k + 122 < n ) {
         b62[0] = *( m2 + n * (k+122) + j );
       } else {
         b62[0] = 0;
       }
      if( k + 123 < n ) {
        b62[1] = *( m2 + n * (k+123) + j );
      } else {
        b62[1] = 0;
      }
       if( k + 124 < n ) {
         b63[0] = *( m2 + n * (k+124) + j );
       } else {
         b63[0] = 0;
       }
      if( k + 125 < n ) {
        b63[1] = *( m2 + n * (k+125) + j );
      } else {
        b63[1] = 0;
      }
       if( k + 126 < n ) {
         b64[0] = *( m2 + n * (k+126) + j );
       } else {
         b64[0] = 0;
       }
      if( k + 127 < n ) {
        b64[1] = *( m2 + n * (k+127) + j );
      } else {
        b64[1] = 0;
      }
       if( k + 128 < n ) {
         b65[0] = *( m2 + n * (k+128) + j );
       } else {
         b65[0] = 0;
       }
      if( k + 129 < n ) {
        b65[1] = *( m2 + n * (k+129) + j );
      } else {
        b65[1] = 0;
      }
       if( k + 130 < n ) {
         b66[0] = *( m2 + n * (k+130) + j );
       } else {
         b66[0] = 0;
       }
      if( k + 131 < n ) {
        b66[1] = *( m2 + n * (k+131) + j );
      } else {
        b66[1] = 0;
      }
       if( k + 132 < n ) {
         b67[0] = *( m2 + n * (k+132) + j );
       } else {
         b67[0] = 0;
       }
      if( k + 133 < n ) {
        b67[1] = *( m2 + n * (k+133) + j );
      } else {
        b67[1] = 0;
      }
       if( k + 134 < n ) {
         b68[0] = *( m2 + n * (k+134) + j );
       } else {
         b68[0] = 0;
       }
      if( k + 135 < n ) {
        b68[1] = *( m2 + n * (k+135) + j );
      } else {
        b68[1] = 0;
      }
       if( k + 136 < n ) {
         b69[0] = *( m2 + n * (k+136) + j );
       } else {
         b69[0] = 0;
       }
      if( k + 137 < n ) {
        b69[1] = *( m2 + n * (k+137) + j );
      } else {
        b69[1] = 0;
      }
       if( k + 138 < n ) {
         b70[0] = *( m2 + n * (k+138) + j );
       } else {
         b70[0] = 0;
       }
      if( k + 139 < n ) {
        b70[1] = *( m2 + n * (k+139) + j );
      } else {
        b70[1] = 0;
      }
       if( k + 140 < n ) {
         b71[0] = *( m2 + n * (k+140) + j );
       } else {
         b71[0] = 0;
       }
      if( k + 141 < n ) {
        b71[1] = *( m2 + n * (k+141) + j );
      } else {
        b71[1] = 0;
      }
       if( k + 142 < n ) {
         b72[0] = *( m2 + n * (k+142) + j );
       } else {
         b72[0] = 0;
       }
      if( k + 143 < n ) {
        b72[1] = *( m2 + n * (k+143) + j );
      } else {
        b72[1] = 0;
      }
       if( k + 144 < n ) {
         b73[0] = *( m2 + n * (k+144) + j );
       } else {
         b73[0] = 0;
       }
      if( k + 145 < n ) {
        b73[1] = *( m2 + n * (k+145) + j );
      } else {
        b73[1] = 0;
      }
       if( k + 146 < n ) {
         b74[0] = *( m2 + n * (k+146) + j );
       } else {
         b74[0] = 0;
       }
      if( k + 147 < n ) {
        b74[1] = *( m2 + n * (k+147) + j );
      } else {
        b74[1] = 0;
      }
       if( k + 148 < n ) {
         b75[0] = *( m2 + n * (k+148) + j );
       } else {
         b75[0] = 0;
       }
      if( k + 149 < n ) {
        b75[1] = *( m2 + n * (k+149) + j );
      } else {
        b75[1] = 0;
      }
       if( k + 150 < n ) {
         b76[0] = *( m2 + n * (k+150) + j );
       } else {
         b76[0] = 0;
       }
      if( k + 151 < n ) {
        b76[1] = *( m2 + n * (k+151) + j );
      } else {
        b76[1] = 0;
      }
       if( k + 152 < n ) {
         b77[0] = *( m2 + n * (k+152) + j );
       } else {
         b77[0] = 0;
       }
      if( k + 153 < n ) {
        b77[1] = *( m2 + n * (k+153) + j );
      } else {
        b77[1] = 0;
      }
       if( k + 154 < n ) {
         b78[0] = *( m2 + n * (k+154) + j );
       } else {
         b78[0] = 0;
       }
      if( k + 155 < n ) {
        b78[1] = *( m2 + n * (k+155) + j );
      } else {
        b78[1] = 0;
      }
       if( k + 156 < n ) {
         b79[0] = *( m2 + n * (k+156) + j );
       } else {
         b79[0] = 0;
       }
      if( k + 157 < n ) {
        b79[1] = *( m2 + n * (k+157) + j );
      } else {
        b79[1] = 0;
      }
       if( k + 158 < n ) {
         b80[0] = *( m2 + n * (k+158) + j );
       } else {
         b80[0] = 0;
       }
      if( k + 159 < n ) {
        b80[1] = *( m2 + n * (k+159) + j );
      } else {
        b80[1] = 0;
      }
       if( k + 160 < n ) {
         b81[0] = *( m2 + n * (k+160) + j );
       } else {
         b81[0] = 0;
       }
      if( k + 161 < n ) {
        b81[1] = *( m2 + n * (k+161) + j );
      } else {
        b81[1] = 0;
      }
       if( k + 162 < n ) {
         b82[0] = *( m2 + n * (k+162) + j );
       } else {
         b82[0] = 0;
       }
      if( k + 163 < n ) {
        b82[1] = *( m2 + n * (k+163) + j );
      } else {
        b82[1] = 0;
      }
       if( k + 164 < n ) {
         b83[0] = *( m2 + n * (k+164) + j );
       } else {
         b83[0] = 0;
       }
      if( k + 165 < n ) {
        b83[1] = *( m2 + n * (k+165) + j );
      } else {
        b83[1] = 0;
      }
       if( k + 166 < n ) {
         b84[0] = *( m2 + n * (k+166) + j );
       } else {
         b84[0] = 0;
       }
      if( k + 167 < n ) {
        b84[1] = *( m2 + n * (k+167) + j );
      } else {
        b84[1] = 0;
      }
       if( k + 168 < n ) {
         b85[0] = *( m2 + n * (k+168) + j );
       } else {
         b85[0] = 0;
       }
      if( k + 169 < n ) {
        b85[1] = *( m2 + n * (k+169) + j );
      } else {
        b85[1] = 0;
      }
       if( k + 170 < n ) {
         b86[0] = *( m2 + n * (k+170) + j );
       } else {
         b86[0] = 0;
       }
      if( k + 171 < n ) {
        b86[1] = *( m2 + n * (k+171) + j );
      } else {
        b86[1] = 0;
      }
       if( k + 172 < n ) {
         b87[0] = *( m2 + n * (k+172) + j );
       } else {
         b87[0] = 0;
       }
      if( k + 173 < n ) {
        b87[1] = *( m2 + n * (k+173) + j );
      } else {
        b87[1] = 0;
      }
       if( k + 174 < n ) {
         b88[0] = *( m2 + n * (k+174) + j );
       } else {
         b88[0] = 0;
       }
      if( k + 175 < n ) {
        b88[1] = *( m2 + n * (k+175) + j );
      } else {
        b88[1] = 0;
      }
       if( k + 176 < n ) {
         b89[0] = *( m2 + n * (k+176) + j );
       } else {
         b89[0] = 0;
       }
      if( k + 177 < n ) {
        b89[1] = *( m2 + n * (k+177) + j );
      } else {
        b89[1] = 0;
      }
       if( k + 178 < n ) {
         b90[0] = *( m2 + n * (k+178) + j );
       } else {
         b90[0] = 0;
       }
      if( k + 179 < n ) {
        b90[1] = *( m2 + n * (k+179) + j );
      } else {
        b90[1] = 0;
      }
       if( k + 180 < n ) {
         b91[0] = *( m2 + n * (k+180) + j );
       } else {
         b91[0] = 0;
       }
      if( k + 181 < n ) {
        b91[1] = *( m2 + n * (k+181) + j );
      } else {
        b91[1] = 0;
      }
       if( k + 182 < n ) {
         b92[0] = *( m2 + n * (k+182) + j );
       } else {
         b92[0] = 0;
       }
      if( k + 183 < n ) {
        b92[1] = *( m2 + n * (k+183) + j );
      } else {
        b92[1] = 0;
      }
       if( k + 184 < n ) {
         b93[0] = *( m2 + n * (k+184) + j );
       } else {
         b93[0] = 0;
       }
      if( k + 185 < n ) {
        b93[1] = *( m2 + n * (k+185) + j );
      } else {
        b93[1] = 0;
      }
       if( k + 186 < n ) {
         b94[0] = *( m2 + n * (k+186) + j );
       } else {
         b94[0] = 0;
       }
      if( k + 187 < n ) {
        b94[1] = *( m2 + n * (k+187) + j );
      } else {
        b94[1] = 0;
      }
       if( k + 188 < n ) {
         b95[0] = *( m2 + n * (k+188) + j );
       } else {
         b95[0] = 0;
       }
      if( k + 189 < n ) {
        b95[1] = *( m2 + n * (k+189) + j );
      } else {
        b95[1] = 0;
      }
       if( k + 190 < n ) {
         b96[0] = *( m2 + n * (k+190) + j );
       } else {
         b96[0] = 0;
       }
      if( k + 191 < n ) {
        b96[1] = *( m2 + n * (k+191) + j );
      } else {
        b96[1] = 0;
      }
       if( k + 192 < n ) {
         b97[0] = *( m2 + n * (k+192) + j );
       } else {
         b97[0] = 0;
       }
      if( k + 193 < n ) {
        b97[1] = *( m2 + n * (k+193) + j );
      } else {
        b97[1] = 0;
      }
       if( k + 194 < n ) {
         b98[0] = *( m2 + n * (k+194) + j );
       } else {
         b98[0] = 0;
       }
      if( k + 195 < n ) {
        b98[1] = *( m2 + n * (k+195) + j );
      } else {
        b98[1] = 0;
      }
       if( k + 196 < n ) {
         b99[0] = *( m2 + n * (k+196) + j );
       } else {
         b99[0] = 0;
       }
      if( k + 197 < n ) {
        b99[1] = *( m2 + n * (k+197) + j );
      } else {
        b99[1] = 0;
      }
       if( k + 198 < n ) {
         b100[0] = *( m2 + n * (k+198) + j );
       } else {
         b100[0] = 0;
       }
      if( k + 199 < n ) {
        b100[1] = *( m2 + n * (k+199) + j );
      } else {
        b100[1] = 0;
      }
       if( k + 200 < n ) {
         b101[0] = *( m2 + n * (k+200) + j );
       } else {
         b101[0] = 0;
       }
      if( k + 201 < n ) {
        b101[1] = *( m2 + n * (k+201) + j );
      } else {
        b101[1] = 0;
      }
       if( k + 202 < n ) {
         b102[0] = *( m2 + n * (k+202) + j );
       } else {
         b102[0] = 0;
       }
      if( k + 203 < n ) {
        b102[1] = *( m2 + n * (k+203) + j );
      } else {
        b102[1] = 0;
      }
       if( k + 204 < n ) {
         b103[0] = *( m2 + n * (k+204) + j );
       } else {
         b103[0] = 0;
       }
      if( k + 205 < n ) {
        b103[1] = *( m2 + n * (k+205) + j );
      } else {
        b103[1] = 0;
      }
       if( k + 206 < n ) {
         b104[0] = *( m2 + n * (k+206) + j );
       } else {
         b104[0] = 0;
       }
      if( k + 207 < n ) {
        b104[1] = *( m2 + n * (k+207) + j );
      } else {
        b104[1] = 0;
      }
       if( k + 208 < n ) {
         b105[0] = *( m2 + n * (k+208) + j );
       } else {
         b105[0] = 0;
       }
      if( k + 209 < n ) {
        b105[1] = *( m2 + n * (k+209) + j );
      } else {
        b105[1] = 0;
      }
       if( k + 210 < n ) {
         b106[0] = *( m2 + n * (k+210) + j );
       } else {
         b106[0] = 0;
       }
      if( k + 211 < n ) {
        b106[1] = *( m2 + n * (k+211) + j );
      } else {
        b106[1] = 0;
      }
       if( k + 212 < n ) {
         b107[0] = *( m2 + n * (k+212) + j );
       } else {
         b107[0] = 0;
       }
      if( k + 213 < n ) {
        b107[1] = *( m2 + n * (k+213) + j );
      } else {
        b107[1] = 0;
      }
       if( k + 214 < n ) {
         b108[0] = *( m2 + n * (k+214) + j );
       } else {
         b108[0] = 0;
       }
      if( k + 215 < n ) {
        b108[1] = *( m2 + n * (k+215) + j );
      } else {
        b108[1] = 0;
      }
       if( k + 216 < n ) {
         b109[0] = *( m2 + n * (k+216) + j );
       } else {
         b109[0] = 0;
       }
      if( k + 217 < n ) {
        b109[1] = *( m2 + n * (k+217) + j );
      } else {
        b109[1] = 0;
      }
       if( k + 218 < n ) {
         b110[0] = *( m2 + n * (k+218) + j );
       } else {
         b110[0] = 0;
       }
      if( k + 219 < n ) {
        b110[1] = *( m2 + n * (k+219) + j );
      } else {
        b110[1] = 0;
      }
       if( k + 220 < n ) {
         b111[0] = *( m2 + n * (k+220) + j );
       } else {
         b111[0] = 0;
       }
      if( k + 221 < n ) {
        b111[1] = *( m2 + n * (k+221) + j );
      } else {
        b111[1] = 0;
      }
       if( k + 222 < n ) {
         b112[0] = *( m2 + n * (k+222) + j );
       } else {
         b112[0] = 0;
       }
      if( k + 223 < n ) {
        b112[1] = *( m2 + n * (k+223) + j );
      } else {
        b112[1] = 0;
      }
       if( k + 224 < n ) {
         b113[0] = *( m2 + n * (k+224) + j );
       } else {
         b113[0] = 0;
       }
      if( k + 225 < n ) {
        b113[1] = *( m2 + n * (k+225) + j );
      } else {
        b113[1] = 0;
      }
       if( k + 226 < n ) {
         b114[0] = *( m2 + n * (k+226) + j );
       } else {
         b114[0] = 0;
       }
      if( k + 227 < n ) {
        b114[1] = *( m2 + n * (k+227) + j );
      } else {
        b114[1] = 0;
      }
       if( k + 228 < n ) {
         b115[0] = *( m2 + n * (k+228) + j );
       } else {
         b115[0] = 0;
       }
      if( k + 229 < n ) {
        b115[1] = *( m2 + n * (k+229) + j );
      } else {
        b115[1] = 0;
      }
       if( k + 230 < n ) {
         b116[0] = *( m2 + n * (k+230) + j );
       } else {
         b116[0] = 0;
       }
      if( k + 231 < n ) {
        b116[1] = *( m2 + n * (k+231) + j );
      } else {
        b116[1] = 0;
      }
       if( k + 232 < n ) {
         b117[0] = *( m2 + n * (k+232) + j );
       } else {
         b117[0] = 0;
       }
      if( k + 233 < n ) {
        b117[1] = *( m2 + n * (k+233) + j );
      } else {
        b117[1] = 0;
      }
       if( k + 234 < n ) {
         b118[0] = *( m2 + n * (k+234) + j );
       } else {
         b118[0] = 0;
       }
      if( k + 235 < n ) {
        b118[1] = *( m2 + n * (k+235) + j );
      } else {
        b118[1] = 0;
      }
       if( k + 236 < n ) {
         b119[0] = *( m2 + n * (k+236) + j );
       } else {
         b119[0] = 0;
       }
      if( k + 237 < n ) {
        b119[1] = *( m2 + n * (k+237) + j );
      } else {
        b119[1] = 0;
      }
       if( k + 238 < n ) {
         b120[0] = *( m2 + n * (k+238) + j );
       } else {
         b120[0] = 0;
       }
      if( k + 239 < n ) {
        b120[1] = *( m2 + n * (k+239) + j );
      } else {
        b120[1] = 0;
      }
       if( k + 240 < n ) {
         b121[0] = *( m2 + n * (k+240) + j );
       } else {
         b121[0] = 0;
       }
      if( k + 241 < n ) {
        b121[1] = *( m2 + n * (k+241) + j );
      } else {
        b121[1] = 0;
      }
       if( k + 242 < n ) {
         b122[0] = *( m2 + n * (k+242) + j );
       } else {
         b122[0] = 0;
       }
      if( k + 243 < n ) {
        b122[1] = *( m2 + n * (k+243) + j );
      } else {
        b122[1] = 0;
      }
       if( k + 244 < n ) {
         b123[0] = *( m2 + n * (k+244) + j );
       } else {
         b123[0] = 0;
       }
      if( k + 245 < n ) {
        b123[1] = *( m2 + n * (k+245) + j );
      } else {
        b123[1] = 0;
      }
       if( k + 246 < n ) {
         b124[0] = *( m2 + n * (k+246) + j );
       } else {
         b124[0] = 0;
       }
      if( k + 247 < n ) {
        b124[1] = *( m2 + n * (k+247) + j );
      } else {
        b124[1] = 0;
      }
       if( k + 248 < n ) {
         b125[0] = *( m2 + n * (k+248) + j );
       } else {
         b125[0] = 0;
       }
      if( k + 249 < n ) {
        b125[1] = *( m2 + n * (k+249) + j );
      } else {
        b125[1] = 0;
      }
       if( k + 250 < n ) {
         b126[0] = *( m2 + n * (k+250) + j );
       } else {
         b126[0] = 0;
       }
      if( k + 251 < n ) {
        b126[1] = *( m2 + n * (k+251) + j );
      } else {
        b126[1] = 0;
      }
       if( k + 252 < n ) {
         b127[0] = *( m2 + n * (k+252) + j );
       } else {
         b127[0] = 0;
       }
      if( k + 253 < n ) {
        b127[1] = *( m2 + n * (k+253) + j );
      } else {
        b127[1] = 0;
      }
       if( k + 254 < n ) {
         b128[0] = *( m2 + n * (k+254) + j );
       } else {
         b128[0] = 0;
       }
      if( k + 255 < n ) {
        b128[1] = *( m2 + n * (k+255) + j );
      } else {
        b128[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t13 = _mm_load_pd( b7 );
       t15 = _mm_load_pd( b8 );
       t17 = _mm_load_pd( b9 );
       t19 = _mm_load_pd( b10 );
       t21 = _mm_load_pd( b11 );
       t23 = _mm_load_pd( b12 );
       t25 = _mm_load_pd( b13 );
       t27 = _mm_load_pd( b14 );
       t29 = _mm_load_pd( b15 );
       t31 = _mm_load_pd( b16 );
       t33 = _mm_load_pd( b17 );
       t35 = _mm_load_pd( b18 );
       t37 = _mm_load_pd( b19 );
       t39 = _mm_load_pd( b20 );
       t41 = _mm_load_pd( b21 );
       t43 = _mm_load_pd( b22 );
       t45 = _mm_load_pd( b23 );
       t47 = _mm_load_pd( b24 );
       t49 = _mm_load_pd( b25 );
       t51 = _mm_load_pd( b26 );
       t53 = _mm_load_pd( b27 );
       t55 = _mm_load_pd( b28 );
       t57 = _mm_load_pd( b29 );
       t59 = _mm_load_pd( b30 );
       t61 = _mm_load_pd( b31 );
       t63 = _mm_load_pd( b32 );
       t65 = _mm_load_pd( b33 );
       t67 = _mm_load_pd( b34 );
       t69 = _mm_load_pd( b35 );
       t71 = _mm_load_pd( b36 );
       t73 = _mm_load_pd( b37 );
       t75 = _mm_load_pd( b38 );
       t77 = _mm_load_pd( b39 );
       t79 = _mm_load_pd( b40 );
       t81 = _mm_load_pd( b41 );
       t83 = _mm_load_pd( b42 );
       t85 = _mm_load_pd( b43 );
       t87 = _mm_load_pd( b44 );
       t89 = _mm_load_pd( b45 );
       t91 = _mm_load_pd( b46 );
       t93 = _mm_load_pd( b47 );
       t95 = _mm_load_pd( b48 );
       t97 = _mm_load_pd( b49 );
       t99 = _mm_load_pd( b50 );
       t101 = _mm_load_pd( b51 );
       t103 = _mm_load_pd( b52 );
       t105 = _mm_load_pd( b53 );
       t107 = _mm_load_pd( b54 );
       t109 = _mm_load_pd( b55 );
       t111 = _mm_load_pd( b56 );
       t113 = _mm_load_pd( b57 );
       t115 = _mm_load_pd( b58 );
       t117 = _mm_load_pd( b59 );
       t119 = _mm_load_pd( b60 );
       t121 = _mm_load_pd( b61 );
       t123 = _mm_load_pd( b62 );
       t125 = _mm_load_pd( b63 );
       t127 = _mm_load_pd( b64 );
       t129 = _mm_load_pd( b65 );
       t131 = _mm_load_pd( b66 );
       t133 = _mm_load_pd( b67 );
       t135 = _mm_load_pd( b68 );
       t137 = _mm_load_pd( b69 );
       t139 = _mm_load_pd( b70 );
       t141 = _mm_load_pd( b71 );
       t143 = _mm_load_pd( b72 );
       t145 = _mm_load_pd( b73 );
       t147 = _mm_load_pd( b74 );
       t149 = _mm_load_pd( b75 );
       t151 = _mm_load_pd( b76 );
       t153 = _mm_load_pd( b77 );
       t155 = _mm_load_pd( b78 );
       t157 = _mm_load_pd( b79 );
       t159 = _mm_load_pd( b80 );
       t161 = _mm_load_pd( b81 );
       t163 = _mm_load_pd( b82 );
       t165 = _mm_load_pd( b83 );
       t167 = _mm_load_pd( b84 );
       t169 = _mm_load_pd( b85 );
       t171 = _mm_load_pd( b86 );
       t173 = _mm_load_pd( b87 );
       t175 = _mm_load_pd( b88 );
       t177 = _mm_load_pd( b89 );
       t179 = _mm_load_pd( b90 );
       t181 = _mm_load_pd( b91 );
       t183 = _mm_load_pd( b92 );
       t185 = _mm_load_pd( b93 );
       t187 = _mm_load_pd( b94 );
       t189 = _mm_load_pd( b95 );
       t191 = _mm_load_pd( b96 );
       t193 = _mm_load_pd( b97 );
       t195 = _mm_load_pd( b98 );
       t197 = _mm_load_pd( b99 );
       t199 = _mm_load_pd( b100 );
       t201 = _mm_load_pd( b101 );
       t203 = _mm_load_pd( b102 );
       t205 = _mm_load_pd( b103 );
       t207 = _mm_load_pd( b104 );
       t209 = _mm_load_pd( b105 );
       t211 = _mm_load_pd( b106 );
       t213 = _mm_load_pd( b107 );
       t215 = _mm_load_pd( b108 );
       t217 = _mm_load_pd( b109 );
       t219 = _mm_load_pd( b110 );
       t221 = _mm_load_pd( b111 );
       t223 = _mm_load_pd( b112 );
       t225 = _mm_load_pd( b113 );
       t227 = _mm_load_pd( b114 );
       t229 = _mm_load_pd( b115 );
       t231 = _mm_load_pd( b116 );
       t233 = _mm_load_pd( b117 );
       t235 = _mm_load_pd( b118 );
       t237 = _mm_load_pd( b119 );
       t239 = _mm_load_pd( b120 );
       t241 = _mm_load_pd( b121 );
       t243 = _mm_load_pd( b122 );
       t245 = _mm_load_pd( b123 );
       t247 = _mm_load_pd( b124 );
       t249 = _mm_load_pd( b125 );
       t251 = _mm_load_pd( b126 );
       t253 = _mm_load_pd( b127 );
       t255 = _mm_load_pd( b128 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );
       t13 = _mm_dp_pd( t12, t13, 0xff );
       t15 = _mm_dp_pd( t14, t15, 0xff );
       t17 = _mm_dp_pd( t16, t17, 0xff );
       t19 = _mm_dp_pd( t18, t19, 0xff );
       t21 = _mm_dp_pd( t20, t21, 0xff );
       t23 = _mm_dp_pd( t22, t23, 0xff );
       t25 = _mm_dp_pd( t24, t25, 0xff );
       t27 = _mm_dp_pd( t26, t27, 0xff );
       t29 = _mm_dp_pd( t28, t29, 0xff );
       t31 = _mm_dp_pd( t30, t31, 0xff );
       t33 = _mm_dp_pd( t32, t33, 0xff );
       t35 = _mm_dp_pd( t34, t35, 0xff );
       t37 = _mm_dp_pd( t36, t37, 0xff );
       t39 = _mm_dp_pd( t38, t39, 0xff );
       t41 = _mm_dp_pd( t40, t41, 0xff );
       t43 = _mm_dp_pd( t42, t43, 0xff );
       t45 = _mm_dp_pd( t44, t45, 0xff );
       t47 = _mm_dp_pd( t46, t47, 0xff );
       t49 = _mm_dp_pd( t48, t49, 0xff );
       t51 = _mm_dp_pd( t50, t51, 0xff );
       t53 = _mm_dp_pd( t52, t53, 0xff );
       t55 = _mm_dp_pd( t54, t55, 0xff );
       t57 = _mm_dp_pd( t56, t57, 0xff );
       t59 = _mm_dp_pd( t58, t59, 0xff );
       t61 = _mm_dp_pd( t60, t61, 0xff );
       t63 = _mm_dp_pd( t62, t63, 0xff );
       t65 = _mm_dp_pd( t64, t65, 0xff );
       t67 = _mm_dp_pd( t66, t67, 0xff );
       t69 = _mm_dp_pd( t68, t69, 0xff );
       t71 = _mm_dp_pd( t70, t71, 0xff );
       t73 = _mm_dp_pd( t72, t73, 0xff );
       t75 = _mm_dp_pd( t74, t75, 0xff );
       t77 = _mm_dp_pd( t76, t77, 0xff );
       t79 = _mm_dp_pd( t78, t79, 0xff );
       t81 = _mm_dp_pd( t80, t81, 0xff );
       t83 = _mm_dp_pd( t82, t83, 0xff );
       t85 = _mm_dp_pd( t84, t85, 0xff );
       t87 = _mm_dp_pd( t86, t87, 0xff );
       t89 = _mm_dp_pd( t88, t89, 0xff );
       t91 = _mm_dp_pd( t90, t91, 0xff );
       t93 = _mm_dp_pd( t92, t93, 0xff );
       t95 = _mm_dp_pd( t94, t95, 0xff );
       t97 = _mm_dp_pd( t96, t97, 0xff );
       t99 = _mm_dp_pd( t98, t99, 0xff );
       t101 = _mm_dp_pd( t100, t101, 0xff );
       t103 = _mm_dp_pd( t102, t103, 0xff );
       t105 = _mm_dp_pd( t104, t105, 0xff );
       t107 = _mm_dp_pd( t106, t107, 0xff );
       t109 = _mm_dp_pd( t108, t109, 0xff );
       t111 = _mm_dp_pd( t110, t111, 0xff );
       t113 = _mm_dp_pd( t112, t113, 0xff );
       t115 = _mm_dp_pd( t114, t115, 0xff );
       t117 = _mm_dp_pd( t116, t117, 0xff );
       t119 = _mm_dp_pd( t118, t119, 0xff );
       t121 = _mm_dp_pd( t120, t121, 0xff );
       t123 = _mm_dp_pd( t122, t123, 0xff );
       t125 = _mm_dp_pd( t124, t125, 0xff );
       t127 = _mm_dp_pd( t126, t127, 0xff );
       t129 = _mm_dp_pd( t128, t129, 0xff );
       t131 = _mm_dp_pd( t130, t131, 0xff );
       t133 = _mm_dp_pd( t132, t133, 0xff );
       t135 = _mm_dp_pd( t134, t135, 0xff );
       t137 = _mm_dp_pd( t136, t137, 0xff );
       t139 = _mm_dp_pd( t138, t139, 0xff );
       t141 = _mm_dp_pd( t140, t141, 0xff );
       t143 = _mm_dp_pd( t142, t143, 0xff );
       t145 = _mm_dp_pd( t144, t145, 0xff );
       t147 = _mm_dp_pd( t146, t147, 0xff );
       t149 = _mm_dp_pd( t148, t149, 0xff );
       t151 = _mm_dp_pd( t150, t151, 0xff );
       t153 = _mm_dp_pd( t152, t153, 0xff );
       t155 = _mm_dp_pd( t154, t155, 0xff );
       t157 = _mm_dp_pd( t156, t157, 0xff );
       t159 = _mm_dp_pd( t158, t159, 0xff );
       t161 = _mm_dp_pd( t160, t161, 0xff );
       t163 = _mm_dp_pd( t162, t163, 0xff );
       t165 = _mm_dp_pd( t164, t165, 0xff );
       t167 = _mm_dp_pd( t166, t167, 0xff );
       t169 = _mm_dp_pd( t168, t169, 0xff );
       t171 = _mm_dp_pd( t170, t171, 0xff );
       t173 = _mm_dp_pd( t172, t173, 0xff );
       t175 = _mm_dp_pd( t174, t175, 0xff );
       t177 = _mm_dp_pd( t176, t177, 0xff );
       t179 = _mm_dp_pd( t178, t179, 0xff );
       t181 = _mm_dp_pd( t180, t181, 0xff );
       t183 = _mm_dp_pd( t182, t183, 0xff );
       t185 = _mm_dp_pd( t184, t185, 0xff );
       t187 = _mm_dp_pd( t186, t187, 0xff );
       t189 = _mm_dp_pd( t188, t189, 0xff );
       t191 = _mm_dp_pd( t190, t191, 0xff );
       t193 = _mm_dp_pd( t192, t193, 0xff );
       t195 = _mm_dp_pd( t194, t195, 0xff );
       t197 = _mm_dp_pd( t196, t197, 0xff );
       t199 = _mm_dp_pd( t198, t199, 0xff );
       t201 = _mm_dp_pd( t200, t201, 0xff );
       t203 = _mm_dp_pd( t202, t203, 0xff );
       t205 = _mm_dp_pd( t204, t205, 0xff );
       t207 = _mm_dp_pd( t206, t207, 0xff );
       t209 = _mm_dp_pd( t208, t209, 0xff );
       t211 = _mm_dp_pd( t210, t211, 0xff );
       t213 = _mm_dp_pd( t212, t213, 0xff );
       t215 = _mm_dp_pd( t214, t215, 0xff );
       t217 = _mm_dp_pd( t216, t217, 0xff );
       t219 = _mm_dp_pd( t218, t219, 0xff );
       t221 = _mm_dp_pd( t220, t221, 0xff );
       t223 = _mm_dp_pd( t222, t223, 0xff );
       t225 = _mm_dp_pd( t224, t225, 0xff );
       t227 = _mm_dp_pd( t226, t227, 0xff );
       t229 = _mm_dp_pd( t228, t229, 0xff );
       t231 = _mm_dp_pd( t230, t231, 0xff );
       t233 = _mm_dp_pd( t232, t233, 0xff );
       t235 = _mm_dp_pd( t234, t235, 0xff );
       t237 = _mm_dp_pd( t236, t237, 0xff );
       t239 = _mm_dp_pd( t238, t239, 0xff );
       t241 = _mm_dp_pd( t240, t241, 0xff );
       t243 = _mm_dp_pd( t242, t243, 0xff );
       t245 = _mm_dp_pd( t244, t245, 0xff );
       t247 = _mm_dp_pd( t246, t247, 0xff );
       t249 = _mm_dp_pd( t248, t249, 0xff );
       t251 = _mm_dp_pd( t250, t251, 0xff );
       t253 = _mm_dp_pd( t252, t253, 0xff );
       t255 = _mm_dp_pd( t254, t255, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t13 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t15 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t17 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t19 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t21 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t23 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t25 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t27 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t29 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t31 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t33 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t35 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t37 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t39 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t41 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t43 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t45 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t47 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t49 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t51 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t53 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t55 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t57 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t59 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t61 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t63 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t65 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t67 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t69 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t71 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t73 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t75 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t77 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t79 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t81 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t83 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t85 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t87 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t89 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t91 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t93 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t95 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t97 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t99 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t101 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t103 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t105 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t107 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t109 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t111 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t113 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t115 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t117 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t119 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t121 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t123 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t125 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t127 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t129 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t131 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t133 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t135 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t137 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t139 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t141 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t143 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t145 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t147 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t149 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t151 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t153 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t155 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t157 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t159 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t161 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t163 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t165 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t167 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t169 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t171 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t173 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t175 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t177 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t179 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t181 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t183 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t185 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t187 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t189 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t191 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t193 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t195 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t197 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t199 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t201 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t203 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t205 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t207 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t209 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t211 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t213 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t215 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t217 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t219 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t221 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t223 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t225 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t227 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t229 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t231 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t233 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t235 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t237 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t239 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t241 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t243 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t245 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t247 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t249 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t251 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t253 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t255 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_512( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2], a7[2], b7[2], a8[2], b8[2], a9[2], b9[2], a10[2], b10[2], a11[2], b11[2], a12[2], b12[2], a13[2], b13[2], a14[2], b14[2], a15[2], b15[2], a16[2], b16[2], a17[2], b17[2], a18[2], b18[2], a19[2], b19[2], a20[2], b20[2], a21[2], b21[2], a22[2], b22[2], a23[2], b23[2], a24[2], b24[2], a25[2], b25[2], a26[2], b26[2], a27[2], b27[2], a28[2], b28[2], a29[2], b29[2], a30[2], b30[2], a31[2], b31[2], a32[2], b32[2], a33[2], b33[2], a34[2], b34[2], a35[2], b35[2], a36[2], b36[2], a37[2], b37[2], a38[2], b38[2], a39[2], b39[2], a40[2], b40[2], a41[2], b41[2], a42[2], b42[2], a43[2], b43[2], a44[2], b44[2], a45[2], b45[2], a46[2], b46[2], a47[2], b47[2], a48[2], b48[2], a49[2], b49[2], a50[2], b50[2], a51[2], b51[2], a52[2], b52[2], a53[2], b53[2], a54[2], b54[2], a55[2], b55[2], a56[2], b56[2], a57[2], b57[2], a58[2], b58[2], a59[2], b59[2], a60[2], b60[2], a61[2], b61[2], a62[2], b62[2], a63[2], b63[2], a64[2], b64[2], a65[2], b65[2], a66[2], b66[2], a67[2], b67[2], a68[2], b68[2], a69[2], b69[2], a70[2], b70[2], a71[2], b71[2], a72[2], b72[2], a73[2], b73[2], a74[2], b74[2], a75[2], b75[2], a76[2], b76[2], a77[2], b77[2], a78[2], b78[2], a79[2], b79[2], a80[2], b80[2], a81[2], b81[2], a82[2], b82[2], a83[2], b83[2], a84[2], b84[2], a85[2], b85[2], a86[2], b86[2], a87[2], b87[2], a88[2], b88[2], a89[2], b89[2], a90[2], b90[2], a91[2], b91[2], a92[2], b92[2], a93[2], b93[2], a94[2], b94[2], a95[2], b95[2], a96[2], b96[2], a97[2], b97[2], a98[2], b98[2], a99[2], b99[2], a100[2], b100[2], a101[2], b101[2], a102[2], b102[2], a103[2], b103[2], a104[2], b104[2], a105[2], b105[2], a106[2], b106[2], a107[2], b107[2], a108[2], b108[2], a109[2], b109[2], a110[2], b110[2], a111[2], b111[2], a112[2], b112[2], a113[2], b113[2], a114[2], b114[2], a115[2], b115[2], a116[2], b116[2], a117[2], b117[2], a118[2], b118[2], a119[2], b119[2], a120[2], b120[2], a121[2], b121[2], a122[2], b122[2], a123[2], b123[2], a124[2], b124[2], a125[2], b125[2], a126[2], b126[2], a127[2], b127[2], a128[2], b128[2], a129[2], b129[2], a130[2], b130[2], a131[2], b131[2], a132[2], b132[2], a133[2], b133[2], a134[2], b134[2], a135[2], b135[2], a136[2], b136[2], a137[2], b137[2], a138[2], b138[2], a139[2], b139[2], a140[2], b140[2], a141[2], b141[2], a142[2], b142[2], a143[2], b143[2], a144[2], b144[2], a145[2], b145[2], a146[2], b146[2], a147[2], b147[2], a148[2], b148[2], a149[2], b149[2], a150[2], b150[2], a151[2], b151[2], a152[2], b152[2], a153[2], b153[2], a154[2], b154[2], a155[2], b155[2], a156[2], b156[2], a157[2], b157[2], a158[2], b158[2], a159[2], b159[2], a160[2], b160[2], a161[2], b161[2], a162[2], b162[2], a163[2], b163[2], a164[2], b164[2], a165[2], b165[2], a166[2], b166[2], a167[2], b167[2], a168[2], b168[2], a169[2], b169[2], a170[2], b170[2], a171[2], b171[2], a172[2], b172[2], a173[2], b173[2], a174[2], b174[2], a175[2], b175[2], a176[2], b176[2], a177[2], b177[2], a178[2], b178[2], a179[2], b179[2], a180[2], b180[2], a181[2], b181[2], a182[2], b182[2], a183[2], b183[2], a184[2], b184[2], a185[2], b185[2], a186[2], b186[2], a187[2], b187[2], a188[2], b188[2], a189[2], b189[2], a190[2], b190[2], a191[2], b191[2], a192[2], b192[2], a193[2], b193[2], a194[2], b194[2], a195[2], b195[2], a196[2], b196[2], a197[2], b197[2], a198[2], b198[2], a199[2], b199[2], a200[2], b200[2], a201[2], b201[2], a202[2], b202[2], a203[2], b203[2], a204[2], b204[2], a205[2], b205[2], a206[2], b206[2], a207[2], b207[2], a208[2], b208[2], a209[2], b209[2], a210[2], b210[2], a211[2], b211[2], a212[2], b212[2], a213[2], b213[2], a214[2], b214[2], a215[2], b215[2], a216[2], b216[2], a217[2], b217[2], a218[2], b218[2], a219[2], b219[2], a220[2], b220[2], a221[2], b221[2], a222[2], b222[2], a223[2], b223[2], a224[2], b224[2], a225[2], b225[2], a226[2], b226[2], a227[2], b227[2], a228[2], b228[2], a229[2], b229[2], a230[2], b230[2], a231[2], b231[2], a232[2], b232[2], a233[2], b233[2], a234[2], b234[2], a235[2], b235[2], a236[2], b236[2], a237[2], b237[2], a238[2], b238[2], a239[2], b239[2], a240[2], b240[2], a241[2], b241[2], a242[2], b242[2], a243[2], b243[2], a244[2], b244[2], a245[2], b245[2], a246[2], b246[2], a247[2], b247[2], a248[2], b248[2], a249[2], b249[2], a250[2], b250[2], a251[2], b251[2], a252[2], b252[2], a253[2], b253[2], a254[2], b254[2], a255[2], b255[2], a256[2], b256[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79, t80, t81, t82, t83, t84, t85, t86, t87, t88, t89, t90, t91, t92, t93, t94, t95, t96, t97, t98, t99, t100, t101, t102, t103, t104, t105, t106, t107, t108, t109, t110, t111, t112, t113, t114, t115, t116, t117, t118, t119, t120, t121, t122, t123, t124, t125, t126, t127, t128, t129, t130, t131, t132, t133, t134, t135, t136, t137, t138, t139, t140, t141, t142, t143, t144, t145, t146, t147, t148, t149, t150, t151, t152, t153, t154, t155, t156, t157, t158, t159, t160, t161, t162, t163, t164, t165, t166, t167, t168, t169, t170, t171, t172, t173, t174, t175, t176, t177, t178, t179, t180, t181, t182, t183, t184, t185, t186, t187, t188, t189, t190, t191, t192, t193, t194, t195, t196, t197, t198, t199, t200, t201, t202, t203, t204, t205, t206, t207, t208, t209, t210, t211, t212, t213, t214, t215, t216, t217, t218, t219, t220, t221, t222, t223, t224, t225, t226, t227, t228, t229, t230, t231, t232, t233, t234, t235, t236, t237, t238, t239, t240, t241, t242, t243, t244, t245, t246, t247, t248, t249, t250, t251, t252, t253, t254, t255, t256, t257, t258, t259, t260, t261, t262, t263, t264, t265, t266, t267, t268, t269, t270, t271, t272, t273, t274, t275, t276, t277, t278, t279, t280, t281, t282, t283, t284, t285, t286, t287, t288, t289, t290, t291, t292, t293, t294, t295, t296, t297, t298, t299, t300, t301, t302, t303, t304, t305, t306, t307, t308, t309, t310, t311, t312, t313, t314, t315, t316, t317, t318, t319, t320, t321, t322, t323, t324, t325, t326, t327, t328, t329, t330, t331, t332, t333, t334, t335, t336, t337, t338, t339, t340, t341, t342, t343, t344, t345, t346, t347, t348, t349, t350, t351, t352, t353, t354, t355, t356, t357, t358, t359, t360, t361, t362, t363, t364, t365, t366, t367, t368, t369, t370, t371, t372, t373, t374, t375, t376, t377, t378, t379, t380, t381, t382, t383, t384, t385, t386, t387, t388, t389, t390, t391, t392, t393, t394, t395, t396, t397, t398, t399, t400, t401, t402, t403, t404, t405, t406, t407, t408, t409, t410, t411, t412, t413, t414, t415, t416, t417, t418, t419, t420, t421, t422, t423, t424, t425, t426, t427, t428, t429, t430, t431, t432, t433, t434, t435, t436, t437, t438, t439, t440, t441, t442, t443, t444, t445, t446, t447, t448, t449, t450, t451, t452, t453, t454, t455, t456, t457, t458, t459, t460, t461, t462, t463, t464, t465, t466, t467, t468, t469, t470, t471, t472, t473, t474, t475, t476, t477, t478, t479, t480, t481, t482, t483, t484, t485, t486, t487, t488, t489, t490, t491, t492, t493, t494, t495, t496, t497, t498, t499, t500, t501, t502, t503, t504, t505, t506, t507, t508, t509, t510, t511;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=512 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     if( k + 12 < n ) {
       a7[0] = *( m1 + n * i + (k+12) );
     } else {
       a7[0] = 0;
     }
     if( k + 13 < n ) {
       a7[1] = *( m1 + n * i + (k+13) );
     } else {
       a7[1] = 0;
     }
     if( k + 14 < n ) {
       a8[0] = *( m1 + n * i + (k+14) );
     } else {
       a8[0] = 0;
     }
     if( k + 15 < n ) {
       a8[1] = *( m1 + n * i + (k+15) );
     } else {
       a8[1] = 0;
     }
     if( k + 16 < n ) {
       a9[0] = *( m1 + n * i + (k+16) );
     } else {
       a9[0] = 0;
     }
     if( k + 17 < n ) {
       a9[1] = *( m1 + n * i + (k+17) );
     } else {
       a9[1] = 0;
     }
     if( k + 18 < n ) {
       a10[0] = *( m1 + n * i + (k+18) );
     } else {
       a10[0] = 0;
     }
     if( k + 19 < n ) {
       a10[1] = *( m1 + n * i + (k+19) );
     } else {
       a10[1] = 0;
     }
     if( k + 20 < n ) {
       a11[0] = *( m1 + n * i + (k+20) );
     } else {
       a11[0] = 0;
     }
     if( k + 21 < n ) {
       a11[1] = *( m1 + n * i + (k+21) );
     } else {
       a11[1] = 0;
     }
     if( k + 22 < n ) {
       a12[0] = *( m1 + n * i + (k+22) );
     } else {
       a12[0] = 0;
     }
     if( k + 23 < n ) {
       a12[1] = *( m1 + n * i + (k+23) );
     } else {
       a12[1] = 0;
     }
     if( k + 24 < n ) {
       a13[0] = *( m1 + n * i + (k+24) );
     } else {
       a13[0] = 0;
     }
     if( k + 25 < n ) {
       a13[1] = *( m1 + n * i + (k+25) );
     } else {
       a13[1] = 0;
     }
     if( k + 26 < n ) {
       a14[0] = *( m1 + n * i + (k+26) );
     } else {
       a14[0] = 0;
     }
     if( k + 27 < n ) {
       a14[1] = *( m1 + n * i + (k+27) );
     } else {
       a14[1] = 0;
     }
     if( k + 28 < n ) {
       a15[0] = *( m1 + n * i + (k+28) );
     } else {
       a15[0] = 0;
     }
     if( k + 29 < n ) {
       a15[1] = *( m1 + n * i + (k+29) );
     } else {
       a15[1] = 0;
     }
     if( k + 30 < n ) {
       a16[0] = *( m1 + n * i + (k+30) );
     } else {
       a16[0] = 0;
     }
     if( k + 31 < n ) {
       a16[1] = *( m1 + n * i + (k+31) );
     } else {
       a16[1] = 0;
     }
     if( k + 32 < n ) {
       a17[0] = *( m1 + n * i + (k+32) );
     } else {
       a17[0] = 0;
     }
     if( k + 33 < n ) {
       a17[1] = *( m1 + n * i + (k+33) );
     } else {
       a17[1] = 0;
     }
     if( k + 34 < n ) {
       a18[0] = *( m1 + n * i + (k+34) );
     } else {
       a18[0] = 0;
     }
     if( k + 35 < n ) {
       a18[1] = *( m1 + n * i + (k+35) );
     } else {
       a18[1] = 0;
     }
     if( k + 36 < n ) {
       a19[0] = *( m1 + n * i + (k+36) );
     } else {
       a19[0] = 0;
     }
     if( k + 37 < n ) {
       a19[1] = *( m1 + n * i + (k+37) );
     } else {
       a19[1] = 0;
     }
     if( k + 38 < n ) {
       a20[0] = *( m1 + n * i + (k+38) );
     } else {
       a20[0] = 0;
     }
     if( k + 39 < n ) {
       a20[1] = *( m1 + n * i + (k+39) );
     } else {
       a20[1] = 0;
     }
     if( k + 40 < n ) {
       a21[0] = *( m1 + n * i + (k+40) );
     } else {
       a21[0] = 0;
     }
     if( k + 41 < n ) {
       a21[1] = *( m1 + n * i + (k+41) );
     } else {
       a21[1] = 0;
     }
     if( k + 42 < n ) {
       a22[0] = *( m1 + n * i + (k+42) );
     } else {
       a22[0] = 0;
     }
     if( k + 43 < n ) {
       a22[1] = *( m1 + n * i + (k+43) );
     } else {
       a22[1] = 0;
     }
     if( k + 44 < n ) {
       a23[0] = *( m1 + n * i + (k+44) );
     } else {
       a23[0] = 0;
     }
     if( k + 45 < n ) {
       a23[1] = *( m1 + n * i + (k+45) );
     } else {
       a23[1] = 0;
     }
     if( k + 46 < n ) {
       a24[0] = *( m1 + n * i + (k+46) );
     } else {
       a24[0] = 0;
     }
     if( k + 47 < n ) {
       a24[1] = *( m1 + n * i + (k+47) );
     } else {
       a24[1] = 0;
     }
     if( k + 48 < n ) {
       a25[0] = *( m1 + n * i + (k+48) );
     } else {
       a25[0] = 0;
     }
     if( k + 49 < n ) {
       a25[1] = *( m1 + n * i + (k+49) );
     } else {
       a25[1] = 0;
     }
     if( k + 50 < n ) {
       a26[0] = *( m1 + n * i + (k+50) );
     } else {
       a26[0] = 0;
     }
     if( k + 51 < n ) {
       a26[1] = *( m1 + n * i + (k+51) );
     } else {
       a26[1] = 0;
     }
     if( k + 52 < n ) {
       a27[0] = *( m1 + n * i + (k+52) );
     } else {
       a27[0] = 0;
     }
     if( k + 53 < n ) {
       a27[1] = *( m1 + n * i + (k+53) );
     } else {
       a27[1] = 0;
     }
     if( k + 54 < n ) {
       a28[0] = *( m1 + n * i + (k+54) );
     } else {
       a28[0] = 0;
     }
     if( k + 55 < n ) {
       a28[1] = *( m1 + n * i + (k+55) );
     } else {
       a28[1] = 0;
     }
     if( k + 56 < n ) {
       a29[0] = *( m1 + n * i + (k+56) );
     } else {
       a29[0] = 0;
     }
     if( k + 57 < n ) {
       a29[1] = *( m1 + n * i + (k+57) );
     } else {
       a29[1] = 0;
     }
     if( k + 58 < n ) {
       a30[0] = *( m1 + n * i + (k+58) );
     } else {
       a30[0] = 0;
     }
     if( k + 59 < n ) {
       a30[1] = *( m1 + n * i + (k+59) );
     } else {
       a30[1] = 0;
     }
     if( k + 60 < n ) {
       a31[0] = *( m1 + n * i + (k+60) );
     } else {
       a31[0] = 0;
     }
     if( k + 61 < n ) {
       a31[1] = *( m1 + n * i + (k+61) );
     } else {
       a31[1] = 0;
     }
     if( k + 62 < n ) {
       a32[0] = *( m1 + n * i + (k+62) );
     } else {
       a32[0] = 0;
     }
     if( k + 63 < n ) {
       a32[1] = *( m1 + n * i + (k+63) );
     } else {
       a32[1] = 0;
     }
     if( k + 64 < n ) {
       a33[0] = *( m1 + n * i + (k+64) );
     } else {
       a33[0] = 0;
     }
     if( k + 65 < n ) {
       a33[1] = *( m1 + n * i + (k+65) );
     } else {
       a33[1] = 0;
     }
     if( k + 66 < n ) {
       a34[0] = *( m1 + n * i + (k+66) );
     } else {
       a34[0] = 0;
     }
     if( k + 67 < n ) {
       a34[1] = *( m1 + n * i + (k+67) );
     } else {
       a34[1] = 0;
     }
     if( k + 68 < n ) {
       a35[0] = *( m1 + n * i + (k+68) );
     } else {
       a35[0] = 0;
     }
     if( k + 69 < n ) {
       a35[1] = *( m1 + n * i + (k+69) );
     } else {
       a35[1] = 0;
     }
     if( k + 70 < n ) {
       a36[0] = *( m1 + n * i + (k+70) );
     } else {
       a36[0] = 0;
     }
     if( k + 71 < n ) {
       a36[1] = *( m1 + n * i + (k+71) );
     } else {
       a36[1] = 0;
     }
     if( k + 72 < n ) {
       a37[0] = *( m1 + n * i + (k+72) );
     } else {
       a37[0] = 0;
     }
     if( k + 73 < n ) {
       a37[1] = *( m1 + n * i + (k+73) );
     } else {
       a37[1] = 0;
     }
     if( k + 74 < n ) {
       a38[0] = *( m1 + n * i + (k+74) );
     } else {
       a38[0] = 0;
     }
     if( k + 75 < n ) {
       a38[1] = *( m1 + n * i + (k+75) );
     } else {
       a38[1] = 0;
     }
     if( k + 76 < n ) {
       a39[0] = *( m1 + n * i + (k+76) );
     } else {
       a39[0] = 0;
     }
     if( k + 77 < n ) {
       a39[1] = *( m1 + n * i + (k+77) );
     } else {
       a39[1] = 0;
     }
     if( k + 78 < n ) {
       a40[0] = *( m1 + n * i + (k+78) );
     } else {
       a40[0] = 0;
     }
     if( k + 79 < n ) {
       a40[1] = *( m1 + n * i + (k+79) );
     } else {
       a40[1] = 0;
     }
     if( k + 80 < n ) {
       a41[0] = *( m1 + n * i + (k+80) );
     } else {
       a41[0] = 0;
     }
     if( k + 81 < n ) {
       a41[1] = *( m1 + n * i + (k+81) );
     } else {
       a41[1] = 0;
     }
     if( k + 82 < n ) {
       a42[0] = *( m1 + n * i + (k+82) );
     } else {
       a42[0] = 0;
     }
     if( k + 83 < n ) {
       a42[1] = *( m1 + n * i + (k+83) );
     } else {
       a42[1] = 0;
     }
     if( k + 84 < n ) {
       a43[0] = *( m1 + n * i + (k+84) );
     } else {
       a43[0] = 0;
     }
     if( k + 85 < n ) {
       a43[1] = *( m1 + n * i + (k+85) );
     } else {
       a43[1] = 0;
     }
     if( k + 86 < n ) {
       a44[0] = *( m1 + n * i + (k+86) );
     } else {
       a44[0] = 0;
     }
     if( k + 87 < n ) {
       a44[1] = *( m1 + n * i + (k+87) );
     } else {
       a44[1] = 0;
     }
     if( k + 88 < n ) {
       a45[0] = *( m1 + n * i + (k+88) );
     } else {
       a45[0] = 0;
     }
     if( k + 89 < n ) {
       a45[1] = *( m1 + n * i + (k+89) );
     } else {
       a45[1] = 0;
     }
     if( k + 90 < n ) {
       a46[0] = *( m1 + n * i + (k+90) );
     } else {
       a46[0] = 0;
     }
     if( k + 91 < n ) {
       a46[1] = *( m1 + n * i + (k+91) );
     } else {
       a46[1] = 0;
     }
     if( k + 92 < n ) {
       a47[0] = *( m1 + n * i + (k+92) );
     } else {
       a47[0] = 0;
     }
     if( k + 93 < n ) {
       a47[1] = *( m1 + n * i + (k+93) );
     } else {
       a47[1] = 0;
     }
     if( k + 94 < n ) {
       a48[0] = *( m1 + n * i + (k+94) );
     } else {
       a48[0] = 0;
     }
     if( k + 95 < n ) {
       a48[1] = *( m1 + n * i + (k+95) );
     } else {
       a48[1] = 0;
     }
     if( k + 96 < n ) {
       a49[0] = *( m1 + n * i + (k+96) );
     } else {
       a49[0] = 0;
     }
     if( k + 97 < n ) {
       a49[1] = *( m1 + n * i + (k+97) );
     } else {
       a49[1] = 0;
     }
     if( k + 98 < n ) {
       a50[0] = *( m1 + n * i + (k+98) );
     } else {
       a50[0] = 0;
     }
     if( k + 99 < n ) {
       a50[1] = *( m1 + n * i + (k+99) );
     } else {
       a50[1] = 0;
     }
     if( k + 100 < n ) {
       a51[0] = *( m1 + n * i + (k+100) );
     } else {
       a51[0] = 0;
     }
     if( k + 101 < n ) {
       a51[1] = *( m1 + n * i + (k+101) );
     } else {
       a51[1] = 0;
     }
     if( k + 102 < n ) {
       a52[0] = *( m1 + n * i + (k+102) );
     } else {
       a52[0] = 0;
     }
     if( k + 103 < n ) {
       a52[1] = *( m1 + n * i + (k+103) );
     } else {
       a52[1] = 0;
     }
     if( k + 104 < n ) {
       a53[0] = *( m1 + n * i + (k+104) );
     } else {
       a53[0] = 0;
     }
     if( k + 105 < n ) {
       a53[1] = *( m1 + n * i + (k+105) );
     } else {
       a53[1] = 0;
     }
     if( k + 106 < n ) {
       a54[0] = *( m1 + n * i + (k+106) );
     } else {
       a54[0] = 0;
     }
     if( k + 107 < n ) {
       a54[1] = *( m1 + n * i + (k+107) );
     } else {
       a54[1] = 0;
     }
     if( k + 108 < n ) {
       a55[0] = *( m1 + n * i + (k+108) );
     } else {
       a55[0] = 0;
     }
     if( k + 109 < n ) {
       a55[1] = *( m1 + n * i + (k+109) );
     } else {
       a55[1] = 0;
     }
     if( k + 110 < n ) {
       a56[0] = *( m1 + n * i + (k+110) );
     } else {
       a56[0] = 0;
     }
     if( k + 111 < n ) {
       a56[1] = *( m1 + n * i + (k+111) );
     } else {
       a56[1] = 0;
     }
     if( k + 112 < n ) {
       a57[0] = *( m1 + n * i + (k+112) );
     } else {
       a57[0] = 0;
     }
     if( k + 113 < n ) {
       a57[1] = *( m1 + n * i + (k+113) );
     } else {
       a57[1] = 0;
     }
     if( k + 114 < n ) {
       a58[0] = *( m1 + n * i + (k+114) );
     } else {
       a58[0] = 0;
     }
     if( k + 115 < n ) {
       a58[1] = *( m1 + n * i + (k+115) );
     } else {
       a58[1] = 0;
     }
     if( k + 116 < n ) {
       a59[0] = *( m1 + n * i + (k+116) );
     } else {
       a59[0] = 0;
     }
     if( k + 117 < n ) {
       a59[1] = *( m1 + n * i + (k+117) );
     } else {
       a59[1] = 0;
     }
     if( k + 118 < n ) {
       a60[0] = *( m1 + n * i + (k+118) );
     } else {
       a60[0] = 0;
     }
     if( k + 119 < n ) {
       a60[1] = *( m1 + n * i + (k+119) );
     } else {
       a60[1] = 0;
     }
     if( k + 120 < n ) {
       a61[0] = *( m1 + n * i + (k+120) );
     } else {
       a61[0] = 0;
     }
     if( k + 121 < n ) {
       a61[1] = *( m1 + n * i + (k+121) );
     } else {
       a61[1] = 0;
     }
     if( k + 122 < n ) {
       a62[0] = *( m1 + n * i + (k+122) );
     } else {
       a62[0] = 0;
     }
     if( k + 123 < n ) {
       a62[1] = *( m1 + n * i + (k+123) );
     } else {
       a62[1] = 0;
     }
     if( k + 124 < n ) {
       a63[0] = *( m1 + n * i + (k+124) );
     } else {
       a63[0] = 0;
     }
     if( k + 125 < n ) {
       a63[1] = *( m1 + n * i + (k+125) );
     } else {
       a63[1] = 0;
     }
     if( k + 126 < n ) {
       a64[0] = *( m1 + n * i + (k+126) );
     } else {
       a64[0] = 0;
     }
     if( k + 127 < n ) {
       a64[1] = *( m1 + n * i + (k+127) );
     } else {
       a64[1] = 0;
     }
     if( k + 128 < n ) {
       a65[0] = *( m1 + n * i + (k+128) );
     } else {
       a65[0] = 0;
     }
     if( k + 129 < n ) {
       a65[1] = *( m1 + n * i + (k+129) );
     } else {
       a65[1] = 0;
     }
     if( k + 130 < n ) {
       a66[0] = *( m1 + n * i + (k+130) );
     } else {
       a66[0] = 0;
     }
     if( k + 131 < n ) {
       a66[1] = *( m1 + n * i + (k+131) );
     } else {
       a66[1] = 0;
     }
     if( k + 132 < n ) {
       a67[0] = *( m1 + n * i + (k+132) );
     } else {
       a67[0] = 0;
     }
     if( k + 133 < n ) {
       a67[1] = *( m1 + n * i + (k+133) );
     } else {
       a67[1] = 0;
     }
     if( k + 134 < n ) {
       a68[0] = *( m1 + n * i + (k+134) );
     } else {
       a68[0] = 0;
     }
     if( k + 135 < n ) {
       a68[1] = *( m1 + n * i + (k+135) );
     } else {
       a68[1] = 0;
     }
     if( k + 136 < n ) {
       a69[0] = *( m1 + n * i + (k+136) );
     } else {
       a69[0] = 0;
     }
     if( k + 137 < n ) {
       a69[1] = *( m1 + n * i + (k+137) );
     } else {
       a69[1] = 0;
     }
     if( k + 138 < n ) {
       a70[0] = *( m1 + n * i + (k+138) );
     } else {
       a70[0] = 0;
     }
     if( k + 139 < n ) {
       a70[1] = *( m1 + n * i + (k+139) );
     } else {
       a70[1] = 0;
     }
     if( k + 140 < n ) {
       a71[0] = *( m1 + n * i + (k+140) );
     } else {
       a71[0] = 0;
     }
     if( k + 141 < n ) {
       a71[1] = *( m1 + n * i + (k+141) );
     } else {
       a71[1] = 0;
     }
     if( k + 142 < n ) {
       a72[0] = *( m1 + n * i + (k+142) );
     } else {
       a72[0] = 0;
     }
     if( k + 143 < n ) {
       a72[1] = *( m1 + n * i + (k+143) );
     } else {
       a72[1] = 0;
     }
     if( k + 144 < n ) {
       a73[0] = *( m1 + n * i + (k+144) );
     } else {
       a73[0] = 0;
     }
     if( k + 145 < n ) {
       a73[1] = *( m1 + n * i + (k+145) );
     } else {
       a73[1] = 0;
     }
     if( k + 146 < n ) {
       a74[0] = *( m1 + n * i + (k+146) );
     } else {
       a74[0] = 0;
     }
     if( k + 147 < n ) {
       a74[1] = *( m1 + n * i + (k+147) );
     } else {
       a74[1] = 0;
     }
     if( k + 148 < n ) {
       a75[0] = *( m1 + n * i + (k+148) );
     } else {
       a75[0] = 0;
     }
     if( k + 149 < n ) {
       a75[1] = *( m1 + n * i + (k+149) );
     } else {
       a75[1] = 0;
     }
     if( k + 150 < n ) {
       a76[0] = *( m1 + n * i + (k+150) );
     } else {
       a76[0] = 0;
     }
     if( k + 151 < n ) {
       a76[1] = *( m1 + n * i + (k+151) );
     } else {
       a76[1] = 0;
     }
     if( k + 152 < n ) {
       a77[0] = *( m1 + n * i + (k+152) );
     } else {
       a77[0] = 0;
     }
     if( k + 153 < n ) {
       a77[1] = *( m1 + n * i + (k+153) );
     } else {
       a77[1] = 0;
     }
     if( k + 154 < n ) {
       a78[0] = *( m1 + n * i + (k+154) );
     } else {
       a78[0] = 0;
     }
     if( k + 155 < n ) {
       a78[1] = *( m1 + n * i + (k+155) );
     } else {
       a78[1] = 0;
     }
     if( k + 156 < n ) {
       a79[0] = *( m1 + n * i + (k+156) );
     } else {
       a79[0] = 0;
     }
     if( k + 157 < n ) {
       a79[1] = *( m1 + n * i + (k+157) );
     } else {
       a79[1] = 0;
     }
     if( k + 158 < n ) {
       a80[0] = *( m1 + n * i + (k+158) );
     } else {
       a80[0] = 0;
     }
     if( k + 159 < n ) {
       a80[1] = *( m1 + n * i + (k+159) );
     } else {
       a80[1] = 0;
     }
     if( k + 160 < n ) {
       a81[0] = *( m1 + n * i + (k+160) );
     } else {
       a81[0] = 0;
     }
     if( k + 161 < n ) {
       a81[1] = *( m1 + n * i + (k+161) );
     } else {
       a81[1] = 0;
     }
     if( k + 162 < n ) {
       a82[0] = *( m1 + n * i + (k+162) );
     } else {
       a82[0] = 0;
     }
     if( k + 163 < n ) {
       a82[1] = *( m1 + n * i + (k+163) );
     } else {
       a82[1] = 0;
     }
     if( k + 164 < n ) {
       a83[0] = *( m1 + n * i + (k+164) );
     } else {
       a83[0] = 0;
     }
     if( k + 165 < n ) {
       a83[1] = *( m1 + n * i + (k+165) );
     } else {
       a83[1] = 0;
     }
     if( k + 166 < n ) {
       a84[0] = *( m1 + n * i + (k+166) );
     } else {
       a84[0] = 0;
     }
     if( k + 167 < n ) {
       a84[1] = *( m1 + n * i + (k+167) );
     } else {
       a84[1] = 0;
     }
     if( k + 168 < n ) {
       a85[0] = *( m1 + n * i + (k+168) );
     } else {
       a85[0] = 0;
     }
     if( k + 169 < n ) {
       a85[1] = *( m1 + n * i + (k+169) );
     } else {
       a85[1] = 0;
     }
     if( k + 170 < n ) {
       a86[0] = *( m1 + n * i + (k+170) );
     } else {
       a86[0] = 0;
     }
     if( k + 171 < n ) {
       a86[1] = *( m1 + n * i + (k+171) );
     } else {
       a86[1] = 0;
     }
     if( k + 172 < n ) {
       a87[0] = *( m1 + n * i + (k+172) );
     } else {
       a87[0] = 0;
     }
     if( k + 173 < n ) {
       a87[1] = *( m1 + n * i + (k+173) );
     } else {
       a87[1] = 0;
     }
     if( k + 174 < n ) {
       a88[0] = *( m1 + n * i + (k+174) );
     } else {
       a88[0] = 0;
     }
     if( k + 175 < n ) {
       a88[1] = *( m1 + n * i + (k+175) );
     } else {
       a88[1] = 0;
     }
     if( k + 176 < n ) {
       a89[0] = *( m1 + n * i + (k+176) );
     } else {
       a89[0] = 0;
     }
     if( k + 177 < n ) {
       a89[1] = *( m1 + n * i + (k+177) );
     } else {
       a89[1] = 0;
     }
     if( k + 178 < n ) {
       a90[0] = *( m1 + n * i + (k+178) );
     } else {
       a90[0] = 0;
     }
     if( k + 179 < n ) {
       a90[1] = *( m1 + n * i + (k+179) );
     } else {
       a90[1] = 0;
     }
     if( k + 180 < n ) {
       a91[0] = *( m1 + n * i + (k+180) );
     } else {
       a91[0] = 0;
     }
     if( k + 181 < n ) {
       a91[1] = *( m1 + n * i + (k+181) );
     } else {
       a91[1] = 0;
     }
     if( k + 182 < n ) {
       a92[0] = *( m1 + n * i + (k+182) );
     } else {
       a92[0] = 0;
     }
     if( k + 183 < n ) {
       a92[1] = *( m1 + n * i + (k+183) );
     } else {
       a92[1] = 0;
     }
     if( k + 184 < n ) {
       a93[0] = *( m1 + n * i + (k+184) );
     } else {
       a93[0] = 0;
     }
     if( k + 185 < n ) {
       a93[1] = *( m1 + n * i + (k+185) );
     } else {
       a93[1] = 0;
     }
     if( k + 186 < n ) {
       a94[0] = *( m1 + n * i + (k+186) );
     } else {
       a94[0] = 0;
     }
     if( k + 187 < n ) {
       a94[1] = *( m1 + n * i + (k+187) );
     } else {
       a94[1] = 0;
     }
     if( k + 188 < n ) {
       a95[0] = *( m1 + n * i + (k+188) );
     } else {
       a95[0] = 0;
     }
     if( k + 189 < n ) {
       a95[1] = *( m1 + n * i + (k+189) );
     } else {
       a95[1] = 0;
     }
     if( k + 190 < n ) {
       a96[0] = *( m1 + n * i + (k+190) );
     } else {
       a96[0] = 0;
     }
     if( k + 191 < n ) {
       a96[1] = *( m1 + n * i + (k+191) );
     } else {
       a96[1] = 0;
     }
     if( k + 192 < n ) {
       a97[0] = *( m1 + n * i + (k+192) );
     } else {
       a97[0] = 0;
     }
     if( k + 193 < n ) {
       a97[1] = *( m1 + n * i + (k+193) );
     } else {
       a97[1] = 0;
     }
     if( k + 194 < n ) {
       a98[0] = *( m1 + n * i + (k+194) );
     } else {
       a98[0] = 0;
     }
     if( k + 195 < n ) {
       a98[1] = *( m1 + n * i + (k+195) );
     } else {
       a98[1] = 0;
     }
     if( k + 196 < n ) {
       a99[0] = *( m1 + n * i + (k+196) );
     } else {
       a99[0] = 0;
     }
     if( k + 197 < n ) {
       a99[1] = *( m1 + n * i + (k+197) );
     } else {
       a99[1] = 0;
     }
     if( k + 198 < n ) {
       a100[0] = *( m1 + n * i + (k+198) );
     } else {
       a100[0] = 0;
     }
     if( k + 199 < n ) {
       a100[1] = *( m1 + n * i + (k+199) );
     } else {
       a100[1] = 0;
     }
     if( k + 200 < n ) {
       a101[0] = *( m1 + n * i + (k+200) );
     } else {
       a101[0] = 0;
     }
     if( k + 201 < n ) {
       a101[1] = *( m1 + n * i + (k+201) );
     } else {
       a101[1] = 0;
     }
     if( k + 202 < n ) {
       a102[0] = *( m1 + n * i + (k+202) );
     } else {
       a102[0] = 0;
     }
     if( k + 203 < n ) {
       a102[1] = *( m1 + n * i + (k+203) );
     } else {
       a102[1] = 0;
     }
     if( k + 204 < n ) {
       a103[0] = *( m1 + n * i + (k+204) );
     } else {
       a103[0] = 0;
     }
     if( k + 205 < n ) {
       a103[1] = *( m1 + n * i + (k+205) );
     } else {
       a103[1] = 0;
     }
     if( k + 206 < n ) {
       a104[0] = *( m1 + n * i + (k+206) );
     } else {
       a104[0] = 0;
     }
     if( k + 207 < n ) {
       a104[1] = *( m1 + n * i + (k+207) );
     } else {
       a104[1] = 0;
     }
     if( k + 208 < n ) {
       a105[0] = *( m1 + n * i + (k+208) );
     } else {
       a105[0] = 0;
     }
     if( k + 209 < n ) {
       a105[1] = *( m1 + n * i + (k+209) );
     } else {
       a105[1] = 0;
     }
     if( k + 210 < n ) {
       a106[0] = *( m1 + n * i + (k+210) );
     } else {
       a106[0] = 0;
     }
     if( k + 211 < n ) {
       a106[1] = *( m1 + n * i + (k+211) );
     } else {
       a106[1] = 0;
     }
     if( k + 212 < n ) {
       a107[0] = *( m1 + n * i + (k+212) );
     } else {
       a107[0] = 0;
     }
     if( k + 213 < n ) {
       a107[1] = *( m1 + n * i + (k+213) );
     } else {
       a107[1] = 0;
     }
     if( k + 214 < n ) {
       a108[0] = *( m1 + n * i + (k+214) );
     } else {
       a108[0] = 0;
     }
     if( k + 215 < n ) {
       a108[1] = *( m1 + n * i + (k+215) );
     } else {
       a108[1] = 0;
     }
     if( k + 216 < n ) {
       a109[0] = *( m1 + n * i + (k+216) );
     } else {
       a109[0] = 0;
     }
     if( k + 217 < n ) {
       a109[1] = *( m1 + n * i + (k+217) );
     } else {
       a109[1] = 0;
     }
     if( k + 218 < n ) {
       a110[0] = *( m1 + n * i + (k+218) );
     } else {
       a110[0] = 0;
     }
     if( k + 219 < n ) {
       a110[1] = *( m1 + n * i + (k+219) );
     } else {
       a110[1] = 0;
     }
     if( k + 220 < n ) {
       a111[0] = *( m1 + n * i + (k+220) );
     } else {
       a111[0] = 0;
     }
     if( k + 221 < n ) {
       a111[1] = *( m1 + n * i + (k+221) );
     } else {
       a111[1] = 0;
     }
     if( k + 222 < n ) {
       a112[0] = *( m1 + n * i + (k+222) );
     } else {
       a112[0] = 0;
     }
     if( k + 223 < n ) {
       a112[1] = *( m1 + n * i + (k+223) );
     } else {
       a112[1] = 0;
     }
     if( k + 224 < n ) {
       a113[0] = *( m1 + n * i + (k+224) );
     } else {
       a113[0] = 0;
     }
     if( k + 225 < n ) {
       a113[1] = *( m1 + n * i + (k+225) );
     } else {
       a113[1] = 0;
     }
     if( k + 226 < n ) {
       a114[0] = *( m1 + n * i + (k+226) );
     } else {
       a114[0] = 0;
     }
     if( k + 227 < n ) {
       a114[1] = *( m1 + n * i + (k+227) );
     } else {
       a114[1] = 0;
     }
     if( k + 228 < n ) {
       a115[0] = *( m1 + n * i + (k+228) );
     } else {
       a115[0] = 0;
     }
     if( k + 229 < n ) {
       a115[1] = *( m1 + n * i + (k+229) );
     } else {
       a115[1] = 0;
     }
     if( k + 230 < n ) {
       a116[0] = *( m1 + n * i + (k+230) );
     } else {
       a116[0] = 0;
     }
     if( k + 231 < n ) {
       a116[1] = *( m1 + n * i + (k+231) );
     } else {
       a116[1] = 0;
     }
     if( k + 232 < n ) {
       a117[0] = *( m1 + n * i + (k+232) );
     } else {
       a117[0] = 0;
     }
     if( k + 233 < n ) {
       a117[1] = *( m1 + n * i + (k+233) );
     } else {
       a117[1] = 0;
     }
     if( k + 234 < n ) {
       a118[0] = *( m1 + n * i + (k+234) );
     } else {
       a118[0] = 0;
     }
     if( k + 235 < n ) {
       a118[1] = *( m1 + n * i + (k+235) );
     } else {
       a118[1] = 0;
     }
     if( k + 236 < n ) {
       a119[0] = *( m1 + n * i + (k+236) );
     } else {
       a119[0] = 0;
     }
     if( k + 237 < n ) {
       a119[1] = *( m1 + n * i + (k+237) );
     } else {
       a119[1] = 0;
     }
     if( k + 238 < n ) {
       a120[0] = *( m1 + n * i + (k+238) );
     } else {
       a120[0] = 0;
     }
     if( k + 239 < n ) {
       a120[1] = *( m1 + n * i + (k+239) );
     } else {
       a120[1] = 0;
     }
     if( k + 240 < n ) {
       a121[0] = *( m1 + n * i + (k+240) );
     } else {
       a121[0] = 0;
     }
     if( k + 241 < n ) {
       a121[1] = *( m1 + n * i + (k+241) );
     } else {
       a121[1] = 0;
     }
     if( k + 242 < n ) {
       a122[0] = *( m1 + n * i + (k+242) );
     } else {
       a122[0] = 0;
     }
     if( k + 243 < n ) {
       a122[1] = *( m1 + n * i + (k+243) );
     } else {
       a122[1] = 0;
     }
     if( k + 244 < n ) {
       a123[0] = *( m1 + n * i + (k+244) );
     } else {
       a123[0] = 0;
     }
     if( k + 245 < n ) {
       a123[1] = *( m1 + n * i + (k+245) );
     } else {
       a123[1] = 0;
     }
     if( k + 246 < n ) {
       a124[0] = *( m1 + n * i + (k+246) );
     } else {
       a124[0] = 0;
     }
     if( k + 247 < n ) {
       a124[1] = *( m1 + n * i + (k+247) );
     } else {
       a124[1] = 0;
     }
     if( k + 248 < n ) {
       a125[0] = *( m1 + n * i + (k+248) );
     } else {
       a125[0] = 0;
     }
     if( k + 249 < n ) {
       a125[1] = *( m1 + n * i + (k+249) );
     } else {
       a125[1] = 0;
     }
     if( k + 250 < n ) {
       a126[0] = *( m1 + n * i + (k+250) );
     } else {
       a126[0] = 0;
     }
     if( k + 251 < n ) {
       a126[1] = *( m1 + n * i + (k+251) );
     } else {
       a126[1] = 0;
     }
     if( k + 252 < n ) {
       a127[0] = *( m1 + n * i + (k+252) );
     } else {
       a127[0] = 0;
     }
     if( k + 253 < n ) {
       a127[1] = *( m1 + n * i + (k+253) );
     } else {
       a127[1] = 0;
     }
     if( k + 254 < n ) {
       a128[0] = *( m1 + n * i + (k+254) );
     } else {
       a128[0] = 0;
     }
     if( k + 255 < n ) {
       a128[1] = *( m1 + n * i + (k+255) );
     } else {
       a128[1] = 0;
     }
     if( k + 256 < n ) {
       a129[0] = *( m1 + n * i + (k+256) );
     } else {
       a129[0] = 0;
     }
     if( k + 257 < n ) {
       a129[1] = *( m1 + n * i + (k+257) );
     } else {
       a129[1] = 0;
     }
     if( k + 258 < n ) {
       a130[0] = *( m1 + n * i + (k+258) );
     } else {
       a130[0] = 0;
     }
     if( k + 259 < n ) {
       a130[1] = *( m1 + n * i + (k+259) );
     } else {
       a130[1] = 0;
     }
     if( k + 260 < n ) {
       a131[0] = *( m1 + n * i + (k+260) );
     } else {
       a131[0] = 0;
     }
     if( k + 261 < n ) {
       a131[1] = *( m1 + n * i + (k+261) );
     } else {
       a131[1] = 0;
     }
     if( k + 262 < n ) {
       a132[0] = *( m1 + n * i + (k+262) );
     } else {
       a132[0] = 0;
     }
     if( k + 263 < n ) {
       a132[1] = *( m1 + n * i + (k+263) );
     } else {
       a132[1] = 0;
     }
     if( k + 264 < n ) {
       a133[0] = *( m1 + n * i + (k+264) );
     } else {
       a133[0] = 0;
     }
     if( k + 265 < n ) {
       a133[1] = *( m1 + n * i + (k+265) );
     } else {
       a133[1] = 0;
     }
     if( k + 266 < n ) {
       a134[0] = *( m1 + n * i + (k+266) );
     } else {
       a134[0] = 0;
     }
     if( k + 267 < n ) {
       a134[1] = *( m1 + n * i + (k+267) );
     } else {
       a134[1] = 0;
     }
     if( k + 268 < n ) {
       a135[0] = *( m1 + n * i + (k+268) );
     } else {
       a135[0] = 0;
     }
     if( k + 269 < n ) {
       a135[1] = *( m1 + n * i + (k+269) );
     } else {
       a135[1] = 0;
     }
     if( k + 270 < n ) {
       a136[0] = *( m1 + n * i + (k+270) );
     } else {
       a136[0] = 0;
     }
     if( k + 271 < n ) {
       a136[1] = *( m1 + n * i + (k+271) );
     } else {
       a136[1] = 0;
     }
     if( k + 272 < n ) {
       a137[0] = *( m1 + n * i + (k+272) );
     } else {
       a137[0] = 0;
     }
     if( k + 273 < n ) {
       a137[1] = *( m1 + n * i + (k+273) );
     } else {
       a137[1] = 0;
     }
     if( k + 274 < n ) {
       a138[0] = *( m1 + n * i + (k+274) );
     } else {
       a138[0] = 0;
     }
     if( k + 275 < n ) {
       a138[1] = *( m1 + n * i + (k+275) );
     } else {
       a138[1] = 0;
     }
     if( k + 276 < n ) {
       a139[0] = *( m1 + n * i + (k+276) );
     } else {
       a139[0] = 0;
     }
     if( k + 277 < n ) {
       a139[1] = *( m1 + n * i + (k+277) );
     } else {
       a139[1] = 0;
     }
     if( k + 278 < n ) {
       a140[0] = *( m1 + n * i + (k+278) );
     } else {
       a140[0] = 0;
     }
     if( k + 279 < n ) {
       a140[1] = *( m1 + n * i + (k+279) );
     } else {
       a140[1] = 0;
     }
     if( k + 280 < n ) {
       a141[0] = *( m1 + n * i + (k+280) );
     } else {
       a141[0] = 0;
     }
     if( k + 281 < n ) {
       a141[1] = *( m1 + n * i + (k+281) );
     } else {
       a141[1] = 0;
     }
     if( k + 282 < n ) {
       a142[0] = *( m1 + n * i + (k+282) );
     } else {
       a142[0] = 0;
     }
     if( k + 283 < n ) {
       a142[1] = *( m1 + n * i + (k+283) );
     } else {
       a142[1] = 0;
     }
     if( k + 284 < n ) {
       a143[0] = *( m1 + n * i + (k+284) );
     } else {
       a143[0] = 0;
     }
     if( k + 285 < n ) {
       a143[1] = *( m1 + n * i + (k+285) );
     } else {
       a143[1] = 0;
     }
     if( k + 286 < n ) {
       a144[0] = *( m1 + n * i + (k+286) );
     } else {
       a144[0] = 0;
     }
     if( k + 287 < n ) {
       a144[1] = *( m1 + n * i + (k+287) );
     } else {
       a144[1] = 0;
     }
     if( k + 288 < n ) {
       a145[0] = *( m1 + n * i + (k+288) );
     } else {
       a145[0] = 0;
     }
     if( k + 289 < n ) {
       a145[1] = *( m1 + n * i + (k+289) );
     } else {
       a145[1] = 0;
     }
     if( k + 290 < n ) {
       a146[0] = *( m1 + n * i + (k+290) );
     } else {
       a146[0] = 0;
     }
     if( k + 291 < n ) {
       a146[1] = *( m1 + n * i + (k+291) );
     } else {
       a146[1] = 0;
     }
     if( k + 292 < n ) {
       a147[0] = *( m1 + n * i + (k+292) );
     } else {
       a147[0] = 0;
     }
     if( k + 293 < n ) {
       a147[1] = *( m1 + n * i + (k+293) );
     } else {
       a147[1] = 0;
     }
     if( k + 294 < n ) {
       a148[0] = *( m1 + n * i + (k+294) );
     } else {
       a148[0] = 0;
     }
     if( k + 295 < n ) {
       a148[1] = *( m1 + n * i + (k+295) );
     } else {
       a148[1] = 0;
     }
     if( k + 296 < n ) {
       a149[0] = *( m1 + n * i + (k+296) );
     } else {
       a149[0] = 0;
     }
     if( k + 297 < n ) {
       a149[1] = *( m1 + n * i + (k+297) );
     } else {
       a149[1] = 0;
     }
     if( k + 298 < n ) {
       a150[0] = *( m1 + n * i + (k+298) );
     } else {
       a150[0] = 0;
     }
     if( k + 299 < n ) {
       a150[1] = *( m1 + n * i + (k+299) );
     } else {
       a150[1] = 0;
     }
     if( k + 300 < n ) {
       a151[0] = *( m1 + n * i + (k+300) );
     } else {
       a151[0] = 0;
     }
     if( k + 301 < n ) {
       a151[1] = *( m1 + n * i + (k+301) );
     } else {
       a151[1] = 0;
     }
     if( k + 302 < n ) {
       a152[0] = *( m1 + n * i + (k+302) );
     } else {
       a152[0] = 0;
     }
     if( k + 303 < n ) {
       a152[1] = *( m1 + n * i + (k+303) );
     } else {
       a152[1] = 0;
     }
     if( k + 304 < n ) {
       a153[0] = *( m1 + n * i + (k+304) );
     } else {
       a153[0] = 0;
     }
     if( k + 305 < n ) {
       a153[1] = *( m1 + n * i + (k+305) );
     } else {
       a153[1] = 0;
     }
     if( k + 306 < n ) {
       a154[0] = *( m1 + n * i + (k+306) );
     } else {
       a154[0] = 0;
     }
     if( k + 307 < n ) {
       a154[1] = *( m1 + n * i + (k+307) );
     } else {
       a154[1] = 0;
     }
     if( k + 308 < n ) {
       a155[0] = *( m1 + n * i + (k+308) );
     } else {
       a155[0] = 0;
     }
     if( k + 309 < n ) {
       a155[1] = *( m1 + n * i + (k+309) );
     } else {
       a155[1] = 0;
     }
     if( k + 310 < n ) {
       a156[0] = *( m1 + n * i + (k+310) );
     } else {
       a156[0] = 0;
     }
     if( k + 311 < n ) {
       a156[1] = *( m1 + n * i + (k+311) );
     } else {
       a156[1] = 0;
     }
     if( k + 312 < n ) {
       a157[0] = *( m1 + n * i + (k+312) );
     } else {
       a157[0] = 0;
     }
     if( k + 313 < n ) {
       a157[1] = *( m1 + n * i + (k+313) );
     } else {
       a157[1] = 0;
     }
     if( k + 314 < n ) {
       a158[0] = *( m1 + n * i + (k+314) );
     } else {
       a158[0] = 0;
     }
     if( k + 315 < n ) {
       a158[1] = *( m1 + n * i + (k+315) );
     } else {
       a158[1] = 0;
     }
     if( k + 316 < n ) {
       a159[0] = *( m1 + n * i + (k+316) );
     } else {
       a159[0] = 0;
     }
     if( k + 317 < n ) {
       a159[1] = *( m1 + n * i + (k+317) );
     } else {
       a159[1] = 0;
     }
     if( k + 318 < n ) {
       a160[0] = *( m1 + n * i + (k+318) );
     } else {
       a160[0] = 0;
     }
     if( k + 319 < n ) {
       a160[1] = *( m1 + n * i + (k+319) );
     } else {
       a160[1] = 0;
     }
     if( k + 320 < n ) {
       a161[0] = *( m1 + n * i + (k+320) );
     } else {
       a161[0] = 0;
     }
     if( k + 321 < n ) {
       a161[1] = *( m1 + n * i + (k+321) );
     } else {
       a161[1] = 0;
     }
     if( k + 322 < n ) {
       a162[0] = *( m1 + n * i + (k+322) );
     } else {
       a162[0] = 0;
     }
     if( k + 323 < n ) {
       a162[1] = *( m1 + n * i + (k+323) );
     } else {
       a162[1] = 0;
     }
     if( k + 324 < n ) {
       a163[0] = *( m1 + n * i + (k+324) );
     } else {
       a163[0] = 0;
     }
     if( k + 325 < n ) {
       a163[1] = *( m1 + n * i + (k+325) );
     } else {
       a163[1] = 0;
     }
     if( k + 326 < n ) {
       a164[0] = *( m1 + n * i + (k+326) );
     } else {
       a164[0] = 0;
     }
     if( k + 327 < n ) {
       a164[1] = *( m1 + n * i + (k+327) );
     } else {
       a164[1] = 0;
     }
     if( k + 328 < n ) {
       a165[0] = *( m1 + n * i + (k+328) );
     } else {
       a165[0] = 0;
     }
     if( k + 329 < n ) {
       a165[1] = *( m1 + n * i + (k+329) );
     } else {
       a165[1] = 0;
     }
     if( k + 330 < n ) {
       a166[0] = *( m1 + n * i + (k+330) );
     } else {
       a166[0] = 0;
     }
     if( k + 331 < n ) {
       a166[1] = *( m1 + n * i + (k+331) );
     } else {
       a166[1] = 0;
     }
     if( k + 332 < n ) {
       a167[0] = *( m1 + n * i + (k+332) );
     } else {
       a167[0] = 0;
     }
     if( k + 333 < n ) {
       a167[1] = *( m1 + n * i + (k+333) );
     } else {
       a167[1] = 0;
     }
     if( k + 334 < n ) {
       a168[0] = *( m1 + n * i + (k+334) );
     } else {
       a168[0] = 0;
     }
     if( k + 335 < n ) {
       a168[1] = *( m1 + n * i + (k+335) );
     } else {
       a168[1] = 0;
     }
     if( k + 336 < n ) {
       a169[0] = *( m1 + n * i + (k+336) );
     } else {
       a169[0] = 0;
     }
     if( k + 337 < n ) {
       a169[1] = *( m1 + n * i + (k+337) );
     } else {
       a169[1] = 0;
     }
     if( k + 338 < n ) {
       a170[0] = *( m1 + n * i + (k+338) );
     } else {
       a170[0] = 0;
     }
     if( k + 339 < n ) {
       a170[1] = *( m1 + n * i + (k+339) );
     } else {
       a170[1] = 0;
     }
     if( k + 340 < n ) {
       a171[0] = *( m1 + n * i + (k+340) );
     } else {
       a171[0] = 0;
     }
     if( k + 341 < n ) {
       a171[1] = *( m1 + n * i + (k+341) );
     } else {
       a171[1] = 0;
     }
     if( k + 342 < n ) {
       a172[0] = *( m1 + n * i + (k+342) );
     } else {
       a172[0] = 0;
     }
     if( k + 343 < n ) {
       a172[1] = *( m1 + n * i + (k+343) );
     } else {
       a172[1] = 0;
     }
     if( k + 344 < n ) {
       a173[0] = *( m1 + n * i + (k+344) );
     } else {
       a173[0] = 0;
     }
     if( k + 345 < n ) {
       a173[1] = *( m1 + n * i + (k+345) );
     } else {
       a173[1] = 0;
     }
     if( k + 346 < n ) {
       a174[0] = *( m1 + n * i + (k+346) );
     } else {
       a174[0] = 0;
     }
     if( k + 347 < n ) {
       a174[1] = *( m1 + n * i + (k+347) );
     } else {
       a174[1] = 0;
     }
     if( k + 348 < n ) {
       a175[0] = *( m1 + n * i + (k+348) );
     } else {
       a175[0] = 0;
     }
     if( k + 349 < n ) {
       a175[1] = *( m1 + n * i + (k+349) );
     } else {
       a175[1] = 0;
     }
     if( k + 350 < n ) {
       a176[0] = *( m1 + n * i + (k+350) );
     } else {
       a176[0] = 0;
     }
     if( k + 351 < n ) {
       a176[1] = *( m1 + n * i + (k+351) );
     } else {
       a176[1] = 0;
     }
     if( k + 352 < n ) {
       a177[0] = *( m1 + n * i + (k+352) );
     } else {
       a177[0] = 0;
     }
     if( k + 353 < n ) {
       a177[1] = *( m1 + n * i + (k+353) );
     } else {
       a177[1] = 0;
     }
     if( k + 354 < n ) {
       a178[0] = *( m1 + n * i + (k+354) );
     } else {
       a178[0] = 0;
     }
     if( k + 355 < n ) {
       a178[1] = *( m1 + n * i + (k+355) );
     } else {
       a178[1] = 0;
     }
     if( k + 356 < n ) {
       a179[0] = *( m1 + n * i + (k+356) );
     } else {
       a179[0] = 0;
     }
     if( k + 357 < n ) {
       a179[1] = *( m1 + n * i + (k+357) );
     } else {
       a179[1] = 0;
     }
     if( k + 358 < n ) {
       a180[0] = *( m1 + n * i + (k+358) );
     } else {
       a180[0] = 0;
     }
     if( k + 359 < n ) {
       a180[1] = *( m1 + n * i + (k+359) );
     } else {
       a180[1] = 0;
     }
     if( k + 360 < n ) {
       a181[0] = *( m1 + n * i + (k+360) );
     } else {
       a181[0] = 0;
     }
     if( k + 361 < n ) {
       a181[1] = *( m1 + n * i + (k+361) );
     } else {
       a181[1] = 0;
     }
     if( k + 362 < n ) {
       a182[0] = *( m1 + n * i + (k+362) );
     } else {
       a182[0] = 0;
     }
     if( k + 363 < n ) {
       a182[1] = *( m1 + n * i + (k+363) );
     } else {
       a182[1] = 0;
     }
     if( k + 364 < n ) {
       a183[0] = *( m1 + n * i + (k+364) );
     } else {
       a183[0] = 0;
     }
     if( k + 365 < n ) {
       a183[1] = *( m1 + n * i + (k+365) );
     } else {
       a183[1] = 0;
     }
     if( k + 366 < n ) {
       a184[0] = *( m1 + n * i + (k+366) );
     } else {
       a184[0] = 0;
     }
     if( k + 367 < n ) {
       a184[1] = *( m1 + n * i + (k+367) );
     } else {
       a184[1] = 0;
     }
     if( k + 368 < n ) {
       a185[0] = *( m1 + n * i + (k+368) );
     } else {
       a185[0] = 0;
     }
     if( k + 369 < n ) {
       a185[1] = *( m1 + n * i + (k+369) );
     } else {
       a185[1] = 0;
     }
     if( k + 370 < n ) {
       a186[0] = *( m1 + n * i + (k+370) );
     } else {
       a186[0] = 0;
     }
     if( k + 371 < n ) {
       a186[1] = *( m1 + n * i + (k+371) );
     } else {
       a186[1] = 0;
     }
     if( k + 372 < n ) {
       a187[0] = *( m1 + n * i + (k+372) );
     } else {
       a187[0] = 0;
     }
     if( k + 373 < n ) {
       a187[1] = *( m1 + n * i + (k+373) );
     } else {
       a187[1] = 0;
     }
     if( k + 374 < n ) {
       a188[0] = *( m1 + n * i + (k+374) );
     } else {
       a188[0] = 0;
     }
     if( k + 375 < n ) {
       a188[1] = *( m1 + n * i + (k+375) );
     } else {
       a188[1] = 0;
     }
     if( k + 376 < n ) {
       a189[0] = *( m1 + n * i + (k+376) );
     } else {
       a189[0] = 0;
     }
     if( k + 377 < n ) {
       a189[1] = *( m1 + n * i + (k+377) );
     } else {
       a189[1] = 0;
     }
     if( k + 378 < n ) {
       a190[0] = *( m1 + n * i + (k+378) );
     } else {
       a190[0] = 0;
     }
     if( k + 379 < n ) {
       a190[1] = *( m1 + n * i + (k+379) );
     } else {
       a190[1] = 0;
     }
     if( k + 380 < n ) {
       a191[0] = *( m1 + n * i + (k+380) );
     } else {
       a191[0] = 0;
     }
     if( k + 381 < n ) {
       a191[1] = *( m1 + n * i + (k+381) );
     } else {
       a191[1] = 0;
     }
     if( k + 382 < n ) {
       a192[0] = *( m1 + n * i + (k+382) );
     } else {
       a192[0] = 0;
     }
     if( k + 383 < n ) {
       a192[1] = *( m1 + n * i + (k+383) );
     } else {
       a192[1] = 0;
     }
     if( k + 384 < n ) {
       a193[0] = *( m1 + n * i + (k+384) );
     } else {
       a193[0] = 0;
     }
     if( k + 385 < n ) {
       a193[1] = *( m1 + n * i + (k+385) );
     } else {
       a193[1] = 0;
     }
     if( k + 386 < n ) {
       a194[0] = *( m1 + n * i + (k+386) );
     } else {
       a194[0] = 0;
     }
     if( k + 387 < n ) {
       a194[1] = *( m1 + n * i + (k+387) );
     } else {
       a194[1] = 0;
     }
     if( k + 388 < n ) {
       a195[0] = *( m1 + n * i + (k+388) );
     } else {
       a195[0] = 0;
     }
     if( k + 389 < n ) {
       a195[1] = *( m1 + n * i + (k+389) );
     } else {
       a195[1] = 0;
     }
     if( k + 390 < n ) {
       a196[0] = *( m1 + n * i + (k+390) );
     } else {
       a196[0] = 0;
     }
     if( k + 391 < n ) {
       a196[1] = *( m1 + n * i + (k+391) );
     } else {
       a196[1] = 0;
     }
     if( k + 392 < n ) {
       a197[0] = *( m1 + n * i + (k+392) );
     } else {
       a197[0] = 0;
     }
     if( k + 393 < n ) {
       a197[1] = *( m1 + n * i + (k+393) );
     } else {
       a197[1] = 0;
     }
     if( k + 394 < n ) {
       a198[0] = *( m1 + n * i + (k+394) );
     } else {
       a198[0] = 0;
     }
     if( k + 395 < n ) {
       a198[1] = *( m1 + n * i + (k+395) );
     } else {
       a198[1] = 0;
     }
     if( k + 396 < n ) {
       a199[0] = *( m1 + n * i + (k+396) );
     } else {
       a199[0] = 0;
     }
     if( k + 397 < n ) {
       a199[1] = *( m1 + n * i + (k+397) );
     } else {
       a199[1] = 0;
     }
     if( k + 398 < n ) {
       a200[0] = *( m1 + n * i + (k+398) );
     } else {
       a200[0] = 0;
     }
     if( k + 399 < n ) {
       a200[1] = *( m1 + n * i + (k+399) );
     } else {
       a200[1] = 0;
     }
     if( k + 400 < n ) {
       a201[0] = *( m1 + n * i + (k+400) );
     } else {
       a201[0] = 0;
     }
     if( k + 401 < n ) {
       a201[1] = *( m1 + n * i + (k+401) );
     } else {
       a201[1] = 0;
     }
     if( k + 402 < n ) {
       a202[0] = *( m1 + n * i + (k+402) );
     } else {
       a202[0] = 0;
     }
     if( k + 403 < n ) {
       a202[1] = *( m1 + n * i + (k+403) );
     } else {
       a202[1] = 0;
     }
     if( k + 404 < n ) {
       a203[0] = *( m1 + n * i + (k+404) );
     } else {
       a203[0] = 0;
     }
     if( k + 405 < n ) {
       a203[1] = *( m1 + n * i + (k+405) );
     } else {
       a203[1] = 0;
     }
     if( k + 406 < n ) {
       a204[0] = *( m1 + n * i + (k+406) );
     } else {
       a204[0] = 0;
     }
     if( k + 407 < n ) {
       a204[1] = *( m1 + n * i + (k+407) );
     } else {
       a204[1] = 0;
     }
     if( k + 408 < n ) {
       a205[0] = *( m1 + n * i + (k+408) );
     } else {
       a205[0] = 0;
     }
     if( k + 409 < n ) {
       a205[1] = *( m1 + n * i + (k+409) );
     } else {
       a205[1] = 0;
     }
     if( k + 410 < n ) {
       a206[0] = *( m1 + n * i + (k+410) );
     } else {
       a206[0] = 0;
     }
     if( k + 411 < n ) {
       a206[1] = *( m1 + n * i + (k+411) );
     } else {
       a206[1] = 0;
     }
     if( k + 412 < n ) {
       a207[0] = *( m1 + n * i + (k+412) );
     } else {
       a207[0] = 0;
     }
     if( k + 413 < n ) {
       a207[1] = *( m1 + n * i + (k+413) );
     } else {
       a207[1] = 0;
     }
     if( k + 414 < n ) {
       a208[0] = *( m1 + n * i + (k+414) );
     } else {
       a208[0] = 0;
     }
     if( k + 415 < n ) {
       a208[1] = *( m1 + n * i + (k+415) );
     } else {
       a208[1] = 0;
     }
     if( k + 416 < n ) {
       a209[0] = *( m1 + n * i + (k+416) );
     } else {
       a209[0] = 0;
     }
     if( k + 417 < n ) {
       a209[1] = *( m1 + n * i + (k+417) );
     } else {
       a209[1] = 0;
     }
     if( k + 418 < n ) {
       a210[0] = *( m1 + n * i + (k+418) );
     } else {
       a210[0] = 0;
     }
     if( k + 419 < n ) {
       a210[1] = *( m1 + n * i + (k+419) );
     } else {
       a210[1] = 0;
     }
     if( k + 420 < n ) {
       a211[0] = *( m1 + n * i + (k+420) );
     } else {
       a211[0] = 0;
     }
     if( k + 421 < n ) {
       a211[1] = *( m1 + n * i + (k+421) );
     } else {
       a211[1] = 0;
     }
     if( k + 422 < n ) {
       a212[0] = *( m1 + n * i + (k+422) );
     } else {
       a212[0] = 0;
     }
     if( k + 423 < n ) {
       a212[1] = *( m1 + n * i + (k+423) );
     } else {
       a212[1] = 0;
     }
     if( k + 424 < n ) {
       a213[0] = *( m1 + n * i + (k+424) );
     } else {
       a213[0] = 0;
     }
     if( k + 425 < n ) {
       a213[1] = *( m1 + n * i + (k+425) );
     } else {
       a213[1] = 0;
     }
     if( k + 426 < n ) {
       a214[0] = *( m1 + n * i + (k+426) );
     } else {
       a214[0] = 0;
     }
     if( k + 427 < n ) {
       a214[1] = *( m1 + n * i + (k+427) );
     } else {
       a214[1] = 0;
     }
     if( k + 428 < n ) {
       a215[0] = *( m1 + n * i + (k+428) );
     } else {
       a215[0] = 0;
     }
     if( k + 429 < n ) {
       a215[1] = *( m1 + n * i + (k+429) );
     } else {
       a215[1] = 0;
     }
     if( k + 430 < n ) {
       a216[0] = *( m1 + n * i + (k+430) );
     } else {
       a216[0] = 0;
     }
     if( k + 431 < n ) {
       a216[1] = *( m1 + n * i + (k+431) );
     } else {
       a216[1] = 0;
     }
     if( k + 432 < n ) {
       a217[0] = *( m1 + n * i + (k+432) );
     } else {
       a217[0] = 0;
     }
     if( k + 433 < n ) {
       a217[1] = *( m1 + n * i + (k+433) );
     } else {
       a217[1] = 0;
     }
     if( k + 434 < n ) {
       a218[0] = *( m1 + n * i + (k+434) );
     } else {
       a218[0] = 0;
     }
     if( k + 435 < n ) {
       a218[1] = *( m1 + n * i + (k+435) );
     } else {
       a218[1] = 0;
     }
     if( k + 436 < n ) {
       a219[0] = *( m1 + n * i + (k+436) );
     } else {
       a219[0] = 0;
     }
     if( k + 437 < n ) {
       a219[1] = *( m1 + n * i + (k+437) );
     } else {
       a219[1] = 0;
     }
     if( k + 438 < n ) {
       a220[0] = *( m1 + n * i + (k+438) );
     } else {
       a220[0] = 0;
     }
     if( k + 439 < n ) {
       a220[1] = *( m1 + n * i + (k+439) );
     } else {
       a220[1] = 0;
     }
     if( k + 440 < n ) {
       a221[0] = *( m1 + n * i + (k+440) );
     } else {
       a221[0] = 0;
     }
     if( k + 441 < n ) {
       a221[1] = *( m1 + n * i + (k+441) );
     } else {
       a221[1] = 0;
     }
     if( k + 442 < n ) {
       a222[0] = *( m1 + n * i + (k+442) );
     } else {
       a222[0] = 0;
     }
     if( k + 443 < n ) {
       a222[1] = *( m1 + n * i + (k+443) );
     } else {
       a222[1] = 0;
     }
     if( k + 444 < n ) {
       a223[0] = *( m1 + n * i + (k+444) );
     } else {
       a223[0] = 0;
     }
     if( k + 445 < n ) {
       a223[1] = *( m1 + n * i + (k+445) );
     } else {
       a223[1] = 0;
     }
     if( k + 446 < n ) {
       a224[0] = *( m1 + n * i + (k+446) );
     } else {
       a224[0] = 0;
     }
     if( k + 447 < n ) {
       a224[1] = *( m1 + n * i + (k+447) );
     } else {
       a224[1] = 0;
     }
     if( k + 448 < n ) {
       a225[0] = *( m1 + n * i + (k+448) );
     } else {
       a225[0] = 0;
     }
     if( k + 449 < n ) {
       a225[1] = *( m1 + n * i + (k+449) );
     } else {
       a225[1] = 0;
     }
     if( k + 450 < n ) {
       a226[0] = *( m1 + n * i + (k+450) );
     } else {
       a226[0] = 0;
     }
     if( k + 451 < n ) {
       a226[1] = *( m1 + n * i + (k+451) );
     } else {
       a226[1] = 0;
     }
     if( k + 452 < n ) {
       a227[0] = *( m1 + n * i + (k+452) );
     } else {
       a227[0] = 0;
     }
     if( k + 453 < n ) {
       a227[1] = *( m1 + n * i + (k+453) );
     } else {
       a227[1] = 0;
     }
     if( k + 454 < n ) {
       a228[0] = *( m1 + n * i + (k+454) );
     } else {
       a228[0] = 0;
     }
     if( k + 455 < n ) {
       a228[1] = *( m1 + n * i + (k+455) );
     } else {
       a228[1] = 0;
     }
     if( k + 456 < n ) {
       a229[0] = *( m1 + n * i + (k+456) );
     } else {
       a229[0] = 0;
     }
     if( k + 457 < n ) {
       a229[1] = *( m1 + n * i + (k+457) );
     } else {
       a229[1] = 0;
     }
     if( k + 458 < n ) {
       a230[0] = *( m1 + n * i + (k+458) );
     } else {
       a230[0] = 0;
     }
     if( k + 459 < n ) {
       a230[1] = *( m1 + n * i + (k+459) );
     } else {
       a230[1] = 0;
     }
     if( k + 460 < n ) {
       a231[0] = *( m1 + n * i + (k+460) );
     } else {
       a231[0] = 0;
     }
     if( k + 461 < n ) {
       a231[1] = *( m1 + n * i + (k+461) );
     } else {
       a231[1] = 0;
     }
     if( k + 462 < n ) {
       a232[0] = *( m1 + n * i + (k+462) );
     } else {
       a232[0] = 0;
     }
     if( k + 463 < n ) {
       a232[1] = *( m1 + n * i + (k+463) );
     } else {
       a232[1] = 0;
     }
     if( k + 464 < n ) {
       a233[0] = *( m1 + n * i + (k+464) );
     } else {
       a233[0] = 0;
     }
     if( k + 465 < n ) {
       a233[1] = *( m1 + n * i + (k+465) );
     } else {
       a233[1] = 0;
     }
     if( k + 466 < n ) {
       a234[0] = *( m1 + n * i + (k+466) );
     } else {
       a234[0] = 0;
     }
     if( k + 467 < n ) {
       a234[1] = *( m1 + n * i + (k+467) );
     } else {
       a234[1] = 0;
     }
     if( k + 468 < n ) {
       a235[0] = *( m1 + n * i + (k+468) );
     } else {
       a235[0] = 0;
     }
     if( k + 469 < n ) {
       a235[1] = *( m1 + n * i + (k+469) );
     } else {
       a235[1] = 0;
     }
     if( k + 470 < n ) {
       a236[0] = *( m1 + n * i + (k+470) );
     } else {
       a236[0] = 0;
     }
     if( k + 471 < n ) {
       a236[1] = *( m1 + n * i + (k+471) );
     } else {
       a236[1] = 0;
     }
     if( k + 472 < n ) {
       a237[0] = *( m1 + n * i + (k+472) );
     } else {
       a237[0] = 0;
     }
     if( k + 473 < n ) {
       a237[1] = *( m1 + n * i + (k+473) );
     } else {
       a237[1] = 0;
     }
     if( k + 474 < n ) {
       a238[0] = *( m1 + n * i + (k+474) );
     } else {
       a238[0] = 0;
     }
     if( k + 475 < n ) {
       a238[1] = *( m1 + n * i + (k+475) );
     } else {
       a238[1] = 0;
     }
     if( k + 476 < n ) {
       a239[0] = *( m1 + n * i + (k+476) );
     } else {
       a239[0] = 0;
     }
     if( k + 477 < n ) {
       a239[1] = *( m1 + n * i + (k+477) );
     } else {
       a239[1] = 0;
     }
     if( k + 478 < n ) {
       a240[0] = *( m1 + n * i + (k+478) );
     } else {
       a240[0] = 0;
     }
     if( k + 479 < n ) {
       a240[1] = *( m1 + n * i + (k+479) );
     } else {
       a240[1] = 0;
     }
     if( k + 480 < n ) {
       a241[0] = *( m1 + n * i + (k+480) );
     } else {
       a241[0] = 0;
     }
     if( k + 481 < n ) {
       a241[1] = *( m1 + n * i + (k+481) );
     } else {
       a241[1] = 0;
     }
     if( k + 482 < n ) {
       a242[0] = *( m1 + n * i + (k+482) );
     } else {
       a242[0] = 0;
     }
     if( k + 483 < n ) {
       a242[1] = *( m1 + n * i + (k+483) );
     } else {
       a242[1] = 0;
     }
     if( k + 484 < n ) {
       a243[0] = *( m1 + n * i + (k+484) );
     } else {
       a243[0] = 0;
     }
     if( k + 485 < n ) {
       a243[1] = *( m1 + n * i + (k+485) );
     } else {
       a243[1] = 0;
     }
     if( k + 486 < n ) {
       a244[0] = *( m1 + n * i + (k+486) );
     } else {
       a244[0] = 0;
     }
     if( k + 487 < n ) {
       a244[1] = *( m1 + n * i + (k+487) );
     } else {
       a244[1] = 0;
     }
     if( k + 488 < n ) {
       a245[0] = *( m1 + n * i + (k+488) );
     } else {
       a245[0] = 0;
     }
     if( k + 489 < n ) {
       a245[1] = *( m1 + n * i + (k+489) );
     } else {
       a245[1] = 0;
     }
     if( k + 490 < n ) {
       a246[0] = *( m1 + n * i + (k+490) );
     } else {
       a246[0] = 0;
     }
     if( k + 491 < n ) {
       a246[1] = *( m1 + n * i + (k+491) );
     } else {
       a246[1] = 0;
     }
     if( k + 492 < n ) {
       a247[0] = *( m1 + n * i + (k+492) );
     } else {
       a247[0] = 0;
     }
     if( k + 493 < n ) {
       a247[1] = *( m1 + n * i + (k+493) );
     } else {
       a247[1] = 0;
     }
     if( k + 494 < n ) {
       a248[0] = *( m1 + n * i + (k+494) );
     } else {
       a248[0] = 0;
     }
     if( k + 495 < n ) {
       a248[1] = *( m1 + n * i + (k+495) );
     } else {
       a248[1] = 0;
     }
     if( k + 496 < n ) {
       a249[0] = *( m1 + n * i + (k+496) );
     } else {
       a249[0] = 0;
     }
     if( k + 497 < n ) {
       a249[1] = *( m1 + n * i + (k+497) );
     } else {
       a249[1] = 0;
     }
     if( k + 498 < n ) {
       a250[0] = *( m1 + n * i + (k+498) );
     } else {
       a250[0] = 0;
     }
     if( k + 499 < n ) {
       a250[1] = *( m1 + n * i + (k+499) );
     } else {
       a250[1] = 0;
     }
     if( k + 500 < n ) {
       a251[0] = *( m1 + n * i + (k+500) );
     } else {
       a251[0] = 0;
     }
     if( k + 501 < n ) {
       a251[1] = *( m1 + n * i + (k+501) );
     } else {
       a251[1] = 0;
     }
     if( k + 502 < n ) {
       a252[0] = *( m1 + n * i + (k+502) );
     } else {
       a252[0] = 0;
     }
     if( k + 503 < n ) {
       a252[1] = *( m1 + n * i + (k+503) );
     } else {
       a252[1] = 0;
     }
     if( k + 504 < n ) {
       a253[0] = *( m1 + n * i + (k+504) );
     } else {
       a253[0] = 0;
     }
     if( k + 505 < n ) {
       a253[1] = *( m1 + n * i + (k+505) );
     } else {
       a253[1] = 0;
     }
     if( k + 506 < n ) {
       a254[0] = *( m1 + n * i + (k+506) );
     } else {
       a254[0] = 0;
     }
     if( k + 507 < n ) {
       a254[1] = *( m1 + n * i + (k+507) );
     } else {
       a254[1] = 0;
     }
     if( k + 508 < n ) {
       a255[0] = *( m1 + n * i + (k+508) );
     } else {
       a255[0] = 0;
     }
     if( k + 509 < n ) {
       a255[1] = *( m1 + n * i + (k+509) );
     } else {
       a255[1] = 0;
     }
     if( k + 510 < n ) {
       a256[0] = *( m1 + n * i + (k+510) );
     } else {
       a256[0] = 0;
     }
     if( k + 511 < n ) {
       a256[1] = *( m1 + n * i + (k+511) );
     } else {
       a256[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );
     t12 = _mm_load_pd( a7 );
     t14 = _mm_load_pd( a8 );
     t16 = _mm_load_pd( a9 );
     t18 = _mm_load_pd( a10 );
     t20 = _mm_load_pd( a11 );
     t22 = _mm_load_pd( a12 );
     t24 = _mm_load_pd( a13 );
     t26 = _mm_load_pd( a14 );
     t28 = _mm_load_pd( a15 );
     t30 = _mm_load_pd( a16 );
     t32 = _mm_load_pd( a17 );
     t34 = _mm_load_pd( a18 );
     t36 = _mm_load_pd( a19 );
     t38 = _mm_load_pd( a20 );
     t40 = _mm_load_pd( a21 );
     t42 = _mm_load_pd( a22 );
     t44 = _mm_load_pd( a23 );
     t46 = _mm_load_pd( a24 );
     t48 = _mm_load_pd( a25 );
     t50 = _mm_load_pd( a26 );
     t52 = _mm_load_pd( a27 );
     t54 = _mm_load_pd( a28 );
     t56 = _mm_load_pd( a29 );
     t58 = _mm_load_pd( a30 );
     t60 = _mm_load_pd( a31 );
     t62 = _mm_load_pd( a32 );
     t64 = _mm_load_pd( a33 );
     t66 = _mm_load_pd( a34 );
     t68 = _mm_load_pd( a35 );
     t70 = _mm_load_pd( a36 );
     t72 = _mm_load_pd( a37 );
     t74 = _mm_load_pd( a38 );
     t76 = _mm_load_pd( a39 );
     t78 = _mm_load_pd( a40 );
     t80 = _mm_load_pd( a41 );
     t82 = _mm_load_pd( a42 );
     t84 = _mm_load_pd( a43 );
     t86 = _mm_load_pd( a44 );
     t88 = _mm_load_pd( a45 );
     t90 = _mm_load_pd( a46 );
     t92 = _mm_load_pd( a47 );
     t94 = _mm_load_pd( a48 );
     t96 = _mm_load_pd( a49 );
     t98 = _mm_load_pd( a50 );
     t100 = _mm_load_pd( a51 );
     t102 = _mm_load_pd( a52 );
     t104 = _mm_load_pd( a53 );
     t106 = _mm_load_pd( a54 );
     t108 = _mm_load_pd( a55 );
     t110 = _mm_load_pd( a56 );
     t112 = _mm_load_pd( a57 );
     t114 = _mm_load_pd( a58 );
     t116 = _mm_load_pd( a59 );
     t118 = _mm_load_pd( a60 );
     t120 = _mm_load_pd( a61 );
     t122 = _mm_load_pd( a62 );
     t124 = _mm_load_pd( a63 );
     t126 = _mm_load_pd( a64 );
     t128 = _mm_load_pd( a65 );
     t130 = _mm_load_pd( a66 );
     t132 = _mm_load_pd( a67 );
     t134 = _mm_load_pd( a68 );
     t136 = _mm_load_pd( a69 );
     t138 = _mm_load_pd( a70 );
     t140 = _mm_load_pd( a71 );
     t142 = _mm_load_pd( a72 );
     t144 = _mm_load_pd( a73 );
     t146 = _mm_load_pd( a74 );
     t148 = _mm_load_pd( a75 );
     t150 = _mm_load_pd( a76 );
     t152 = _mm_load_pd( a77 );
     t154 = _mm_load_pd( a78 );
     t156 = _mm_load_pd( a79 );
     t158 = _mm_load_pd( a80 );
     t160 = _mm_load_pd( a81 );
     t162 = _mm_load_pd( a82 );
     t164 = _mm_load_pd( a83 );
     t166 = _mm_load_pd( a84 );
     t168 = _mm_load_pd( a85 );
     t170 = _mm_load_pd( a86 );
     t172 = _mm_load_pd( a87 );
     t174 = _mm_load_pd( a88 );
     t176 = _mm_load_pd( a89 );
     t178 = _mm_load_pd( a90 );
     t180 = _mm_load_pd( a91 );
     t182 = _mm_load_pd( a92 );
     t184 = _mm_load_pd( a93 );
     t186 = _mm_load_pd( a94 );
     t188 = _mm_load_pd( a95 );
     t190 = _mm_load_pd( a96 );
     t192 = _mm_load_pd( a97 );
     t194 = _mm_load_pd( a98 );
     t196 = _mm_load_pd( a99 );
     t198 = _mm_load_pd( a100 );
     t200 = _mm_load_pd( a101 );
     t202 = _mm_load_pd( a102 );
     t204 = _mm_load_pd( a103 );
     t206 = _mm_load_pd( a104 );
     t208 = _mm_load_pd( a105 );
     t210 = _mm_load_pd( a106 );
     t212 = _mm_load_pd( a107 );
     t214 = _mm_load_pd( a108 );
     t216 = _mm_load_pd( a109 );
     t218 = _mm_load_pd( a110 );
     t220 = _mm_load_pd( a111 );
     t222 = _mm_load_pd( a112 );
     t224 = _mm_load_pd( a113 );
     t226 = _mm_load_pd( a114 );
     t228 = _mm_load_pd( a115 );
     t230 = _mm_load_pd( a116 );
     t232 = _mm_load_pd( a117 );
     t234 = _mm_load_pd( a118 );
     t236 = _mm_load_pd( a119 );
     t238 = _mm_load_pd( a120 );
     t240 = _mm_load_pd( a121 );
     t242 = _mm_load_pd( a122 );
     t244 = _mm_load_pd( a123 );
     t246 = _mm_load_pd( a124 );
     t248 = _mm_load_pd( a125 );
     t250 = _mm_load_pd( a126 );
     t252 = _mm_load_pd( a127 );
     t254 = _mm_load_pd( a128 );
     t256 = _mm_load_pd( a129 );
     t258 = _mm_load_pd( a130 );
     t260 = _mm_load_pd( a131 );
     t262 = _mm_load_pd( a132 );
     t264 = _mm_load_pd( a133 );
     t266 = _mm_load_pd( a134 );
     t268 = _mm_load_pd( a135 );
     t270 = _mm_load_pd( a136 );
     t272 = _mm_load_pd( a137 );
     t274 = _mm_load_pd( a138 );
     t276 = _mm_load_pd( a139 );
     t278 = _mm_load_pd( a140 );
     t280 = _mm_load_pd( a141 );
     t282 = _mm_load_pd( a142 );
     t284 = _mm_load_pd( a143 );
     t286 = _mm_load_pd( a144 );
     t288 = _mm_load_pd( a145 );
     t290 = _mm_load_pd( a146 );
     t292 = _mm_load_pd( a147 );
     t294 = _mm_load_pd( a148 );
     t296 = _mm_load_pd( a149 );
     t298 = _mm_load_pd( a150 );
     t300 = _mm_load_pd( a151 );
     t302 = _mm_load_pd( a152 );
     t304 = _mm_load_pd( a153 );
     t306 = _mm_load_pd( a154 );
     t308 = _mm_load_pd( a155 );
     t310 = _mm_load_pd( a156 );
     t312 = _mm_load_pd( a157 );
     t314 = _mm_load_pd( a158 );
     t316 = _mm_load_pd( a159 );
     t318 = _mm_load_pd( a160 );
     t320 = _mm_load_pd( a161 );
     t322 = _mm_load_pd( a162 );
     t324 = _mm_load_pd( a163 );
     t326 = _mm_load_pd( a164 );
     t328 = _mm_load_pd( a165 );
     t330 = _mm_load_pd( a166 );
     t332 = _mm_load_pd( a167 );
     t334 = _mm_load_pd( a168 );
     t336 = _mm_load_pd( a169 );
     t338 = _mm_load_pd( a170 );
     t340 = _mm_load_pd( a171 );
     t342 = _mm_load_pd( a172 );
     t344 = _mm_load_pd( a173 );
     t346 = _mm_load_pd( a174 );
     t348 = _mm_load_pd( a175 );
     t350 = _mm_load_pd( a176 );
     t352 = _mm_load_pd( a177 );
     t354 = _mm_load_pd( a178 );
     t356 = _mm_load_pd( a179 );
     t358 = _mm_load_pd( a180 );
     t360 = _mm_load_pd( a181 );
     t362 = _mm_load_pd( a182 );
     t364 = _mm_load_pd( a183 );
     t366 = _mm_load_pd( a184 );
     t368 = _mm_load_pd( a185 );
     t370 = _mm_load_pd( a186 );
     t372 = _mm_load_pd( a187 );
     t374 = _mm_load_pd( a188 );
     t376 = _mm_load_pd( a189 );
     t378 = _mm_load_pd( a190 );
     t380 = _mm_load_pd( a191 );
     t382 = _mm_load_pd( a192 );
     t384 = _mm_load_pd( a193 );
     t386 = _mm_load_pd( a194 );
     t388 = _mm_load_pd( a195 );
     t390 = _mm_load_pd( a196 );
     t392 = _mm_load_pd( a197 );
     t394 = _mm_load_pd( a198 );
     t396 = _mm_load_pd( a199 );
     t398 = _mm_load_pd( a200 );
     t400 = _mm_load_pd( a201 );
     t402 = _mm_load_pd( a202 );
     t404 = _mm_load_pd( a203 );
     t406 = _mm_load_pd( a204 );
     t408 = _mm_load_pd( a205 );
     t410 = _mm_load_pd( a206 );
     t412 = _mm_load_pd( a207 );
     t414 = _mm_load_pd( a208 );
     t416 = _mm_load_pd( a209 );
     t418 = _mm_load_pd( a210 );
     t420 = _mm_load_pd( a211 );
     t422 = _mm_load_pd( a212 );
     t424 = _mm_load_pd( a213 );
     t426 = _mm_load_pd( a214 );
     t428 = _mm_load_pd( a215 );
     t430 = _mm_load_pd( a216 );
     t432 = _mm_load_pd( a217 );
     t434 = _mm_load_pd( a218 );
     t436 = _mm_load_pd( a219 );
     t438 = _mm_load_pd( a220 );
     t440 = _mm_load_pd( a221 );
     t442 = _mm_load_pd( a222 );
     t444 = _mm_load_pd( a223 );
     t446 = _mm_load_pd( a224 );
     t448 = _mm_load_pd( a225 );
     t450 = _mm_load_pd( a226 );
     t452 = _mm_load_pd( a227 );
     t454 = _mm_load_pd( a228 );
     t456 = _mm_load_pd( a229 );
     t458 = _mm_load_pd( a230 );
     t460 = _mm_load_pd( a231 );
     t462 = _mm_load_pd( a232 );
     t464 = _mm_load_pd( a233 );
     t466 = _mm_load_pd( a234 );
     t468 = _mm_load_pd( a235 );
     t470 = _mm_load_pd( a236 );
     t472 = _mm_load_pd( a237 );
     t474 = _mm_load_pd( a238 );
     t476 = _mm_load_pd( a239 );
     t478 = _mm_load_pd( a240 );
     t480 = _mm_load_pd( a241 );
     t482 = _mm_load_pd( a242 );
     t484 = _mm_load_pd( a243 );
     t486 = _mm_load_pd( a244 );
     t488 = _mm_load_pd( a245 );
     t490 = _mm_load_pd( a246 );
     t492 = _mm_load_pd( a247 );
     t494 = _mm_load_pd( a248 );
     t496 = _mm_load_pd( a249 );
     t498 = _mm_load_pd( a250 );
     t500 = _mm_load_pd( a251 );
     t502 = _mm_load_pd( a252 );
     t504 = _mm_load_pd( a253 );
     t506 = _mm_load_pd( a254 );
     t508 = _mm_load_pd( a255 );
     t510 = _mm_load_pd( a256 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       if( k + 12 < n ) {
         b7[0] = *( m2 + n * (k+12) + j );
       } else {
         b7[0] = 0;
       }
      if( k + 13 < n ) {
        b7[1] = *( m2 + n * (k+13) + j );
      } else {
        b7[1] = 0;
      }
       if( k + 14 < n ) {
         b8[0] = *( m2 + n * (k+14) + j );
       } else {
         b8[0] = 0;
       }
      if( k + 15 < n ) {
        b8[1] = *( m2 + n * (k+15) + j );
      } else {
        b8[1] = 0;
      }
       if( k + 16 < n ) {
         b9[0] = *( m2 + n * (k+16) + j );
       } else {
         b9[0] = 0;
       }
      if( k + 17 < n ) {
        b9[1] = *( m2 + n * (k+17) + j );
      } else {
        b9[1] = 0;
      }
       if( k + 18 < n ) {
         b10[0] = *( m2 + n * (k+18) + j );
       } else {
         b10[0] = 0;
       }
      if( k + 19 < n ) {
        b10[1] = *( m2 + n * (k+19) + j );
      } else {
        b10[1] = 0;
      }
       if( k + 20 < n ) {
         b11[0] = *( m2 + n * (k+20) + j );
       } else {
         b11[0] = 0;
       }
      if( k + 21 < n ) {
        b11[1] = *( m2 + n * (k+21) + j );
      } else {
        b11[1] = 0;
      }
       if( k + 22 < n ) {
         b12[0] = *( m2 + n * (k+22) + j );
       } else {
         b12[0] = 0;
       }
      if( k + 23 < n ) {
        b12[1] = *( m2 + n * (k+23) + j );
      } else {
        b12[1] = 0;
      }
       if( k + 24 < n ) {
         b13[0] = *( m2 + n * (k+24) + j );
       } else {
         b13[0] = 0;
       }
      if( k + 25 < n ) {
        b13[1] = *( m2 + n * (k+25) + j );
      } else {
        b13[1] = 0;
      }
       if( k + 26 < n ) {
         b14[0] = *( m2 + n * (k+26) + j );
       } else {
         b14[0] = 0;
       }
      if( k + 27 < n ) {
        b14[1] = *( m2 + n * (k+27) + j );
      } else {
        b14[1] = 0;
      }
       if( k + 28 < n ) {
         b15[0] = *( m2 + n * (k+28) + j );
       } else {
         b15[0] = 0;
       }
      if( k + 29 < n ) {
        b15[1] = *( m2 + n * (k+29) + j );
      } else {
        b15[1] = 0;
      }
       if( k + 30 < n ) {
         b16[0] = *( m2 + n * (k+30) + j );
       } else {
         b16[0] = 0;
       }
      if( k + 31 < n ) {
        b16[1] = *( m2 + n * (k+31) + j );
      } else {
        b16[1] = 0;
      }
       if( k + 32 < n ) {
         b17[0] = *( m2 + n * (k+32) + j );
       } else {
         b17[0] = 0;
       }
      if( k + 33 < n ) {
        b17[1] = *( m2 + n * (k+33) + j );
      } else {
        b17[1] = 0;
      }
       if( k + 34 < n ) {
         b18[0] = *( m2 + n * (k+34) + j );
       } else {
         b18[0] = 0;
       }
      if( k + 35 < n ) {
        b18[1] = *( m2 + n * (k+35) + j );
      } else {
        b18[1] = 0;
      }
       if( k + 36 < n ) {
         b19[0] = *( m2 + n * (k+36) + j );
       } else {
         b19[0] = 0;
       }
      if( k + 37 < n ) {
        b19[1] = *( m2 + n * (k+37) + j );
      } else {
        b19[1] = 0;
      }
       if( k + 38 < n ) {
         b20[0] = *( m2 + n * (k+38) + j );
       } else {
         b20[0] = 0;
       }
      if( k + 39 < n ) {
        b20[1] = *( m2 + n * (k+39) + j );
      } else {
        b20[1] = 0;
      }
       if( k + 40 < n ) {
         b21[0] = *( m2 + n * (k+40) + j );
       } else {
         b21[0] = 0;
       }
      if( k + 41 < n ) {
        b21[1] = *( m2 + n * (k+41) + j );
      } else {
        b21[1] = 0;
      }
       if( k + 42 < n ) {
         b22[0] = *( m2 + n * (k+42) + j );
       } else {
         b22[0] = 0;
       }
      if( k + 43 < n ) {
        b22[1] = *( m2 + n * (k+43) + j );
      } else {
        b22[1] = 0;
      }
       if( k + 44 < n ) {
         b23[0] = *( m2 + n * (k+44) + j );
       } else {
         b23[0] = 0;
       }
      if( k + 45 < n ) {
        b23[1] = *( m2 + n * (k+45) + j );
      } else {
        b23[1] = 0;
      }
       if( k + 46 < n ) {
         b24[0] = *( m2 + n * (k+46) + j );
       } else {
         b24[0] = 0;
       }
      if( k + 47 < n ) {
        b24[1] = *( m2 + n * (k+47) + j );
      } else {
        b24[1] = 0;
      }
       if( k + 48 < n ) {
         b25[0] = *( m2 + n * (k+48) + j );
       } else {
         b25[0] = 0;
       }
      if( k + 49 < n ) {
        b25[1] = *( m2 + n * (k+49) + j );
      } else {
        b25[1] = 0;
      }
       if( k + 50 < n ) {
         b26[0] = *( m2 + n * (k+50) + j );
       } else {
         b26[0] = 0;
       }
      if( k + 51 < n ) {
        b26[1] = *( m2 + n * (k+51) + j );
      } else {
        b26[1] = 0;
      }
       if( k + 52 < n ) {
         b27[0] = *( m2 + n * (k+52) + j );
       } else {
         b27[0] = 0;
       }
      if( k + 53 < n ) {
        b27[1] = *( m2 + n * (k+53) + j );
      } else {
        b27[1] = 0;
      }
       if( k + 54 < n ) {
         b28[0] = *( m2 + n * (k+54) + j );
       } else {
         b28[0] = 0;
       }
      if( k + 55 < n ) {
        b28[1] = *( m2 + n * (k+55) + j );
      } else {
        b28[1] = 0;
      }
       if( k + 56 < n ) {
         b29[0] = *( m2 + n * (k+56) + j );
       } else {
         b29[0] = 0;
       }
      if( k + 57 < n ) {
        b29[1] = *( m2 + n * (k+57) + j );
      } else {
        b29[1] = 0;
      }
       if( k + 58 < n ) {
         b30[0] = *( m2 + n * (k+58) + j );
       } else {
         b30[0] = 0;
       }
      if( k + 59 < n ) {
        b30[1] = *( m2 + n * (k+59) + j );
      } else {
        b30[1] = 0;
      }
       if( k + 60 < n ) {
         b31[0] = *( m2 + n * (k+60) + j );
       } else {
         b31[0] = 0;
       }
      if( k + 61 < n ) {
        b31[1] = *( m2 + n * (k+61) + j );
      } else {
        b31[1] = 0;
      }
       if( k + 62 < n ) {
         b32[0] = *( m2 + n * (k+62) + j );
       } else {
         b32[0] = 0;
       }
      if( k + 63 < n ) {
        b32[1] = *( m2 + n * (k+63) + j );
      } else {
        b32[1] = 0;
      }
       if( k + 64 < n ) {
         b33[0] = *( m2 + n * (k+64) + j );
       } else {
         b33[0] = 0;
       }
      if( k + 65 < n ) {
        b33[1] = *( m2 + n * (k+65) + j );
      } else {
        b33[1] = 0;
      }
       if( k + 66 < n ) {
         b34[0] = *( m2 + n * (k+66) + j );
       } else {
         b34[0] = 0;
       }
      if( k + 67 < n ) {
        b34[1] = *( m2 + n * (k+67) + j );
      } else {
        b34[1] = 0;
      }
       if( k + 68 < n ) {
         b35[0] = *( m2 + n * (k+68) + j );
       } else {
         b35[0] = 0;
       }
      if( k + 69 < n ) {
        b35[1] = *( m2 + n * (k+69) + j );
      } else {
        b35[1] = 0;
      }
       if( k + 70 < n ) {
         b36[0] = *( m2 + n * (k+70) + j );
       } else {
         b36[0] = 0;
       }
      if( k + 71 < n ) {
        b36[1] = *( m2 + n * (k+71) + j );
      } else {
        b36[1] = 0;
      }
       if( k + 72 < n ) {
         b37[0] = *( m2 + n * (k+72) + j );
       } else {
         b37[0] = 0;
       }
      if( k + 73 < n ) {
        b37[1] = *( m2 + n * (k+73) + j );
      } else {
        b37[1] = 0;
      }
       if( k + 74 < n ) {
         b38[0] = *( m2 + n * (k+74) + j );
       } else {
         b38[0] = 0;
       }
      if( k + 75 < n ) {
        b38[1] = *( m2 + n * (k+75) + j );
      } else {
        b38[1] = 0;
      }
       if( k + 76 < n ) {
         b39[0] = *( m2 + n * (k+76) + j );
       } else {
         b39[0] = 0;
       }
      if( k + 77 < n ) {
        b39[1] = *( m2 + n * (k+77) + j );
      } else {
        b39[1] = 0;
      }
       if( k + 78 < n ) {
         b40[0] = *( m2 + n * (k+78) + j );
       } else {
         b40[0] = 0;
       }
      if( k + 79 < n ) {
        b40[1] = *( m2 + n * (k+79) + j );
      } else {
        b40[1] = 0;
      }
       if( k + 80 < n ) {
         b41[0] = *( m2 + n * (k+80) + j );
       } else {
         b41[0] = 0;
       }
      if( k + 81 < n ) {
        b41[1] = *( m2 + n * (k+81) + j );
      } else {
        b41[1] = 0;
      }
       if( k + 82 < n ) {
         b42[0] = *( m2 + n * (k+82) + j );
       } else {
         b42[0] = 0;
       }
      if( k + 83 < n ) {
        b42[1] = *( m2 + n * (k+83) + j );
      } else {
        b42[1] = 0;
      }
       if( k + 84 < n ) {
         b43[0] = *( m2 + n * (k+84) + j );
       } else {
         b43[0] = 0;
       }
      if( k + 85 < n ) {
        b43[1] = *( m2 + n * (k+85) + j );
      } else {
        b43[1] = 0;
      }
       if( k + 86 < n ) {
         b44[0] = *( m2 + n * (k+86) + j );
       } else {
         b44[0] = 0;
       }
      if( k + 87 < n ) {
        b44[1] = *( m2 + n * (k+87) + j );
      } else {
        b44[1] = 0;
      }
       if( k + 88 < n ) {
         b45[0] = *( m2 + n * (k+88) + j );
       } else {
         b45[0] = 0;
       }
      if( k + 89 < n ) {
        b45[1] = *( m2 + n * (k+89) + j );
      } else {
        b45[1] = 0;
      }
       if( k + 90 < n ) {
         b46[0] = *( m2 + n * (k+90) + j );
       } else {
         b46[0] = 0;
       }
      if( k + 91 < n ) {
        b46[1] = *( m2 + n * (k+91) + j );
      } else {
        b46[1] = 0;
      }
       if( k + 92 < n ) {
         b47[0] = *( m2 + n * (k+92) + j );
       } else {
         b47[0] = 0;
       }
      if( k + 93 < n ) {
        b47[1] = *( m2 + n * (k+93) + j );
      } else {
        b47[1] = 0;
      }
       if( k + 94 < n ) {
         b48[0] = *( m2 + n * (k+94) + j );
       } else {
         b48[0] = 0;
       }
      if( k + 95 < n ) {
        b48[1] = *( m2 + n * (k+95) + j );
      } else {
        b48[1] = 0;
      }
       if( k + 96 < n ) {
         b49[0] = *( m2 + n * (k+96) + j );
       } else {
         b49[0] = 0;
       }
      if( k + 97 < n ) {
        b49[1] = *( m2 + n * (k+97) + j );
      } else {
        b49[1] = 0;
      }
       if( k + 98 < n ) {
         b50[0] = *( m2 + n * (k+98) + j );
       } else {
         b50[0] = 0;
       }
      if( k + 99 < n ) {
        b50[1] = *( m2 + n * (k+99) + j );
      } else {
        b50[1] = 0;
      }
       if( k + 100 < n ) {
         b51[0] = *( m2 + n * (k+100) + j );
       } else {
         b51[0] = 0;
       }
      if( k + 101 < n ) {
        b51[1] = *( m2 + n * (k+101) + j );
      } else {
        b51[1] = 0;
      }
       if( k + 102 < n ) {
         b52[0] = *( m2 + n * (k+102) + j );
       } else {
         b52[0] = 0;
       }
      if( k + 103 < n ) {
        b52[1] = *( m2 + n * (k+103) + j );
      } else {
        b52[1] = 0;
      }
       if( k + 104 < n ) {
         b53[0] = *( m2 + n * (k+104) + j );
       } else {
         b53[0] = 0;
       }
      if( k + 105 < n ) {
        b53[1] = *( m2 + n * (k+105) + j );
      } else {
        b53[1] = 0;
      }
       if( k + 106 < n ) {
         b54[0] = *( m2 + n * (k+106) + j );
       } else {
         b54[0] = 0;
       }
      if( k + 107 < n ) {
        b54[1] = *( m2 + n * (k+107) + j );
      } else {
        b54[1] = 0;
      }
       if( k + 108 < n ) {
         b55[0] = *( m2 + n * (k+108) + j );
       } else {
         b55[0] = 0;
       }
      if( k + 109 < n ) {
        b55[1] = *( m2 + n * (k+109) + j );
      } else {
        b55[1] = 0;
      }
       if( k + 110 < n ) {
         b56[0] = *( m2 + n * (k+110) + j );
       } else {
         b56[0] = 0;
       }
      if( k + 111 < n ) {
        b56[1] = *( m2 + n * (k+111) + j );
      } else {
        b56[1] = 0;
      }
       if( k + 112 < n ) {
         b57[0] = *( m2 + n * (k+112) + j );
       } else {
         b57[0] = 0;
       }
      if( k + 113 < n ) {
        b57[1] = *( m2 + n * (k+113) + j );
      } else {
        b57[1] = 0;
      }
       if( k + 114 < n ) {
         b58[0] = *( m2 + n * (k+114) + j );
       } else {
         b58[0] = 0;
       }
      if( k + 115 < n ) {
        b58[1] = *( m2 + n * (k+115) + j );
      } else {
        b58[1] = 0;
      }
       if( k + 116 < n ) {
         b59[0] = *( m2 + n * (k+116) + j );
       } else {
         b59[0] = 0;
       }
      if( k + 117 < n ) {
        b59[1] = *( m2 + n * (k+117) + j );
      } else {
        b59[1] = 0;
      }
       if( k + 118 < n ) {
         b60[0] = *( m2 + n * (k+118) + j );
       } else {
         b60[0] = 0;
       }
      if( k + 119 < n ) {
        b60[1] = *( m2 + n * (k+119) + j );
      } else {
        b60[1] = 0;
      }
       if( k + 120 < n ) {
         b61[0] = *( m2 + n * (k+120) + j );
       } else {
         b61[0] = 0;
       }
      if( k + 121 < n ) {
        b61[1] = *( m2 + n * (k+121) + j );
      } else {
        b61[1] = 0;
      }
       if( k + 122 < n ) {
         b62[0] = *( m2 + n * (k+122) + j );
       } else {
         b62[0] = 0;
       }
      if( k + 123 < n ) {
        b62[1] = *( m2 + n * (k+123) + j );
      } else {
        b62[1] = 0;
      }
       if( k + 124 < n ) {
         b63[0] = *( m2 + n * (k+124) + j );
       } else {
         b63[0] = 0;
       }
      if( k + 125 < n ) {
        b63[1] = *( m2 + n * (k+125) + j );
      } else {
        b63[1] = 0;
      }
       if( k + 126 < n ) {
         b64[0] = *( m2 + n * (k+126) + j );
       } else {
         b64[0] = 0;
       }
      if( k + 127 < n ) {
        b64[1] = *( m2 + n * (k+127) + j );
      } else {
        b64[1] = 0;
      }
       if( k + 128 < n ) {
         b65[0] = *( m2 + n * (k+128) + j );
       } else {
         b65[0] = 0;
       }
      if( k + 129 < n ) {
        b65[1] = *( m2 + n * (k+129) + j );
      } else {
        b65[1] = 0;
      }
       if( k + 130 < n ) {
         b66[0] = *( m2 + n * (k+130) + j );
       } else {
         b66[0] = 0;
       }
      if( k + 131 < n ) {
        b66[1] = *( m2 + n * (k+131) + j );
      } else {
        b66[1] = 0;
      }
       if( k + 132 < n ) {
         b67[0] = *( m2 + n * (k+132) + j );
       } else {
         b67[0] = 0;
       }
      if( k + 133 < n ) {
        b67[1] = *( m2 + n * (k+133) + j );
      } else {
        b67[1] = 0;
      }
       if( k + 134 < n ) {
         b68[0] = *( m2 + n * (k+134) + j );
       } else {
         b68[0] = 0;
       }
      if( k + 135 < n ) {
        b68[1] = *( m2 + n * (k+135) + j );
      } else {
        b68[1] = 0;
      }
       if( k + 136 < n ) {
         b69[0] = *( m2 + n * (k+136) + j );
       } else {
         b69[0] = 0;
       }
      if( k + 137 < n ) {
        b69[1] = *( m2 + n * (k+137) + j );
      } else {
        b69[1] = 0;
      }
       if( k + 138 < n ) {
         b70[0] = *( m2 + n * (k+138) + j );
       } else {
         b70[0] = 0;
       }
      if( k + 139 < n ) {
        b70[1] = *( m2 + n * (k+139) + j );
      } else {
        b70[1] = 0;
      }
       if( k + 140 < n ) {
         b71[0] = *( m2 + n * (k+140) + j );
       } else {
         b71[0] = 0;
       }
      if( k + 141 < n ) {
        b71[1] = *( m2 + n * (k+141) + j );
      } else {
        b71[1] = 0;
      }
       if( k + 142 < n ) {
         b72[0] = *( m2 + n * (k+142) + j );
       } else {
         b72[0] = 0;
       }
      if( k + 143 < n ) {
        b72[1] = *( m2 + n * (k+143) + j );
      } else {
        b72[1] = 0;
      }
       if( k + 144 < n ) {
         b73[0] = *( m2 + n * (k+144) + j );
       } else {
         b73[0] = 0;
       }
      if( k + 145 < n ) {
        b73[1] = *( m2 + n * (k+145) + j );
      } else {
        b73[1] = 0;
      }
       if( k + 146 < n ) {
         b74[0] = *( m2 + n * (k+146) + j );
       } else {
         b74[0] = 0;
       }
      if( k + 147 < n ) {
        b74[1] = *( m2 + n * (k+147) + j );
      } else {
        b74[1] = 0;
      }
       if( k + 148 < n ) {
         b75[0] = *( m2 + n * (k+148) + j );
       } else {
         b75[0] = 0;
       }
      if( k + 149 < n ) {
        b75[1] = *( m2 + n * (k+149) + j );
      } else {
        b75[1] = 0;
      }
       if( k + 150 < n ) {
         b76[0] = *( m2 + n * (k+150) + j );
       } else {
         b76[0] = 0;
       }
      if( k + 151 < n ) {
        b76[1] = *( m2 + n * (k+151) + j );
      } else {
        b76[1] = 0;
      }
       if( k + 152 < n ) {
         b77[0] = *( m2 + n * (k+152) + j );
       } else {
         b77[0] = 0;
       }
      if( k + 153 < n ) {
        b77[1] = *( m2 + n * (k+153) + j );
      } else {
        b77[1] = 0;
      }
       if( k + 154 < n ) {
         b78[0] = *( m2 + n * (k+154) + j );
       } else {
         b78[0] = 0;
       }
      if( k + 155 < n ) {
        b78[1] = *( m2 + n * (k+155) + j );
      } else {
        b78[1] = 0;
      }
       if( k + 156 < n ) {
         b79[0] = *( m2 + n * (k+156) + j );
       } else {
         b79[0] = 0;
       }
      if( k + 157 < n ) {
        b79[1] = *( m2 + n * (k+157) + j );
      } else {
        b79[1] = 0;
      }
       if( k + 158 < n ) {
         b80[0] = *( m2 + n * (k+158) + j );
       } else {
         b80[0] = 0;
       }
      if( k + 159 < n ) {
        b80[1] = *( m2 + n * (k+159) + j );
      } else {
        b80[1] = 0;
      }
       if( k + 160 < n ) {
         b81[0] = *( m2 + n * (k+160) + j );
       } else {
         b81[0] = 0;
       }
      if( k + 161 < n ) {
        b81[1] = *( m2 + n * (k+161) + j );
      } else {
        b81[1] = 0;
      }
       if( k + 162 < n ) {
         b82[0] = *( m2 + n * (k+162) + j );
       } else {
         b82[0] = 0;
       }
      if( k + 163 < n ) {
        b82[1] = *( m2 + n * (k+163) + j );
      } else {
        b82[1] = 0;
      }
       if( k + 164 < n ) {
         b83[0] = *( m2 + n * (k+164) + j );
       } else {
         b83[0] = 0;
       }
      if( k + 165 < n ) {
        b83[1] = *( m2 + n * (k+165) + j );
      } else {
        b83[1] = 0;
      }
       if( k + 166 < n ) {
         b84[0] = *( m2 + n * (k+166) + j );
       } else {
         b84[0] = 0;
       }
      if( k + 167 < n ) {
        b84[1] = *( m2 + n * (k+167) + j );
      } else {
        b84[1] = 0;
      }
       if( k + 168 < n ) {
         b85[0] = *( m2 + n * (k+168) + j );
       } else {
         b85[0] = 0;
       }
      if( k + 169 < n ) {
        b85[1] = *( m2 + n * (k+169) + j );
      } else {
        b85[1] = 0;
      }
       if( k + 170 < n ) {
         b86[0] = *( m2 + n * (k+170) + j );
       } else {
         b86[0] = 0;
       }
      if( k + 171 < n ) {
        b86[1] = *( m2 + n * (k+171) + j );
      } else {
        b86[1] = 0;
      }
       if( k + 172 < n ) {
         b87[0] = *( m2 + n * (k+172) + j );
       } else {
         b87[0] = 0;
       }
      if( k + 173 < n ) {
        b87[1] = *( m2 + n * (k+173) + j );
      } else {
        b87[1] = 0;
      }
       if( k + 174 < n ) {
         b88[0] = *( m2 + n * (k+174) + j );
       } else {
         b88[0] = 0;
       }
      if( k + 175 < n ) {
        b88[1] = *( m2 + n * (k+175) + j );
      } else {
        b88[1] = 0;
      }
       if( k + 176 < n ) {
         b89[0] = *( m2 + n * (k+176) + j );
       } else {
         b89[0] = 0;
       }
      if( k + 177 < n ) {
        b89[1] = *( m2 + n * (k+177) + j );
      } else {
        b89[1] = 0;
      }
       if( k + 178 < n ) {
         b90[0] = *( m2 + n * (k+178) + j );
       } else {
         b90[0] = 0;
       }
      if( k + 179 < n ) {
        b90[1] = *( m2 + n * (k+179) + j );
      } else {
        b90[1] = 0;
      }
       if( k + 180 < n ) {
         b91[0] = *( m2 + n * (k+180) + j );
       } else {
         b91[0] = 0;
       }
      if( k + 181 < n ) {
        b91[1] = *( m2 + n * (k+181) + j );
      } else {
        b91[1] = 0;
      }
       if( k + 182 < n ) {
         b92[0] = *( m2 + n * (k+182) + j );
       } else {
         b92[0] = 0;
       }
      if( k + 183 < n ) {
        b92[1] = *( m2 + n * (k+183) + j );
      } else {
        b92[1] = 0;
      }
       if( k + 184 < n ) {
         b93[0] = *( m2 + n * (k+184) + j );
       } else {
         b93[0] = 0;
       }
      if( k + 185 < n ) {
        b93[1] = *( m2 + n * (k+185) + j );
      } else {
        b93[1] = 0;
      }
       if( k + 186 < n ) {
         b94[0] = *( m2 + n * (k+186) + j );
       } else {
         b94[0] = 0;
       }
      if( k + 187 < n ) {
        b94[1] = *( m2 + n * (k+187) + j );
      } else {
        b94[1] = 0;
      }
       if( k + 188 < n ) {
         b95[0] = *( m2 + n * (k+188) + j );
       } else {
         b95[0] = 0;
       }
      if( k + 189 < n ) {
        b95[1] = *( m2 + n * (k+189) + j );
      } else {
        b95[1] = 0;
      }
       if( k + 190 < n ) {
         b96[0] = *( m2 + n * (k+190) + j );
       } else {
         b96[0] = 0;
       }
      if( k + 191 < n ) {
        b96[1] = *( m2 + n * (k+191) + j );
      } else {
        b96[1] = 0;
      }
       if( k + 192 < n ) {
         b97[0] = *( m2 + n * (k+192) + j );
       } else {
         b97[0] = 0;
       }
      if( k + 193 < n ) {
        b97[1] = *( m2 + n * (k+193) + j );
      } else {
        b97[1] = 0;
      }
       if( k + 194 < n ) {
         b98[0] = *( m2 + n * (k+194) + j );
       } else {
         b98[0] = 0;
       }
      if( k + 195 < n ) {
        b98[1] = *( m2 + n * (k+195) + j );
      } else {
        b98[1] = 0;
      }
       if( k + 196 < n ) {
         b99[0] = *( m2 + n * (k+196) + j );
       } else {
         b99[0] = 0;
       }
      if( k + 197 < n ) {
        b99[1] = *( m2 + n * (k+197) + j );
      } else {
        b99[1] = 0;
      }
       if( k + 198 < n ) {
         b100[0] = *( m2 + n * (k+198) + j );
       } else {
         b100[0] = 0;
       }
      if( k + 199 < n ) {
        b100[1] = *( m2 + n * (k+199) + j );
      } else {
        b100[1] = 0;
      }
       if( k + 200 < n ) {
         b101[0] = *( m2 + n * (k+200) + j );
       } else {
         b101[0] = 0;
       }
      if( k + 201 < n ) {
        b101[1] = *( m2 + n * (k+201) + j );
      } else {
        b101[1] = 0;
      }
       if( k + 202 < n ) {
         b102[0] = *( m2 + n * (k+202) + j );
       } else {
         b102[0] = 0;
       }
      if( k + 203 < n ) {
        b102[1] = *( m2 + n * (k+203) + j );
      } else {
        b102[1] = 0;
      }
       if( k + 204 < n ) {
         b103[0] = *( m2 + n * (k+204) + j );
       } else {
         b103[0] = 0;
       }
      if( k + 205 < n ) {
        b103[1] = *( m2 + n * (k+205) + j );
      } else {
        b103[1] = 0;
      }
       if( k + 206 < n ) {
         b104[0] = *( m2 + n * (k+206) + j );
       } else {
         b104[0] = 0;
       }
      if( k + 207 < n ) {
        b104[1] = *( m2 + n * (k+207) + j );
      } else {
        b104[1] = 0;
      }
       if( k + 208 < n ) {
         b105[0] = *( m2 + n * (k+208) + j );
       } else {
         b105[0] = 0;
       }
      if( k + 209 < n ) {
        b105[1] = *( m2 + n * (k+209) + j );
      } else {
        b105[1] = 0;
      }
       if( k + 210 < n ) {
         b106[0] = *( m2 + n * (k+210) + j );
       } else {
         b106[0] = 0;
       }
      if( k + 211 < n ) {
        b106[1] = *( m2 + n * (k+211) + j );
      } else {
        b106[1] = 0;
      }
       if( k + 212 < n ) {
         b107[0] = *( m2 + n * (k+212) + j );
       } else {
         b107[0] = 0;
       }
      if( k + 213 < n ) {
        b107[1] = *( m2 + n * (k+213) + j );
      } else {
        b107[1] = 0;
      }
       if( k + 214 < n ) {
         b108[0] = *( m2 + n * (k+214) + j );
       } else {
         b108[0] = 0;
       }
      if( k + 215 < n ) {
        b108[1] = *( m2 + n * (k+215) + j );
      } else {
        b108[1] = 0;
      }
       if( k + 216 < n ) {
         b109[0] = *( m2 + n * (k+216) + j );
       } else {
         b109[0] = 0;
       }
      if( k + 217 < n ) {
        b109[1] = *( m2 + n * (k+217) + j );
      } else {
        b109[1] = 0;
      }
       if( k + 218 < n ) {
         b110[0] = *( m2 + n * (k+218) + j );
       } else {
         b110[0] = 0;
       }
      if( k + 219 < n ) {
        b110[1] = *( m2 + n * (k+219) + j );
      } else {
        b110[1] = 0;
      }
       if( k + 220 < n ) {
         b111[0] = *( m2 + n * (k+220) + j );
       } else {
         b111[0] = 0;
       }
      if( k + 221 < n ) {
        b111[1] = *( m2 + n * (k+221) + j );
      } else {
        b111[1] = 0;
      }
       if( k + 222 < n ) {
         b112[0] = *( m2 + n * (k+222) + j );
       } else {
         b112[0] = 0;
       }
      if( k + 223 < n ) {
        b112[1] = *( m2 + n * (k+223) + j );
      } else {
        b112[1] = 0;
      }
       if( k + 224 < n ) {
         b113[0] = *( m2 + n * (k+224) + j );
       } else {
         b113[0] = 0;
       }
      if( k + 225 < n ) {
        b113[1] = *( m2 + n * (k+225) + j );
      } else {
        b113[1] = 0;
      }
       if( k + 226 < n ) {
         b114[0] = *( m2 + n * (k+226) + j );
       } else {
         b114[0] = 0;
       }
      if( k + 227 < n ) {
        b114[1] = *( m2 + n * (k+227) + j );
      } else {
        b114[1] = 0;
      }
       if( k + 228 < n ) {
         b115[0] = *( m2 + n * (k+228) + j );
       } else {
         b115[0] = 0;
       }
      if( k + 229 < n ) {
        b115[1] = *( m2 + n * (k+229) + j );
      } else {
        b115[1] = 0;
      }
       if( k + 230 < n ) {
         b116[0] = *( m2 + n * (k+230) + j );
       } else {
         b116[0] = 0;
       }
      if( k + 231 < n ) {
        b116[1] = *( m2 + n * (k+231) + j );
      } else {
        b116[1] = 0;
      }
       if( k + 232 < n ) {
         b117[0] = *( m2 + n * (k+232) + j );
       } else {
         b117[0] = 0;
       }
      if( k + 233 < n ) {
        b117[1] = *( m2 + n * (k+233) + j );
      } else {
        b117[1] = 0;
      }
       if( k + 234 < n ) {
         b118[0] = *( m2 + n * (k+234) + j );
       } else {
         b118[0] = 0;
       }
      if( k + 235 < n ) {
        b118[1] = *( m2 + n * (k+235) + j );
      } else {
        b118[1] = 0;
      }
       if( k + 236 < n ) {
         b119[0] = *( m2 + n * (k+236) + j );
       } else {
         b119[0] = 0;
       }
      if( k + 237 < n ) {
        b119[1] = *( m2 + n * (k+237) + j );
      } else {
        b119[1] = 0;
      }
       if( k + 238 < n ) {
         b120[0] = *( m2 + n * (k+238) + j );
       } else {
         b120[0] = 0;
       }
      if( k + 239 < n ) {
        b120[1] = *( m2 + n * (k+239) + j );
      } else {
        b120[1] = 0;
      }
       if( k + 240 < n ) {
         b121[0] = *( m2 + n * (k+240) + j );
       } else {
         b121[0] = 0;
       }
      if( k + 241 < n ) {
        b121[1] = *( m2 + n * (k+241) + j );
      } else {
        b121[1] = 0;
      }
       if( k + 242 < n ) {
         b122[0] = *( m2 + n * (k+242) + j );
       } else {
         b122[0] = 0;
       }
      if( k + 243 < n ) {
        b122[1] = *( m2 + n * (k+243) + j );
      } else {
        b122[1] = 0;
      }
       if( k + 244 < n ) {
         b123[0] = *( m2 + n * (k+244) + j );
       } else {
         b123[0] = 0;
       }
      if( k + 245 < n ) {
        b123[1] = *( m2 + n * (k+245) + j );
      } else {
        b123[1] = 0;
      }
       if( k + 246 < n ) {
         b124[0] = *( m2 + n * (k+246) + j );
       } else {
         b124[0] = 0;
       }
      if( k + 247 < n ) {
        b124[1] = *( m2 + n * (k+247) + j );
      } else {
        b124[1] = 0;
      }
       if( k + 248 < n ) {
         b125[0] = *( m2 + n * (k+248) + j );
       } else {
         b125[0] = 0;
       }
      if( k + 249 < n ) {
        b125[1] = *( m2 + n * (k+249) + j );
      } else {
        b125[1] = 0;
      }
       if( k + 250 < n ) {
         b126[0] = *( m2 + n * (k+250) + j );
       } else {
         b126[0] = 0;
       }
      if( k + 251 < n ) {
        b126[1] = *( m2 + n * (k+251) + j );
      } else {
        b126[1] = 0;
      }
       if( k + 252 < n ) {
         b127[0] = *( m2 + n * (k+252) + j );
       } else {
         b127[0] = 0;
       }
      if( k + 253 < n ) {
        b127[1] = *( m2 + n * (k+253) + j );
      } else {
        b127[1] = 0;
      }
       if( k + 254 < n ) {
         b128[0] = *( m2 + n * (k+254) + j );
       } else {
         b128[0] = 0;
       }
      if( k + 255 < n ) {
        b128[1] = *( m2 + n * (k+255) + j );
      } else {
        b128[1] = 0;
      }
       if( k + 256 < n ) {
         b129[0] = *( m2 + n * (k+256) + j );
       } else {
         b129[0] = 0;
       }
      if( k + 257 < n ) {
        b129[1] = *( m2 + n * (k+257) + j );
      } else {
        b129[1] = 0;
      }
       if( k + 258 < n ) {
         b130[0] = *( m2 + n * (k+258) + j );
       } else {
         b130[0] = 0;
       }
      if( k + 259 < n ) {
        b130[1] = *( m2 + n * (k+259) + j );
      } else {
        b130[1] = 0;
      }
       if( k + 260 < n ) {
         b131[0] = *( m2 + n * (k+260) + j );
       } else {
         b131[0] = 0;
       }
      if( k + 261 < n ) {
        b131[1] = *( m2 + n * (k+261) + j );
      } else {
        b131[1] = 0;
      }
       if( k + 262 < n ) {
         b132[0] = *( m2 + n * (k+262) + j );
       } else {
         b132[0] = 0;
       }
      if( k + 263 < n ) {
        b132[1] = *( m2 + n * (k+263) + j );
      } else {
        b132[1] = 0;
      }
       if( k + 264 < n ) {
         b133[0] = *( m2 + n * (k+264) + j );
       } else {
         b133[0] = 0;
       }
      if( k + 265 < n ) {
        b133[1] = *( m2 + n * (k+265) + j );
      } else {
        b133[1] = 0;
      }
       if( k + 266 < n ) {
         b134[0] = *( m2 + n * (k+266) + j );
       } else {
         b134[0] = 0;
       }
      if( k + 267 < n ) {
        b134[1] = *( m2 + n * (k+267) + j );
      } else {
        b134[1] = 0;
      }
       if( k + 268 < n ) {
         b135[0] = *( m2 + n * (k+268) + j );
       } else {
         b135[0] = 0;
       }
      if( k + 269 < n ) {
        b135[1] = *( m2 + n * (k+269) + j );
      } else {
        b135[1] = 0;
      }
       if( k + 270 < n ) {
         b136[0] = *( m2 + n * (k+270) + j );
       } else {
         b136[0] = 0;
       }
      if( k + 271 < n ) {
        b136[1] = *( m2 + n * (k+271) + j );
      } else {
        b136[1] = 0;
      }
       if( k + 272 < n ) {
         b137[0] = *( m2 + n * (k+272) + j );
       } else {
         b137[0] = 0;
       }
      if( k + 273 < n ) {
        b137[1] = *( m2 + n * (k+273) + j );
      } else {
        b137[1] = 0;
      }
       if( k + 274 < n ) {
         b138[0] = *( m2 + n * (k+274) + j );
       } else {
         b138[0] = 0;
       }
      if( k + 275 < n ) {
        b138[1] = *( m2 + n * (k+275) + j );
      } else {
        b138[1] = 0;
      }
       if( k + 276 < n ) {
         b139[0] = *( m2 + n * (k+276) + j );
       } else {
         b139[0] = 0;
       }
      if( k + 277 < n ) {
        b139[1] = *( m2 + n * (k+277) + j );
      } else {
        b139[1] = 0;
      }
       if( k + 278 < n ) {
         b140[0] = *( m2 + n * (k+278) + j );
       } else {
         b140[0] = 0;
       }
      if( k + 279 < n ) {
        b140[1] = *( m2 + n * (k+279) + j );
      } else {
        b140[1] = 0;
      }
       if( k + 280 < n ) {
         b141[0] = *( m2 + n * (k+280) + j );
       } else {
         b141[0] = 0;
       }
      if( k + 281 < n ) {
        b141[1] = *( m2 + n * (k+281) + j );
      } else {
        b141[1] = 0;
      }
       if( k + 282 < n ) {
         b142[0] = *( m2 + n * (k+282) + j );
       } else {
         b142[0] = 0;
       }
      if( k + 283 < n ) {
        b142[1] = *( m2 + n * (k+283) + j );
      } else {
        b142[1] = 0;
      }
       if( k + 284 < n ) {
         b143[0] = *( m2 + n * (k+284) + j );
       } else {
         b143[0] = 0;
       }
      if( k + 285 < n ) {
        b143[1] = *( m2 + n * (k+285) + j );
      } else {
        b143[1] = 0;
      }
       if( k + 286 < n ) {
         b144[0] = *( m2 + n * (k+286) + j );
       } else {
         b144[0] = 0;
       }
      if( k + 287 < n ) {
        b144[1] = *( m2 + n * (k+287) + j );
      } else {
        b144[1] = 0;
      }
       if( k + 288 < n ) {
         b145[0] = *( m2 + n * (k+288) + j );
       } else {
         b145[0] = 0;
       }
      if( k + 289 < n ) {
        b145[1] = *( m2 + n * (k+289) + j );
      } else {
        b145[1] = 0;
      }
       if( k + 290 < n ) {
         b146[0] = *( m2 + n * (k+290) + j );
       } else {
         b146[0] = 0;
       }
      if( k + 291 < n ) {
        b146[1] = *( m2 + n * (k+291) + j );
      } else {
        b146[1] = 0;
      }
       if( k + 292 < n ) {
         b147[0] = *( m2 + n * (k+292) + j );
       } else {
         b147[0] = 0;
       }
      if( k + 293 < n ) {
        b147[1] = *( m2 + n * (k+293) + j );
      } else {
        b147[1] = 0;
      }
       if( k + 294 < n ) {
         b148[0] = *( m2 + n * (k+294) + j );
       } else {
         b148[0] = 0;
       }
      if( k + 295 < n ) {
        b148[1] = *( m2 + n * (k+295) + j );
      } else {
        b148[1] = 0;
      }
       if( k + 296 < n ) {
         b149[0] = *( m2 + n * (k+296) + j );
       } else {
         b149[0] = 0;
       }
      if( k + 297 < n ) {
        b149[1] = *( m2 + n * (k+297) + j );
      } else {
        b149[1] = 0;
      }
       if( k + 298 < n ) {
         b150[0] = *( m2 + n * (k+298) + j );
       } else {
         b150[0] = 0;
       }
      if( k + 299 < n ) {
        b150[1] = *( m2 + n * (k+299) + j );
      } else {
        b150[1] = 0;
      }
       if( k + 300 < n ) {
         b151[0] = *( m2 + n * (k+300) + j );
       } else {
         b151[0] = 0;
       }
      if( k + 301 < n ) {
        b151[1] = *( m2 + n * (k+301) + j );
      } else {
        b151[1] = 0;
      }
       if( k + 302 < n ) {
         b152[0] = *( m2 + n * (k+302) + j );
       } else {
         b152[0] = 0;
       }
      if( k + 303 < n ) {
        b152[1] = *( m2 + n * (k+303) + j );
      } else {
        b152[1] = 0;
      }
       if( k + 304 < n ) {
         b153[0] = *( m2 + n * (k+304) + j );
       } else {
         b153[0] = 0;
       }
      if( k + 305 < n ) {
        b153[1] = *( m2 + n * (k+305) + j );
      } else {
        b153[1] = 0;
      }
       if( k + 306 < n ) {
         b154[0] = *( m2 + n * (k+306) + j );
       } else {
         b154[0] = 0;
       }
      if( k + 307 < n ) {
        b154[1] = *( m2 + n * (k+307) + j );
      } else {
        b154[1] = 0;
      }
       if( k + 308 < n ) {
         b155[0] = *( m2 + n * (k+308) + j );
       } else {
         b155[0] = 0;
       }
      if( k + 309 < n ) {
        b155[1] = *( m2 + n * (k+309) + j );
      } else {
        b155[1] = 0;
      }
       if( k + 310 < n ) {
         b156[0] = *( m2 + n * (k+310) + j );
       } else {
         b156[0] = 0;
       }
      if( k + 311 < n ) {
        b156[1] = *( m2 + n * (k+311) + j );
      } else {
        b156[1] = 0;
      }
       if( k + 312 < n ) {
         b157[0] = *( m2 + n * (k+312) + j );
       } else {
         b157[0] = 0;
       }
      if( k + 313 < n ) {
        b157[1] = *( m2 + n * (k+313) + j );
      } else {
        b157[1] = 0;
      }
       if( k + 314 < n ) {
         b158[0] = *( m2 + n * (k+314) + j );
       } else {
         b158[0] = 0;
       }
      if( k + 315 < n ) {
        b158[1] = *( m2 + n * (k+315) + j );
      } else {
        b158[1] = 0;
      }
       if( k + 316 < n ) {
         b159[0] = *( m2 + n * (k+316) + j );
       } else {
         b159[0] = 0;
       }
      if( k + 317 < n ) {
        b159[1] = *( m2 + n * (k+317) + j );
      } else {
        b159[1] = 0;
      }
       if( k + 318 < n ) {
         b160[0] = *( m2 + n * (k+318) + j );
       } else {
         b160[0] = 0;
       }
      if( k + 319 < n ) {
        b160[1] = *( m2 + n * (k+319) + j );
      } else {
        b160[1] = 0;
      }
       if( k + 320 < n ) {
         b161[0] = *( m2 + n * (k+320) + j );
       } else {
         b161[0] = 0;
       }
      if( k + 321 < n ) {
        b161[1] = *( m2 + n * (k+321) + j );
      } else {
        b161[1] = 0;
      }
       if( k + 322 < n ) {
         b162[0] = *( m2 + n * (k+322) + j );
       } else {
         b162[0] = 0;
       }
      if( k + 323 < n ) {
        b162[1] = *( m2 + n * (k+323) + j );
      } else {
        b162[1] = 0;
      }
       if( k + 324 < n ) {
         b163[0] = *( m2 + n * (k+324) + j );
       } else {
         b163[0] = 0;
       }
      if( k + 325 < n ) {
        b163[1] = *( m2 + n * (k+325) + j );
      } else {
        b163[1] = 0;
      }
       if( k + 326 < n ) {
         b164[0] = *( m2 + n * (k+326) + j );
       } else {
         b164[0] = 0;
       }
      if( k + 327 < n ) {
        b164[1] = *( m2 + n * (k+327) + j );
      } else {
        b164[1] = 0;
      }
       if( k + 328 < n ) {
         b165[0] = *( m2 + n * (k+328) + j );
       } else {
         b165[0] = 0;
       }
      if( k + 329 < n ) {
        b165[1] = *( m2 + n * (k+329) + j );
      } else {
        b165[1] = 0;
      }
       if( k + 330 < n ) {
         b166[0] = *( m2 + n * (k+330) + j );
       } else {
         b166[0] = 0;
       }
      if( k + 331 < n ) {
        b166[1] = *( m2 + n * (k+331) + j );
      } else {
        b166[1] = 0;
      }
       if( k + 332 < n ) {
         b167[0] = *( m2 + n * (k+332) + j );
       } else {
         b167[0] = 0;
       }
      if( k + 333 < n ) {
        b167[1] = *( m2 + n * (k+333) + j );
      } else {
        b167[1] = 0;
      }
       if( k + 334 < n ) {
         b168[0] = *( m2 + n * (k+334) + j );
       } else {
         b168[0] = 0;
       }
      if( k + 335 < n ) {
        b168[1] = *( m2 + n * (k+335) + j );
      } else {
        b168[1] = 0;
      }
       if( k + 336 < n ) {
         b169[0] = *( m2 + n * (k+336) + j );
       } else {
         b169[0] = 0;
       }
      if( k + 337 < n ) {
        b169[1] = *( m2 + n * (k+337) + j );
      } else {
        b169[1] = 0;
      }
       if( k + 338 < n ) {
         b170[0] = *( m2 + n * (k+338) + j );
       } else {
         b170[0] = 0;
       }
      if( k + 339 < n ) {
        b170[1] = *( m2 + n * (k+339) + j );
      } else {
        b170[1] = 0;
      }
       if( k + 340 < n ) {
         b171[0] = *( m2 + n * (k+340) + j );
       } else {
         b171[0] = 0;
       }
      if( k + 341 < n ) {
        b171[1] = *( m2 + n * (k+341) + j );
      } else {
        b171[1] = 0;
      }
       if( k + 342 < n ) {
         b172[0] = *( m2 + n * (k+342) + j );
       } else {
         b172[0] = 0;
       }
      if( k + 343 < n ) {
        b172[1] = *( m2 + n * (k+343) + j );
      } else {
        b172[1] = 0;
      }
       if( k + 344 < n ) {
         b173[0] = *( m2 + n * (k+344) + j );
       } else {
         b173[0] = 0;
       }
      if( k + 345 < n ) {
        b173[1] = *( m2 + n * (k+345) + j );
      } else {
        b173[1] = 0;
      }
       if( k + 346 < n ) {
         b174[0] = *( m2 + n * (k+346) + j );
       } else {
         b174[0] = 0;
       }
      if( k + 347 < n ) {
        b174[1] = *( m2 + n * (k+347) + j );
      } else {
        b174[1] = 0;
      }
       if( k + 348 < n ) {
         b175[0] = *( m2 + n * (k+348) + j );
       } else {
         b175[0] = 0;
       }
      if( k + 349 < n ) {
        b175[1] = *( m2 + n * (k+349) + j );
      } else {
        b175[1] = 0;
      }
       if( k + 350 < n ) {
         b176[0] = *( m2 + n * (k+350) + j );
       } else {
         b176[0] = 0;
       }
      if( k + 351 < n ) {
        b176[1] = *( m2 + n * (k+351) + j );
      } else {
        b176[1] = 0;
      }
       if( k + 352 < n ) {
         b177[0] = *( m2 + n * (k+352) + j );
       } else {
         b177[0] = 0;
       }
      if( k + 353 < n ) {
        b177[1] = *( m2 + n * (k+353) + j );
      } else {
        b177[1] = 0;
      }
       if( k + 354 < n ) {
         b178[0] = *( m2 + n * (k+354) + j );
       } else {
         b178[0] = 0;
       }
      if( k + 355 < n ) {
        b178[1] = *( m2 + n * (k+355) + j );
      } else {
        b178[1] = 0;
      }
       if( k + 356 < n ) {
         b179[0] = *( m2 + n * (k+356) + j );
       } else {
         b179[0] = 0;
       }
      if( k + 357 < n ) {
        b179[1] = *( m2 + n * (k+357) + j );
      } else {
        b179[1] = 0;
      }
       if( k + 358 < n ) {
         b180[0] = *( m2 + n * (k+358) + j );
       } else {
         b180[0] = 0;
       }
      if( k + 359 < n ) {
        b180[1] = *( m2 + n * (k+359) + j );
      } else {
        b180[1] = 0;
      }
       if( k + 360 < n ) {
         b181[0] = *( m2 + n * (k+360) + j );
       } else {
         b181[0] = 0;
       }
      if( k + 361 < n ) {
        b181[1] = *( m2 + n * (k+361) + j );
      } else {
        b181[1] = 0;
      }
       if( k + 362 < n ) {
         b182[0] = *( m2 + n * (k+362) + j );
       } else {
         b182[0] = 0;
       }
      if( k + 363 < n ) {
        b182[1] = *( m2 + n * (k+363) + j );
      } else {
        b182[1] = 0;
      }
       if( k + 364 < n ) {
         b183[0] = *( m2 + n * (k+364) + j );
       } else {
         b183[0] = 0;
       }
      if( k + 365 < n ) {
        b183[1] = *( m2 + n * (k+365) + j );
      } else {
        b183[1] = 0;
      }
       if( k + 366 < n ) {
         b184[0] = *( m2 + n * (k+366) + j );
       } else {
         b184[0] = 0;
       }
      if( k + 367 < n ) {
        b184[1] = *( m2 + n * (k+367) + j );
      } else {
        b184[1] = 0;
      }
       if( k + 368 < n ) {
         b185[0] = *( m2 + n * (k+368) + j );
       } else {
         b185[0] = 0;
       }
      if( k + 369 < n ) {
        b185[1] = *( m2 + n * (k+369) + j );
      } else {
        b185[1] = 0;
      }
       if( k + 370 < n ) {
         b186[0] = *( m2 + n * (k+370) + j );
       } else {
         b186[0] = 0;
       }
      if( k + 371 < n ) {
        b186[1] = *( m2 + n * (k+371) + j );
      } else {
        b186[1] = 0;
      }
       if( k + 372 < n ) {
         b187[0] = *( m2 + n * (k+372) + j );
       } else {
         b187[0] = 0;
       }
      if( k + 373 < n ) {
        b187[1] = *( m2 + n * (k+373) + j );
      } else {
        b187[1] = 0;
      }
       if( k + 374 < n ) {
         b188[0] = *( m2 + n * (k+374) + j );
       } else {
         b188[0] = 0;
       }
      if( k + 375 < n ) {
        b188[1] = *( m2 + n * (k+375) + j );
      } else {
        b188[1] = 0;
      }
       if( k + 376 < n ) {
         b189[0] = *( m2 + n * (k+376) + j );
       } else {
         b189[0] = 0;
       }
      if( k + 377 < n ) {
        b189[1] = *( m2 + n * (k+377) + j );
      } else {
        b189[1] = 0;
      }
       if( k + 378 < n ) {
         b190[0] = *( m2 + n * (k+378) + j );
       } else {
         b190[0] = 0;
       }
      if( k + 379 < n ) {
        b190[1] = *( m2 + n * (k+379) + j );
      } else {
        b190[1] = 0;
      }
       if( k + 380 < n ) {
         b191[0] = *( m2 + n * (k+380) + j );
       } else {
         b191[0] = 0;
       }
      if( k + 381 < n ) {
        b191[1] = *( m2 + n * (k+381) + j );
      } else {
        b191[1] = 0;
      }
       if( k + 382 < n ) {
         b192[0] = *( m2 + n * (k+382) + j );
       } else {
         b192[0] = 0;
       }
      if( k + 383 < n ) {
        b192[1] = *( m2 + n * (k+383) + j );
      } else {
        b192[1] = 0;
      }
       if( k + 384 < n ) {
         b193[0] = *( m2 + n * (k+384) + j );
       } else {
         b193[0] = 0;
       }
      if( k + 385 < n ) {
        b193[1] = *( m2 + n * (k+385) + j );
      } else {
        b193[1] = 0;
      }
       if( k + 386 < n ) {
         b194[0] = *( m2 + n * (k+386) + j );
       } else {
         b194[0] = 0;
       }
      if( k + 387 < n ) {
        b194[1] = *( m2 + n * (k+387) + j );
      } else {
        b194[1] = 0;
      }
       if( k + 388 < n ) {
         b195[0] = *( m2 + n * (k+388) + j );
       } else {
         b195[0] = 0;
       }
      if( k + 389 < n ) {
        b195[1] = *( m2 + n * (k+389) + j );
      } else {
        b195[1] = 0;
      }
       if( k + 390 < n ) {
         b196[0] = *( m2 + n * (k+390) + j );
       } else {
         b196[0] = 0;
       }
      if( k + 391 < n ) {
        b196[1] = *( m2 + n * (k+391) + j );
      } else {
        b196[1] = 0;
      }
       if( k + 392 < n ) {
         b197[0] = *( m2 + n * (k+392) + j );
       } else {
         b197[0] = 0;
       }
      if( k + 393 < n ) {
        b197[1] = *( m2 + n * (k+393) + j );
      } else {
        b197[1] = 0;
      }
       if( k + 394 < n ) {
         b198[0] = *( m2 + n * (k+394) + j );
       } else {
         b198[0] = 0;
       }
      if( k + 395 < n ) {
        b198[1] = *( m2 + n * (k+395) + j );
      } else {
        b198[1] = 0;
      }
       if( k + 396 < n ) {
         b199[0] = *( m2 + n * (k+396) + j );
       } else {
         b199[0] = 0;
       }
      if( k + 397 < n ) {
        b199[1] = *( m2 + n * (k+397) + j );
      } else {
        b199[1] = 0;
      }
       if( k + 398 < n ) {
         b200[0] = *( m2 + n * (k+398) + j );
       } else {
         b200[0] = 0;
       }
      if( k + 399 < n ) {
        b200[1] = *( m2 + n * (k+399) + j );
      } else {
        b200[1] = 0;
      }
       if( k + 400 < n ) {
         b201[0] = *( m2 + n * (k+400) + j );
       } else {
         b201[0] = 0;
       }
      if( k + 401 < n ) {
        b201[1] = *( m2 + n * (k+401) + j );
      } else {
        b201[1] = 0;
      }
       if( k + 402 < n ) {
         b202[0] = *( m2 + n * (k+402) + j );
       } else {
         b202[0] = 0;
       }
      if( k + 403 < n ) {
        b202[1] = *( m2 + n * (k+403) + j );
      } else {
        b202[1] = 0;
      }
       if( k + 404 < n ) {
         b203[0] = *( m2 + n * (k+404) + j );
       } else {
         b203[0] = 0;
       }
      if( k + 405 < n ) {
        b203[1] = *( m2 + n * (k+405) + j );
      } else {
        b203[1] = 0;
      }
       if( k + 406 < n ) {
         b204[0] = *( m2 + n * (k+406) + j );
       } else {
         b204[0] = 0;
       }
      if( k + 407 < n ) {
        b204[1] = *( m2 + n * (k+407) + j );
      } else {
        b204[1] = 0;
      }
       if( k + 408 < n ) {
         b205[0] = *( m2 + n * (k+408) + j );
       } else {
         b205[0] = 0;
       }
      if( k + 409 < n ) {
        b205[1] = *( m2 + n * (k+409) + j );
      } else {
        b205[1] = 0;
      }
       if( k + 410 < n ) {
         b206[0] = *( m2 + n * (k+410) + j );
       } else {
         b206[0] = 0;
       }
      if( k + 411 < n ) {
        b206[1] = *( m2 + n * (k+411) + j );
      } else {
        b206[1] = 0;
      }
       if( k + 412 < n ) {
         b207[0] = *( m2 + n * (k+412) + j );
       } else {
         b207[0] = 0;
       }
      if( k + 413 < n ) {
        b207[1] = *( m2 + n * (k+413) + j );
      } else {
        b207[1] = 0;
      }
       if( k + 414 < n ) {
         b208[0] = *( m2 + n * (k+414) + j );
       } else {
         b208[0] = 0;
       }
      if( k + 415 < n ) {
        b208[1] = *( m2 + n * (k+415) + j );
      } else {
        b208[1] = 0;
      }
       if( k + 416 < n ) {
         b209[0] = *( m2 + n * (k+416) + j );
       } else {
         b209[0] = 0;
       }
      if( k + 417 < n ) {
        b209[1] = *( m2 + n * (k+417) + j );
      } else {
        b209[1] = 0;
      }
       if( k + 418 < n ) {
         b210[0] = *( m2 + n * (k+418) + j );
       } else {
         b210[0] = 0;
       }
      if( k + 419 < n ) {
        b210[1] = *( m2 + n * (k+419) + j );
      } else {
        b210[1] = 0;
      }
       if( k + 420 < n ) {
         b211[0] = *( m2 + n * (k+420) + j );
       } else {
         b211[0] = 0;
       }
      if( k + 421 < n ) {
        b211[1] = *( m2 + n * (k+421) + j );
      } else {
        b211[1] = 0;
      }
       if( k + 422 < n ) {
         b212[0] = *( m2 + n * (k+422) + j );
       } else {
         b212[0] = 0;
       }
      if( k + 423 < n ) {
        b212[1] = *( m2 + n * (k+423) + j );
      } else {
        b212[1] = 0;
      }
       if( k + 424 < n ) {
         b213[0] = *( m2 + n * (k+424) + j );
       } else {
         b213[0] = 0;
       }
      if( k + 425 < n ) {
        b213[1] = *( m2 + n * (k+425) + j );
      } else {
        b213[1] = 0;
      }
       if( k + 426 < n ) {
         b214[0] = *( m2 + n * (k+426) + j );
       } else {
         b214[0] = 0;
       }
      if( k + 427 < n ) {
        b214[1] = *( m2 + n * (k+427) + j );
      } else {
        b214[1] = 0;
      }
       if( k + 428 < n ) {
         b215[0] = *( m2 + n * (k+428) + j );
       } else {
         b215[0] = 0;
       }
      if( k + 429 < n ) {
        b215[1] = *( m2 + n * (k+429) + j );
      } else {
        b215[1] = 0;
      }
       if( k + 430 < n ) {
         b216[0] = *( m2 + n * (k+430) + j );
       } else {
         b216[0] = 0;
       }
      if( k + 431 < n ) {
        b216[1] = *( m2 + n * (k+431) + j );
      } else {
        b216[1] = 0;
      }
       if( k + 432 < n ) {
         b217[0] = *( m2 + n * (k+432) + j );
       } else {
         b217[0] = 0;
       }
      if( k + 433 < n ) {
        b217[1] = *( m2 + n * (k+433) + j );
      } else {
        b217[1] = 0;
      }
       if( k + 434 < n ) {
         b218[0] = *( m2 + n * (k+434) + j );
       } else {
         b218[0] = 0;
       }
      if( k + 435 < n ) {
        b218[1] = *( m2 + n * (k+435) + j );
      } else {
        b218[1] = 0;
      }
       if( k + 436 < n ) {
         b219[0] = *( m2 + n * (k+436) + j );
       } else {
         b219[0] = 0;
       }
      if( k + 437 < n ) {
        b219[1] = *( m2 + n * (k+437) + j );
      } else {
        b219[1] = 0;
      }
       if( k + 438 < n ) {
         b220[0] = *( m2 + n * (k+438) + j );
       } else {
         b220[0] = 0;
       }
      if( k + 439 < n ) {
        b220[1] = *( m2 + n * (k+439) + j );
      } else {
        b220[1] = 0;
      }
       if( k + 440 < n ) {
         b221[0] = *( m2 + n * (k+440) + j );
       } else {
         b221[0] = 0;
       }
      if( k + 441 < n ) {
        b221[1] = *( m2 + n * (k+441) + j );
      } else {
        b221[1] = 0;
      }
       if( k + 442 < n ) {
         b222[0] = *( m2 + n * (k+442) + j );
       } else {
         b222[0] = 0;
       }
      if( k + 443 < n ) {
        b222[1] = *( m2 + n * (k+443) + j );
      } else {
        b222[1] = 0;
      }
       if( k + 444 < n ) {
         b223[0] = *( m2 + n * (k+444) + j );
       } else {
         b223[0] = 0;
       }
      if( k + 445 < n ) {
        b223[1] = *( m2 + n * (k+445) + j );
      } else {
        b223[1] = 0;
      }
       if( k + 446 < n ) {
         b224[0] = *( m2 + n * (k+446) + j );
       } else {
         b224[0] = 0;
       }
      if( k + 447 < n ) {
        b224[1] = *( m2 + n * (k+447) + j );
      } else {
        b224[1] = 0;
      }
       if( k + 448 < n ) {
         b225[0] = *( m2 + n * (k+448) + j );
       } else {
         b225[0] = 0;
       }
      if( k + 449 < n ) {
        b225[1] = *( m2 + n * (k+449) + j );
      } else {
        b225[1] = 0;
      }
       if( k + 450 < n ) {
         b226[0] = *( m2 + n * (k+450) + j );
       } else {
         b226[0] = 0;
       }
      if( k + 451 < n ) {
        b226[1] = *( m2 + n * (k+451) + j );
      } else {
        b226[1] = 0;
      }
       if( k + 452 < n ) {
         b227[0] = *( m2 + n * (k+452) + j );
       } else {
         b227[0] = 0;
       }
      if( k + 453 < n ) {
        b227[1] = *( m2 + n * (k+453) + j );
      } else {
        b227[1] = 0;
      }
       if( k + 454 < n ) {
         b228[0] = *( m2 + n * (k+454) + j );
       } else {
         b228[0] = 0;
       }
      if( k + 455 < n ) {
        b228[1] = *( m2 + n * (k+455) + j );
      } else {
        b228[1] = 0;
      }
       if( k + 456 < n ) {
         b229[0] = *( m2 + n * (k+456) + j );
       } else {
         b229[0] = 0;
       }
      if( k + 457 < n ) {
        b229[1] = *( m2 + n * (k+457) + j );
      } else {
        b229[1] = 0;
      }
       if( k + 458 < n ) {
         b230[0] = *( m2 + n * (k+458) + j );
       } else {
         b230[0] = 0;
       }
      if( k + 459 < n ) {
        b230[1] = *( m2 + n * (k+459) + j );
      } else {
        b230[1] = 0;
      }
       if( k + 460 < n ) {
         b231[0] = *( m2 + n * (k+460) + j );
       } else {
         b231[0] = 0;
       }
      if( k + 461 < n ) {
        b231[1] = *( m2 + n * (k+461) + j );
      } else {
        b231[1] = 0;
      }
       if( k + 462 < n ) {
         b232[0] = *( m2 + n * (k+462) + j );
       } else {
         b232[0] = 0;
       }
      if( k + 463 < n ) {
        b232[1] = *( m2 + n * (k+463) + j );
      } else {
        b232[1] = 0;
      }
       if( k + 464 < n ) {
         b233[0] = *( m2 + n * (k+464) + j );
       } else {
         b233[0] = 0;
       }
      if( k + 465 < n ) {
        b233[1] = *( m2 + n * (k+465) + j );
      } else {
        b233[1] = 0;
      }
       if( k + 466 < n ) {
         b234[0] = *( m2 + n * (k+466) + j );
       } else {
         b234[0] = 0;
       }
      if( k + 467 < n ) {
        b234[1] = *( m2 + n * (k+467) + j );
      } else {
        b234[1] = 0;
      }
       if( k + 468 < n ) {
         b235[0] = *( m2 + n * (k+468) + j );
       } else {
         b235[0] = 0;
       }
      if( k + 469 < n ) {
        b235[1] = *( m2 + n * (k+469) + j );
      } else {
        b235[1] = 0;
      }
       if( k + 470 < n ) {
         b236[0] = *( m2 + n * (k+470) + j );
       } else {
         b236[0] = 0;
       }
      if( k + 471 < n ) {
        b236[1] = *( m2 + n * (k+471) + j );
      } else {
        b236[1] = 0;
      }
       if( k + 472 < n ) {
         b237[0] = *( m2 + n * (k+472) + j );
       } else {
         b237[0] = 0;
       }
      if( k + 473 < n ) {
        b237[1] = *( m2 + n * (k+473) + j );
      } else {
        b237[1] = 0;
      }
       if( k + 474 < n ) {
         b238[0] = *( m2 + n * (k+474) + j );
       } else {
         b238[0] = 0;
       }
      if( k + 475 < n ) {
        b238[1] = *( m2 + n * (k+475) + j );
      } else {
        b238[1] = 0;
      }
       if( k + 476 < n ) {
         b239[0] = *( m2 + n * (k+476) + j );
       } else {
         b239[0] = 0;
       }
      if( k + 477 < n ) {
        b239[1] = *( m2 + n * (k+477) + j );
      } else {
        b239[1] = 0;
      }
       if( k + 478 < n ) {
         b240[0] = *( m2 + n * (k+478) + j );
       } else {
         b240[0] = 0;
       }
      if( k + 479 < n ) {
        b240[1] = *( m2 + n * (k+479) + j );
      } else {
        b240[1] = 0;
      }
       if( k + 480 < n ) {
         b241[0] = *( m2 + n * (k+480) + j );
       } else {
         b241[0] = 0;
       }
      if( k + 481 < n ) {
        b241[1] = *( m2 + n * (k+481) + j );
      } else {
        b241[1] = 0;
      }
       if( k + 482 < n ) {
         b242[0] = *( m2 + n * (k+482) + j );
       } else {
         b242[0] = 0;
       }
      if( k + 483 < n ) {
        b242[1] = *( m2 + n * (k+483) + j );
      } else {
        b242[1] = 0;
      }
       if( k + 484 < n ) {
         b243[0] = *( m2 + n * (k+484) + j );
       } else {
         b243[0] = 0;
       }
      if( k + 485 < n ) {
        b243[1] = *( m2 + n * (k+485) + j );
      } else {
        b243[1] = 0;
      }
       if( k + 486 < n ) {
         b244[0] = *( m2 + n * (k+486) + j );
       } else {
         b244[0] = 0;
       }
      if( k + 487 < n ) {
        b244[1] = *( m2 + n * (k+487) + j );
      } else {
        b244[1] = 0;
      }
       if( k + 488 < n ) {
         b245[0] = *( m2 + n * (k+488) + j );
       } else {
         b245[0] = 0;
       }
      if( k + 489 < n ) {
        b245[1] = *( m2 + n * (k+489) + j );
      } else {
        b245[1] = 0;
      }
       if( k + 490 < n ) {
         b246[0] = *( m2 + n * (k+490) + j );
       } else {
         b246[0] = 0;
       }
      if( k + 491 < n ) {
        b246[1] = *( m2 + n * (k+491) + j );
      } else {
        b246[1] = 0;
      }
       if( k + 492 < n ) {
         b247[0] = *( m2 + n * (k+492) + j );
       } else {
         b247[0] = 0;
       }
      if( k + 493 < n ) {
        b247[1] = *( m2 + n * (k+493) + j );
      } else {
        b247[1] = 0;
      }
       if( k + 494 < n ) {
         b248[0] = *( m2 + n * (k+494) + j );
       } else {
         b248[0] = 0;
       }
      if( k + 495 < n ) {
        b248[1] = *( m2 + n * (k+495) + j );
      } else {
        b248[1] = 0;
      }
       if( k + 496 < n ) {
         b249[0] = *( m2 + n * (k+496) + j );
       } else {
         b249[0] = 0;
       }
      if( k + 497 < n ) {
        b249[1] = *( m2 + n * (k+497) + j );
      } else {
        b249[1] = 0;
      }
       if( k + 498 < n ) {
         b250[0] = *( m2 + n * (k+498) + j );
       } else {
         b250[0] = 0;
       }
      if( k + 499 < n ) {
        b250[1] = *( m2 + n * (k+499) + j );
      } else {
        b250[1] = 0;
      }
       if( k + 500 < n ) {
         b251[0] = *( m2 + n * (k+500) + j );
       } else {
         b251[0] = 0;
       }
      if( k + 501 < n ) {
        b251[1] = *( m2 + n * (k+501) + j );
      } else {
        b251[1] = 0;
      }
       if( k + 502 < n ) {
         b252[0] = *( m2 + n * (k+502) + j );
       } else {
         b252[0] = 0;
       }
      if( k + 503 < n ) {
        b252[1] = *( m2 + n * (k+503) + j );
      } else {
        b252[1] = 0;
      }
       if( k + 504 < n ) {
         b253[0] = *( m2 + n * (k+504) + j );
       } else {
         b253[0] = 0;
       }
      if( k + 505 < n ) {
        b253[1] = *( m2 + n * (k+505) + j );
      } else {
        b253[1] = 0;
      }
       if( k + 506 < n ) {
         b254[0] = *( m2 + n * (k+506) + j );
       } else {
         b254[0] = 0;
       }
      if( k + 507 < n ) {
        b254[1] = *( m2 + n * (k+507) + j );
      } else {
        b254[1] = 0;
      }
       if( k + 508 < n ) {
         b255[0] = *( m2 + n * (k+508) + j );
       } else {
         b255[0] = 0;
       }
      if( k + 509 < n ) {
        b255[1] = *( m2 + n * (k+509) + j );
      } else {
        b255[1] = 0;
      }
       if( k + 510 < n ) {
         b256[0] = *( m2 + n * (k+510) + j );
       } else {
         b256[0] = 0;
       }
      if( k + 511 < n ) {
        b256[1] = *( m2 + n * (k+511) + j );
      } else {
        b256[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t13 = _mm_load_pd( b7 );
       t15 = _mm_load_pd( b8 );
       t17 = _mm_load_pd( b9 );
       t19 = _mm_load_pd( b10 );
       t21 = _mm_load_pd( b11 );
       t23 = _mm_load_pd( b12 );
       t25 = _mm_load_pd( b13 );
       t27 = _mm_load_pd( b14 );
       t29 = _mm_load_pd( b15 );
       t31 = _mm_load_pd( b16 );
       t33 = _mm_load_pd( b17 );
       t35 = _mm_load_pd( b18 );
       t37 = _mm_load_pd( b19 );
       t39 = _mm_load_pd( b20 );
       t41 = _mm_load_pd( b21 );
       t43 = _mm_load_pd( b22 );
       t45 = _mm_load_pd( b23 );
       t47 = _mm_load_pd( b24 );
       t49 = _mm_load_pd( b25 );
       t51 = _mm_load_pd( b26 );
       t53 = _mm_load_pd( b27 );
       t55 = _mm_load_pd( b28 );
       t57 = _mm_load_pd( b29 );
       t59 = _mm_load_pd( b30 );
       t61 = _mm_load_pd( b31 );
       t63 = _mm_load_pd( b32 );
       t65 = _mm_load_pd( b33 );
       t67 = _mm_load_pd( b34 );
       t69 = _mm_load_pd( b35 );
       t71 = _mm_load_pd( b36 );
       t73 = _mm_load_pd( b37 );
       t75 = _mm_load_pd( b38 );
       t77 = _mm_load_pd( b39 );
       t79 = _mm_load_pd( b40 );
       t81 = _mm_load_pd( b41 );
       t83 = _mm_load_pd( b42 );
       t85 = _mm_load_pd( b43 );
       t87 = _mm_load_pd( b44 );
       t89 = _mm_load_pd( b45 );
       t91 = _mm_load_pd( b46 );
       t93 = _mm_load_pd( b47 );
       t95 = _mm_load_pd( b48 );
       t97 = _mm_load_pd( b49 );
       t99 = _mm_load_pd( b50 );
       t101 = _mm_load_pd( b51 );
       t103 = _mm_load_pd( b52 );
       t105 = _mm_load_pd( b53 );
       t107 = _mm_load_pd( b54 );
       t109 = _mm_load_pd( b55 );
       t111 = _mm_load_pd( b56 );
       t113 = _mm_load_pd( b57 );
       t115 = _mm_load_pd( b58 );
       t117 = _mm_load_pd( b59 );
       t119 = _mm_load_pd( b60 );
       t121 = _mm_load_pd( b61 );
       t123 = _mm_load_pd( b62 );
       t125 = _mm_load_pd( b63 );
       t127 = _mm_load_pd( b64 );
       t129 = _mm_load_pd( b65 );
       t131 = _mm_load_pd( b66 );
       t133 = _mm_load_pd( b67 );
       t135 = _mm_load_pd( b68 );
       t137 = _mm_load_pd( b69 );
       t139 = _mm_load_pd( b70 );
       t141 = _mm_load_pd( b71 );
       t143 = _mm_load_pd( b72 );
       t145 = _mm_load_pd( b73 );
       t147 = _mm_load_pd( b74 );
       t149 = _mm_load_pd( b75 );
       t151 = _mm_load_pd( b76 );
       t153 = _mm_load_pd( b77 );
       t155 = _mm_load_pd( b78 );
       t157 = _mm_load_pd( b79 );
       t159 = _mm_load_pd( b80 );
       t161 = _mm_load_pd( b81 );
       t163 = _mm_load_pd( b82 );
       t165 = _mm_load_pd( b83 );
       t167 = _mm_load_pd( b84 );
       t169 = _mm_load_pd( b85 );
       t171 = _mm_load_pd( b86 );
       t173 = _mm_load_pd( b87 );
       t175 = _mm_load_pd( b88 );
       t177 = _mm_load_pd( b89 );
       t179 = _mm_load_pd( b90 );
       t181 = _mm_load_pd( b91 );
       t183 = _mm_load_pd( b92 );
       t185 = _mm_load_pd( b93 );
       t187 = _mm_load_pd( b94 );
       t189 = _mm_load_pd( b95 );
       t191 = _mm_load_pd( b96 );
       t193 = _mm_load_pd( b97 );
       t195 = _mm_load_pd( b98 );
       t197 = _mm_load_pd( b99 );
       t199 = _mm_load_pd( b100 );
       t201 = _mm_load_pd( b101 );
       t203 = _mm_load_pd( b102 );
       t205 = _mm_load_pd( b103 );
       t207 = _mm_load_pd( b104 );
       t209 = _mm_load_pd( b105 );
       t211 = _mm_load_pd( b106 );
       t213 = _mm_load_pd( b107 );
       t215 = _mm_load_pd( b108 );
       t217 = _mm_load_pd( b109 );
       t219 = _mm_load_pd( b110 );
       t221 = _mm_load_pd( b111 );
       t223 = _mm_load_pd( b112 );
       t225 = _mm_load_pd( b113 );
       t227 = _mm_load_pd( b114 );
       t229 = _mm_load_pd( b115 );
       t231 = _mm_load_pd( b116 );
       t233 = _mm_load_pd( b117 );
       t235 = _mm_load_pd( b118 );
       t237 = _mm_load_pd( b119 );
       t239 = _mm_load_pd( b120 );
       t241 = _mm_load_pd( b121 );
       t243 = _mm_load_pd( b122 );
       t245 = _mm_load_pd( b123 );
       t247 = _mm_load_pd( b124 );
       t249 = _mm_load_pd( b125 );
       t251 = _mm_load_pd( b126 );
       t253 = _mm_load_pd( b127 );
       t255 = _mm_load_pd( b128 );
       t257 = _mm_load_pd( b129 );
       t259 = _mm_load_pd( b130 );
       t261 = _mm_load_pd( b131 );
       t263 = _mm_load_pd( b132 );
       t265 = _mm_load_pd( b133 );
       t267 = _mm_load_pd( b134 );
       t269 = _mm_load_pd( b135 );
       t271 = _mm_load_pd( b136 );
       t273 = _mm_load_pd( b137 );
       t275 = _mm_load_pd( b138 );
       t277 = _mm_load_pd( b139 );
       t279 = _mm_load_pd( b140 );
       t281 = _mm_load_pd( b141 );
       t283 = _mm_load_pd( b142 );
       t285 = _mm_load_pd( b143 );
       t287 = _mm_load_pd( b144 );
       t289 = _mm_load_pd( b145 );
       t291 = _mm_load_pd( b146 );
       t293 = _mm_load_pd( b147 );
       t295 = _mm_load_pd( b148 );
       t297 = _mm_load_pd( b149 );
       t299 = _mm_load_pd( b150 );
       t301 = _mm_load_pd( b151 );
       t303 = _mm_load_pd( b152 );
       t305 = _mm_load_pd( b153 );
       t307 = _mm_load_pd( b154 );
       t309 = _mm_load_pd( b155 );
       t311 = _mm_load_pd( b156 );
       t313 = _mm_load_pd( b157 );
       t315 = _mm_load_pd( b158 );
       t317 = _mm_load_pd( b159 );
       t319 = _mm_load_pd( b160 );
       t321 = _mm_load_pd( b161 );
       t323 = _mm_load_pd( b162 );
       t325 = _mm_load_pd( b163 );
       t327 = _mm_load_pd( b164 );
       t329 = _mm_load_pd( b165 );
       t331 = _mm_load_pd( b166 );
       t333 = _mm_load_pd( b167 );
       t335 = _mm_load_pd( b168 );
       t337 = _mm_load_pd( b169 );
       t339 = _mm_load_pd( b170 );
       t341 = _mm_load_pd( b171 );
       t343 = _mm_load_pd( b172 );
       t345 = _mm_load_pd( b173 );
       t347 = _mm_load_pd( b174 );
       t349 = _mm_load_pd( b175 );
       t351 = _mm_load_pd( b176 );
       t353 = _mm_load_pd( b177 );
       t355 = _mm_load_pd( b178 );
       t357 = _mm_load_pd( b179 );
       t359 = _mm_load_pd( b180 );
       t361 = _mm_load_pd( b181 );
       t363 = _mm_load_pd( b182 );
       t365 = _mm_load_pd( b183 );
       t367 = _mm_load_pd( b184 );
       t369 = _mm_load_pd( b185 );
       t371 = _mm_load_pd( b186 );
       t373 = _mm_load_pd( b187 );
       t375 = _mm_load_pd( b188 );
       t377 = _mm_load_pd( b189 );
       t379 = _mm_load_pd( b190 );
       t381 = _mm_load_pd( b191 );
       t383 = _mm_load_pd( b192 );
       t385 = _mm_load_pd( b193 );
       t387 = _mm_load_pd( b194 );
       t389 = _mm_load_pd( b195 );
       t391 = _mm_load_pd( b196 );
       t393 = _mm_load_pd( b197 );
       t395 = _mm_load_pd( b198 );
       t397 = _mm_load_pd( b199 );
       t399 = _mm_load_pd( b200 );
       t401 = _mm_load_pd( b201 );
       t403 = _mm_load_pd( b202 );
       t405 = _mm_load_pd( b203 );
       t407 = _mm_load_pd( b204 );
       t409 = _mm_load_pd( b205 );
       t411 = _mm_load_pd( b206 );
       t413 = _mm_load_pd( b207 );
       t415 = _mm_load_pd( b208 );
       t417 = _mm_load_pd( b209 );
       t419 = _mm_load_pd( b210 );
       t421 = _mm_load_pd( b211 );
       t423 = _mm_load_pd( b212 );
       t425 = _mm_load_pd( b213 );
       t427 = _mm_load_pd( b214 );
       t429 = _mm_load_pd( b215 );
       t431 = _mm_load_pd( b216 );
       t433 = _mm_load_pd( b217 );
       t435 = _mm_load_pd( b218 );
       t437 = _mm_load_pd( b219 );
       t439 = _mm_load_pd( b220 );
       t441 = _mm_load_pd( b221 );
       t443 = _mm_load_pd( b222 );
       t445 = _mm_load_pd( b223 );
       t447 = _mm_load_pd( b224 );
       t449 = _mm_load_pd( b225 );
       t451 = _mm_load_pd( b226 );
       t453 = _mm_load_pd( b227 );
       t455 = _mm_load_pd( b228 );
       t457 = _mm_load_pd( b229 );
       t459 = _mm_load_pd( b230 );
       t461 = _mm_load_pd( b231 );
       t463 = _mm_load_pd( b232 );
       t465 = _mm_load_pd( b233 );
       t467 = _mm_load_pd( b234 );
       t469 = _mm_load_pd( b235 );
       t471 = _mm_load_pd( b236 );
       t473 = _mm_load_pd( b237 );
       t475 = _mm_load_pd( b238 );
       t477 = _mm_load_pd( b239 );
       t479 = _mm_load_pd( b240 );
       t481 = _mm_load_pd( b241 );
       t483 = _mm_load_pd( b242 );
       t485 = _mm_load_pd( b243 );
       t487 = _mm_load_pd( b244 );
       t489 = _mm_load_pd( b245 );
       t491 = _mm_load_pd( b246 );
       t493 = _mm_load_pd( b247 );
       t495 = _mm_load_pd( b248 );
       t497 = _mm_load_pd( b249 );
       t499 = _mm_load_pd( b250 );
       t501 = _mm_load_pd( b251 );
       t503 = _mm_load_pd( b252 );
       t505 = _mm_load_pd( b253 );
       t507 = _mm_load_pd( b254 );
       t509 = _mm_load_pd( b255 );
       t511 = _mm_load_pd( b256 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );
       t13 = _mm_dp_pd( t12, t13, 0xff );
       t15 = _mm_dp_pd( t14, t15, 0xff );
       t17 = _mm_dp_pd( t16, t17, 0xff );
       t19 = _mm_dp_pd( t18, t19, 0xff );
       t21 = _mm_dp_pd( t20, t21, 0xff );
       t23 = _mm_dp_pd( t22, t23, 0xff );
       t25 = _mm_dp_pd( t24, t25, 0xff );
       t27 = _mm_dp_pd( t26, t27, 0xff );
       t29 = _mm_dp_pd( t28, t29, 0xff );
       t31 = _mm_dp_pd( t30, t31, 0xff );
       t33 = _mm_dp_pd( t32, t33, 0xff );
       t35 = _mm_dp_pd( t34, t35, 0xff );
       t37 = _mm_dp_pd( t36, t37, 0xff );
       t39 = _mm_dp_pd( t38, t39, 0xff );
       t41 = _mm_dp_pd( t40, t41, 0xff );
       t43 = _mm_dp_pd( t42, t43, 0xff );
       t45 = _mm_dp_pd( t44, t45, 0xff );
       t47 = _mm_dp_pd( t46, t47, 0xff );
       t49 = _mm_dp_pd( t48, t49, 0xff );
       t51 = _mm_dp_pd( t50, t51, 0xff );
       t53 = _mm_dp_pd( t52, t53, 0xff );
       t55 = _mm_dp_pd( t54, t55, 0xff );
       t57 = _mm_dp_pd( t56, t57, 0xff );
       t59 = _mm_dp_pd( t58, t59, 0xff );
       t61 = _mm_dp_pd( t60, t61, 0xff );
       t63 = _mm_dp_pd( t62, t63, 0xff );
       t65 = _mm_dp_pd( t64, t65, 0xff );
       t67 = _mm_dp_pd( t66, t67, 0xff );
       t69 = _mm_dp_pd( t68, t69, 0xff );
       t71 = _mm_dp_pd( t70, t71, 0xff );
       t73 = _mm_dp_pd( t72, t73, 0xff );
       t75 = _mm_dp_pd( t74, t75, 0xff );
       t77 = _mm_dp_pd( t76, t77, 0xff );
       t79 = _mm_dp_pd( t78, t79, 0xff );
       t81 = _mm_dp_pd( t80, t81, 0xff );
       t83 = _mm_dp_pd( t82, t83, 0xff );
       t85 = _mm_dp_pd( t84, t85, 0xff );
       t87 = _mm_dp_pd( t86, t87, 0xff );
       t89 = _mm_dp_pd( t88, t89, 0xff );
       t91 = _mm_dp_pd( t90, t91, 0xff );
       t93 = _mm_dp_pd( t92, t93, 0xff );
       t95 = _mm_dp_pd( t94, t95, 0xff );
       t97 = _mm_dp_pd( t96, t97, 0xff );
       t99 = _mm_dp_pd( t98, t99, 0xff );
       t101 = _mm_dp_pd( t100, t101, 0xff );
       t103 = _mm_dp_pd( t102, t103, 0xff );
       t105 = _mm_dp_pd( t104, t105, 0xff );
       t107 = _mm_dp_pd( t106, t107, 0xff );
       t109 = _mm_dp_pd( t108, t109, 0xff );
       t111 = _mm_dp_pd( t110, t111, 0xff );
       t113 = _mm_dp_pd( t112, t113, 0xff );
       t115 = _mm_dp_pd( t114, t115, 0xff );
       t117 = _mm_dp_pd( t116, t117, 0xff );
       t119 = _mm_dp_pd( t118, t119, 0xff );
       t121 = _mm_dp_pd( t120, t121, 0xff );
       t123 = _mm_dp_pd( t122, t123, 0xff );
       t125 = _mm_dp_pd( t124, t125, 0xff );
       t127 = _mm_dp_pd( t126, t127, 0xff );
       t129 = _mm_dp_pd( t128, t129, 0xff );
       t131 = _mm_dp_pd( t130, t131, 0xff );
       t133 = _mm_dp_pd( t132, t133, 0xff );
       t135 = _mm_dp_pd( t134, t135, 0xff );
       t137 = _mm_dp_pd( t136, t137, 0xff );
       t139 = _mm_dp_pd( t138, t139, 0xff );
       t141 = _mm_dp_pd( t140, t141, 0xff );
       t143 = _mm_dp_pd( t142, t143, 0xff );
       t145 = _mm_dp_pd( t144, t145, 0xff );
       t147 = _mm_dp_pd( t146, t147, 0xff );
       t149 = _mm_dp_pd( t148, t149, 0xff );
       t151 = _mm_dp_pd( t150, t151, 0xff );
       t153 = _mm_dp_pd( t152, t153, 0xff );
       t155 = _mm_dp_pd( t154, t155, 0xff );
       t157 = _mm_dp_pd( t156, t157, 0xff );
       t159 = _mm_dp_pd( t158, t159, 0xff );
       t161 = _mm_dp_pd( t160, t161, 0xff );
       t163 = _mm_dp_pd( t162, t163, 0xff );
       t165 = _mm_dp_pd( t164, t165, 0xff );
       t167 = _mm_dp_pd( t166, t167, 0xff );
       t169 = _mm_dp_pd( t168, t169, 0xff );
       t171 = _mm_dp_pd( t170, t171, 0xff );
       t173 = _mm_dp_pd( t172, t173, 0xff );
       t175 = _mm_dp_pd( t174, t175, 0xff );
       t177 = _mm_dp_pd( t176, t177, 0xff );
       t179 = _mm_dp_pd( t178, t179, 0xff );
       t181 = _mm_dp_pd( t180, t181, 0xff );
       t183 = _mm_dp_pd( t182, t183, 0xff );
       t185 = _mm_dp_pd( t184, t185, 0xff );
       t187 = _mm_dp_pd( t186, t187, 0xff );
       t189 = _mm_dp_pd( t188, t189, 0xff );
       t191 = _mm_dp_pd( t190, t191, 0xff );
       t193 = _mm_dp_pd( t192, t193, 0xff );
       t195 = _mm_dp_pd( t194, t195, 0xff );
       t197 = _mm_dp_pd( t196, t197, 0xff );
       t199 = _mm_dp_pd( t198, t199, 0xff );
       t201 = _mm_dp_pd( t200, t201, 0xff );
       t203 = _mm_dp_pd( t202, t203, 0xff );
       t205 = _mm_dp_pd( t204, t205, 0xff );
       t207 = _mm_dp_pd( t206, t207, 0xff );
       t209 = _mm_dp_pd( t208, t209, 0xff );
       t211 = _mm_dp_pd( t210, t211, 0xff );
       t213 = _mm_dp_pd( t212, t213, 0xff );
       t215 = _mm_dp_pd( t214, t215, 0xff );
       t217 = _mm_dp_pd( t216, t217, 0xff );
       t219 = _mm_dp_pd( t218, t219, 0xff );
       t221 = _mm_dp_pd( t220, t221, 0xff );
       t223 = _mm_dp_pd( t222, t223, 0xff );
       t225 = _mm_dp_pd( t224, t225, 0xff );
       t227 = _mm_dp_pd( t226, t227, 0xff );
       t229 = _mm_dp_pd( t228, t229, 0xff );
       t231 = _mm_dp_pd( t230, t231, 0xff );
       t233 = _mm_dp_pd( t232, t233, 0xff );
       t235 = _mm_dp_pd( t234, t235, 0xff );
       t237 = _mm_dp_pd( t236, t237, 0xff );
       t239 = _mm_dp_pd( t238, t239, 0xff );
       t241 = _mm_dp_pd( t240, t241, 0xff );
       t243 = _mm_dp_pd( t242, t243, 0xff );
       t245 = _mm_dp_pd( t244, t245, 0xff );
       t247 = _mm_dp_pd( t246, t247, 0xff );
       t249 = _mm_dp_pd( t248, t249, 0xff );
       t251 = _mm_dp_pd( t250, t251, 0xff );
       t253 = _mm_dp_pd( t252, t253, 0xff );
       t255 = _mm_dp_pd( t254, t255, 0xff );
       t257 = _mm_dp_pd( t256, t257, 0xff );
       t259 = _mm_dp_pd( t258, t259, 0xff );
       t261 = _mm_dp_pd( t260, t261, 0xff );
       t263 = _mm_dp_pd( t262, t263, 0xff );
       t265 = _mm_dp_pd( t264, t265, 0xff );
       t267 = _mm_dp_pd( t266, t267, 0xff );
       t269 = _mm_dp_pd( t268, t269, 0xff );
       t271 = _mm_dp_pd( t270, t271, 0xff );
       t273 = _mm_dp_pd( t272, t273, 0xff );
       t275 = _mm_dp_pd( t274, t275, 0xff );
       t277 = _mm_dp_pd( t276, t277, 0xff );
       t279 = _mm_dp_pd( t278, t279, 0xff );
       t281 = _mm_dp_pd( t280, t281, 0xff );
       t283 = _mm_dp_pd( t282, t283, 0xff );
       t285 = _mm_dp_pd( t284, t285, 0xff );
       t287 = _mm_dp_pd( t286, t287, 0xff );
       t289 = _mm_dp_pd( t288, t289, 0xff );
       t291 = _mm_dp_pd( t290, t291, 0xff );
       t293 = _mm_dp_pd( t292, t293, 0xff );
       t295 = _mm_dp_pd( t294, t295, 0xff );
       t297 = _mm_dp_pd( t296, t297, 0xff );
       t299 = _mm_dp_pd( t298, t299, 0xff );
       t301 = _mm_dp_pd( t300, t301, 0xff );
       t303 = _mm_dp_pd( t302, t303, 0xff );
       t305 = _mm_dp_pd( t304, t305, 0xff );
       t307 = _mm_dp_pd( t306, t307, 0xff );
       t309 = _mm_dp_pd( t308, t309, 0xff );
       t311 = _mm_dp_pd( t310, t311, 0xff );
       t313 = _mm_dp_pd( t312, t313, 0xff );
       t315 = _mm_dp_pd( t314, t315, 0xff );
       t317 = _mm_dp_pd( t316, t317, 0xff );
       t319 = _mm_dp_pd( t318, t319, 0xff );
       t321 = _mm_dp_pd( t320, t321, 0xff );
       t323 = _mm_dp_pd( t322, t323, 0xff );
       t325 = _mm_dp_pd( t324, t325, 0xff );
       t327 = _mm_dp_pd( t326, t327, 0xff );
       t329 = _mm_dp_pd( t328, t329, 0xff );
       t331 = _mm_dp_pd( t330, t331, 0xff );
       t333 = _mm_dp_pd( t332, t333, 0xff );
       t335 = _mm_dp_pd( t334, t335, 0xff );
       t337 = _mm_dp_pd( t336, t337, 0xff );
       t339 = _mm_dp_pd( t338, t339, 0xff );
       t341 = _mm_dp_pd( t340, t341, 0xff );
       t343 = _mm_dp_pd( t342, t343, 0xff );
       t345 = _mm_dp_pd( t344, t345, 0xff );
       t347 = _mm_dp_pd( t346, t347, 0xff );
       t349 = _mm_dp_pd( t348, t349, 0xff );
       t351 = _mm_dp_pd( t350, t351, 0xff );
       t353 = _mm_dp_pd( t352, t353, 0xff );
       t355 = _mm_dp_pd( t354, t355, 0xff );
       t357 = _mm_dp_pd( t356, t357, 0xff );
       t359 = _mm_dp_pd( t358, t359, 0xff );
       t361 = _mm_dp_pd( t360, t361, 0xff );
       t363 = _mm_dp_pd( t362, t363, 0xff );
       t365 = _mm_dp_pd( t364, t365, 0xff );
       t367 = _mm_dp_pd( t366, t367, 0xff );
       t369 = _mm_dp_pd( t368, t369, 0xff );
       t371 = _mm_dp_pd( t370, t371, 0xff );
       t373 = _mm_dp_pd( t372, t373, 0xff );
       t375 = _mm_dp_pd( t374, t375, 0xff );
       t377 = _mm_dp_pd( t376, t377, 0xff );
       t379 = _mm_dp_pd( t378, t379, 0xff );
       t381 = _mm_dp_pd( t380, t381, 0xff );
       t383 = _mm_dp_pd( t382, t383, 0xff );
       t385 = _mm_dp_pd( t384, t385, 0xff );
       t387 = _mm_dp_pd( t386, t387, 0xff );
       t389 = _mm_dp_pd( t388, t389, 0xff );
       t391 = _mm_dp_pd( t390, t391, 0xff );
       t393 = _mm_dp_pd( t392, t393, 0xff );
       t395 = _mm_dp_pd( t394, t395, 0xff );
       t397 = _mm_dp_pd( t396, t397, 0xff );
       t399 = _mm_dp_pd( t398, t399, 0xff );
       t401 = _mm_dp_pd( t400, t401, 0xff );
       t403 = _mm_dp_pd( t402, t403, 0xff );
       t405 = _mm_dp_pd( t404, t405, 0xff );
       t407 = _mm_dp_pd( t406, t407, 0xff );
       t409 = _mm_dp_pd( t408, t409, 0xff );
       t411 = _mm_dp_pd( t410, t411, 0xff );
       t413 = _mm_dp_pd( t412, t413, 0xff );
       t415 = _mm_dp_pd( t414, t415, 0xff );
       t417 = _mm_dp_pd( t416, t417, 0xff );
       t419 = _mm_dp_pd( t418, t419, 0xff );
       t421 = _mm_dp_pd( t420, t421, 0xff );
       t423 = _mm_dp_pd( t422, t423, 0xff );
       t425 = _mm_dp_pd( t424, t425, 0xff );
       t427 = _mm_dp_pd( t426, t427, 0xff );
       t429 = _mm_dp_pd( t428, t429, 0xff );
       t431 = _mm_dp_pd( t430, t431, 0xff );
       t433 = _mm_dp_pd( t432, t433, 0xff );
       t435 = _mm_dp_pd( t434, t435, 0xff );
       t437 = _mm_dp_pd( t436, t437, 0xff );
       t439 = _mm_dp_pd( t438, t439, 0xff );
       t441 = _mm_dp_pd( t440, t441, 0xff );
       t443 = _mm_dp_pd( t442, t443, 0xff );
       t445 = _mm_dp_pd( t444, t445, 0xff );
       t447 = _mm_dp_pd( t446, t447, 0xff );
       t449 = _mm_dp_pd( t448, t449, 0xff );
       t451 = _mm_dp_pd( t450, t451, 0xff );
       t453 = _mm_dp_pd( t452, t453, 0xff );
       t455 = _mm_dp_pd( t454, t455, 0xff );
       t457 = _mm_dp_pd( t456, t457, 0xff );
       t459 = _mm_dp_pd( t458, t459, 0xff );
       t461 = _mm_dp_pd( t460, t461, 0xff );
       t463 = _mm_dp_pd( t462, t463, 0xff );
       t465 = _mm_dp_pd( t464, t465, 0xff );
       t467 = _mm_dp_pd( t466, t467, 0xff );
       t469 = _mm_dp_pd( t468, t469, 0xff );
       t471 = _mm_dp_pd( t470, t471, 0xff );
       t473 = _mm_dp_pd( t472, t473, 0xff );
       t475 = _mm_dp_pd( t474, t475, 0xff );
       t477 = _mm_dp_pd( t476, t477, 0xff );
       t479 = _mm_dp_pd( t478, t479, 0xff );
       t481 = _mm_dp_pd( t480, t481, 0xff );
       t483 = _mm_dp_pd( t482, t483, 0xff );
       t485 = _mm_dp_pd( t484, t485, 0xff );
       t487 = _mm_dp_pd( t486, t487, 0xff );
       t489 = _mm_dp_pd( t488, t489, 0xff );
       t491 = _mm_dp_pd( t490, t491, 0xff );
       t493 = _mm_dp_pd( t492, t493, 0xff );
       t495 = _mm_dp_pd( t494, t495, 0xff );
       t497 = _mm_dp_pd( t496, t497, 0xff );
       t499 = _mm_dp_pd( t498, t499, 0xff );
       t501 = _mm_dp_pd( t500, t501, 0xff );
       t503 = _mm_dp_pd( t502, t503, 0xff );
       t505 = _mm_dp_pd( t504, t505, 0xff );
       t507 = _mm_dp_pd( t506, t507, 0xff );
       t509 = _mm_dp_pd( t508, t509, 0xff );
       t511 = _mm_dp_pd( t510, t511, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t13 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t15 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t17 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t19 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t21 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t23 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t25 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t27 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t29 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t31 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t33 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t35 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t37 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t39 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t41 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t43 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t45 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t47 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t49 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t51 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t53 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t55 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t57 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t59 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t61 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t63 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t65 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t67 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t69 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t71 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t73 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t75 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t77 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t79 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t81 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t83 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t85 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t87 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t89 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t91 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t93 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t95 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t97 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t99 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t101 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t103 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t105 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t107 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t109 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t111 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t113 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t115 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t117 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t119 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t121 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t123 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t125 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t127 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t129 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t131 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t133 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t135 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t137 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t139 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t141 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t143 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t145 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t147 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t149 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t151 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t153 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t155 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t157 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t159 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t161 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t163 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t165 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t167 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t169 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t171 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t173 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t175 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t177 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t179 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t181 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t183 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t185 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t187 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t189 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t191 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t193 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t195 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t197 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t199 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t201 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t203 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t205 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t207 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t209 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t211 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t213 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t215 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t217 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t219 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t221 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t223 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t225 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t227 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t229 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t231 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t233 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t235 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t237 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t239 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t241 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t243 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t245 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t247 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t249 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t251 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t253 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t255 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t257 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t259 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t261 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t263 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t265 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t267 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t269 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t271 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t273 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t275 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t277 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t279 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t281 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t283 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t285 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t287 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t289 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t291 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t293 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t295 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t297 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t299 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t301 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t303 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t305 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t307 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t309 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t311 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t313 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t315 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t317 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t319 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t321 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t323 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t325 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t327 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t329 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t331 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t333 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t335 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t337 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t339 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t341 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t343 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t345 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t347 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t349 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t351 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t353 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t355 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t357 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t359 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t361 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t363 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t365 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t367 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t369 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t371 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t373 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t375 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t377 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t379 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t381 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t383 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t385 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t387 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t389 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t391 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t393 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t395 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t397 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t399 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t401 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t403 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t405 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t407 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t409 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t411 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t413 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t415 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t417 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t419 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t421 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t423 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t425 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t427 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t429 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t431 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t433 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t435 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t437 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t439 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t441 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t443 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t445 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t447 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t449 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t451 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t453 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t455 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t457 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t459 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t461 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t463 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t465 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t467 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t469 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t471 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t473 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t475 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t477 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t479 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t481 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t483 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t485 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t487 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t489 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t491 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t493 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t495 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t497 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t499 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t501 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t503 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t505 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t507 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t509 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t511 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_80( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2], a7[2], b7[2], a8[2], b8[2], a9[2], b9[2], a10[2], b10[2], a11[2], b11[2], a12[2], b12[2], a13[2], b13[2], a14[2], b14[2], a15[2], b15[2], a16[2], b16[2], a17[2], b17[2], a18[2], b18[2], a19[2], b19[2], a20[2], b20[2], a21[2], b21[2], a22[2], b22[2], a23[2], b23[2], a24[2], b24[2], a25[2], b25[2], a26[2], b26[2], a27[2], b27[2], a28[2], b28[2], a29[2], b29[2], a30[2], b30[2], a31[2], b31[2], a32[2], b32[2], a33[2], b33[2], a34[2], b34[2], a35[2], b35[2], a36[2], b36[2], a37[2], b37[2], a38[2], b38[2], a39[2], b39[2], a40[2], b40[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39, t40, t41, t42, t43, t44, t45, t46, t47, t48, t49, t50, t51, t52, t53, t54, t55, t56, t57, t58, t59, t60, t61, t62, t63, t64, t65, t66, t67, t68, t69, t70, t71, t72, t73, t74, t75, t76, t77, t78, t79;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=80 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     if( k + 12 < n ) {
       a7[0] = *( m1 + n * i + (k+12) );
     } else {
       a7[0] = 0;
     }
     if( k + 13 < n ) {
       a7[1] = *( m1 + n * i + (k+13) );
     } else {
       a7[1] = 0;
     }
     if( k + 14 < n ) {
       a8[0] = *( m1 + n * i + (k+14) );
     } else {
       a8[0] = 0;
     }
     if( k + 15 < n ) {
       a8[1] = *( m1 + n * i + (k+15) );
     } else {
       a8[1] = 0;
     }
     if( k + 16 < n ) {
       a9[0] = *( m1 + n * i + (k+16) );
     } else {
       a9[0] = 0;
     }
     if( k + 17 < n ) {
       a9[1] = *( m1 + n * i + (k+17) );
     } else {
       a9[1] = 0;
     }
     if( k + 18 < n ) {
       a10[0] = *( m1 + n * i + (k+18) );
     } else {
       a10[0] = 0;
     }
     if( k + 19 < n ) {
       a10[1] = *( m1 + n * i + (k+19) );
     } else {
       a10[1] = 0;
     }
     if( k + 20 < n ) {
       a11[0] = *( m1 + n * i + (k+20) );
     } else {
       a11[0] = 0;
     }
     if( k + 21 < n ) {
       a11[1] = *( m1 + n * i + (k+21) );
     } else {
       a11[1] = 0;
     }
     if( k + 22 < n ) {
       a12[0] = *( m1 + n * i + (k+22) );
     } else {
       a12[0] = 0;
     }
     if( k + 23 < n ) {
       a12[1] = *( m1 + n * i + (k+23) );
     } else {
       a12[1] = 0;
     }
     if( k + 24 < n ) {
       a13[0] = *( m1 + n * i + (k+24) );
     } else {
       a13[0] = 0;
     }
     if( k + 25 < n ) {
       a13[1] = *( m1 + n * i + (k+25) );
     } else {
       a13[1] = 0;
     }
     if( k + 26 < n ) {
       a14[0] = *( m1 + n * i + (k+26) );
     } else {
       a14[0] = 0;
     }
     if( k + 27 < n ) {
       a14[1] = *( m1 + n * i + (k+27) );
     } else {
       a14[1] = 0;
     }
     if( k + 28 < n ) {
       a15[0] = *( m1 + n * i + (k+28) );
     } else {
       a15[0] = 0;
     }
     if( k + 29 < n ) {
       a15[1] = *( m1 + n * i + (k+29) );
     } else {
       a15[1] = 0;
     }
     if( k + 30 < n ) {
       a16[0] = *( m1 + n * i + (k+30) );
     } else {
       a16[0] = 0;
     }
     if( k + 31 < n ) {
       a16[1] = *( m1 + n * i + (k+31) );
     } else {
       a16[1] = 0;
     }
     if( k + 32 < n ) {
       a17[0] = *( m1 + n * i + (k+32) );
     } else {
       a17[0] = 0;
     }
     if( k + 33 < n ) {
       a17[1] = *( m1 + n * i + (k+33) );
     } else {
       a17[1] = 0;
     }
     if( k + 34 < n ) {
       a18[0] = *( m1 + n * i + (k+34) );
     } else {
       a18[0] = 0;
     }
     if( k + 35 < n ) {
       a18[1] = *( m1 + n * i + (k+35) );
     } else {
       a18[1] = 0;
     }
     if( k + 36 < n ) {
       a19[0] = *( m1 + n * i + (k+36) );
     } else {
       a19[0] = 0;
     }
     if( k + 37 < n ) {
       a19[1] = *( m1 + n * i + (k+37) );
     } else {
       a19[1] = 0;
     }
     if( k + 38 < n ) {
       a20[0] = *( m1 + n * i + (k+38) );
     } else {
       a20[0] = 0;
     }
     if( k + 39 < n ) {
       a20[1] = *( m1 + n * i + (k+39) );
     } else {
       a20[1] = 0;
     }
     if( k + 40 < n ) {
       a21[0] = *( m1 + n * i + (k+40) );
     } else {
       a21[0] = 0;
     }
     if( k + 41 < n ) {
       a21[1] = *( m1 + n * i + (k+41) );
     } else {
       a21[1] = 0;
     }
     if( k + 42 < n ) {
       a22[0] = *( m1 + n * i + (k+42) );
     } else {
       a22[0] = 0;
     }
     if( k + 43 < n ) {
       a22[1] = *( m1 + n * i + (k+43) );
     } else {
       a22[1] = 0;
     }
     if( k + 44 < n ) {
       a23[0] = *( m1 + n * i + (k+44) );
     } else {
       a23[0] = 0;
     }
     if( k + 45 < n ) {
       a23[1] = *( m1 + n * i + (k+45) );
     } else {
       a23[1] = 0;
     }
     if( k + 46 < n ) {
       a24[0] = *( m1 + n * i + (k+46) );
     } else {
       a24[0] = 0;
     }
     if( k + 47 < n ) {
       a24[1] = *( m1 + n * i + (k+47) );
     } else {
       a24[1] = 0;
     }
     if( k + 48 < n ) {
       a25[0] = *( m1 + n * i + (k+48) );
     } else {
       a25[0] = 0;
     }
     if( k + 49 < n ) {
       a25[1] = *( m1 + n * i + (k+49) );
     } else {
       a25[1] = 0;
     }
     if( k + 50 < n ) {
       a26[0] = *( m1 + n * i + (k+50) );
     } else {
       a26[0] = 0;
     }
     if( k + 51 < n ) {
       a26[1] = *( m1 + n * i + (k+51) );
     } else {
       a26[1] = 0;
     }
     if( k + 52 < n ) {
       a27[0] = *( m1 + n * i + (k+52) );
     } else {
       a27[0] = 0;
     }
     if( k + 53 < n ) {
       a27[1] = *( m1 + n * i + (k+53) );
     } else {
       a27[1] = 0;
     }
     if( k + 54 < n ) {
       a28[0] = *( m1 + n * i + (k+54) );
     } else {
       a28[0] = 0;
     }
     if( k + 55 < n ) {
       a28[1] = *( m1 + n * i + (k+55) );
     } else {
       a28[1] = 0;
     }
     if( k + 56 < n ) {
       a29[0] = *( m1 + n * i + (k+56) );
     } else {
       a29[0] = 0;
     }
     if( k + 57 < n ) {
       a29[1] = *( m1 + n * i + (k+57) );
     } else {
       a29[1] = 0;
     }
     if( k + 58 < n ) {
       a30[0] = *( m1 + n * i + (k+58) );
     } else {
       a30[0] = 0;
     }
     if( k + 59 < n ) {
       a30[1] = *( m1 + n * i + (k+59) );
     } else {
       a30[1] = 0;
     }
     if( k + 60 < n ) {
       a31[0] = *( m1 + n * i + (k+60) );
     } else {
       a31[0] = 0;
     }
     if( k + 61 < n ) {
       a31[1] = *( m1 + n * i + (k+61) );
     } else {
       a31[1] = 0;
     }
     if( k + 62 < n ) {
       a32[0] = *( m1 + n * i + (k+62) );
     } else {
       a32[0] = 0;
     }
     if( k + 63 < n ) {
       a32[1] = *( m1 + n * i + (k+63) );
     } else {
       a32[1] = 0;
     }
     if( k + 64 < n ) {
       a33[0] = *( m1 + n * i + (k+64) );
     } else {
       a33[0] = 0;
     }
     if( k + 65 < n ) {
       a33[1] = *( m1 + n * i + (k+65) );
     } else {
       a33[1] = 0;
     }
     if( k + 66 < n ) {
       a34[0] = *( m1 + n * i + (k+66) );
     } else {
       a34[0] = 0;
     }
     if( k + 67 < n ) {
       a34[1] = *( m1 + n * i + (k+67) );
     } else {
       a34[1] = 0;
     }
     if( k + 68 < n ) {
       a35[0] = *( m1 + n * i + (k+68) );
     } else {
       a35[0] = 0;
     }
     if( k + 69 < n ) {
       a35[1] = *( m1 + n * i + (k+69) );
     } else {
       a35[1] = 0;
     }
     if( k + 70 < n ) {
       a36[0] = *( m1 + n * i + (k+70) );
     } else {
       a36[0] = 0;
     }
     if( k + 71 < n ) {
       a36[1] = *( m1 + n * i + (k+71) );
     } else {
       a36[1] = 0;
     }
     if( k + 72 < n ) {
       a37[0] = *( m1 + n * i + (k+72) );
     } else {
       a37[0] = 0;
     }
     if( k + 73 < n ) {
       a37[1] = *( m1 + n * i + (k+73) );
     } else {
       a37[1] = 0;
     }
     if( k + 74 < n ) {
       a38[0] = *( m1 + n * i + (k+74) );
     } else {
       a38[0] = 0;
     }
     if( k + 75 < n ) {
       a38[1] = *( m1 + n * i + (k+75) );
     } else {
       a38[1] = 0;
     }
     if( k + 76 < n ) {
       a39[0] = *( m1 + n * i + (k+76) );
     } else {
       a39[0] = 0;
     }
     if( k + 77 < n ) {
       a39[1] = *( m1 + n * i + (k+77) );
     } else {
       a39[1] = 0;
     }
     if( k + 78 < n ) {
       a40[0] = *( m1 + n * i + (k+78) );
     } else {
       a40[0] = 0;
     }
     if( k + 79 < n ) {
       a40[1] = *( m1 + n * i + (k+79) );
     } else {
       a40[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );
     t12 = _mm_load_pd( a7 );
     t14 = _mm_load_pd( a8 );
     t16 = _mm_load_pd( a9 );
     t18 = _mm_load_pd( a10 );
     t20 = _mm_load_pd( a11 );
     t22 = _mm_load_pd( a12 );
     t24 = _mm_load_pd( a13 );
     t26 = _mm_load_pd( a14 );
     t28 = _mm_load_pd( a15 );
     t30 = _mm_load_pd( a16 );
     t32 = _mm_load_pd( a17 );
     t34 = _mm_load_pd( a18 );
     t36 = _mm_load_pd( a19 );
     t38 = _mm_load_pd( a20 );
     t40 = _mm_load_pd( a21 );
     t42 = _mm_load_pd( a22 );
     t44 = _mm_load_pd( a23 );
     t46 = _mm_load_pd( a24 );
     t48 = _mm_load_pd( a25 );
     t50 = _mm_load_pd( a26 );
     t52 = _mm_load_pd( a27 );
     t54 = _mm_load_pd( a28 );
     t56 = _mm_load_pd( a29 );
     t58 = _mm_load_pd( a30 );
     t60 = _mm_load_pd( a31 );
     t62 = _mm_load_pd( a32 );
     t64 = _mm_load_pd( a33 );
     t66 = _mm_load_pd( a34 );
     t68 = _mm_load_pd( a35 );
     t70 = _mm_load_pd( a36 );
     t72 = _mm_load_pd( a37 );
     t74 = _mm_load_pd( a38 );
     t76 = _mm_load_pd( a39 );
     t78 = _mm_load_pd( a40 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       if( k + 12 < n ) {
         b7[0] = *( m2 + n * (k+12) + j );
       } else {
         b7[0] = 0;
       }
      if( k + 13 < n ) {
        b7[1] = *( m2 + n * (k+13) + j );
      } else {
        b7[1] = 0;
      }
       if( k + 14 < n ) {
         b8[0] = *( m2 + n * (k+14) + j );
       } else {
         b8[0] = 0;
       }
      if( k + 15 < n ) {
        b8[1] = *( m2 + n * (k+15) + j );
      } else {
        b8[1] = 0;
      }
       if( k + 16 < n ) {
         b9[0] = *( m2 + n * (k+16) + j );
       } else {
         b9[0] = 0;
       }
      if( k + 17 < n ) {
        b9[1] = *( m2 + n * (k+17) + j );
      } else {
        b9[1] = 0;
      }
       if( k + 18 < n ) {
         b10[0] = *( m2 + n * (k+18) + j );
       } else {
         b10[0] = 0;
       }
      if( k + 19 < n ) {
        b10[1] = *( m2 + n * (k+19) + j );
      } else {
        b10[1] = 0;
      }
       if( k + 20 < n ) {
         b11[0] = *( m2 + n * (k+20) + j );
       } else {
         b11[0] = 0;
       }
      if( k + 21 < n ) {
        b11[1] = *( m2 + n * (k+21) + j );
      } else {
        b11[1] = 0;
      }
       if( k + 22 < n ) {
         b12[0] = *( m2 + n * (k+22) + j );
       } else {
         b12[0] = 0;
       }
      if( k + 23 < n ) {
        b12[1] = *( m2 + n * (k+23) + j );
      } else {
        b12[1] = 0;
      }
       if( k + 24 < n ) {
         b13[0] = *( m2 + n * (k+24) + j );
       } else {
         b13[0] = 0;
       }
      if( k + 25 < n ) {
        b13[1] = *( m2 + n * (k+25) + j );
      } else {
        b13[1] = 0;
      }
       if( k + 26 < n ) {
         b14[0] = *( m2 + n * (k+26) + j );
       } else {
         b14[0] = 0;
       }
      if( k + 27 < n ) {
        b14[1] = *( m2 + n * (k+27) + j );
      } else {
        b14[1] = 0;
      }
       if( k + 28 < n ) {
         b15[0] = *( m2 + n * (k+28) + j );
       } else {
         b15[0] = 0;
       }
      if( k + 29 < n ) {
        b15[1] = *( m2 + n * (k+29) + j );
      } else {
        b15[1] = 0;
      }
       if( k + 30 < n ) {
         b16[0] = *( m2 + n * (k+30) + j );
       } else {
         b16[0] = 0;
       }
      if( k + 31 < n ) {
        b16[1] = *( m2 + n * (k+31) + j );
      } else {
        b16[1] = 0;
      }
       if( k + 32 < n ) {
         b17[0] = *( m2 + n * (k+32) + j );
       } else {
         b17[0] = 0;
       }
      if( k + 33 < n ) {
        b17[1] = *( m2 + n * (k+33) + j );
      } else {
        b17[1] = 0;
      }
       if( k + 34 < n ) {
         b18[0] = *( m2 + n * (k+34) + j );
       } else {
         b18[0] = 0;
       }
      if( k + 35 < n ) {
        b18[1] = *( m2 + n * (k+35) + j );
      } else {
        b18[1] = 0;
      }
       if( k + 36 < n ) {
         b19[0] = *( m2 + n * (k+36) + j );
       } else {
         b19[0] = 0;
       }
      if( k + 37 < n ) {
        b19[1] = *( m2 + n * (k+37) + j );
      } else {
        b19[1] = 0;
      }
       if( k + 38 < n ) {
         b20[0] = *( m2 + n * (k+38) + j );
       } else {
         b20[0] = 0;
       }
      if( k + 39 < n ) {
        b20[1] = *( m2 + n * (k+39) + j );
      } else {
        b20[1] = 0;
      }
       if( k + 40 < n ) {
         b21[0] = *( m2 + n * (k+40) + j );
       } else {
         b21[0] = 0;
       }
      if( k + 41 < n ) {
        b21[1] = *( m2 + n * (k+41) + j );
      } else {
        b21[1] = 0;
      }
       if( k + 42 < n ) {
         b22[0] = *( m2 + n * (k+42) + j );
       } else {
         b22[0] = 0;
       }
      if( k + 43 < n ) {
        b22[1] = *( m2 + n * (k+43) + j );
      } else {
        b22[1] = 0;
      }
       if( k + 44 < n ) {
         b23[0] = *( m2 + n * (k+44) + j );
       } else {
         b23[0] = 0;
       }
      if( k + 45 < n ) {
        b23[1] = *( m2 + n * (k+45) + j );
      } else {
        b23[1] = 0;
      }
       if( k + 46 < n ) {
         b24[0] = *( m2 + n * (k+46) + j );
       } else {
         b24[0] = 0;
       }
      if( k + 47 < n ) {
        b24[1] = *( m2 + n * (k+47) + j );
      } else {
        b24[1] = 0;
      }
       if( k + 48 < n ) {
         b25[0] = *( m2 + n * (k+48) + j );
       } else {
         b25[0] = 0;
       }
      if( k + 49 < n ) {
        b25[1] = *( m2 + n * (k+49) + j );
      } else {
        b25[1] = 0;
      }
       if( k + 50 < n ) {
         b26[0] = *( m2 + n * (k+50) + j );
       } else {
         b26[0] = 0;
       }
      if( k + 51 < n ) {
        b26[1] = *( m2 + n * (k+51) + j );
      } else {
        b26[1] = 0;
      }
       if( k + 52 < n ) {
         b27[0] = *( m2 + n * (k+52) + j );
       } else {
         b27[0] = 0;
       }
      if( k + 53 < n ) {
        b27[1] = *( m2 + n * (k+53) + j );
      } else {
        b27[1] = 0;
      }
       if( k + 54 < n ) {
         b28[0] = *( m2 + n * (k+54) + j );
       } else {
         b28[0] = 0;
       }
      if( k + 55 < n ) {
        b28[1] = *( m2 + n * (k+55) + j );
      } else {
        b28[1] = 0;
      }
       if( k + 56 < n ) {
         b29[0] = *( m2 + n * (k+56) + j );
       } else {
         b29[0] = 0;
       }
      if( k + 57 < n ) {
        b29[1] = *( m2 + n * (k+57) + j );
      } else {
        b29[1] = 0;
      }
       if( k + 58 < n ) {
         b30[0] = *( m2 + n * (k+58) + j );
       } else {
         b30[0] = 0;
       }
      if( k + 59 < n ) {
        b30[1] = *( m2 + n * (k+59) + j );
      } else {
        b30[1] = 0;
      }
       if( k + 60 < n ) {
         b31[0] = *( m2 + n * (k+60) + j );
       } else {
         b31[0] = 0;
       }
      if( k + 61 < n ) {
        b31[1] = *( m2 + n * (k+61) + j );
      } else {
        b31[1] = 0;
      }
       if( k + 62 < n ) {
         b32[0] = *( m2 + n * (k+62) + j );
       } else {
         b32[0] = 0;
       }
      if( k + 63 < n ) {
        b32[1] = *( m2 + n * (k+63) + j );
      } else {
        b32[1] = 0;
      }
       if( k + 64 < n ) {
         b33[0] = *( m2 + n * (k+64) + j );
       } else {
         b33[0] = 0;
       }
      if( k + 65 < n ) {
        b33[1] = *( m2 + n * (k+65) + j );
      } else {
        b33[1] = 0;
      }
       if( k + 66 < n ) {
         b34[0] = *( m2 + n * (k+66) + j );
       } else {
         b34[0] = 0;
       }
      if( k + 67 < n ) {
        b34[1] = *( m2 + n * (k+67) + j );
      } else {
        b34[1] = 0;
      }
       if( k + 68 < n ) {
         b35[0] = *( m2 + n * (k+68) + j );
       } else {
         b35[0] = 0;
       }
      if( k + 69 < n ) {
        b35[1] = *( m2 + n * (k+69) + j );
      } else {
        b35[1] = 0;
      }
       if( k + 70 < n ) {
         b36[0] = *( m2 + n * (k+70) + j );
       } else {
         b36[0] = 0;
       }
      if( k + 71 < n ) {
        b36[1] = *( m2 + n * (k+71) + j );
      } else {
        b36[1] = 0;
      }
       if( k + 72 < n ) {
         b37[0] = *( m2 + n * (k+72) + j );
       } else {
         b37[0] = 0;
       }
      if( k + 73 < n ) {
        b37[1] = *( m2 + n * (k+73) + j );
      } else {
        b37[1] = 0;
      }
       if( k + 74 < n ) {
         b38[0] = *( m2 + n * (k+74) + j );
       } else {
         b38[0] = 0;
       }
      if( k + 75 < n ) {
        b38[1] = *( m2 + n * (k+75) + j );
      } else {
        b38[1] = 0;
      }
       if( k + 76 < n ) {
         b39[0] = *( m2 + n * (k+76) + j );
       } else {
         b39[0] = 0;
       }
      if( k + 77 < n ) {
        b39[1] = *( m2 + n * (k+77) + j );
      } else {
        b39[1] = 0;
      }
       if( k + 78 < n ) {
         b40[0] = *( m2 + n * (k+78) + j );
       } else {
         b40[0] = 0;
       }
      if( k + 79 < n ) {
        b40[1] = *( m2 + n * (k+79) + j );
      } else {
        b40[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t13 = _mm_load_pd( b7 );
       t15 = _mm_load_pd( b8 );
       t17 = _mm_load_pd( b9 );
       t19 = _mm_load_pd( b10 );
       t21 = _mm_load_pd( b11 );
       t23 = _mm_load_pd( b12 );
       t25 = _mm_load_pd( b13 );
       t27 = _mm_load_pd( b14 );
       t29 = _mm_load_pd( b15 );
       t31 = _mm_load_pd( b16 );
       t33 = _mm_load_pd( b17 );
       t35 = _mm_load_pd( b18 );
       t37 = _mm_load_pd( b19 );
       t39 = _mm_load_pd( b20 );
       t41 = _mm_load_pd( b21 );
       t43 = _mm_load_pd( b22 );
       t45 = _mm_load_pd( b23 );
       t47 = _mm_load_pd( b24 );
       t49 = _mm_load_pd( b25 );
       t51 = _mm_load_pd( b26 );
       t53 = _mm_load_pd( b27 );
       t55 = _mm_load_pd( b28 );
       t57 = _mm_load_pd( b29 );
       t59 = _mm_load_pd( b30 );
       t61 = _mm_load_pd( b31 );
       t63 = _mm_load_pd( b32 );
       t65 = _mm_load_pd( b33 );
       t67 = _mm_load_pd( b34 );
       t69 = _mm_load_pd( b35 );
       t71 = _mm_load_pd( b36 );
       t73 = _mm_load_pd( b37 );
       t75 = _mm_load_pd( b38 );
       t77 = _mm_load_pd( b39 );
       t79 = _mm_load_pd( b40 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );
       t13 = _mm_dp_pd( t12, t13, 0xff );
       t15 = _mm_dp_pd( t14, t15, 0xff );
       t17 = _mm_dp_pd( t16, t17, 0xff );
       t19 = _mm_dp_pd( t18, t19, 0xff );
       t21 = _mm_dp_pd( t20, t21, 0xff );
       t23 = _mm_dp_pd( t22, t23, 0xff );
       t25 = _mm_dp_pd( t24, t25, 0xff );
       t27 = _mm_dp_pd( t26, t27, 0xff );
       t29 = _mm_dp_pd( t28, t29, 0xff );
       t31 = _mm_dp_pd( t30, t31, 0xff );
       t33 = _mm_dp_pd( t32, t33, 0xff );
       t35 = _mm_dp_pd( t34, t35, 0xff );
       t37 = _mm_dp_pd( t36, t37, 0xff );
       t39 = _mm_dp_pd( t38, t39, 0xff );
       t41 = _mm_dp_pd( t40, t41, 0xff );
       t43 = _mm_dp_pd( t42, t43, 0xff );
       t45 = _mm_dp_pd( t44, t45, 0xff );
       t47 = _mm_dp_pd( t46, t47, 0xff );
       t49 = _mm_dp_pd( t48, t49, 0xff );
       t51 = _mm_dp_pd( t50, t51, 0xff );
       t53 = _mm_dp_pd( t52, t53, 0xff );
       t55 = _mm_dp_pd( t54, t55, 0xff );
       t57 = _mm_dp_pd( t56, t57, 0xff );
       t59 = _mm_dp_pd( t58, t59, 0xff );
       t61 = _mm_dp_pd( t60, t61, 0xff );
       t63 = _mm_dp_pd( t62, t63, 0xff );
       t65 = _mm_dp_pd( t64, t65, 0xff );
       t67 = _mm_dp_pd( t66, t67, 0xff );
       t69 = _mm_dp_pd( t68, t69, 0xff );
       t71 = _mm_dp_pd( t70, t71, 0xff );
       t73 = _mm_dp_pd( t72, t73, 0xff );
       t75 = _mm_dp_pd( t74, t75, 0xff );
       t77 = _mm_dp_pd( t76, t77, 0xff );
       t79 = _mm_dp_pd( t78, t79, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t13 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t15 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t17 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t19 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t21 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t23 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t25 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t27 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t29 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t31 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t33 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t35 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t37 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t39 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t41 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t43 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t45 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t47 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t49 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t51 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t53 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t55 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t57 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t59 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t61 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t63 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t65 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t67 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t69 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t71 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t73 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t75 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t77 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t79 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
void* naiveMultiply_parallel_intrinsics_40( void *thread_args )
{
 int i, j, k, start, end;

 struct thread_info *args = ( struct thread_info * ) thread_args;
 double *m1 = args->m1;
 double *m2 = args->m2;
 double *result = args->answer;

 long n = args->size;
 start = args->start;
 end = args->end;
 double a1[2], b1[2], a2[2], b2[2], a3[2], b3[2], a4[2], b4[2], a5[2], b5[2], a6[2], b6[2], a7[2], b7[2], a8[2], b8[2], a9[2], b9[2], a10[2], b10[2], a11[2], b11[2], a12[2], b12[2], a13[2], b13[2], a14[2], b14[2], a15[2], b15[2], a16[2], b16[2], a17[2], b17[2], a18[2], b18[2], a19[2], b19[2], a20[2], b20[2];

  double c;

 __m128d t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35, t36, t37, t38, t39;

  j = 0;
  for ( i = start; i < end; i++ )
{
    for ( k = 0; k < n; k+=40 )
{
     if( k + 0 < n ) {
       a1[0] = *( m1 + n * i + (k+0) );
     } else {
       a1[0] = 0;
     }
     if( k + 1 < n ) {
       a1[1] = *( m1 + n * i + (k+1) );
     } else {
       a1[1] = 0;
     }
     if( k + 2 < n ) {
       a2[0] = *( m1 + n * i + (k+2) );
     } else {
       a2[0] = 0;
     }
     if( k + 3 < n ) {
       a2[1] = *( m1 + n * i + (k+3) );
     } else {
       a2[1] = 0;
     }
     if( k + 4 < n ) {
       a3[0] = *( m1 + n * i + (k+4) );
     } else {
       a3[0] = 0;
     }
     if( k + 5 < n ) {
       a3[1] = *( m1 + n * i + (k+5) );
     } else {
       a3[1] = 0;
     }
     if( k + 6 < n ) {
       a4[0] = *( m1 + n * i + (k+6) );
     } else {
       a4[0] = 0;
     }
     if( k + 7 < n ) {
       a4[1] = *( m1 + n * i + (k+7) );
     } else {
       a4[1] = 0;
     }
     if( k + 8 < n ) {
       a5[0] = *( m1 + n * i + (k+8) );
     } else {
       a5[0] = 0;
     }
     if( k + 9 < n ) {
       a5[1] = *( m1 + n * i + (k+9) );
     } else {
       a5[1] = 0;
     }
     if( k + 10 < n ) {
       a6[0] = *( m1 + n * i + (k+10) );
     } else {
       a6[0] = 0;
     }
     if( k + 11 < n ) {
       a6[1] = *( m1 + n * i + (k+11) );
     } else {
       a6[1] = 0;
     }
     if( k + 12 < n ) {
       a7[0] = *( m1 + n * i + (k+12) );
     } else {
       a7[0] = 0;
     }
     if( k + 13 < n ) {
       a7[1] = *( m1 + n * i + (k+13) );
     } else {
       a7[1] = 0;
     }
     if( k + 14 < n ) {
       a8[0] = *( m1 + n * i + (k+14) );
     } else {
       a8[0] = 0;
     }
     if( k + 15 < n ) {
       a8[1] = *( m1 + n * i + (k+15) );
     } else {
       a8[1] = 0;
     }
     if( k + 16 < n ) {
       a9[0] = *( m1 + n * i + (k+16) );
     } else {
       a9[0] = 0;
     }
     if( k + 17 < n ) {
       a9[1] = *( m1 + n * i + (k+17) );
     } else {
       a9[1] = 0;
     }
     if( k + 18 < n ) {
       a10[0] = *( m1 + n * i + (k+18) );
     } else {
       a10[0] = 0;
     }
     if( k + 19 < n ) {
       a10[1] = *( m1 + n * i + (k+19) );
     } else {
       a10[1] = 0;
     }
     if( k + 20 < n ) {
       a11[0] = *( m1 + n * i + (k+20) );
     } else {
       a11[0] = 0;
     }
     if( k + 21 < n ) {
       a11[1] = *( m1 + n * i + (k+21) );
     } else {
       a11[1] = 0;
     }
     if( k + 22 < n ) {
       a12[0] = *( m1 + n * i + (k+22) );
     } else {
       a12[0] = 0;
     }
     if( k + 23 < n ) {
       a12[1] = *( m1 + n * i + (k+23) );
     } else {
       a12[1] = 0;
     }
     if( k + 24 < n ) {
       a13[0] = *( m1 + n * i + (k+24) );
     } else {
       a13[0] = 0;
     }
     if( k + 25 < n ) {
       a13[1] = *( m1 + n * i + (k+25) );
     } else {
       a13[1] = 0;
     }
     if( k + 26 < n ) {
       a14[0] = *( m1 + n * i + (k+26) );
     } else {
       a14[0] = 0;
     }
     if( k + 27 < n ) {
       a14[1] = *( m1 + n * i + (k+27) );
     } else {
       a14[1] = 0;
     }
     if( k + 28 < n ) {
       a15[0] = *( m1 + n * i + (k+28) );
     } else {
       a15[0] = 0;
     }
     if( k + 29 < n ) {
       a15[1] = *( m1 + n * i + (k+29) );
     } else {
       a15[1] = 0;
     }
     if( k + 30 < n ) {
       a16[0] = *( m1 + n * i + (k+30) );
     } else {
       a16[0] = 0;
     }
     if( k + 31 < n ) {
       a16[1] = *( m1 + n * i + (k+31) );
     } else {
       a16[1] = 0;
     }
     if( k + 32 < n ) {
       a17[0] = *( m1 + n * i + (k+32) );
     } else {
       a17[0] = 0;
     }
     if( k + 33 < n ) {
       a17[1] = *( m1 + n * i + (k+33) );
     } else {
       a17[1] = 0;
     }
     if( k + 34 < n ) {
       a18[0] = *( m1 + n * i + (k+34) );
     } else {
       a18[0] = 0;
     }
     if( k + 35 < n ) {
       a18[1] = *( m1 + n * i + (k+35) );
     } else {
       a18[1] = 0;
     }
     if( k + 36 < n ) {
       a19[0] = *( m1 + n * i + (k+36) );
     } else {
       a19[0] = 0;
     }
     if( k + 37 < n ) {
       a19[1] = *( m1 + n * i + (k+37) );
     } else {
       a19[1] = 0;
     }
     if( k + 38 < n ) {
       a20[0] = *( m1 + n * i + (k+38) );
     } else {
       a20[0] = 0;
     }
     if( k + 39 < n ) {
       a20[1] = *( m1 + n * i + (k+39) );
     } else {
       a20[1] = 0;
     }
     t0 = _mm_load_pd( a1 );
     t2 = _mm_load_pd( a2 );
     t4 = _mm_load_pd( a3 );
     t6 = _mm_load_pd( a4 );
     t8 = _mm_load_pd( a5 );
     t10 = _mm_load_pd( a6 );
     t12 = _mm_load_pd( a7 );
     t14 = _mm_load_pd( a8 );
     t16 = _mm_load_pd( a9 );
     t18 = _mm_load_pd( a10 );
     t20 = _mm_load_pd( a11 );
     t22 = _mm_load_pd( a12 );
     t24 = _mm_load_pd( a13 );
     t26 = _mm_load_pd( a14 );
     t28 = _mm_load_pd( a15 );
     t30 = _mm_load_pd( a16 );
     t32 = _mm_load_pd( a17 );
     t34 = _mm_load_pd( a18 );
     t36 = _mm_load_pd( a19 );
     t38 = _mm_load_pd( a20 );

      for ( j = 0; j < n; j++ )
{
       if( k + 0 < n ) {
         b1[0] = *( m2 + n * (k+0) + j );
       } else {
         b1[0] = 0;
       }
      if( k + 1 < n ) {
        b1[1] = *( m2 + n * (k+1) + j );
      } else {
        b1[1] = 0;
      }
       if( k + 2 < n ) {
         b2[0] = *( m2 + n * (k+2) + j );
       } else {
         b2[0] = 0;
       }
      if( k + 3 < n ) {
        b2[1] = *( m2 + n * (k+3) + j );
      } else {
        b2[1] = 0;
      }
       if( k + 4 < n ) {
         b3[0] = *( m2 + n * (k+4) + j );
       } else {
         b3[0] = 0;
       }
      if( k + 5 < n ) {
        b3[1] = *( m2 + n * (k+5) + j );
      } else {
        b3[1] = 0;
      }
       if( k + 6 < n ) {
         b4[0] = *( m2 + n * (k+6) + j );
       } else {
         b4[0] = 0;
       }
      if( k + 7 < n ) {
        b4[1] = *( m2 + n * (k+7) + j );
      } else {
        b4[1] = 0;
      }
       if( k + 8 < n ) {
         b5[0] = *( m2 + n * (k+8) + j );
       } else {
         b5[0] = 0;
       }
      if( k + 9 < n ) {
        b5[1] = *( m2 + n * (k+9) + j );
      } else {
        b5[1] = 0;
      }
       if( k + 10 < n ) {
         b6[0] = *( m2 + n * (k+10) + j );
       } else {
         b6[0] = 0;
       }
      if( k + 11 < n ) {
        b6[1] = *( m2 + n * (k+11) + j );
      } else {
        b6[1] = 0;
      }
       if( k + 12 < n ) {
         b7[0] = *( m2 + n * (k+12) + j );
       } else {
         b7[0] = 0;
       }
      if( k + 13 < n ) {
        b7[1] = *( m2 + n * (k+13) + j );
      } else {
        b7[1] = 0;
      }
       if( k + 14 < n ) {
         b8[0] = *( m2 + n * (k+14) + j );
       } else {
         b8[0] = 0;
       }
      if( k + 15 < n ) {
        b8[1] = *( m2 + n * (k+15) + j );
      } else {
        b8[1] = 0;
      }
       if( k + 16 < n ) {
         b9[0] = *( m2 + n * (k+16) + j );
       } else {
         b9[0] = 0;
       }
      if( k + 17 < n ) {
        b9[1] = *( m2 + n * (k+17) + j );
      } else {
        b9[1] = 0;
      }
       if( k + 18 < n ) {
         b10[0] = *( m2 + n * (k+18) + j );
       } else {
         b10[0] = 0;
       }
      if( k + 19 < n ) {
        b10[1] = *( m2 + n * (k+19) + j );
      } else {
        b10[1] = 0;
      }
       if( k + 20 < n ) {
         b11[0] = *( m2 + n * (k+20) + j );
       } else {
         b11[0] = 0;
       }
      if( k + 21 < n ) {
        b11[1] = *( m2 + n * (k+21) + j );
      } else {
        b11[1] = 0;
      }
       if( k + 22 < n ) {
         b12[0] = *( m2 + n * (k+22) + j );
       } else {
         b12[0] = 0;
       }
      if( k + 23 < n ) {
        b12[1] = *( m2 + n * (k+23) + j );
      } else {
        b12[1] = 0;
      }
       if( k + 24 < n ) {
         b13[0] = *( m2 + n * (k+24) + j );
       } else {
         b13[0] = 0;
       }
      if( k + 25 < n ) {
        b13[1] = *( m2 + n * (k+25) + j );
      } else {
        b13[1] = 0;
      }
       if( k + 26 < n ) {
         b14[0] = *( m2 + n * (k+26) + j );
       } else {
         b14[0] = 0;
       }
      if( k + 27 < n ) {
        b14[1] = *( m2 + n * (k+27) + j );
      } else {
        b14[1] = 0;
      }
       if( k + 28 < n ) {
         b15[0] = *( m2 + n * (k+28) + j );
       } else {
         b15[0] = 0;
       }
      if( k + 29 < n ) {
        b15[1] = *( m2 + n * (k+29) + j );
      } else {
        b15[1] = 0;
      }
       if( k + 30 < n ) {
         b16[0] = *( m2 + n * (k+30) + j );
       } else {
         b16[0] = 0;
       }
      if( k + 31 < n ) {
        b16[1] = *( m2 + n * (k+31) + j );
      } else {
        b16[1] = 0;
      }
       if( k + 32 < n ) {
         b17[0] = *( m2 + n * (k+32) + j );
       } else {
         b17[0] = 0;
       }
      if( k + 33 < n ) {
        b17[1] = *( m2 + n * (k+33) + j );
      } else {
        b17[1] = 0;
      }
       if( k + 34 < n ) {
         b18[0] = *( m2 + n * (k+34) + j );
       } else {
         b18[0] = 0;
       }
      if( k + 35 < n ) {
        b18[1] = *( m2 + n * (k+35) + j );
      } else {
        b18[1] = 0;
      }
       if( k + 36 < n ) {
         b19[0] = *( m2 + n * (k+36) + j );
       } else {
         b19[0] = 0;
       }
      if( k + 37 < n ) {
        b19[1] = *( m2 + n * (k+37) + j );
      } else {
        b19[1] = 0;
      }
       if( k + 38 < n ) {
         b20[0] = *( m2 + n * (k+38) + j );
       } else {
         b20[0] = 0;
       }
      if( k + 39 < n ) {
        b20[1] = *( m2 + n * (k+39) + j );
      } else {
        b20[1] = 0;
      }
       t1 = _mm_load_pd( b1 );
       t3 = _mm_load_pd( b2 );
       t5 = _mm_load_pd( b3 );
       t7 = _mm_load_pd( b4 );
       t9 = _mm_load_pd( b5 );
       t11 = _mm_load_pd( b6 );
       t13 = _mm_load_pd( b7 );
       t15 = _mm_load_pd( b8 );
       t17 = _mm_load_pd( b9 );
       t19 = _mm_load_pd( b10 );
       t21 = _mm_load_pd( b11 );
       t23 = _mm_load_pd( b12 );
       t25 = _mm_load_pd( b13 );
       t27 = _mm_load_pd( b14 );
       t29 = _mm_load_pd( b15 );
       t31 = _mm_load_pd( b16 );
       t33 = _mm_load_pd( b17 );
       t35 = _mm_load_pd( b18 );
       t37 = _mm_load_pd( b19 );
       t39 = _mm_load_pd( b20 );
       t1 = _mm_dp_pd( t0, t1, 0xff );
       t3 = _mm_dp_pd( t2, t3, 0xff );
       t5 = _mm_dp_pd( t4, t5, 0xff );
       t7 = _mm_dp_pd( t6, t7, 0xff );
       t9 = _mm_dp_pd( t8, t9, 0xff );
       t11 = _mm_dp_pd( t10, t11, 0xff );
       t13 = _mm_dp_pd( t12, t13, 0xff );
       t15 = _mm_dp_pd( t14, t15, 0xff );
       t17 = _mm_dp_pd( t16, t17, 0xff );
       t19 = _mm_dp_pd( t18, t19, 0xff );
       t21 = _mm_dp_pd( t20, t21, 0xff );
       t23 = _mm_dp_pd( t22, t23, 0xff );
       t25 = _mm_dp_pd( t24, t25, 0xff );
       t27 = _mm_dp_pd( t26, t27, 0xff );
       t29 = _mm_dp_pd( t28, t29, 0xff );
       t31 = _mm_dp_pd( t30, t31, 0xff );
       t33 = _mm_dp_pd( t32, t33, 0xff );
       t35 = _mm_dp_pd( t34, t35, 0xff );
       t37 = _mm_dp_pd( t36, t37, 0xff );
       t39 = _mm_dp_pd( t38, t39, 0xff );

       _mm_storel_pd( &c, t1 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t3 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t5 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t7 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t9 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t11 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t13 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t15 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t17 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t19 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t21 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t23 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t25 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t27 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t29 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t31 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t33 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t35 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t37 );
       *( result + n * i + j ) += c;
       _mm_storel_pd( &c, t39 );
       *( result + n * i + j ) += c;
     }
   }
 }
 pthread_exit( NULL );
}
