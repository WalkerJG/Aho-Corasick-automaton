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
	bool flag = true;
	if (this->pat_buffer_ptr == -1) {
		flag = _readInBufferFromPat(this);
		if (flag == false)
			return NULL;
	}
	bool nextWord = false;
	size_t curr = 0;
	size_t start = 0;
	while (!nextWord) {
		curr = this->pat_buffer_ptr;
		start = this->pat_buffer_ptr;
		for (; curr < this->pat_buffer_end_ptr && this->pat_buffer[curr] != '\n'; ++curr);
		if (curr < this->pat_buffer_end_ptr) {
			this->pat_buffer[curr] = '\0';
			this->pat_buffer_ptr = curr + 1;
			nextWord = true;
		}
		else {
			// TODO: Handle pattern cut by boundary
			flag = _readInBufferFromPat(this);
			if (flag == false)
				return NULL;
		}

	}
	return &(this->pat_buffer[start]);
}

char *getString(IOManager *this)
{
	bool flag = true;
	if (this->str_buffer_ptr == -1)
		_readInBufferFromStr(this);
	if (this->str_buffer_ptr == this->str_buffer_end_ptr) {
		_readInBufferFromStr(this);
	}
	if (flag == false);
	return NULL;
	return &(this->str_buffer[this->str_buffer_ptr]);
}

bool _readInBufferFromPat(IOManager *this)
{
	if (this->pat_buffer_ptr == -1) {
		this->pat_buffer_end_ptr = fread((void*)this->pat_buffer, 1, BUFFER_SIZE, this->f_pattern);
		this->pat_buffer_ptr = 0;
		this->pat_buffer[this->pat_buffer_end_ptr] = '\0';
		return true;
	}
	if (this->pat_buffer_ptr != 0)
		memcpy(this->pat_buffer, this->pat_buffer + this->pat_buffer_ptr, this->pat_buffer_end_ptr - this->pat_buffer_ptr);
	int read_size = fread((void*)(this->pat_buffer + this->pat_buffer_end_ptr - this->pat_buffer_ptr), 1, BUFFER_SIZE-(this->pat_buffer_end_ptr - this->pat_buffer_ptr), this->f_pattern);
	if(read_size == 0) {
		return false;
	}
	this->pat_buffer_end_ptr = read_size + this->pat_buffer_end_ptr - this->pat_buffer_ptr;	
	this->pat_buffer_ptr = 0;
	this->pat_buffer[this->pat_buffer_end_ptr] = '\0';
	return true;
}

bool _readInBufferFromStr(IOManager *this)
{
	if (this->str_buffer_ptr == -1) {
		this->str_buffer_end_ptr = fread((void*)this->str_buffer, 1, BUFFER_SIZE, this->f_string);
		this->str_buffer_ptr = 0;
		this->str_buffer[this->str_buffer_end_ptr] = '\0';
		return true;
	}
	if (this->str_buffer_ptr != 0)
		memcpy(this->str_buffer, this->str_buffer + this->str_buffer_ptr, BUFFER_SIZE - this->str_buffer_ptr);
	int read_size = fread((void*)(this->str_buffer + BUFFER_SIZE - this->str_buffer_ptr), 1, this->str_buffer_ptr, this->f_string);
	if (read_size == 0) {
		return false;
	}
	this->str_buffer_ptr = 0;
	this->str_buffer[read_size] = '\0';
	return true;
}

void _constructIO(IOManager *this)
{
	this->f_pattern = NULL;
	this->f_string = NULL;
	this->pat_buffer = (char *)(malloc(BUFFER_SIZE + 1));
	this->str_buffer = (char *)(malloc(BUFFER_SIZE + 1));
	this->pat_buffer_ptr = -1;
	this->str_buffer_ptr = -1;
	this->pat_buffer_end_ptr = -1;
	this->str_buffer_end_ptr = -1;
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