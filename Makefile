all: hangman.exe spock.exe tetris.exe ufo.exe

hangman.exe: hangman.c
	gcc -o hangman.exe hangman.c

spock.exe: spock.cpp
	g++ -o spock.exe spock.cpp

tetris.exe: tetris.cpp
	g++ -o tetris.exe tetris.cpp

ufo.exe: ufo.cpp ufo_functions.cpp
	g++ -o ufo ufo.cpp ufo_functions.cpp

clean:
	rm *.exe