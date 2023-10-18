all: item.o skiplist.o main.o
	gcc item.o skiplist.o main.o -o main.exe
item.o: item.c
	gcc -c item.c -o item.o
skiplist.o: skipList.c
	gcc -c skipList.c -o skiplist.o
main.o: main.c
	gcc -c main.c -o main.o
clean:
	rm main.o item.o skiplist.o main.exe
run: all
	./main.exe