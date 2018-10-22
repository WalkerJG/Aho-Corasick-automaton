#ifndef _IO_MANAGER_H_
#define _IO_MANAGER_H_
#include <stdbool.h>
#include <stdio.h>
#define BUFFER_SIZE 102400

typedef struct IOManager {
	FILE *f_string;
	FILE *f_pattern;
	char *pat_buffer;
	char *str_buffer;
	int pat_buffer_ptr;
	int str_buffer_ptr;
	int pat_buffer_end_ptr;
	int str_buffer_end_ptr;
}IOManager;

// Get next pattern from buffer
char *getPattern(IOManager *this);

// Get next string from buffer
char *getString(IOManager *this);

// Open string file
bool openStrFile(IOManager *this, char *name);

// Open pattern file
bool openPatFile(IOManager *this, char *name);

// Read in buffer from pattern file
bool _readInBufferFromPat(IOManager *this);

// Read in buffer from string file
bool _readInBufferFromStr(IOManager *this);

// Construct IO Manager 
void _constructIO(IOManager *this);

// Deconstruct IO Manager 
void _deconstructIO(IOManager *this);
#endif