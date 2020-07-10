CC=gcc
CFLAGS = -Wall
TARGET=matrix_mult
$(TARGET) : matrixUtil.o naive.o main.o
	$(CC) $(CFLAGS) -o $@ naive.o matrixUtil.o main.o

matrixUtil.o : matrixUtil.h matrixUtil.c
	$(CC) $(CFLAGS) -c  matrixUtil.c

naive.o : naive.h naive.c
	$(CC) $(CFLAGS) -c naive.c

main.o : matrixUtil.h naive.h main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o
