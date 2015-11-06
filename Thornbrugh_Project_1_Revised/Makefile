all: main.o
	g++ -g -o nfa2dfa main.o

main.o: main.cpp
	c++ -g -c main.cpp

execute:
	./nfa2dfa < input.txt

clean:
	rm -rf *.o nfa2dfa
