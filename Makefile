CC=gcc
CFLAGS = -Wall
TARGET=matrix_mult
$(TARGET) : matrixUtil.o naive.o main.o
	$(CC) $(CFLAGS) -o $@ naive.o matrixUtil.o main.o

matrixUtil.o : matrixUtil.h
	$(CC) $(CFLAGS) -c  matrixUtil.c

naive.o : naive.h
	$(CC) $(CFLAGS) -c naive.c

main.o : matrixUtil.h naive.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o
