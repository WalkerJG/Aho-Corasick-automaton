#include "ACAutomaton.h"
#include "malloc.h"
#include "string.h"
#include "Queue.h"

// Matching from aca->state_
void matchStringACA(ACAutomaton *aca, char *str, size_t size)
{
	size_t i = 0;
	while (i < size) {
		TreeNodeACA *child = aca->state_->child;
		//Traverse all children nodes of state_ to find whether match str[i]str[i+1]
		while (child != NULL && !_cmpChCharACA(child->val_, &str[i])) {
			child = child->cousin;
		}
		if (child == NULL) {
			aca->state_ = aca->state_->fail;
			if (aca->state_ == NULL) {
				aca->state_ = aca->root_;
				i += 2;
			}
			continue;
		}
		else {
			aca->state_ = child;
			if (aca->state_->is_end_)
				aca->key_count_[aca->state_->keyId] += 1;
		}
		i += 2;

	}
}

void insertKeywordACA(ACAutomaton * aca, char * word, long id)
{
	TreeNodeACA *curr_node = aca->root_;
	for (int i = 0; word[i] != '\0'; i += 2) {
		// Traverse all children nodes to find whether word[i] exists or not.
		TreeNodeACA *child = curr_node->child;
		TreeNodeACA *before = curr_node;

		while (child != NULL && !_cmpChCharACA(child->val_, &word[i])) {
			before = child;
			child = child->cousin;
		}

		// Found charcter
		if (child != NULL) {
			curr_node = child;
		}
		else {// Not found
			TreeNodeACA *new_node = (TreeNodeACA*)malloc(sizeof(TreeNodeACA));
			memcpy(new_node->val_, (void *)&word[i], 2);
			new_node->is_end_ = word[i + 2] == '\0' ? true : false;
			new_node->child = NULL;
			new_node->cousin = NULL;
			new_node->keyId = id;
			aca->key_num_ += 1;
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

bool queryKeywordACA(ACAutomaton * aca, char * word)
{
	TreeNodeACA *curr_node = aca->root_;
	TreeNodeACA *child = NULL;
	for (size_t i = 0; curr_node != NULL && word[i] != '\0'; i += 2) {
		child = curr_node->child;
		// Find the child with same character as word[i] word[i+1
		while (child != NULL && !_cmpChCharACA(child->val_, &word[i])) {
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

void resetStateACA(ACAutomaton * aca)
{
	aca->state_ = aca->root_;
	memset(aca->key_count_, 0, sizeof(DICT_SIZE) * sizeof(int));
}

void buildACA(ACAutomaton * aca, char ** words, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		size_t offset = i * 256;
		insertKeywordACA(aca, ((char *)(words)) + offset, aca->key_num_);
	}
	_addFailPointer(aca);
}

void _addFailPointer(ACAutomaton * aca)
{
	TreeNodeACA *root = aca->root_;
	Queue queue;
	_constructQueue(&queue);
	TreeNodeACA *child = root->child;
	// Set all children nodes of root to root node
	// TODO: Verify whether it's okay to optimize this part.
	while (child != NULL) {
		AppendQueue(&queue, child);
		child->fail = root;
		child = child->cousin;
	}
	while (PeekFrontQueue(&queue) != NULL) {
		TreeNodeACA *parent = PeekFrontQueue(&queue);
		PopFrontQueue(&queue);
		TreeNodeACA *child = parent->child;
		while (child != NULL) {
			AppendQueue(&queue, child);

			// Walking along fail pointer of child's parentchildren nodes containing child->val_
			TreeNodeACA *fail = parent->fail;
			bool findFlag = false;

			// Traverse children node of fail node
			while (fail != NULL) {
				TreeNodeACA *fail_child = fail->child;
				while (fail_child != NULL && !_cmpChCharACA(fail_child->val_, child->val_)) {
					fail_child = fail_child->cousin;
				}

				if (fail_child == NULL) {//Not Found
					fail = fail->fail;
				}
				else { // Found
					child->fail = fail_child;
					break;
				}
			}
			if (fail == NULL) {
				child->fail = root;
			}
			child = child->cousin;
		}
	}
	_deconstructQueue(&queue);
}

bool _cmpChCharACA(char * ch1, char * ch2)
{
	if (ch1[0] == ch2[0] && ch1[1] == ch2[1])
		return true;
	return false;
}

void _constructACA(ACAutomaton *aca)
{
	TreeNodeACA *root = (TreeNodeACA *)malloc(sizeof(TreeNodeACA));
	root->child = NULL;
	root->cousin = NULL;
	root->is_end_ = false;
	root->fail = NULL;
	memset(root->val_, 0, 2);

	aca->root_ = root;
	aca->state_ = NULL;
	aca->key_num_ = 0;

	memset(aca->key_count_, 0, DICT_SIZE * sizeof(int));
}

void _deconstructACA(ACAutomaton * aca)
{
	TreeNodeACA *root = aca->root_;
	_freeACATree(root);
}

void _freeACATree(TreeNodeACA *root)
{
	TreeNodeACA *cousin = root->cousin;
	TreeNodeACA *child = root->child;
	if (cousin != NULL)
		_freeACATree(cousin);
	if (child != NULL)
		_freeACATree(child);
	free(root);
}
