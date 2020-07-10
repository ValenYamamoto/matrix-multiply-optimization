import sys
import matplotlib.pyplot as plt

def parse_file( f: "file" ) -> dict:
	matrix_stats = dict()
	for line in f:
		N, mean, std_dev = tuple( float(x) for x in line.rstrip( "\n" ).split(" ") )
		matrix_stats[N] = {"mean": mean, "std_dev": std_dev}
	return matrix_stats

def plot_matrix_mean( data: dict, filename: str ) -> None:
	N_array = [ x for x in sorted( data.keys(), key=lambda x: x ) ]
	mean_array = [ value["mean"] for key, value in sorted( data.items(), key=lambda x: x[0] ) ]
	plt.xlabel( "Matrix Size N" )
	plt.ylabel( "Mean Execute Time" )	
	plt.scatter( N_array, mean_array )
	plt.savefig( f"{filename}-graph.png" )

if __name__ == "__main__":
	filename = sys.argv[1]
	with open(filename) as f:
		matrix_data = parse_file( f )
		plot_matrix_mean( matrix_data, filename )
