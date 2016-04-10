#include<stdio.h>
#include<stdlib.h>

struct Node 
{
    double element;
    struct Node * next;
};

struct Queue 
{
	struct Node *head;
	struct Node *tail;
	int size;
};

struct Queue *newQueue(void);
void enqueue(struct Queue *, double);
void dequeue(struct Queue *);
void toString(struct Queue *);
void testQueue(struct Queue *);
void freeQueue(struct Queue *);

struct Queue* newQueue()
{
	struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	
	return q;
}

void freeQueue(struct Queue *q)
{
	struct Node *current = q->head;
	struct Node * temp = current;
	while(current != NULL) 
	{
		temp = current->next;
		current = temp;
		free(temp);
	}
	free(q);
}

void enqueue(struct Queue *q, double newElement)
{
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->element = newElement; 
	newNode->next = NULL;
	struct Node *temp = newNode;
	temp->next = NULL;
	if(q->size == 0)
		q->head = newNode;
	else
		q->tail->next = newNode;
	q->tail = newNode;
	q->size++;
	free(temp);
}

void dequeue(struct Queue *q) 
{	
	if(q->size == 0)
		return;
	struct Node *temp = q->head;
	temp->next = NULL;
	q->head = q->head->next;
	free(temp);
	q->size--;
	if(q->size == 0)
		q->tail = NULL;
}

void toString(struct Queue *q) 
{	
	struct Node *current = (struct Node*)malloc(sizeof(struct Node));
	for (current = q->head; current != NULL; current = current->next)
	{
		struct Node *temp = current;
		printf("  %f", current->element);
		free(temp);
	}
	printf("\n");
	free(current);
	
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



