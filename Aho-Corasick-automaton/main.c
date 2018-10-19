#include <stdio.h>
#include "StringMatcher.h"
//TODO: Split Trie And ACA, clean code.
int main() {
	StringMatcher matcher;
	_constructStringMatcher(&matcher);
	matchString(&matcher, "string.txt", "pattern.txt", "output.txt");
	_deconstructStringMatcher(&matcher);
	return 0;
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
//char *res = "Œ“µƒÃÏ∞°s";
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
//char words[][256] = { "…±∞°—Ω","…±∫Ÿﬂ¿","…±∫Ÿ»’","∫Ÿﬂ¿»’" };
//buildACA(aca, words, sizeof(words) / 256);
//resetStateACA(aca);
//char str[] = "∫Ÿﬂ¿»’";
//matchStringACA(aca, str, sizeof(str) - 1);
//matchStringACA(aca, "…±∞°—Ω", 6);
//matchStringACA(aca, "Œ“µƒÃÏ", 6);
//matchStringACA(aca, str, sizeof(str) - 1);
//_deconstructACA(aca);
//free(aca);
////////////////////////////////////////////////////////////////////////