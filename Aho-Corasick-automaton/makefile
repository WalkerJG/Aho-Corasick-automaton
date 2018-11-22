objects = ACAutomaton.o Queue.o IOManager.o\
          Trie.o RBTree.o StringMatcher.o\
          main.o

acmatch : $(objects) 
	gcc $(objects) -o acmatch
main.o : main.c
	gcc -c main.c 
ACAutomaton.o : ACAutomaton.h ACAutomaton.c
	gcc -c ACAutomaton.c
Queue.o : Queue.h Queue.c
	gcc -c Queue.c
IOManager.o : IOManager.h IOManager.c
	gcc -c IOManager.c
Trie.o : Trie.h Trie.c
	gcc -c Trie.c
RBTree.o : RBTree.h RBTree.c
	gcc -c RBTree.c 
StringMatcher.o : StringMatcher.h StringMatcher.c
	gcc -c StringMatcher.c

clean:
	rm acmatch $(objects)
