#include "IOManager.h"
#include "string.h"
#include "malloc.h"
#pragma warning(disable:4996)
bool openStrFile(IOManager *this, char *name)
{
	if (this->f_string) {
		fclose(this->f_string);
	}
	this->f_string = fopen(name, "r");
	if (!this->f_string)
		return false;
	return true;
}

bool openPatFile(IOManager *this, char *name)
{
	if (this->f_pattern) {
		fclose(this->f_pattern);
	}
	this->f_pattern = fopen(name, "r");
	if (!this->f_pattern)
		return false;
	return true;
}

char *getPattern(IOManager *this)
{
	size_t curr = this->pat_buffer_ptr;
	for (; curr < BUFFER_SIZE && this->pat_buffer[curr] != '\n'; ++curr);
	if(curr<BUFFER_SIZE)
	this->pat_buffer[curr] = '\0';
	else {
		// TODO: Handle pattern cut by boundary
		_readInBufferFromPat(this);
	}
	return &(this->pat_buffer[this->pat_buffer_ptr]);
}

char *getStr(IOManager *this)
{

}

bool _readInBufferFromPat(IOManager *this)
{
	if (this->pat_buffer_ptr != 0)
		memcpy(this->pat_buffer, this->pat_buffer + this->pat_buffer_ptr, BUFFER_SIZE - this->str_buffer_ptr);
	fread((void*)(this->pat_buffer + BUFFER_SIZE - this->pat_buffer_ptr), 1, this->pat_buffer_ptr, this->f_pattern);
	this->pat_buffer_ptr = 0;
	return true;
}

bool _readInBufferFromStr(IOManager *this)
{
	if (this->str_buffer_ptr != 0)
		memcpy(this->str_buffer, this->str_buffer + this->str_buffer_ptr, BUFFER_SIZE - this->str_buffer_ptr);
	fread((void*)(this->str_buffer + BUFFER_SIZE - this->str_buffer_ptr), 1, this->str_buffer_ptr, this->f_string);
	this->str_buffer_ptr = 0;
	return true;
}

void _constructIO(IOManager *this)
{
	this->f_pattern = NULL;
	this->f_string = NULL;
	this->pat_buffer = (char *)(malloc(BUFFER_SIZE));
	this->str_buffer = (char *)(malloc(BUFFER_SIZE));
	this->pat_buffer_ptr = 0;
	this->str_buffer_ptr = 0;
}

void _deconstructIO(IOManager *this) {
	if (this->f_pattern != NULL)
		fclose(this->f_pattern);
	if (this->f_string != NULL)
		fclose(this->f_string);
	this->f_pattern = NULL;
	this->f_string = NULL;
	if (this->pat_buffer != NULL) {
		free(this->pat_buffer);
		this->pat_buffer = NULL;
	}
	if (this->str_buffer != NULL) {
		free(this->str_buffer);
		this->str_buffer = NULL;
	}
}