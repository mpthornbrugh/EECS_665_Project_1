all:
	gcc -g -w main.cpp -o nfa2dfa

execute:
	./nfa2dfa < small.txt

clean:
	rm -rf *.o nfa2dfa
