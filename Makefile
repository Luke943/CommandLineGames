all:
	gcc -o hangman hangman.c
	g++ -o tetris tetris.cpp
	g++ -o ufo ufo.cpp ufo_functions.cpp

hangman:
	gcc -o hangman hangman.c

tetris:
	g++ -o tetris tetris.cpp

ufo:
	g++ -o ufo ufo.cpp ufo_functions.cpp
