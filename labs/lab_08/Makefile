all: obj obj/matrix.o obj/shared_ptr.o obj/main.o lab_08

obj:
	if [ ! -d "obj" ]; then mkdir "obj"; fi

obj/matrix.o: src/matrix.cpp include/matrix.h
	g++ -c -std=c++17 -Wall -Wextra -Werror src/matrix.cpp -o obj/matrix.o -I include

obj/shared_ptr.o: src/shared_ptr.cpp include/shared_ptr.h include/matrix.h
	g++ -c -std=c++17 -Wall -Wextra -Werror src/shared_ptr.cpp -o obj/shared_ptr.o -I include

obj/main.o: src/main.cpp include/shared_ptr.h include/matrix.h
	g++ -c -std=c++17 -Wall -Wextra -Werror src/main.cpp -o obj/main.o -I include

lab_08: obj obj/matrix.o obj/shared_ptr.o obj/main.o
	g++ -std=c++17 obj/matrix.o obj/shared_ptr.o obj/main.o -o lab_08

clean:
	rm obj/* lab_08
	rmdir obj