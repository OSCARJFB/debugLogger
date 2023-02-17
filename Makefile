#	Writen by: Oscar Bergström
#   https://github.com/OSCARJFB

lib: loglib.c loglib.h tests.c loglib.o
	cc -c loglib.c; cc tests.c loglib.o -o tests.o

clean: 
	rm -rf *.o