#include "ACAutomaton.h"
#include "malloc.h"
#include "string.h"
#include "Queue.h"

#pragma warning(disable:4996)
// Matching from this->state_
void matchStringACA(ACAutomaton *this, char *str)
{
	size_t i = 0;
	while (str[i] != '\0') {
		/*if ((unsigned char)str[i] <= 0x1F) {
			++i;
			continue;
		}
	        */
		if(str[i] == '\r' || str[i] == '\n'){
			++i;
			continue;
		}	
		//Traverse all children nodes of state_ to find whether match str[i]
		TreeNodeACA *child = iterative_rbtree_search(this->state_->children, str[i]);
		if (child == NULL) {
			if (this->state_ == this->root_) {
				++i;
				continue;
			}
			else {
				this->state_ = this->state_->fail;
				if (this->state_ == NULL) {
					this->state_ = this->root_;
				}
			}
			continue;
		}
		else {
			this->state_ = child;
			if (this->state_->is_end_)
				this->key_count_[this->state_->keyId] += 1;

			TreeNodeACA *tmp = this->state_;
			while (tmp != this->root_) {
				tmp = tmp->fail;
				if (tmp->is_end_)
					this->key_count_[tmp->keyId] += 1;
			}
		}
		++i;

	}
}

void insertKeywordACA(ACAutomaton * this, char * word)
{
	TreeNodeACA *curr_node = this->root_;
	int i = 0;
	while (word[i] != '\0') {
		// Traverse all children nodes to find whether word[i] exists or not.
		TreeNodeACA *child = iterative_rbtree_search(curr_node->children, word[i]);

		TreeNodeACA *before = curr_node;


		// Found charcter
		if (child != NULL) {
			curr_node = child;
			if(curr_node->is_end_ == false && word[i+1] == '\0'){
				curr_node->is_end_ = true;
				curr_node->keyId = this->key_num_;
				strcpy(this->keyword_[this->key_num_], word);
				++this->key_num_;
				}
		}
		else {// Not found
			TreeNodeACA *new_node = (TreeNodeACA *)malloc(sizeof(TreeNodeACA));
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
				return ;
			curr_node = new_node;
		}
		++i;

	}
}

bool queryKeywordACA(ACAutomaton * this, char * word)
{
	TreeNodeACA *curr_node = this->root_;
	TreeNodeACA *child = NULL;
	for (size_t i = 0; curr_node != NULL && word[i] != '\0'; ++i) {
		child = iterative_rbtree_search(curr_node->children, word[i]);
		
		if (child == NULL) {
			return false;
		}
		else
			curr_node = child;
	}
	return child->is_end_;
}

void resetStateACA(ACAutomaton * this)
{
	this->state_ = this->root_;
	memset(this->key_count_, 0, sizeof(DICT_SIZE) * sizeof(int));
}

void buildACA(ACAutomaton * this, char ** words, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		size_t offset = i * 256;
		insertKeywordACA(this, ((char *)(words)) + offset);
	}
	_addFailPointer(this);
}

void _addFailPointer(ACAutomaton * this)
{
	TreeNodeACA *root = this->root_;
	Queue queue;
	Queue child_queue;
	_constructQueue(&queue);
	_constructQueue(&child_queue);
	put_all_nodes_in_queue(root->children, &child_queue);
	TreeNodeACA *child = NULL;
	// Set all children nodes of root to root node
	// TODO: Verify whether it's okay to optimize this part.
	while ((child=PeekFrontQueue(&child_queue)) != NULL) {
		AppendQueue(&queue, child);
		PopFrontQueue(&child_queue);
		child->fail = root;
	}
	while (PeekFrontQueue(&queue) != NULL) {
		TreeNodeACA *parent = PeekFrontQueue(&queue);
		PopFrontQueue(&queue);
		put_all_nodes_in_queue(parent->children, &child_queue);
		while ((child = PeekFrontQueue(&child_queue)) != NULL) {
			AppendQueue(&queue, child);
			PopFrontQueue(&child_queue);

			// Walking along fail pointer of child's parentchildren nodes containing child->val_
			TreeNodeACA *fail = parent->fail;
			bool findFlag = false;

			// Traverse children node of fail node
			while (fail != NULL) {

				TreeNodeACA *fail_child = iterative_rbtree_search(fail->children, child->val_);

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
		}
	}
	_deconstructQueue(&queue);
	_deconstructQueue(&child_queue);
}


void _constructACA(ACAutomaton *this)
{
	TreeNodeACA *root = (TreeNodeACA *)malloc(sizeof(TreeNodeACA));
	root->children = create_rbtree();
	root->is_end_ = false;
	root->fail = NULL;
	root->val_ = 0;

	this->root_ = root;
	this->state_ = NULL;
	this->key_num_ = 0;

	memset(this->key_count_, 0, DICT_SIZE * sizeof(int));

	int i = 0;
	for (i = 0; i < DICT_SIZE; ++i)
		this->keyword_[i] = (char *)malloc(MAX_WORD_LEGNTH);
}

void _deconstructACA(ACAutomaton * this)
{
	TreeNodeACA *root = this->root_;
	int i = 0;
	for (i = 0; i < DICT_SIZE; ++i)
		free((char *)this->keyword_[i]);
	_freeACATree(root);
}

void _freeACATree(TreeNodeACA *root)
{
	/*TreeNodeACA *cousin = root->cousin;
	TreeNodeACA *child = root->child;
	free(root);
	if (cousin != NULL)
		_freeACATree(cousin);
	if (child != NULL)
		_freeACATree(child);*/
}
