CC=gcc
CFLAGS=-O3 -Wall
# LIBS=-pthread
LIBS=-fopenmp

all: server.out client.out
server.out: server.o
	$(CC) $(CFLAGS) $(LIBS) -o server.out server.o
client.out: client.o string.o
	$(CC) $(CFLAGS) $(LIBS) -o client.out client.o string.o
server.o: server_OpenMP.c
	$(CC) $(CFLAGS) -c server.c
string.o: string.c
	$(CC) $(CFLAGS) -c string.c
client.o: client_OpenMP.c
	$(CC) $(CFLAGS) -c client.c

.PHONY: clean
clean:
	rm -f *.o *.out
