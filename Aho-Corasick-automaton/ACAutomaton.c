#include "ACAutomaton.h"
#include "malloc.h"
#include "string.h"
#include "Queue.h"

// Matching from this->state_
void matchStringACA(ACAutomaton *this, char *str, size_t size)
{
	size_t i = 0;
	char tmp_ch[2];
	while (i < size) {
		TreeNodeACA *child = this->state_->child;
		if (_isGB2312Char(&str[i])) {
			tmp_ch[0] = str[0];
			tmp_ch[1] = str[1];
			i += 2;
		}
		else {
			tmp_ch[0] = 0;
			tmp_ch[1] = str[0];
			i += 1;
		}
		//Traverse all children nodes of state_ to find whether match str[i]str[i+1]
		while (child != NULL && !_cmpChCharACA(child->val_, &tmp_ch)) {
			child = child->cousin;
		}
		if (child == NULL) {
			this->state_ = this->state_->fail;
			if (this->state_ == NULL) {
				this->state_ = this->root_;
				i += 2;
			}
			continue;
		}
		else {
			this->state_ = child;
			if (this->state_->is_end_)
				this->key_count_[this->state_->keyId] += 1;
		}
		i += 2;

	}
}

void insertKeywordACA(ACAutomaton * this, char * word)
{
	TreeNodeACA *curr_node = this->root_;
	char tmp_ch[2];
	int i = 0;
	while (word[i] != '\0') {
			// Traverse all children nodes to find whether word[i] exists or not.
			TreeNodeACA *child = curr_node->child;
			TreeNodeACA *before = curr_node;

			if (_isGB2312Char(&word[i]) ){
				tmp_ch[0] = word[0];
					tmp_ch[1] = word[1];
					i+=2;
			}
			else {
				tmp_ch[0] = 0;
				tmp_ch[1] = word[0];
				i += 1;
			}
			while (child != NULL && !_cmpChCharACA(child->val_, &tmp_ch)) {
				before = child;
				child = child->cousin;
			}

			// Found charcter
			if (child != NULL) {
				curr_node = child;
			}
			else {// Not found
				TreeNodeACA *new_node = (TreeNodeACA*)malloc(sizeof(TreeNodeACA));
				
				memcpy(new_node->val_, (void *)&tmp_ch[i], 2);
				new_node->is_end_ = word[i + 2] == '\0' ? true : false;
				new_node->child = NULL;
				new_node->cousin = NULL;
				new_node->keyId = this->key_num_;
				this->key_num_ += word[i + 2] == '\0' ? 1 : 0;
				if (this->key_num_ == 40790)
					printf("%s", "here");
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

bool queryKeywordACA(ACAutomaton * this, char * word)
{
	TreeNodeACA *curr_node = this->root_;
	TreeNodeACA *child = NULL;
	char tmp_ch[2];
	for (size_t i = 0; curr_node != NULL && word[i] != '\0'; i += 2) {
		child = curr_node->child;
		if (_isGB2312Char(&word[i])) {
			tmp_ch[0] = word[0];
			tmp_ch[1] = word[1];
			i += 2;
		}
		else {
			tmp_ch[0] = 0;
			tmp_ch[1] = word[0];
			i += 1;
		}
		// Find the child with same character as word[i] word[i+1
		while (child != NULL && !_cmpChCharACA(child->val_, &tmp_ch)) {
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

bool _isGB2312Char(char * word)
{
		bool high = (unsigned char)word[0] >= (0xA1) && (unsigned char)word[0] <= (0xFE);
	bool low = (unsigned char)word[1] >= (0xA1) && (unsigned char)word[1] <= (0xFE);
	return high && low;
}

void _constructACA(ACAutomaton *this)
{
	TreeNodeACA *root = (TreeNodeACA *)malloc(sizeof(TreeNodeACA));
	root->child = NULL;
	root->cousin = NULL;
	root->is_end_ = false;
	root->fail = NULL;
	memset(root->val_, 0, 2);

	this->root_ = root;
	this->state_ = NULL;
	this->key_num_ = 0;

	memset(this->key_count_, 0, DICT_SIZE * sizeof(int));
}

void _deconstructACA(ACAutomaton * this)
{
	TreeNodeACA *root = this->root_;
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
