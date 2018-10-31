#include "IOManager.h"
#include "string.h"
#include "malloc.h"
#pragma warning(disable:4996)
bool openKeywordFile(IOManager *this, char *name)
{
	if (this->f_keywords) {
		fclose(this->f_keywords);
	}
	this->f_keywords = fopen(name, "r");
	if (!this->f_keywords)
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
			flag = _readInBufferFromPat(this);
			if (flag == false)
				return NULL;
		}

	}
	return &(this->pat_buffer[start]);
}
char *getKeyword(IOManager *this)
{
	bool flag = true;
	if (this->keyword_buffer_ptr == -1) {
		flag = _readInBufferFromKeyword(this);
		if (flag == false)
			return NULL;
	}
	bool nextWord = false;
	size_t curr = 0;
	size_t start = 0;
	while (!nextWord) {
		curr = this->keyword_buffer_ptr;
		start = this->keyword_buffer_ptr;
		for (; curr < this->keyword_buffer_end_ptr && this->keyword_buffer[curr] != '\n'; ++curr);
		if (curr < this->keyword_buffer_end_ptr) {
			this->keyword_buffer[curr] = '\0';
			this->keyword_buffer_ptr = curr + 1;
			nextWord = true;
		}
		else {
			flag = _readInBufferFromKeyword(this);
			if (flag == false)
				return NULL;
		}

	}
	return &(this->keyword_buffer[start]);
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
	size_t read_size = fread((void*)(this->pat_buffer + this->pat_buffer_end_ptr - this->pat_buffer_ptr), 1,
		BUFFER_SIZE - (this->pat_buffer_end_ptr - this->pat_buffer_ptr), this->f_pattern);
	if (read_size == 0) {
		return false;
	}
	this->pat_buffer_end_ptr = read_size + this->pat_buffer_end_ptr - this->pat_buffer_ptr;
	this->pat_buffer_ptr = 0;
	this->pat_buffer[this->pat_buffer_end_ptr] = '\0';
	return true;
}

bool _readInBufferFromKeyword(IOManager *this)
{
	if (this->keyword_buffer_ptr == -1) {
		this->keyword_buffer_end_ptr = fread((void*)this->keyword_buffer, 1, BUFFER_SIZE, this->f_keywords);
		this->keyword_buffer_ptr = 0;
		this->keyword_buffer[this->keyword_buffer_end_ptr] = '\0';
		return true;
	}
	if (this->keyword_buffer_ptr != 0)
		memcpy(this->keyword_buffer, this->keyword_buffer + this->keyword_buffer_ptr, this->keyword_buffer_end_ptr - this->keyword_buffer_ptr);
	size_t read_size = fread((void*)(this->keyword_buffer + this->keyword_buffer_end_ptr - this->keyword_buffer_ptr), 1,
		BUFFER_SIZE - (this->keyword_buffer_end_ptr - this->keyword_buffer_ptr), this->f_keywords);
	if (read_size == 0) {
		return false;
	}
	this->keyword_buffer_end_ptr = read_size + this->keyword_buffer_end_ptr - this->keyword_buffer_ptr;
	this->keyword_buffer_ptr = 0;
	this->keyword_buffer[this->keyword_buffer_end_ptr] = '\0';
	return true;
}

void _constructIO(IOManager *this)
{
	this->f_pattern = NULL;
	this->f_keywords = NULL;
	this->pat_buffer = (char *)(malloc(BUFFER_SIZE + 1));
	this->keyword_buffer = (char *)(malloc(BUFFER_SIZE + 1));
	this->pat_buffer_ptr = -1;
	this->keyword_buffer_ptr = -1;
	this->pat_buffer_end_ptr = -1;
	this->keyword_buffer_end_ptr = -1;
}

void _deconstructIO(IOManager *this) {
	if (this->f_pattern != NULL)
		fclose(this->f_pattern);
	if (this->f_keywords != NULL)
		fclose(this->f_keywords);
	this->f_pattern = NULL;
	this->f_keywords = NULL;
	if (this->pat_buffer != NULL) {
		free(this->pat_buffer);
		this->pat_buffer = NULL;
	}
	if (this->keyword_buffer != NULL) {
		free(this->keyword_buffer);
		this->keyword_buffer = NULL;
	}
}