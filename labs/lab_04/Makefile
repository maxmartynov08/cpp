all: obj obj/clist.o obj/main.o lab_04

obj: 
	if [ ! -d "obj" ]; then mkdir "obj"; fi

obj/clist.o: src/clist.c include/clist.h
	gcc -c src/clist.c -o obj/clist.o -I include

obj/main.o: src/main.c include/clist.h
	gcc -c src/main.c -o obj/main.o -I include

lab_04: obj obj/clist.o obj/main.o
	gcc obj/clist.o obj/main.o -o lab_04

clean:
	rm obj/* lab_04
	rmdir obj