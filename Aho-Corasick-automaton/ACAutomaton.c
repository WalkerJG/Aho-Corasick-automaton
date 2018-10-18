#include "ACAutomaton.h"
#include "malloc.h"
#include "string.h"
#include "Queue.h"

void InsertKeywordACA(ACAutomaton * aca, char * word)
{
	TreeNodeACA *curr_node = aca->root_;
	for (int i = 0; word[i] != '\0'; i += 2) {
		// Traverse all children nodes to find whether word[i] exists or not.
		TreeNodeACA *child = curr_node->child;
		TreeNodeACA *before = curr_node;

		while (child != NULL && !_cmpChChar(child->val_, &word[i])) {
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

bool QueryKeywordACA(ACAutomaton * aca, char * word)
{
	TreeNodeACA *curr_node = aca->root_;
	TreeNodeACA *child = NULL;
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

void BuildACA(ACAutomaton * aca, char ** words, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		InsertKeyword(aca, words[i][256]);
	}
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
		TreeNodeACA *child = parent->child;
		while (child != NULL) {
			AppendQueue(&queue, child);

			// Walking along fail pointer of child's parentchildren nodes containing child->val_
			TreeNodeACA *fail = parent->fail;
			bool findFlag = false;

			// Traverse children node of fail node
			while (fail != root) {
				TreeNodeACA *fail_child = fail->child;
				while (fail_child != NULL && _cmpChChar(fail_child->val_, child->val_)) {
					fail_child = fail_child->cousin;
				}

				if (fail_child == NULL) {//Not Found
					fail = parent->fail;
				}
				else { // Found
					child->fail = fail_child;
					break;
				}
			}
			if (fail == root) {
				child->fail = root;
			}
			child = child->cousin;
		}
	}
	_deconstructQueue(&queue);
}

void _constructACA(ACAutomaton *aca)
{
	TreeNodeACA *root = (TreeNodeACA *)malloc(sizeof(TreeNodeACA));
	root->child = NULL;
	root->cousin = NULL;
	root->is_end_ = false;
	root->fail = root;
	memset(root->val_, 0, 2);
	aca->root_ = root;
	aca->state_ = NULL;
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
		_freeTree(cousin);
	if (child != NULL)
		_freeTree(child);
	free(root);
}
