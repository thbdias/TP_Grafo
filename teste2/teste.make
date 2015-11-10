all: main

main: Main.o Cachorro.o
		g++ -o Main Main.o Cachorro.o

Main.o: Main.cpp
		g++ -c Main.cpp

Cachorro.o: Cachorro.cpp
		g++ -c Cachorro.cpp

//Makefile