#ifndef _AC_AUTOMATON_H_
#define _AC_AUTOMATON_H_
#include <stdbool.h>
#include <stdio.h>
#include "rbtree.h"
#define DICT_SIZE (3*1024*1024)
#define MAX_WORD_LEGNTH (60)

typedef struct TreeNode {
	// Store Chinese Charcter
	char val_;

	// Indicating whether current path from the root to the current node is a keyword.
	bool is_end_;

	// Children
	struct RBRoot *children;

	// Fail pointer
	struct TreeNode *fail;

	// Keyword Id
	long keyId;
} TreeNode;

typedef struct Trie{
	TreeNode *root_;
	long key_count_[DICT_SIZE];
	char *keyword_[DICT_SIZE];
	long key_num_;
} Trie;


void matchKeywordAndPattern(Trie *this, char *word);

// Insert a keyword into trie tree.
void insertKeyword(Trie *this, char *word);

// Query whether a keyword is in trie tree.
TreeNode *queryKeyword(Trie *this, char *word);

// Construct a trie tree from keywords;
void _constructTrie(Trie *this);

// Deconstruct a trie tree;
void _deconstructTrie(Trie *this);

// Free trie tree in ACA
void _freeTrie(Trie *root);

#endif