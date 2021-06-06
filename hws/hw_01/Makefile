all: obj obj/bmp.o obj/main.o hw_01

obj: 
	if [ ! -d "obj" ]; then mkdir "obj"; fi

obj/bmp.o: src/bmp.c include/bmp.h
	gcc -c -Wall -Wextra -Werror src/bmp.c -o obj/bmp.o -I include

obj/main.o: src/main.c include/bmp.h
	gcc -c -Wall -Wextra -Werror src/main.c -o obj/main.o -I include

hw_01: obj obj/bmp.o obj/main.o
	gcc obj/bmp.o obj/main.o -o hw_01

clean:
	rm obj/* hw_01
	rmdir obj