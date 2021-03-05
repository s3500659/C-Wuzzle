###############################################################################
# Student Name    : Vinh Duc Tran
# RMIT Student ID : S3500659
#
# Startup code provided by Paul Miller for use in "Programming in C",
# Assignment 2, study period 4, 2020.
###############################################################################

# -*- MakeFile -*-

wuzzle-c: board.o game.o io.o player.o rules-b.o score_list.o shared.o word_list.o wuzzle.o
	gcc -ansi -Wall -pedantic board.o game.o io.o player.o rules-b.o score_list.o shared.o word_list.o wuzzle.o -o wuzzle-c

board.o: board.c
	gcc -ansi -Wall -pedantic -c board.c

game.o: game.c
	gcc -ansi -Wall -pedantic -c game.c

io.o: io.c
	gcc -ansi -Wall -pedantic -c io.c

player.o: player.c
	gcc -ansi -Wall -pedantic -c player.c

rules-b.o: rules-b.c
	gcc -ansi -Wall -pedantic -c rules-b.c

score_list.o: score_list.c
	gcc -ansi -Wall -pedantic -c score_list.c

shared.o: shared.c
	gcc -ansi -Wall -pedantic -c shared.c

word_list.o: word_list.c
	gcc -ansi -Wall -pedantic -c word_list.c

wuzzle.o: wuzzle.c
	gcc -ansi -Wall -pedantic -c wuzzle.c

clean:
	rm -f *.o wuzzle-c