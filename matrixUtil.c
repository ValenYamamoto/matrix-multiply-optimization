#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrixUtil.h"

#if 0
int main() 
{
	double *m;
	m = ( double * ) malloc( 100 * sizeof( double ));
	
	readMatrixFromFile( "test_cases/x10", m );

	int i = 0;
//	for( i = 0; i < 100; i ++ )
//		printf("%lf	", *( m + i ));

	free( m );
	return 0;
}
#endif

void readMatrixFromFile( char *filepath, double *m )
{
	FILE *inFile;
	ssize_t nread;
	size_t len = 0;
	char *line = NULL;
	char *token;
	int i = 0;

	inFile = fopen( filepath, "r" );

	while(( nread = getline( &line, &len, inFile )) != -1 ) {
		token = strtok( line, " " );
		while( token != NULL ) {
			*( m + i++ ) = atof( token );
			token = strtok( NULL, " " );
		}
	}
	free( line );
	free( token );
	fclose( inFile );
}

int checkAnswer( int n, double *result, double *answer, int debug )
{
	int i;
	int correct = 1;

	for ( i = 0; i < n * n; i++ ) {
		if ( fabs( *( result + i ) - *( answer + i ) ) > EPSILON ) {
			printf( "multiply answer: %.14lf	correct answer: %.14lf\n", *( result + i ), *( answer + i ));
			correct = 0;
		} else if ( debug )  {
			printf( "multiply answer: %.14lf	correct answer: %.14lf\n", *( result + i ), *( answer + i ));
		}
	}
	return correct;
}
		
 		
void generateMatrix( int n, double *m )
{
	        int i;
		for ( i = 0; i < n * n; i++ ) {
			*(m + i) = rand() % 50; // mod 50 just for testing purposes
	        }

}

void addMatrix( int n, double *m1, double *m2, double *answer ) {
  int i;
  for( i = 0; i < n * n; i++ ) {
    *( answer + i ) = *( m1 + i) + *( m2 + i );
  }
}

void subtractMatrix( int n, double *m1, double *m2, double *answer ) {
  int i;
  for( i = 0; i < n * n; i++ ) {
    *( answer + i ) = *( m1 + i) - *( m2 + i );
  }
}

void split( int n, int quadrant, double *m, double *result ) {
  int start_i, start_j;

  switch( quadrant ) {
    case 1:
      start_i = 0;
      start_j = 0;
      break;
    case 3:
      start_i = n / 2;
      start_j = 0;
      break;
    case 2:
      start_i = 0;
      start_j = n / 2;
      break;
    case 4:
      start_i = n / 2;
      start_j = n / 2;
      break;
  }

  int i, j;
  for( i = 0; i < ( n / 2 ); i++ ) {
    for( j = 0; j < ( n / 2 ); j++ ) {
      *( result + ( n / 2 ) * i + j ) = *( m + ( start_i + i ) * ( n / 2) + ( start_j + j ) );
    }
  }
}

void combine( int n, double *a, double *b, double *c, double *d, double *result ) {
  int i, j;
  for( i = 0; i < ( n / 2 ); i++ ) {
    for( j = 0; j < ( n / 2 ); j++ ) {
      *( result + n * i + j ) = *( a + n * i + j );
    }
  }
  for( i = 0; i < ( n / 2 ); i++ ) {
    for( j = ( n / 2 ); j < n; j++ ) {
      *( result + n * i + j ) = *( b + n * i + j );
    }
  }
  for( i = ( n / 2 ); i < n; i++ ) {
    for( j = 0; j < ( n / 2 ); j++ ) {
      *( result + n * i + j ) = *( c + n * i + j );
    }
  }
  for( i = ( n / 2 ); i < n; i++ ) {
    for( j = ( n / 2 ); j < n; j++ ) {
      *( result + n * i + j ) = *( d + n * i + j );
    }
  }
}
