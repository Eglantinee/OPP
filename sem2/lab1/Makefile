all: main

main: main.o data.o data.h
	gcc main.o data.o -o main -lpthread
main.o: main.c
	gcc -c -Wall -Wextra main.c
data.o: data.c
	gcc -c -Wall -Wextra -O2 data.c

clean:
	rm -rf *.o main
