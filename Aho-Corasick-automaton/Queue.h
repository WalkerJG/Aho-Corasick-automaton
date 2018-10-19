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

// Peek the front of queue 
TreeNodeACA *PeekFrontQueue(Queue *queue);

// Append node at the end of queue
void AppendQueue(Queue *queue, TreeNodeACA *tree_node);

// Pop the front node of queue
void PopFrontQueue(Queue *queue);

// Construct a queue
void _constructQueue(Queue *q);

// Deconstruct a queue
void _deconstructQueue(Queue *q);
#endif