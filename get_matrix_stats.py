#!/bin/python3
import os
import sys
import numpy


def process_stream( stream: "iterable" ) -> int:
	iterable = iter( stream )
	output = next( iterable )
	correct, usec = tuple( int(x) for x in output.rstrip( "\n" ). split( " " ))
	if correct:
		return usec
	return -1

def generate_test_file_names( n: int, answer_file: "a" or "b" ):
	if answer_file == "a":
		return tuple( f"test_cases/{name}{str(n)}" for name in ( "x", "y", "a") )
	return tuple( f"{name}{str(n)}" for name in ( "y", "x", "b") )


if __name__ == "__main__":
	N = int( sys.argv[1] )
	
	answers = []
	
	for _ in range(100):
		stream = os.popen( f'./matrix_mult {N} {" ".join( generate_test_file_names( N, "a" ) )} ')
		exetime = process_stream( stream ) 
		if exetime != -1:
			answers.append(exetime)
		stream.close()

	print( f"------------Matrix Size N={N}-------------" )
	print( f"Mean: {numpy.mean( answers )}" )
	print( f"Std Dev: {numpy.std( answers, ddof=1 )}" )
	
