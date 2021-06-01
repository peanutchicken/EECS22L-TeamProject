# Root level makefile for chessgame project
# This allows make to be called from the top level project directory, and it will compile everything
# in ./src/

# subdirectories (obviously)
CC = gcc
CFLAGS = -c -ansi -std=c99 -Wall
LFLAGS = -ansi -std=c99 -Wall
#SUBDIRS = src
OBJECTS = $(addprefix bin/, ai.o board.o fileio.o  legalityCheck.o main.o server.o movelist.o)
CLIENT_OBJECTS = $(addprefix bin/, gameClient.o)

all: bin/chessGame bin/gameClient

#up arrow (^) reduces amount of code in makefile, fills all dependencies with $(OBJECTS)
#$@ declares what I want object to be generated to, placeholder filled by name of makefile item
bin/chessGame: $(OBJECTS)
	$(CC) $(LFLAGS) -DNDEBUG $^ -o $@

#compile client program
bin/gameClient: $(CLIENT_OBJECTS)
	$(CC) $(LFLAGS) -DNDEBUG $^ -o $@

# compiles all files ending in .c in src/ 
# $< is used when you only have one field that you want to fill in (in this case test.c), only fills 
# 	one file name in that placeholder
bin/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@
	

clean:
	rm -f bin/*.o bin/chessGame



