#ifndef _AC_AUTOMATON_H_
#define _AC_AUTOMATON_H_
#include <stdbool.h>
#include <stdio.h>
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
} TreeNodeACA;

typedef struct ACAutomaton{
	TreeNodeACA *root_;
	TreeNodeACA *state_;
} ACAutomaton;

// Insert a keyword into trie tree.
void InsertKeywordACA(ACAutomaton *aca, char *word);

// Query whether a keyword is in trie tree
bool QueryKeywordACA(ACAutomaton *aca, char *word);

// Build Aho-Corasick Automaton
void BuildACA(ACAutomaton *aca, char **words, size_t size);

void _addFailPointer(ACAutomaton *aca);

// Construct a trie tree from keywords;
void _constructACA(ACAutomaton *aca);

// Deconstruct a trie tree;
void _deconstructACA(ACAutomaton *aca);

// Free trie tree in ACA
void _freeACATree(TreeNodeACA *root);

// Compare two Chinese character return true if same.
// Assuming each Chinese character occupys two bytes.
bool _cmpChChar(char *ch1, char *ch2);

#endif