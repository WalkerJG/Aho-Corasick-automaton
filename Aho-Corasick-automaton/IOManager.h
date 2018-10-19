#ifndef _IO_MANAGER_H_
#define _IO_MANAGER_H_
#include <stdbool.h>
#include <stdio.h>
#define BUFFER_SIZE 10240

typedef struct IOManager {
	FILE *f_string;
	FILE *f_pattern;
	char *pat_buffer;
	char *str_buffer;
	int pat_buffer_ptr;
	int str_buffer_ptr;
}IOManager;

char *getPattern(IOManager *this);

char *getStr(IOManager *this);

bool openStrFile(IOManager *this, char *name);

bool openPatFile(IOManager *this, char *name);

bool _readInBufferFromPat(IOManager *this);
bool _readInBufferFromStr(IOManager *this);

void _constructIO(IOManager *this);
void _deconstructIO(IOManager *this);
#endif