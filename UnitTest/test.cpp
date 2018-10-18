#include "pch.h"
#include "../Aho-Corasick-automaton/Trie.h"
#include "../Aho-Corasick-automaton/Queue.h"

// TODO: fix the link issue
#include "../Aho-Corasick-automaton/Trie.c"
#include "../Aho-Corasick-automaton/Queue.c"

TEST(TRIE_TREE, CONSTRUCT_INSERT_QUERT) {
	Trie trie;
	_constructTrie(&trie, NULL, 0);
	InsertKeyword(&trie, "�ҵ���");
	InsertKeyword(&trie, "��Ҫ");
	InsertKeyword(&trie, "�����");
		EXPECT_EQ(QueryKeyword(&trie, "�ҵ���"), true);
	EXPECT_EQ(QueryKeyword(&trie, "�ҵ�"), false);
	EXPECT_EQ(QueryKeyword(&trie, "���"), false);
	EXPECT_EQ(QueryKeyword(&trie, "��Ҫ"), true);
	EXPECT_EQ(QueryKeyword(&trie, "�����Ӧ�ñ��ʵ��"), false); 
}

TEST(QUEUE, CONSTRUCT_PUSH_POP) {
	Queue q;
	TreeNodeACA *node, *node2, *node3;
	node = (TreeNodeACA *)(malloc(sizeof(TreeNode)));
	node2 = (TreeNodeACA *)(malloc(sizeof(TreeNode)));
	node3 = (TreeNodeACA *)(malloc(sizeof(TreeNode)));
	//EXPECT_NE(node, NULL);
	AppendQueue(&q, node);
	EXPECT_EQ(PeekFrontQueue(&q), node);
	PopFrontQueue(&q);
	//EXPECT_EQ(PeekFrontQueue(&q), NULL);
	AppendQueue(&q, node2);
	AppendQueue(&q, node3);
	EXPECT_EQ(PeekFrontQueue(&q), node2);
	PopFrontQueue(&q);
	EXPECT_EQ(PeekFrontQueue(&q), node3);
		free(node);
	free(node2);
	free(node3);
}