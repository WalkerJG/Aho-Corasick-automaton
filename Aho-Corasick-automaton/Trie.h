#ifndef _TRIE_H_
#define _TRIE_H_
#include <stdio.h>
#include <stdbool.h>

typedef struct TreeNode {
	// Store Chinese Charcter
	char val_[2];

	// Indicating whether current path from the root to the current node is a keyword.
	bool is_end_;

	//Children
	struct TreeNode *child;
	
	//Cousion
	struct TreeNode *cousin;
} TreeNode;

typedef struct Trie {
	TreeNode *root_;
} Trie;

// Insert a keyword into trie tree.
void InsertKeyword(Trie *trie, char *word);

// Query whether a keyword is in trie tree
bool QueryKeyword(Trie *trie, char *word);

// Construct a trie tree from keywords;
void _constructTrie(Trie *trie, char **words, size_t size);

// Deconstruct a trie tree;
void _deconstructTrie(Trie *trie);

void _freeTree(TreeNode *root);

// Compare two Chinese character return true if same.
// Assuming each Chinese character occupys two bytes.
bool _cmpChChar(char *ch1, char *ch2);

#endif //_TRIE_H_