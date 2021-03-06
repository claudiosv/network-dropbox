CC=gcc
CFLAGS=-c -Wall -g

all: p1

p1: server.o p1.o
	$(CC) server.o p1.o -o p1 -lpthread -Wno-unused-variable

server.o: server.c
	$(CC) $(CFLAGS) server.c -Wno-unused-variable

p1.o: p1.c
	$(CC) $(CFLAGS) p1.c -Wno-unused-variable

clean:
	/bin/rm -f p1 *.o *.gz

run:
	./p1 8888

tarball:
	tar -cvzf spiess.tar.gz *