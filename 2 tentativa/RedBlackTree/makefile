all: redBlackTree

redBlackTree: main.o redBlackTree.o
	gcc -o redBlackTree main.o redBlackTree.o

main.o: main.c redBlackTree.h
	gcc -o main.o main.c -c

redBlackTree.o: redBlackTree.c redBlackTree.h
	gcc -o redBlackTree.o redBlackTree.c -c

clean:
	rm -rf *.o*~ redBlackTree