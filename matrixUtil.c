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
		
 		
