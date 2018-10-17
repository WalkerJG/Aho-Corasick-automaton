#include "pch.h"
#include "../Aho-Corasick-automaton/Trie.h"

// TODO: fix the link issue
#include "../Aho-Corasick-automaton//Trie.c"
TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
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
	EXPECT_TRUE(true);
}