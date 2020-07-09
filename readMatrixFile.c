#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readMatrixFile.h"


int main() 
{
	long double *m;
	m = ( long double * ) malloc( 100 * sizeof( long double ));
	
	readMatrixFromFile( "test_cases/x10", m );

	int i = 0;
//	for( i = 0; i < 100; i ++ )
//		printf("%lf	", *( m + i ));

	free( m );
	return 0;
}

void readMatrixFromFile( char *filepath, long double *m )
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
			printf( "%s %Lf \n", token, *( m + i -1));
			token = strtok( NULL, " " );
		}
	}
	free( line );
	free( token );
	fclose( inFile );
}
		
 		
