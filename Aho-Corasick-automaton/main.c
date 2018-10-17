#include <stdio.h>
#include "Trie.h"
int main() {
	printf("%s", "hello trie.");
	Trie trie;
	_constructTrie(&trie, NULL, 0);
	InsertKeyword(&trie, "我的天");
	InsertKeyword(&trie, "我要");
	QueryKeyword(&trie, "我要");
	QueryKeyword(&trie, "我的");
	QueryKeyword(&trie, "我了个去");
	QueryKeyword(&trie, "我的天");

	_deconstructTrie(&trie);
	return 0;
}