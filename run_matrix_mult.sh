#!/bin/bash
TIMESTAMP=$(date +"%Y-%m-%d-%H%M%S")
OUTPUT_FILE=./matrix_output_$TIMESTAMP
echo "Output file: $OUTPUT_FILE"
touch $OUTPUT_FILE
touch_pid=$!
wait $touch_pid
for x in $@; do
	python3 get_matrix_stats.py $x  >> "$OUTPUT_FILE"
done
