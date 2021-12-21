CC=g++
CPPFLAGS=-O2 -Wall -std=c++11
TARGET=main

all: $(TARGET).cpp
	$(CC) $(CPPFLAGS) -o $(TARGET).out $<

ADM: ADM-AdjacencyList.cpp
	$(CC) $(CPPFLAGS) ADM-AdjacencyList.cpp -o a.out
	./a.out < graph_ADM.in

easy: easyGraph.cpp
	$(CC) $(CPPFLAGS) easyGraph.cpp -o main.out
	./main.out

clean:
	rm *.out

