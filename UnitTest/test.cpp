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

TEST(ACA, ACA_QUERY) {
	ACAutomaton *aca = (ACAutomaton *)(malloc(sizeof(ACAutomaton)));
	_constructACA(aca);
	char words[][256] = { "ɱ��ѽ","ɱ����","ɱ����","������" };
	buildACA(aca, (char **)words, sizeof(words) / 256);
	resetStateACA(aca);
	char str[] = "������";
	matchStringACA(aca, str, sizeof(str) - 1);
	EXPECT_EQ(aca->key_count_[3], 1);
	matchStringACA(aca, "ɱ��ѽ", 6);
	EXPECT_EQ(aca->key_count_[0], 1);
	matchStringACA(aca, "�ҵ���", 6);
	matchStringACA(aca, str, sizeof(str) - 1);
	EXPECT_EQ(aca->key_count_[3], 2);
	_deconstructACA(aca);
	free(aca);
}


///////////////////////////////////////////////////////////////////////////
//IOManager io_manager;
//_constructIO(&io_manager);
//if (false == openPatFile(&io_manager, "pattern.txt")) {
//	printf("%s", "failed to open pattern.txt\n");
//	return -1;
//}
//if (false == openStrFile(&io_manager, "string.txt")) {
//	printf("%s", "failed to open string.txt\n");
//	return -1;
//}
//char *res = "�ҵ��찡s";
//printf(L"%s", res);
//char * ret = getPattern(&io_manager);
//printf("%s", ret);
//ret = getPattern(&io_manager);
//printf("%s", ret);
//ret = getPattern(&io_manager);
//printf("%s", ret);
//ret = getString(&io_manager);
//printf("%s", ret);
//////////////////////////////////////////////////////////////////////////////
//printf("%s", "hello trie.");
////ACAutomaton aca;
////_constructACA(&aca, NULL, 0);
//
///////////////////////////////////////////////////////////////////
//Queue q;
//_constructQueue(&q);
//TreeNodeACA *node, *node2, *node3;
//node = (TreeNodeACA *)(malloc(sizeof(TreeNodeACA)));
//node2 = (TreeNodeACA *)(malloc(sizeof(TreeNodeACA)));
//node3 = (TreeNodeACA *)(malloc(sizeof(TreeNodeACA)));
////EXPECT_NE(node, NULL);
//AppendQueue(&q, node);
//if (PeekFrontQueue(&q) == node) {
//	printf("%s", "Append Correct");
//}
//PopFrontQueue(&q);
//if (PeekFrontQueue(&q) == NULL) {
//
//	printf("%s", "Pop Correct");
//}
//
//AppendQueue(&q, node2);
//AppendQueue(&q, node3);
//if (PeekFrontQueue(&q) == node2) {
//	printf("%s", "Append node2 Correct.");
//}
//PopFrontQueue(&q);
//if (PeekFrontQueue(&q) == node3) {
//	printf("%s", "Pop node2 Correct.");
//}
//_deconstructQueue(&q);
//free(node);
//free(node2);
//free(node3);
////////////////////////////////////////////////////////////////////////
//ACAutomaton *aca = malloc(sizeof(ACAutomaton));
//_constructACA(aca);
//char words[][256] = { "ɱ��ѽ","ɱ����","ɱ����","������" };
//buildACA(aca, words, sizeof(words) / 256);
//resetStateACA(aca);
//char str[] = "������";
//matchStringACA(aca, str, sizeof(str) - 1);
//matchStringACA(aca, "ɱ��ѽ", 6);
//matchStringACA(aca, "�ҵ���", 6);
//matchStringACA(aca, str, sizeof(str) - 1);
//_deconstructACA(aca);
//free(aca);
////////////////////////////////////////////////////////////////////////