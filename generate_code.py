#!/bin/python3

def make_code( x: int, f: "open file" ) -> None:
  f.write(f"void* naiveMultiply_parallel_intrinsics_{ x }( void *thread_args )" + "\n{\n" )
  f.write(" int i, j, k, start, end;\n\n");
  
  f.write(" struct thread_info *args = ( struct thread_info * ) thread_args;\n")
  f.write(" double *m1 = args->m1;\n")
  f.write(" double *m2 = args->m2;\n")
  f.write(" double *result = args->answer;\n\n")
  
  f.write(" long n = args->size;\n")
  f.write(" start = args->start;\n")
  f.write(" end = args->end;\n")

  num_arrays = x//2;
  s = " double " + ", ".join( f"a{i+1}[2], b{i+1}[2]" for i in range( num_arrays ) ) + ";\n\n"
  f.write( s )
  f.write( "  double c;\n\n" )

  s = " __m128d " + ", ".join( f"t{i}" for i in range( x ) ) + ";\n\n"
  f.write( s )

  f.write( "  j = 0;\n" )
  f.write( "  for ( i = start; i < end; i++ )" + "\n{\n" ) 
  f.write( f"    for ( k = 0; k < n; k+={ x } )" + "\n{\n" ) 
	
  for i in range( num_arrays ):
    f.write( f"     if( k + {2*i} < n ) " + "{\n" )
    f.write( f"       a{i+1}[0] = *( m1 + n * i + (k+{2*i}) );" + "\n")
    f.write( "     } else {\n" )
    f.write( f"       a{i+1}[0] = 0;" + "\n")
    f.write( "     }\n" )

    f.write( f"     if( k + {2*i+1} < n ) " + "{\n" )
    f.write( f"       a{i+1}[1] = *( m1 + n * i + (k+{2*i+1}) );" + "\n")
    f.write( "     } else {\n" )
    f.write( f"       a{i+1}[1] = 0;" + "\n")
    f.write( "     }\n")

  for i in range( num_arrays ):
    f.write( f"     t{2*i} = _mm_load_pd( a{i+1} );\n" )
  f.write( "\n" )

  f.write( "      for ( j = 0; j < n; j++ )\n{\n" )
  for i in range( num_arrays ):
    f.write( f"       if( k + {2*i} < n ) " + "{\n" )
    f.write( f"         b{i+1}[0] = *( m2 + n * (k+{2*i}) + j );\n")
    f.write( "       } else {\n" )
    f.write( f"         b{i+1}[0] = 0;\n")
    f.write( "       }\n" )

    f.write( f"      if( k + {2*i+1} < n ) " + "{\n" )
    f.write( f"        b{i+1}[1] = *( m2 + n * (k+{2*i+1}) + j );\n")
    f.write( "      } else {\n" )
    f.write( f"        b{i+1}[1] = 0;\n")
    f.write( "      }\n")

  for i in range( num_arrays ):
    f.write( f"       t{2*i+1} = _mm_load_pd( b{i+1} );\n" )

  for i in range( num_arrays ):
    f.write( f"       t{2*i+1} = _mm_dp_pd( t{2*i}, t{2*i+1}, 0xff );\n" )

  f.write( "\n" )
  
  for i in range( num_arrays ):
    f.write( f"       _mm_storel_pd( &c, t{2*i+1} );\n" )
    f.write( f"       *( result + n * i + j ) += c;\n" )
  f.write( "     }\n" )
  f.write( "   }\n" )
  f.write( " }\n" )
  f.write( " pthread_exit( NULL );\n" )
  f.write( "}\n" )

with open( "naive_generated.c", "a" ) as f:
  make_code( 64, f )
  make_code( 128, f )
  make_code( 256, f )
  make_code( 512, f )
  make_code( 80, f )
  make_code( 40, f )
