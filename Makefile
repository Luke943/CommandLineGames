all:
	gcc -o hangman hangman.c
	g++ -o jim jim.cpp
	g++ -o spock spock.cpp
	g++ -o tetris tetris.cpp
	g++ -o ufo ufo.cpp ufo_functions.cpp

hangman:
	gcc -o hangman hangman.c

jim:
	g++ -o jim jim.cpp

spock: 
	g++ -o spock spock.cpp

tetris:
	g++ -o tetris tetris.cpp

ufo:
	g++ -o ufo ufo.cpp ufo_functions.cpp
