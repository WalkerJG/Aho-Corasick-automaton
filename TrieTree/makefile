objects = IOManager.o Trie.o RBTree.o\
	  StringMatcher.o\
          main.o

triematch : $(objects) 
	gcc $(objects) -o triematch 
main.o : main.c
	gcc -c main.c 
IOManager.o : IOManager.h IOManager.c
	gcc -c IOManager.c
Trie.o : Trie.h Trie.c
	gcc -c Trie.c
RBTree.o : RBTree.h RBTree.c
	gcc -c RBTree.c 
StringMatcher.o : StringMatcher.h StringMatcher.c
	gcc -c StringMatcher.c

clean:
	rm triematch $(objects)
