#include <stdio.h>
#include "ACAutomaton.h"
#include "Queue.h"
#include "malloc.h"
//TODO: Split Trie And ACA, clean code.
int main() {
	printf("%s", "hello trie.");
	//ACAutomaton aca;
	//_constructACA(&aca, NULL, 0);

	/////////////////////////////////////////////////////////////////
	Queue q;
	_constructQueue(&q);
	TreeNodeACA *node, *node2, *node3;
	node = (TreeNodeACA *)(malloc(sizeof(TreeNodeACA)));
	node2 = (TreeNodeACA *)(malloc(sizeof(TreeNodeACA)));
	node3 = (TreeNodeACA *)(malloc(sizeof(TreeNodeACA)));
	//EXPECT_NE(node, NULL);
	AppendQueue(&q, node);
	if (PeekFrontQueue(&q) == node) {

		printf("%s", "Append Correct");
	}
	PopFrontQueue(&q);
	if (PeekFrontQueue(&q) == NULL) {

		printf("%s", "Pop Correct");
	}

	AppendQueue(&q, node2);
	AppendQueue(&q, node3);
	if (PeekFrontQueue(&q) == node2) {
		printf("%s", "Append node2 Correct.");
	}
	PopFrontQueue(&q);
	if (PeekFrontQueue(&q) == node3) {
		printf("%s", "Pop node2 Correct.");
	}
	_deconstructQueue(&q);
	free(node);
	free(node2);
	free(node3);
	//////////////////////////////////////////////////////////////////////
	ACAutomaton aca;
	_constructACA(&aca);
	char words[][256] = { "我的","我的天","我要","我吃了吗","你猜猜看","你猜什么"};
	BuildACA(&aca, &words, 5);
	_deconstructACA(&aca);
	//////////////////////////////////////////////////////////////////////
	return 0;
}