all: example test_syscall

example: example.o
	gcc -o example example.o

example.o: example.c
	gcc -c example.c

test_syscall1: test_syscall.o
	gcc -o test_syscall test_syscall.o

test_syscall1.o: test_syscall.c
	gcc -c test_syscall.c

clean:
	rm -rf example example.o
	rm -rf test_syscall test_syscall.o
