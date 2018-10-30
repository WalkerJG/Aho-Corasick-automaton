#ifndef _STRING_MATCHER_H_
#define _STRING_MATCHER_H_
#include "ACAutomaton.h"
#include "IOManager.h"

typedef struct StringMatcher {
	ACAutomaton *aca_;
	IOManager *io_;
} StringMatcher;

typedef struct key_count {
	long keyId;
	long count;
}key_count;
// Use patterns from pat to match string and output.
void matchString(StringMatcher * this, char * str, char * pat);

// Output result ordered by count
void outPutResult(StringMatcher *this, char * file);

// Sort count array
void _Qsort(StringMatcher *this, int a[], int low, int high);

// Construct StringMatcher
void _constructStringMatcher(StringMatcher *this);

// Deconstruct StringMatcher
void _deconstructStringMatcher(StringMatcher *this);

#endif //_STRING_MATCHER_H_