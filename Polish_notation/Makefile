CC=gcc
CFLAGS=-Wall -Wextra -Werror


all: graph

graph: read_string.o struct_token.o graph.o
	$(CC) $(CFLAGS) graph.o read_string.o struct_token.o -o ../build/graph

read_string.o: read_string.c read_string.h
	$(CC) $(CFLAGS) -c read_string.c -o read_string.o

struct_token.o: struct_token.c struct_token.h
	$(CC) $(CFLAGS) -c struct_token.c -o struct_token.o

graph.o: graph.c read_string.h struct_token.h
	$(CC) $(CFLAGS) -c graph.c -o graph.o


clean:
	rm -f *.o ../build/graph

rebuild: clean all
