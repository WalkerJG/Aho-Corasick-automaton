#include <stdio.h>
#include "Trie.h"
int main() {
	printf("%s", "hello trie.");
	Trie trie;
	_constructTrie(&trie, NULL, 0);
	InsertKeyword(&trie, "�ҵ���");
	InsertKeyword(&trie, "��Ҫ");
	QueryKeyword(&trie, "��Ҫ");
	QueryKeyword(&trie, "�ҵ�");
	QueryKeyword(&trie, "���˸�ȥ");
	QueryKeyword(&trie, "�ҵ���");

	_deconstructTrie(&trie);
	return 0;
}