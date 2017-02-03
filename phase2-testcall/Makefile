all: example2 

example: example2.o
	gcc -o example2 example2.o

example.o: example2.c
	gcc -c example2.c

clean:
	rm -rf example2 example2.o

