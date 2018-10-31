#ifndef _STRING_MATCHER_H_
#define _STRING_MATCHER_H_
#include "Trie.h"
#include "IOManager.h"

typedef struct StringMatcher {
	Trie *trie_;
	IOManager *io_;
} StringMatcher;

typedef struct key_count {
	long keyId;
	long count;
}key_count;

void matchKeywords(StringMatcher * this, char * keywords, char * pat);

// Output result ordered by count
void outPutResult(StringMatcher *this, char * file);

// Construct StringMatcher
void _constructStringMatcher(StringMatcher *this);

// Deconstruct StringMatcher
void _deconstructStringMatcher(StringMatcher *this);

#endif //_STRING_MATCHER_H_