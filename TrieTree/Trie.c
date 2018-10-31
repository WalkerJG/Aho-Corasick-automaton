#include "Trie.h"
#include "malloc.h"
#include "string.h"

#pragma warning(disable:4996)
// Matching from this->state_

void matchKeywordAndPattern(Trie * this, char * word)
{
	TreeNode *res = queryKeyword(this, word);
	if (res != NULL)
		++this->key_count_[res->keyId];
		
}

void insertKeyword(Trie * this, char * word)
{
	TreeNode *curr_node = this->root_;
	int i = 0;
	while (word[i] != '\0') {
		// Traverse all children nodes to find whether word[i] exists or not.
		TreeNode*child = iterative_rbtree_search(curr_node->children, word[i]);

		TreeNode *before = curr_node;


		// Found charcter
		if (child != NULL) {
			curr_node = child;
		}
		else {// Not found
			TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
			new_node->children = create_rbtree();
			new_node->is_end_ = false;
			new_node->fail = NULL;
			new_node->val_ = word[i];

			new_node->is_end_ = word[i + 1] == '\0' ? true : false;

			if (new_node->is_end_) {
				new_node->keyId = this->key_num_;
				strcpy(this->keyword_[this->key_num_], word);
				++this->key_num_;
			}
			// curr_node have no children

			int insert_flag = insert_rbtree(before->children, word[i], new_node);
			if (insert_flag == -1)
				return -1;
			curr_node = new_node;
		}
		++i;

	}
}

TreeNode *queryKeyword(Trie * this, char * word)
{
	TreeNode *curr_node = this->root_;
	TreeNode *child = NULL;
	if (word[0] == '\0')
		return NULL;
	for (size_t i = 0; curr_node != NULL && word[i] != '\0'; ++i) {
		child = iterative_rbtree_search(curr_node->children, word[i]);

		if (child == NULL) {
			return false;
		}
		else
			curr_node = child;
	}
	
	return child->is_end_?child:NULL;
}

void buildACA(Trie * this, char ** words, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		size_t offset = i * 256;
		insertKeyword(this, ((char *)(words)) + offset);
	}
}

void _constructTrie(Trie *this)
{
	TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
	root->children = create_rbtree();
	root->is_end_ = false;
	root->fail = NULL;
	root->val_ = 0;

	this->root_ = root;
	this->key_num_ = 0;

	memset(this->key_count_, 0, DICT_SIZE * sizeof(int));

	int i = 0;
	for (i = 0; i < DICT_SIZE; ++i)
		this->keyword_[i] = (char *)malloc(MAX_WORD_LEGNTH);
}

void _deconstructTrie(Trie * this)
{
	TreeNode *root = this->root_;
	int i = 0;
	for (i = 0; i < DICT_SIZE; ++i)
		free((char *)this->keyword_[i]);
	_freeTrie(this);
}

void _freeTrie(Trie *root)
{
	/*TreeNodeACA *cousin = root->cousin;
	TreeNodeACA *child = root->child;
	free(root);
	if (cousin != NULL)
		_freeACATree(cousin);
	if (child != NULL)
		_freeACATree(child);*/
}
