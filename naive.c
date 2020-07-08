#include <stdio.h>
#include <sys/time.h>
#define N 4


void naiveMultiply(int n, float m1[][N], float m2[][N], float result[][N]);


int main()
{

	int i, j;
	float exetime;
	struct timeval start, end;

	float a[N][N] = {{1, 2, 3, 4},
		       {1, 2, 3, 4},
		       {1, 2, 3, 4},
                       {1, 2, 3, 4}};
	float b[N][N] = {{1, 2, 3, 4},
		       {1, 2, 3, 4},
		       {1, 2, 3, 4},
                       {1, 2, 3, 4}};
	float c[N][N];

	gettimeofday(&start, NULL);
	naiveMultiply( N, a, b, c );
	gettimeofday(&end, NULL);

	for ( i = 0; i < 4; i++ )
		for ( j = 0; j < 4; j++ )
			printf( "%.0f\n",  c[i][j] );

	exetime = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
	printf( "Execution time is: %f microseconds\n", exetime );

	
	return 0;
}

// multiply two nxn matrices together
void naiveMultiply(int n, float m1[][N], float m2[][N], float result[][N])
{
	int i, j, k;
	float sum;

	for ( i = 0; i < n; i++ ) 
	{
		for ( j = 0; j < n; j++ ) 
		{
			sum = 0;
			for ( k = 0; k < n; k++ )
			{
				sum += m1[i][k] * m2[k][j];
			}
			result[i][j] = sum;
		}
	}
}

