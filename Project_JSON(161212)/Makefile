#please note that to run the file (i.e under the taget 'run1') the file that is to be read must be typed as a command line argument

run1: object
	./read <file name>
test: 
	gcc -c read.c stack_funct.c myfunct.c 
object: test
	gcc -o read read.o stack_funct.o myfunct.o
run2: object2
	./json
object2: test2
	gcc -o json jsonmake.o
test2:
	gcc -c jsonmake.c
clean:
	 rm -rf *.o
