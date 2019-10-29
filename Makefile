CC=gcc
CFLAGS=-g

all: main list
	$(CC) $(CFLAGS) -o example.o main.o list.o

main: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

list: list.c 
	$(CC) $(CFLAGS) -c list.c -o list.o

clean:
	rm *.o


