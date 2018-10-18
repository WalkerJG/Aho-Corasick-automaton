#include "pch.h"
#include "../Aho-Corasick-automaton/Trie.h"
#include "../Aho-Corasick-automaton/Queue.h"
#include "../Aho-Corasick-automaton/ACAutomaton.h"
// TODO: fix the link issue
#include "../Aho-Corasick-automaton/Trie.c"
#include "../Aho-Corasick-automaton/Queue.c"
#include "../Aho-Corasick-automaton/ACAutomaton.c"

TEST(TRIE_TREE, CONSTRUCT_INSERT_QUERT) {
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

TEST(ACA, ACA_QUERY) {
	ACAutomaton *aca = (ACAutomaton *)(malloc(sizeof(ACAutomaton)));
	_constructACA(aca);
	char words[][256] = { "杀啊呀","杀嘿呃","杀嘿日","嘿呃日" };
	buildACA(aca, (char **)words, sizeof(words) / 256);
	resetStateACA(aca);
	char str[] = "嘿呃日";
	matchStringACA(aca, str, sizeof(str) - 1);
	EXPECT_EQ(aca->key_count_[3], 1);
	matchStringACA(aca, "杀啊呀", 6);
	EXPECT_EQ(aca->key_count_[0], 1);
	matchStringACA(aca, "我的天", 6);
	matchStringACA(aca, str, sizeof(str) - 1);
	EXPECT_EQ(aca->key_count_[3], 2);
	_deconstructACA(aca);
	free(aca);
}