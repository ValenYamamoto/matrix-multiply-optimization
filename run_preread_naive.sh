#!/bin/bash
TIMESTAMP=$(date +"%Y-%m-%d-%H%M%S")
NAIVE_OUTPUT=./naive_preread_8_$TIMESTAMP
touch $NAIVE_OUTPUT

for NUM_THREADS in $(seq 2 2 32 ); 
do
  for SIZE in 256 512 1024 2048 4096 
  do
	  echo "$NUM_THREADS $SIZE $( make runnaive_intrinsics_noecho N=$SIZE THREADS=$NUM_THREADS PREREAD=8 )" >> "$NAIVE_OUTPUT"
	  echo "$NUM_THREADS $SIZE $( make runnaive_intrinsics_noecho N=$SIZE THREADS=$NUM_THREADS PREREAD=8 )" >> "$NAIVE_OUTPUT"
    echo "$NUM_THREADS $SIZE $( make runnaive_intrinsics_noecho N=$SIZE THREADS=$NUM_THREADS PREREAD=8 )" >> "$NAIVE_OUTPUT"
  done
done
#python3 plot_matrix_data.py "$NAIVE_OUTPUT" "$STRASSEN_OUTPUT"

