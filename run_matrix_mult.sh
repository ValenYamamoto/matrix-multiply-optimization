#!/bin/bash
TIMESTAMP=$(date +"%Y-%m-%d-%H%M%S")
OUTPUT_FILE=./matrix_output_$TIMESTAMP
echo "Output file: $OUTPUT_FILE"
touch $OUTPUT_FILE
touch_pid=$!
wait $touch_pid
ls ~/matrix-multiply-optimization/
for x in $@; do
	python3 get_matrix_stats.py $x  >> "~/matrix-multiply-optimization/$OUTPUT_FLIE"
done
