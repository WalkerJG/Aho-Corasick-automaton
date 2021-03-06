#ifndef _AC_AUTOMATON_H_
#define _AC_AUTOMATON_H_
#include <stdbool.h>
#include <stdio.h>
#include "RBTree.h"
#define DICT_SIZE (3*1024*1024)
#define MAX_WORD_LEGNTH (60)

typedef struct TreeNodeACA {
	// Store Chinese Charcter
	char val_;

	// Indicating whether current path from the root to the current node is a keyword.
	bool is_end_;

	// Children
	struct RBRoot *children;

	// Fail pointer
	struct TreeNodeACA *fail;

	// Keyword Id
	long keyId;
} TreeNodeACA;

typedef struct ACAutomaton{
	TreeNodeACA *root_;
	TreeNodeACA *state_;
	long key_count_[DICT_SIZE];
	char *keyword_[DICT_SIZE];
	long key_num_;
} ACAutomaton;

// Match String with length size
void matchStringACA(ACAutomaton *this, char *str);

// Transfer from current state to root.
void backToRootACA(ACAutomaton *this);

// Insert a keyword into trie tree.
void insertKeywordACA(ACAutomaton *this, char *word);

// Query whether a keyword is in trie tree.
bool queryKeywordACA(ACAutomaton *this, char *word);

// Reset Automaton state to root.
void resetStateACA(ACAutomaton *this);

// Build Aho-Corasick Automaton
void buildACA(ACAutomaton *this, char **words, size_t size);

void _addFailPointer(ACAutomaton *this);

// Construct a trie tree from keywords;
void _constructACA(ACAutomaton *this);

// Deconstruct a trie tree;
void _deconstructACA(ACAutomaton *this);

// Free trie tree in ACA
void _freeACATree(TreeNodeACA *root);

// Compare two Chinese character return true if same.
// Assuming each Chinese character occupys two bytes.
bool _cmpChCharACA(char *ch1, char *ch2);

// Judge whether word is GB2312 character.
bool _isGB2312Char(char*word);
#endif
