#	Writen by: Oscar Bergström
#   https://github.com/OSCARJFB

lib: loglib.c loglib.h
	cc -c loglib.c

tests: testA.c testB.c loglib.o
	cc testA.c loglib.o -o testA.o
	cc testB.c loglib.o -o testB.o

clean: 
	rm -rf *.o 
	rm -rf *.log