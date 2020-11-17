all: compile_str compile_test compile_test_str link

compile_str: src/str.c
	gcc -c src/str.c -o obj/str.o -I include

compile_test: src/test.c
	gcc -c src/test.c -o obj/test.o -I include

compile_test_str: src/test_str.c
	gcc -c src/test_str.c -o obj/test_str.o -I include

link: obj/str.o obj/test.o obj/test_str.o
	gcc obj/str.o obj/test.o obj/test_str.o -o lab_02

clean: obj/*.o lab_02
	rm obj/*.o lab_02