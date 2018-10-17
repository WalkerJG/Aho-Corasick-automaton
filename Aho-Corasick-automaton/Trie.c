#include "Trie.h"
#include "malloc.h"
#include "string.h"

void InsertKeyword(Trie * trie, char * word)
{
	TreeNode *curr_node = trie->root_;
	for (int i = 0; word[i] != '\0'; i += 2) {
		// Traverse all children nodes to find whether word[i] exists or not.
		TreeNode *child = curr_node->child;
		TreeNode *before = curr_node;

		while (child != NULL && !_cmpChChar(child->val_, &word[i])) {
			before = child;
			child = child->cousin;
		}

		// Found charcter
		if (child != NULL) {
			curr_node = child;
		}
		else {// Not found
			TreeNode *new_node = (TreeNode*)malloc(sizeof(TreeNode));
			memcpy(new_node->val_, (void *)&word[i], 2);
			new_node->is_end_ = word[i + 2] == '\0' ? true : false;
			new_node->child = NULL;
			new_node->cousin = NULL;

			// curr_node have no children
			if (before == curr_node) {
				before->child = new_node;
			}
			else {
				before->cousin = new_node;
			}
			curr_node = new_node;
		}
	}
}

bool QueryKeyword(Trie * trie, char * word)
{
	TreeNode *curr_node = trie->root_;
	TreeNode *child = NULL;
	for (size_t i = 0; curr_node != NULL && word[i] != '\0'; i += 2) {
		child = curr_node->child;
		// Find the child with same character as word[i] word[i+1
		while (child != NULL && !_cmpChChar(child->val_, &word[i])) {
			child = child->cousin;
		}
		if (child == NULL) {
			return false;
		}
		else
			curr_node = child;
	}
	return child->is_end_;
}

void _constructTrie(Trie * trie, char ** words, size_t size)
{
	TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
	root->child = NULL;
	root->cousin = NULL;
	root->is_end_ = false;
	memset(root->val_, 0, 2);
	trie->root_ = root;
	for (size_t i = 0; i < size; ++i) {
		InsertKeyword(trie, words[i]);
	}
}

void _deconstructTrie(Trie * trie)
{
	TreeNode *root = trie->root_;
	_freeTree(root);
}

void _freeTree(TreeNode *root) {
	TreeNode *cousin = root->cousin;
	TreeNode *child = root->child;
	if (cousin != NULL)
	   _freeTree(cousin);
	if (child != NULL)
		_freeTree(child);
	free(root);
}
bool _cmpChChar(char * ch1, char * ch2)
{
	if (ch1[0] == ch2[0] && ch1[1] == ch2[1])
		return true;
	return false;
}
