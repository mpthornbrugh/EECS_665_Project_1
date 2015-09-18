all:
	gcc -g -w main.cpp -o nfa2dfa

execute:
	./nfa2dfa < input.txt

clean:
	rm -rf *.o nfa2dfa
