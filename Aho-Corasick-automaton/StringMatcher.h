#ifndef _STRING_MATCHER_H_
#define _STRING_MATCHER_H_
#include "ACAutomaton.h"
#include "IOManager.h"

typedef struct StringMatcher {
	ACAutomaton *aca_;
	IOManager *io_;
} StringMatcher;


// Use patterns from pat to match string and output.
void matchString(StringMatcher * this, char * str, char * pat, char * output);

// Construct StringMatcher
void _constructStringMatcher(StringMatcher *this);

// Deconstruct StringMatcher
void _deconstructStringMatcher(StringMatcher *this);

#endif //_STRING_MATCHER_H_