all: obj obj/my_vector.o obj/main.o lab_06

obj:
	if [ ! -d "obj" ]; then mkdir "obj"; fi

obj/my_vector.o: src/my_vector.cpp include/my_vector.h
	g++ -c -std=c++17 -Wall -Wextra -Werror src/my_vector.cpp -o obj/my_vector.o -I include

obj/main.o: src/main.cpp include/my_vector.h
	g++ -c -std=c++17 -Wall -Wextra -Werror src/main.cpp -o obj/main.o -I include

lab_06: obj obj/my_vector.o obj/main.o
	g++ -std=c++17 obj/my_vector.o obj/main.o -o lab_06

clean:
	rm obj/* lab_06
	rmdir obj