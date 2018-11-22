#include <stdio.h>
#include "StringMatcher.h"
#include "time.h"
int main(int argc, char **argv) {
	if (argc < 4) {
	    printf("Input arguments: <strint.txt> <pattern.txt> <result.txt>\n");
		return -1;
	}
	StringMatcher matcher;
	_constructStringMatcher(&matcher);
	resetStateACA((&matcher)->aca_);
	matchString(&matcher, argv[1], argv[2]);
	printf("Matching finished.\n");
	printf("Writing results...\n");
	outPutResult(&matcher, argv[3]);
	_deconstructStringMatcher(&matcher);
	return 0;
}
