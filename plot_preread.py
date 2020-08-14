import sys
import matplotlib.pyplot as plt

def parse_file( f: "file", size: int ) -> (list, list):
    sizes = []
    freq = []
    mem = []
    misses_per_cycle = []
    times = []
    prereads = []

    for line in f:
        N, preread, instruct, access, misses, aperf, mperf, mem_loads = tuple( float(x) for count, x in enumerate( line.rstrip( "\n" ).split(" ") , 1) if count <= 8 )
        if N == size and preread < 22:
          frequency = 2.6 * aperf / mperf
          mem_load = mem_loads / aperf
          miss = misses / instruct
          time = aperf / frequency / 1E9
          times.append( time )
          freq.append( frequency )
          misses_per_cycle.append( miss )
          mem.append( mem_load )
          prereads.append( preread )
          print(time, frequency, aperf )
    return prereads, freq, mem, misses_per_cycle, times

def plot_matrix( x, y, label ) -> None:
    plt.scatter( x, y, label=label )

def save_figure( filename: str, xlabel: str, ylabel: str ) -> None:
    plt.xlabel( xlabel )
    plt.ylabel( ylabel )	
    plt.legend()
    plt.savefig( f"{filename}-graph.png" )

if __name__ == "__main__":
    naive_filename = sys.argv[1]
    N = int( sys.argv[2] )
    with open(naive_filename) as f:
        print("opening naive file")
        preread, freq, mem_loads_per_cycle, misses_per_instruct, times = parse_file( f, N )
        plot_matrix( preread, times, f"naive intrinsics threads={ N }" )
        
    save_figure( f"preread_{N}_time_small", "Preread", "time" )
