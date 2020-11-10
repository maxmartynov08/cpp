all: compile_main compile_algorithm compile_io compile_util link

compile_main: src/main.c
	gcc -c src/main.c -o bin/main.o

compile_algorithm: src/algorithm.c
	gcc -c src/algorithm.c -o bin/algorithm.o

compile_io: src/io.c
	gcc -c src/io.c -o bin/io.o

compile_util: src/util.c
	gcc -c src/util.c -o bin/util.o

link: bin/main.o bin/algorithm.o bin/io.o bin/util.o
	gcc bin/main.o bin/algorithm.o bin/io.o bin/util.o -o lab1

clean: bin/*.o lab1
	rm bin/*.o lab1 