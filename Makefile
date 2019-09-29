all: main.c list.c 
	gcc -g main.c list.c -o list.o

clean:
	rm *.o


