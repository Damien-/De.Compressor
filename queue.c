#include "dh.h"
#include "queue.h"
#include <stdlib.h>



Queue Init()
{
	Queue q;
	q.front=q.rear=NULL;
	return q;
}

void Insert(Queue *q, Node * x)
{
	Elem* newElem=(Elem*)malloc(sizeof(Elem));
	newElem->info=x;
	newElem->next=NULL;
	if(q->rear==NULL)
		q->front=newElem;
	else
		q->rear->next=newElem;
	q->rear=newElem;
}


Node * Delete(Queue *q)
{
	if(q->front==NULL)
		return NULL;
	else
	{
		Elem * front = q->front;
		Node * x=front->info;
		q->front=front->next;
		if(q->front==NULL)
		q->rear=NULL;
		free(front);
		return x;
	}
}

int QueueEmpty(Queue q)
{
	if(q.front==NULL)
		return 1;
	return 0;
}