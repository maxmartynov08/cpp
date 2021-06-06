all: obj obj/matrix.o obj/main.o lab_07

obj:
	if [ ! -d "obj" ]; then mkdir "obj"; fi

obj/matrix.o: src/matrix.cpp include/matrix.h
	g++ -c -std=c++17 -Wall -Wextra -Werror src/matrix.cpp -o obj/matrix.o -I include

obj/main.o: src/main.cpp include/matrix.h
	g++ -c -std=c++17 -Wall -Wextra -Werror src/main.cpp -o obj/main.o -I include

lab_07: obj obj/matrix.o obj/main.o
	g++ -std=c++17 obj/matrix.o obj/main.o -o lab_07

clean:
	rm obj/* lab_07
	rmdir obj