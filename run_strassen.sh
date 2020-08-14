##!/bin/bash
TIMESTAMP=$(date +"%Y-%m-%d-%H%M%S")
STRASSEN_OUTPUT=./strassen_$TIMESTAMP
touch $STRASSEN_OUTPUT
# touch_pid=$!
# wait $touch_pid
# echo $@
# SIZES=$( sed 's/\r//' <($@) )
# echo $SIZES
for x in 128 256 512 1024 2048 4096 ; 
do
	echo "$x $( numactl -C 0-6 make runstrassen_noecho N=$x )" >> "$STRASSEN_OUTPUT" 
	echo "$x $( numactl -C 0-6 make runstrassen_noecho N=$x )" >> "$STRASSEN_OUTPUT" 
	echo "$x $( numactl -C 0-6 make runstrassen_noecho N=$x )" >> "$STRASSEN_OUTPUT" 
done
# python3 plot_matrix_data.py "$NAIVE_OUTPUT" "$STRASSEN_OUTPUT"

