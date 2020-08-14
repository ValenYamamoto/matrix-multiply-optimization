SHELL=/bin/bash
CC=gcc
CFLAGS = -Wall -march=native
O = -O3
TARGET=matrix_mult
DEBUG = 0
PREREAD=6

naive: matrixUtil.o naive.o main_naive.o msrUtil.o
	$(CC) $(CFLAGS) $(O) -o $@ naive.o matrixUtil.o main_naive.o msrUtil.o -pthread -lm

naive_intrinsics: matrixUtil.o naive.o main_naive_intrinsics.o msrUtil.o naive_generated.o
	$(CC) $(CFLAGS) $(O) -o $@ naive.o matrixUtil.o main_naive_intrinsics.o msrUtil.o naive_generated.o -pthread -lm

matrixUtil.o : matrixUtil.h matrixUtil.c
	$(CC) $(CFLAGS) -c  matrixUtil.c

msrUtil.o : msrUtil.h msrUtil.c
	$(CC) $(CFLAGS) -c  msrUtil.c

naive.o : naive.h naive.c
	$(CC) $(CFLAGS) -c naive.c

main_naive.o : matrixUtil.h naive.h main_naive.c
	$(CC) $(CFLAGS) -c main_naive.c

main_naive_intrinsics.o : matrixUtil.h naive.h main_naive_intrinsics.c
	$(CC) $(CFLAGS) -c main_naive_intrinsics.c 

naive_generated.o: naive_generated.c matrixUtil.h
	$(CC) -march=native -c naive_generated.c

naive_float: matrixUtil.o naive.o msrUtil.o main_naive_float.o
	$(CC) $(CFLAGS) $(O) -o $@ naive.o msrUtil.o main_naive_float.o matrixUtil.o -pthread -lm

main_naive_float.o : matrixUtil.h naive.h main_naive_float.c
	$(CC) $(CFLAGS) -c main_naive_float.c 

strassen: matrixUtil.o main_strassen.o strassen.o
	$(CC) $(CFLAGS) -o $@  strassen.o matrixUtil.o main_strassen.o -pthread

strassen.o: strassen.c strassen.h matrixUtil.h
	$(CC) $(CFLAGS) $(O) -c strassen.c -o strassen.o

main_strassen.o: main_strassen.c strassen.h matrixUtil.h
	$(CC) $(CFLAGS) -c main_strassen.c -o main_strassen.o

runnaive:
	numactl -C 0-$$(( $(THREADS) - 1 )) ./naive $(N) test_cases/x$(N) test_cases/y$(N) test_cases/a$(N) $(THREADS) $(DEBUG)

runnaive_noecho:
	@numactl -C 0-$$(( $(THREADS) - 1 )) ./naive $(N) test_cases/x$(N) test_cases/y$(N) test_cases/a$(N) $(THREADS) $(DEBUG)

runnaive_intrinsics:
	numactl -C 0-$$(( $(THREADS) - 1 )) ./naive_intrinsics $(N) test_cases/x$(N) test_cases/y$(N) test_cases/a$(N) $(THREADS) $(PREREAD) $(DEBUG)

runnaive_intrinsics_noecho:
	@numactl -C 0-$$(( $(THREADS) - 1 )) ./naive_intrinsics $(N) test_cases/x$(N) test_cases/y$(N) test_cases/a$(N) $(THREADS) $(PREREAD) $(DEBUG)

runstrassen:
	numactl -C 0-6 ./strassen $(N) test_cases/x$(N) test_cases/y$(N) test_cases/a$(N) $(DEBUG) 

runstrassen_noecho:
	@./strassen $(N) test_cases/x$(N) test_cases/y$(N) test_cases/a$(N) $(DEBUG) 

runnaivefloat:
	numactl -C 0-$$(( $(THREADS) - 1 )) ./naive_float $(N) test_cases/x$(N) test_cases/y$(N) test_cases/a$(N) $(THREADS) $(DEBUG)

clean:
	rm -f *.o

cleanlogs:
	rm -f naive_output_* strassen_output_*
