#!/bin/bash
TIMESTAMP=$(date +"%Y-%m-%d-%H%M%S")
NAIVE_OUTPUT=./naive_better_4096_$TIMESTAMP
touch $NAIVE_OUTPUT

for NUM_THREADS in 4 7 8 12 16 20 24 28 32; #$(seq 4 2 32 ); 
do
  for SIZE in 256 512 1024 2048 4096
  do
	  echo "$NUM_THREADS $SIZE $( make runnaive_noecho N=$SIZE THREADS=$NUM_THREADS )" >> "$NAIVE_OUTPUT"
	  echo "$NUM_THREADS $SIZE $( make runnaive_noecho N=$SIZE THREADS=$NUM_THREADS )" >> "$NAIVE_OUTPUT"
    echo "$NUM_THREADS $SIZE $( make runnaive_noecho N=$SIZE THREADS=$NUM_THREADS )" >> "$NAIVE_OUTPUT"
  done
done
#python3 plot_matrix_data.py "$NAIVE_OUTPUT" "$STRASSEN_OUTPUT"

