import sys
import math
import matplotlib.pyplot as plt

def parse_file( f: "file" ) -> (list, list):
    sizes = []
    freq = []
    mem = []
    misses_per_cycle = []
    times = []

    for line in f:
        N, instruct, access, misses, aperf, mperf, mem_loads, instruct_per_cycle, miss_per_instruct, mem_load_per_cycle, frequency, time = tuple( float(x) for x in line.rstrip( "\n" ).split(" ") )
        sizes.append( N )
        times.append( time )
        freq.append( frequency )
        misses_per_cycle.append( miss_per_instruct )
        print(time, frequency, aperf )
    return sizes, freq, misses_per_cycle, times

def plot_matrix( x, y, label ) -> None:
    plt.scatter( x, y, label=label )

def save_figure( filename: str, xlabel: str, ylabel: str ) -> None:
    plt.xlabel( xlabel )
    plt.ylabel( ylabel )	
    plt.legend()
    plt.savefig( f"{filename}-graph.png" )

if __name__ == "__main__":
    original_filename = sys.argv[1]
    intrinsics_filename = sys.argv[2]
    with open(original_filename) as f:
        print("opening orignal file")
        size, freq, misses_per_cycle, times = parse_file( f )
        logs = [ math.log(x) for x in times ]
        plot_matrix( size, logs, f"strassen unoptimized" )
    with open(intrinsics_filename) as f:
        print("opening intrinsics file")
        size, freq, misses_per_cycle, times = parse_file( f )
        logs = [ math.log(x) for x in times ]
        plot_matrix( size, logs, f"strassen intrinsics" )
        
    save_figure( f"strassen_log", "Matrix Size N", "ln(calculation time)" )
