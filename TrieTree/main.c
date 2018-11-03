#include <stdio.h>
#include "StringMatcher.h"
int main(int argc, char **argv) {
	if (argc < 4) {
		printf("�������Ϊ <ƥ�䴮�ļ�> <ģʽ���ļ�> <����ļ�>\n");
		printf("����ƥ�䴮�ļ���ÿ���ʵ���һ��,�� \\n ��β\n");
		printf("��������������ļ���\n");
		return -1;
	}
	StringMatcher matcher;
	_constructStringMatcher(&matcher);
	matchKeywords(&matcher, argv[1], argv[2]);
	printf("�����������Ժ�\n");
	outPutResult(&matcher, argv[3]);
	printf("ƥ�����\n");
	_deconstructStringMatcher(&matcher);
	getchar();
	return 0;
}