#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE  11
typedef struct Queue
{
	double queue[MAX_SIZE];
	int head;
	int tail;
	int size;
} Queue;
//FUNCTION PROTOTYPES

Queue* newQueue(void);
void enqueue(Queue*, double);
double dequeue(Queue*);
int isEmpty(Queue*);
void toString(Queue*);
void testQueue(Queue*);


Queue* newQueue()
{
	struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
	q->head = 0;
	q->size = 0;
	
	return q;
}

int isEmpty(Queue* q)
{
	return (q->size == 0);
}

void enqueue(Queue *q, double newElement)
{
	if(q->size == MAX_SIZE)
		return;
	q->queue[(q->head + q->size) % MAX_SIZE] = newElement;
	q->size++;
}

double dequeue(Queue *q)//REEEEE
{
	double toReturn;

	if(!isEmpty(q))
	{
		toReturn = q->queue[q->head];
		q->queue[q->head] = 0.;
		q->head = (q->head + 1) % MAX_SIZE;
		q->size--;
		return toReturn;
	}
	else
		return -9.;
}

void toString(Queue *q)
{
	int j = q->head;
	for(int i = 0; i < q->size; i++)
	{
		printf("%f ", q->queue[j]);
		j = (j+1)%MAX_SIZE;
	}
	printf("\n");
}

void testQueue(struct Queue *q)
{
	enqueue(q, 2.); 
	toString(q); //2
	enqueue(q, 4.); 
	toString(q); //2, 4
	enqueue(q, 6.); 
	toString(q);//2, 4, 6
	dequeue(q);  
	toString(q);//4, 6
	enqueue(q, 8.); 
	toString(q);// 4, 6, 8
}


