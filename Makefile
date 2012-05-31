CC = gcc
CFLAGS = -pedantic -ansi -Wall -Wstrict-prototypes

all:
	mkdir -p bin
	$(CC) $(CFLAGS) src/emulator.c src/main.c -o bin/4917

clean:
	rm -rf bin/

install:
	