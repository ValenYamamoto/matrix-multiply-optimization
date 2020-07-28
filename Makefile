CC=gcc
CFLAGS = -Wall
TARGET=matrix_mult
DEBUG = 0;

naive: matrixUtil.o naive.o main.o
	$(CC) $(CFLAGS) -o $@ naive.o matrixUtil.o main.o -pthread -lm

matrixUtil.o : matrixUtil.h matrixUtil.c
	$(CC) $(CFLAGS) -c  matrixUtil.c

naive.o : naive.h naive.c
	$(CC) $(CFLAGS) -c naive.c

main.o : matrixUtil.h naive.h main_p1.c
#	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -c main_p1.c -o main.o

strassen: matrixUtil.o main_strassen.o strassen.o
	$(CC) $(CFLAGS) -o $@  strassen.o matrixUtil.o main_strassen.o -pthread

strassen.o: strassen.c strassen.h matrixUtil.h
	$(CC) $(CFLAGS) -c strassen.c -o strassen.o

main_strassen.o: main_strassen.c strassen.h matrixUtil.h
	$(CC) $(CFLAGS) -c main_strassen.c -o main_strassen.o

runnaive:
	./naive $(N) test_cases/x$(N) test_cases/y$(N) test_cases/a$(N) $(THREADS) $(DEBUG)

runnaive_noecho:
	@./naive $(N) test_cases/x$(N) test_cases/y$(N) test_cases/a$(N) $(THREADS) $(DEBUG)

runstrassen:
	./strassen $(N) test_cases/x$(N) test_cases/y$(N) test_cases/a$(N) $(DEBUG) 

runstrassen_noecho:
	@./strassen $(N) test_cases/x$(N) test_cases/y$(N) test_cases/a$(N) $(DEBUG) 

clean:
	rm -f *.o

cleanlogs:
	rm -f naive_output_* strassen_output_*
