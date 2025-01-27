all: puissance4.exe

puissance4.exe: puissance4.o main.o
	g++ puissance4.o main.o -o puissance4.exe

puissance4.o: puissance4.cpp
	g++ -c puissance4.cpp

main.o: main.cpp
	g++ -c main.cpp