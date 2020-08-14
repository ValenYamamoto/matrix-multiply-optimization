import sys
import matplotlib.pyplot as plt

def parse_file( f: "file" ) -> (list, list):
    sizes = []
    times = []
    for line in f:
        N, time = tuple( float(x) for x in line.rstrip( "\n" ).split(" ") )
        if N < 6000:
          print( N )
          sizes.append( N );
          times.append( time );
    return sizes, times

def plot_matrix( x, y, label ) -> None:
    plt.scatter( x, y, label=label )

def save_figure( filename: str ) -> None:
    plt.xlabel( "Matrix Size N" )
    plt.ylabel( "Mean Execute Time" )	
    plt.legend()
    plt.savefig( f"{filename}-graph.png" )

if __name__ == "__main__":
    naive_filename = sys.argv[1]
    strassen_filename = sys.argv[2]
    with open(naive_filename) as f:
        print("opening naive file")
        x, y = parse_file( f )
        plot_matrix( x, y, "naive" )
        
    with open(strassen_filename) as f:
        print("opening strassen file")
        x, y = parse_file( f )
        plot_matrix( x, y, "strassen" )
    save_figure( "comparison" )
