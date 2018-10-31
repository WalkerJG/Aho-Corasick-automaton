#include <stdio.h>
#include "StringMatcher.h"
int main() {
	StringMatcher matcher;
	_constructStringMatcher(&matcher);
	//matchString(&matcher, "string.txt", "pattern.txt");
	matchKeywords(&matcher, "pattern.txt", "pattern.txt");
	outPutResult(&matcher, "result.txt");
	_deconstructStringMatcher(&matcher);
	return 0;
}
