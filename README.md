# Matrix Multiplication Optimization
## Project done as part of LLNL HPC Cluster Engineer Academy

This project analysized matrix multiplication algorithms in an HPC environment.
Analysis was helped by Intel MSRs, enabled by LLNL msr-safe kernel module and
interface. Intel Intrinsics SSE 4.1 instruction libraries were used to help
optimize.

### Environment
Experiment was developed for and executed on Intel Xeon E5-2670 @ 2.6 Hz. Node
had two sockets, each with a cpu with 8 cores and 2 threads per core.

### Generating Test Matrices
Standard test matrices are made and written to files by R to be used as inputs
and known correct answers for checking correctness of algorithm. To generate
test matrices, type:
```bash
Rscript generate_test_cases.R 256
```
where 256 is the size of the matrix

### Naive Matrix Multiply
To make matrix multiplication without Intel Intrinsics libraries, type:
```bash
make naive
```

To run matrix multiplication without Intel Intrinsics, type:
```bash
make runnaive N=256 THREADS=8
```
where N is the size of the matrix NxN and THREADS is the number of threads to
run with

To make naive algorithm with Intel Intrinsics libraries, type:
```bash
make naive_intrinsics
```

To run Intel Intrinsics naive algorithm, type:
```bash
make runnaive_intrinsics N=256 THREADS=8
```
where N is the size of the matrix NxN and THREADS is the number of threads to
run with

To make naive algorithm with single-precision floating point numbers instead of double-precision, type:
```bash
make naive_float
```

To run naive algorithm with single-precision floating points, type:
```bash
make runnaive_float N=256 THREADS=8
```
where N is the size of the matrix NxN and THREADS is the number of threads to
run with. This may result in errors due to a lack of precision.

### Strassen Matrix Multiply
To make strassen multiplication, type:
```bash
make strassen
```

To run the strassen multiplication algorithm, type:
```bash
make runstrassen N=256
```
where N is the size of the matrix NxN.

### Naive Analysis
On the initial unoptimized matrix multiplication, as the matrix size increases,
the instructions per cycle decreases dramaticaly

![Image of Instructions Graph](https://github.com/ValenYamamoto/matrix-multiply-optimization/blob/master/graphs/threaded_naive_8_instructions-graph.png)

At the same time, as the matrix size increase, the cache misses per instruction 
increases.

![Image of Cache Misses Graph](https://github.com/ValenYamamoto/matrix-multiply-optimization/blob/master/graphs/threaded_naive_8_misses-graph.png)

Therefore, it seems like as the matrix size increases, the function becomes 
increasingly more memory bound

To solve this, read and saved 6 values ahead in order to have faster and less reads to RAM,
instead pulling these values into cache. This dramatically speed up the time.

![Image of Naive Better Graph](https://github.com/ValenYamamoto/matrix-multiply-optimization/blob/master/graphs/compare_naive_16_times-graph.png)

Additionally, I did experiments with Intel Intrinsics SSE instructions. Because of the size of
the cache, it seemed like more than just 6 values could be saved for fast access. In order
to get around whether or not the compiler would unroll the loops, used generate_code.py
file to generate multiply functions.

![Image of Intrinsics Graph](https://github.com/ValenYamamoto/matrix-multiply-optimization/blob/master/graphs/preread_32-graph.png)

Focusing on the beginning of the graph, we can see the the most consistently faster 
amount of entries saved is 8, which seems significantly smaller than the size of 
cache, which merits some more investigation.

![Image of Focused Intrinsics Graph](https://github.com/ValenYamamoto/matrix-multiply-optimization/blob/master/graphs/preread_32_time_small-graph.png)

### Strassen Analysis
Strassen's matrix multiplication algorithm is a recursive matrix multiplication 
algorithm which trades less multiplications for more addition and subtraction
operations.

Initially, I had the base case at N=1. Compared to the naive algorithm, the 
strassen lagged behind the naive until the matrices got bigger than 
N=4096 at which point the unoptimized single threaded strassen was 
faster than the single threaded naive.

![Image of initial comparison](https://github.com/ValenYamamoto/matrix-multiply-optimization/blob/master/graphs/comparison-graph.png)

With both axes taken to log base 2

![Image of initial comparison log](https://github.com/ValenYamamoto/matrix-multiply-optimization/blob/master/graphs/log-comparison-graph.png)

To optimize, I took the base case out to N=2 and used Intel Intrinsics
to the base multiplication and used Intrinsics to make the intermediate
matrices, which dramatically lowered the execution time.

![Image of strassen optimization](https://github.com/ValenYamamoto/matrix-multiply-optimization/blob/master/graphs/strassen-graph.png)

With time natural log

![Image of strassen log] (https://github.com/ValenYamamoto/matrix-multiply-optimization/blob/master/graphs/strassen_log-graph.png)

