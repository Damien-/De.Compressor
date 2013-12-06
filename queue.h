#include "dh.h"

#ifndef queue
#define queue

typedef struct elem
{
	Node * info;
	struct elem *next;
}Elem;


typedef struct queue
{
	Elem *front,*rear;
}Queue;


Queue Init();
void Insert(Queue *q, Node * x);
Node * Delete(Queue *q);
int QueueEmpty(Queue q);


#endif