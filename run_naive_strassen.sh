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
for x in $@ ; 
do
	echo "$x $( make runnaive_noecho N=$x THREADS=1 | awk '{print $2}' )" >> "$NAIVE_OUTPUT"
	echo "$x $( make runnaive_noecho N=$x THREADS=1 | awk '{print $2}' )" >> "$NAIVE_OUTPUT"
	echo "$x $( make runnaive_noecho N=$x THREADS=1 | awk '{print $2}' )" >> "$NAIVE_OUTPUT"

	echo "$x $( make runstrassen_noecho N=$x | awk '{print $2}' )" >> "$STRASSEN_OUTPUT"
	echo "$x $( make runstrassen_noecho N=$x | awk '{print $2}' )" >> "$STRASSEN_OUTPUT"
	echo "$x $( make runstrassen_noecho N=$x | awk '{print $2}' )" >> "$STRASSEN_OUTPUT"
done
python3 plot_matrix_data.py "$NAIVE_OUTPUT" "$STRASSEN_OUTPUT"

