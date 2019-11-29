all: arvoreB

arvoreB: main.o arvoreB.o
	gcc -o arvoreB main.o arvoreB.o

main.o: main.c arvoreB.h
	gcc -o main.o main.c -c

arvoreB.o: arvoreB.c arvoreB.h
	gcc -o arvoreB.o arvoreB.c -c

clean:
	rm -rf *.o*~ arvoreB