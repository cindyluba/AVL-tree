CXX=g++

CXXFLAGS= -std=c++1z -Wall -g

all: main

main: main.o avl.o tree25node.o tree25.o
	g++ -o main main.o avl.o tree25node.o tree25.o -lstdc++fs 	

main.o: main.cpp

avl.o: avl.cpp

tree25node.o: tree25node.cpp

tree25.o: tree25.cpp

clean:
	rm -rf *.o main output.txt
