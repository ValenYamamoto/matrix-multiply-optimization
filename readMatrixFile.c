#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "readMatrixFile.h"


void readMatrixFromFile( char *filepath, double *m );
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
			printf( "%s %.14f \n", token, *( m + i -1));
			token = strtok( NULL, " " );
		}
	}
	free( line );
	free( token );
	fclose( inFile );
}
		
 		
