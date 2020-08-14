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
