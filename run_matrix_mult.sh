#!/bin/bash
for x in $@; do
	A_FILE="test_cases/a$x"
	B_FILE="test_cases/b$x"
	X_FILE="test_cases/x$x"
	Y_FILE="test_cases/y$x"

	echo "------- Matrix size N=$x ---------"
	./a.out $x $X_FILE $Y_FILE $A_FILE
	./a.out $x $Y_FILE $X_FILE $B_FILE
	echo

done
