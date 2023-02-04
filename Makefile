#	Writen by: Oscar Bergström
#   https://github.com/OSCARJFB

main: testB.c testB.c
	cc testA.c -DDEBUG -o testA
	cc testB.c -o testB

clean: 
	rm -rf testA
	rm -rf testB
	rm debug.log