#include "pch.h"
#include "../Aho-Corasick-automaton/Trie.h"

// TODO: fix the link issue
#include "../Aho-Corasick-automaton//Trie.c"
TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	Trie trie;
	_constructTrie(&trie, NULL, 0);
	InsertKeyword(&trie, "我的天");
	InsertKeyword(&trie, "我要");
	InsertKeyword(&trie, "计算机");
		EXPECT_EQ(QueryKeyword(&trie, "我的天"), true);
	EXPECT_EQ(QueryKeyword(&trie, "我的"), false);
	EXPECT_EQ(QueryKeyword(&trie, "你的"), false);
	EXPECT_EQ(QueryKeyword(&trie, "我要"), true);
	EXPECT_EQ(QueryKeyword(&trie, "计算机应用编程实验"), false); 
	EXPECT_TRUE(true);
}