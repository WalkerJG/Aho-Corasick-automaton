#include <stdio.h>
#include "StringMatcher.h"
#include "time.h"
int main() {
	StringMatcher matcher;
	_constructStringMatcher(&matcher);
	resetStateACA((&matcher)->aca_);
	//matchString(&matcher, "string.txt", "pattern.txt");
	//matchString(&matcher, "str_test.txt", "ptn_test.txt");
	matchString(&matcher, "string_test.txt", "pattern.txt");
	outPutResult(&matcher, "result.txt");
	_deconstructStringMatcher(&matcher);
	return 0;
}
