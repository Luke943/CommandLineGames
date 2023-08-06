all:
	gcc -o hangman hangman.c
	g++ -o spock spock.cpp
	g++ -o tetris tetris.cpp
	g++ -o ufo ufo.cpp ufo_functions.cpp

hangman:
	gcc -o hangman hangman.c

spock: 
	g++ -o spock spock.cpp

tetris:
	g++ -o tetris tetris.cpp

ufo:
	g++ -o ufo ufo.cpp ufo_functions.cpp
