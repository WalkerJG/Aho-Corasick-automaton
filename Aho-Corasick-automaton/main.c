#include <stdio.h>
#include "StringMatcher.h"
#include "time.h"
int main(int argc, char **argv) {
	if (argc < 4) {
		printf("�������Ϊ <ƥ�䴮�ļ�> <ģʽ���ļ�> <����ļ�>\n");
		printf("��������������ļ���\n");
		return -1;
	}
	StringMatcher matcher;
	_constructStringMatcher(&matcher);
	resetStateACA((&matcher)->aca_);
	matchString(&matcher, argv[1], argv[2]);
	printf("�����������Ժ�\n");
	outPutResult(&matcher, argv[3]);
	printf("ƥ�����\n");
	_deconstructStringMatcher(&matcher);
	return 0;
}
