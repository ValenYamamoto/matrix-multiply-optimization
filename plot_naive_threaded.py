import sys
import matplotlib.pyplot as plt
import math
from plot_matrix_data import parse_file as original_parse

def parse_file( f: "file", size: int ) -> (list, list):
    sizes = []
    freq = []
    mem = []
    misses_per_cycle = []
    times = []
    threads = []
    instructions = []

    for line in f:
        thread, N, instruct, access, misses, aperf, mperf, mem_loads = tuple( float(x) for count, x in enumerate( line.rstrip( "\n" ).split(" ") , 1) if count <= 8 )
        if thread == size:
          frequency = 2.6 * aperf / mperf
          mem_load = mem_loads / aperf
          miss = misses / instruct
          time = aperf / frequency / 1E9
          instructions_per_cycle = instruct / aperf
          times.append( time )
          freq.append( frequency )
          misses_per_cycle.append( miss )
          mem.append( mem_load )
          #threads.append( thread )
          sizes.append( N )
          instructions.append( instructions_per_cycle )
          print(time, frequency, aperf )
    return sizes, freq, instructions, mem, misses_per_cycle, times

def parse_strassen_file( f: "file" ) -> (list, list):
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

def plot_matrix( x, y, label, marker="o" ) -> None:
    plt.scatter( x, y, label=label, marker=marker )

def save_figure( filename: str, xlabel: str, ylabel: str ) -> None:
    plt.xlabel( xlabel )
    plt.ylabel( ylabel )	
    plt.legend()
    plt.savefig( f"{filename}-graph.png" )

if __name__ == "__main__":
    naive_filename = sys.argv[1]
    strassen_filename = sys.argv[2]
    N = int( sys.argv[3] )
    original_naive = sys.argv[4]
    original_strassen = sys.argv[5]

    with open(naive_filename) as f:
        print("opening naive file")
        sizes, freq, instruct_per_cycle, mem_loads_per_cycle, misses_per_instruct, times = parse_file( f, N )
        logs = [ math.log( x ) for x in times ]
        plot_matrix( sizes, logs, f"naive parallelized threads={ N }" )
    with open(strassen_filename) as f:
        print("opening naive file")
        sizes, freq, misses_per_instruct, times = parse_strassen_file( f )
        logs = [ math.log( x ) for x in times ]
        plot_matrix( sizes, logs, f"strassen parallelized threads={ N }" )
    with open(original_naive) as f:
        print("opening naive file")
        sizes, times = original_parse( f )
        logs = [ math.log( x ) for x in times ]
        plot_matrix( sizes, logs, f"Original Unthreaded Naive", marker='x' )
    with open(original_strassen) as f:
        print("opening naive file")
        sizes, times = original_parse( f )
        logs = [ math.log( x ) for x in times ]
        plot_matrix( sizes, logs, f"Original Unthreaded Strassen", marker='x' )
        
    save_figure( f"compare_all_log", "matrix size", "ln( time )" )
