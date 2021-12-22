CC=g++
CPPFLAGS=-O2 -Wall -std=c++11
TARGET=main

all: $(TARGET).cpp
	$(CC) $(CPPFLAGS) -o $(TARGET).out $<

DFS: ADM_Graph_with_DFS.cpp
	$(CC) $(CPPFLAGS) ADM_Graph_with_DFS.cpp -o a.out
	./a.out < graph_ADM.in

clean:
	rm *.out

