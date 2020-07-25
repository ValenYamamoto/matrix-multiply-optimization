##!/bin/bash
TIMESTAMP=$(date +"%Y-%m-%d-%H%M%S")
NAIVE_OUTPUT=./naive_output_$TIMESTAMP
STRASSEN_OUTPUT=./strassen_output_$TIMESTAMP
touch $NAIVE_OUTPUT
touch $STRASSEN_OUTPUT
# touch_pid=$!
# wait $touch_pid
# echo $@
# SIZES=$( sed 's/\r//' <($@) )
# echo $SIZES
for x in "4 8 16 32 64" ; 
do
	echo "$x $( make runnaive_noecho N=$x | awk '{print $2}' )" >> "$NAIVE_FILE"
	echo "$x $( make runstrassen_noecho N=$x | awk '{print $2}' )" >> "$STRASSEN_FILE"
done
# python3 plot_matrix_data.py "$OUTPUT_FILE"

