#!/usr/bin/env Rscript
args = commandArgs( trailingOnly=TRUE )
N_string = args[1]
N = as.numeric( N_string )

x <- matrix( rnorm(N * N), N, N )
y <- matrix( rnorm(N * N), N, N )

a <- x %*% y
b <- y %*% x

write.table( x, file=paste( "x", N_string, sep=""), row.names=FALSE, col.names=FALSE )
write.table( y, file=paste( "y", N_string, sep=""), row.names=FALSE, col.names=FALSE )
write.table( a, file=paste( "a", N_string, sep=""), row.names=FALSE, col.names=FALSE )
write.table( b, file=paste( "b", N_string, sep=""), row.names=FALSE, col.names=FALSE )
