#include <stdio.h>
#include "StringMatcher.h"
int main(int argc, char **argv) {
	if (argc < 4) {
		printf("Input Arguments <string_token.txt> <pattern.txt> <trie_result.txt>\n");
		return -1;
	}
	StringMatcher matcher;
	_constructStringMatcher(&matcher);
	matchKeywords(&matcher, argv[1], argv[2]);
	printf("Matching Succeed.\n");
	printf("Writing Results...\n");
	outPutResult(&matcher, argv[3]);
	_deconstructStringMatcher(&matcher);
	return 0;
}
