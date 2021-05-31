#Makefile for EECS22L Team03 Chess Project

#this is where library name will go
DESIGN = chessGame testChessGame testclient
LIBS = 

#makefile var defs
CC  = gcc
DEBUG  = -DDEBUG -g  # used for debug version only; for normal program, need to add manually
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -ansi -std=c99 -Wall
AR     = ar rc
RANLIB = ranlib

all: chessGame testChessGame testclient

########################################
#Generate object files
########################################

board.o: board.c board.h legalityCheck.h
	$(CC) $(CFLAGS) board.c -o board.o

movelist.o: movelist.c movelist.h
	$(CC) $(CFLAGS) movelist.c -o movelist.o

ai.o: ai.c ai.h
	$(CC) $(CFLAGS) ai.c -o ai.o
	
legalityCheck.o: legalityCheck.c legalityCheck.h
	$(CC) $(CFLAGS) legalityCheck.c -o legalityCheck.o

fileio.o: fileio.c fileio.h
	$(CC) $(CFLAGS) fileio.c -o fileio.o

main.o: main.c board.c board.h movelist.c movelist.h ai.c ai.h legalityCheck.c legalityCheck.h fileio.c fileio.h
	$(CC) $(CFLAGS) main.c -o main.o

server.o: server.c server.h
	$(CC) $(CFLAGS) server.c -o server.o

testclient.o: testclient.c
	$(CC) $(CFLAGS) testclient.c -o testclient.o

#just because a main debug target exists DOES NOT mean that debug is enabled on all other object files
DEBUG_main.o: main.c board.c board.h movelist.c movelist.h ai.c ai.h legalityCheck.c legalityCheck.h fileio.c fileio.h
	$(CC) $(CFLAGS) $(DEBUG) main.c -o DEBUG_main.o


########################################
#Generate Executables
########################################

chessGame: main.o board.o movelist.o ai.o legalityCheck.o fileio.o server.o
	$(CC) $(LFLAGS) -DNDEBUG main.o board.o movelist.o ai.o legalityCheck.o fileio.o -o chessGame

testChessGame: DEBUG_main.o board.o movelist.o ai.o legalityCheck.o fileio.o
	$(CC) $(LFLAGS) $(DEBUG) DEBUG_main.o board.o movelist.o ai.o legalityCheck.o fileio.o -o testChessGame

testclient: testclient.o
	$(CC) $(LFLAGS) testclient.o -o testclient

server: server.o
	$(CC) $(LFLAGS) server.o -o server

#MAKE TARGET TO TAR PACKAGE
#tar:

#target to clean directory
clean:
	rm -f *.o $(DESIGN) $(LIBS)
	rm -f *.swp


