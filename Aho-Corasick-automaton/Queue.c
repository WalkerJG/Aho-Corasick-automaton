#include "Queue.h"
#include "malloc.h"

void AppendQueue(Queue * queue, TreeNodeACA * tree_node)
{
	QueueNode *new_node = NULL; 
	if ((new_node = (QueueNode *)malloc(sizeof(QueueNode))) == NULL) {//Failed to allocate new node
		return;
	}
	new_node->val_ = tree_node;
	new_node->next_ = NULL;
	if (queue->head_ == queue->tail_ && queue->head_ == NULL) {
		queue->head_ = new_node;
		queue->tail_ = new_node;
	}
	else {
		queue->tail_->next_ = new_node;
		queue->tail_ = new_node;
	}
}

TreeNodeACA *PeekFrontQueue(Queue *queue)
{
	if (queue->head_ == NULL)
		return NULL;
	return queue->head_->val_;
}

void PopFrontQueue(Queue *queue)
{
	if (queue->head_ == NULL) {
		return;
	}
	if (queue->head_ == queue->tail_) {
		free(queue->head_);
		queue->head_ = NULL;
		queue->tail_ = NULL;
	}
	else {
		QueueNode *next = queue->head_->next_;
		free(queue->head_);
		queue->head_ = next;
	}
}

void _constructQueue(Queue * q)
{
	q->head_ = NULL;
	q->tail_ = NULL;
}

void _deconstructQueue(Queue * q)
{
	while (q->head_ != q->tail_) {
		PopFrontQueue(q);
	}
}
