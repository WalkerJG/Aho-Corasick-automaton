#ifndef _AC_AUTOMATON_H_
#define _AC_AUTOMATON_H_
#include <stdbool.h>
#include <stdio.h>
#define DICT_SIZE (3*1024*1024)
typedef struct TreeNodeACA {
	// Store Chinese Charcter
	char val_[2];

	// Indicating whether current path from the root to the current node is a keyword.
	bool is_end_;

	// Children
	struct TreeNodeACA *child;

	// Cousin
	struct TreeNodeACA *cousin;

	// Fail pointer
	struct TreeNodeACA *fail;

	// Keyword Id
	long keyId;
} TreeNodeACA;

typedef struct ACAutomaton{
	TreeNodeACA *root_;
	TreeNodeACA *state_;
	int key_count_[DICT_SIZE];
	long key_num_;
} ACAutomaton;

// Match String with length size
void matchStringACA(ACAutomaton *aca, char *str, size_t size);

// Insert a keyword into trie tree.
void insertKeywordACA(ACAutomaton *aca, char *word, long id);

// Query whether a keyword is in trie tree.
bool queryKeywordACA(ACAutomaton *aca, char *word);

// Reset Automaton state to root.
void resetStateACA(ACAutomaton *aca);

// Build Aho-Corasick Automaton
void buildACA(ACAutomaton *aca, char **words, size_t size);

void _addFailPointer(ACAutomaton *aca);

bool _cmpChChar(char * ch1, char * ch2);

// Construct a trie tree from keywords;
void _constructACA(ACAutomaton *aca);

// Deconstruct a trie tree;
void _deconstructACA(ACAutomaton *aca);

// Free trie tree in ACA
void _freeACATree(TreeNodeACA *root);

// Compare two Chinese character return true if same.
// Assuming each Chinese character occupys two bytes.
bool _cmpChCharACA(char *ch1, char *ch2);

#endif