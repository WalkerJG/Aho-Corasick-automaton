#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "ACAutomaton.h"

typedef struct QueueNode {
	TreeNodeACA *val_;
	struct QueueNode *next_;
} QueueNode;

typedef struct Queue {
	QueueNode *head_;
	QueueNode *tail_;
}Queue;

TreeNodeACA *PeekFrontQueue(Queue *queue);
void AppendQueue(Queue *queue, TreeNodeACA *tree_node);
void PopFrontQueue(Queue *queue);

void _constructQueue(Queue *q);
void _deconstructQueue(Queue *q);
#endif