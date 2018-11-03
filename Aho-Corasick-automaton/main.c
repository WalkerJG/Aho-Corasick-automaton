#include <stdio.h>
#include "StringMatcher.h"
#include "time.h"
int main(int argc, char **argv) {
	if (argc < 4) {
		printf("输入参数为 <匹配串文件> <模式串文件> <输出文件>\n");
		printf("结果将输出到输出文件中\n");
		return -1;
	}
	StringMatcher matcher;
	_constructStringMatcher(&matcher);
	resetStateACA((&matcher)->aca_);
	matchString(&matcher, argv[1], argv[2]);
	printf("输出结果，请稍候。\n");
	outPutResult(&matcher, argv[3]);
	printf("匹配完成\n");
	_deconstructStringMatcher(&matcher);
	return 0;
}
