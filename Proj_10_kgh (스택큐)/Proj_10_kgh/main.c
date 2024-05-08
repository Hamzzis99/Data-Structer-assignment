#define _CRT_SECURE_NO_WARNINGS
#define PROB 1 // ���� �ٲٱ� (1.����) (2.ť)

#if PROB == 1 // stack

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WORLD_COORDINATE {
	int x;
	int y;
	int z;
} element;

typedef struct StackNode {
	element data;
	struct StackNode* next;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s)
{
	s->top = NULL;
}

int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}

int is_full(LinkedStackType* s)
{
	return 0;
}

void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));

	temp->data = item;
	temp->next = s->top;
	s->top = temp;
}

void print_stack(LinkedStackType* s)
{
	printf("= ���� ����=\n");
	if (is_empty(s)) {
		printf("NULL <--- TOP \n");
	}
	else
	{
		for (StackNode* p = s->top; p != NULL; p = p->next) {
			if (p == s -> top)
			{
				printf("(%d, %d, %d) <--- Top \n", p->data.x, p->data.y, p->data.z);
			}
			printf("(%d, %d, %d)\n", p->data.x, p->data.y, p->data.z);
		}
	}
	printf("\n");
}

element pop(LinkedStackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else
	{
		StackNode* temp = s->top;
		//int data = temp->data; ���� �ڵ忡�� ������ ->
		element data = temp->data;
		//s->top = s->top->next; ����.
		s->top = temp->next;

		free(temp);
		return data;
	}
}

int main()
{
	LinkedStackType s;
	element item;

	init(&s);
	print_stack(&s);

	item.x = 1; item.y = 1; item.z = 1;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 2; item.y = 2; item.z = 2;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 3; item.y = 3; item.z = 3;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 4; item.y = 4; item.z = 4;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
}



#elif PROB == 2 // queue
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WORLD_COORDINATE {
	int x;
	int y;
	int z;
}element;

typedef struct QueueNode {
	element data;
	struct QueueNode* link;
} QueueNode;

typedef struct {
	QueueNode* front, * rear;
} LinkedlistQueue;

void init(LinkedlistQueue* q)
{
	q->front = q->rear = NULL;
}

int is_empty(LinkedlistQueue* q)
{
	return (q->front == NULL); // ť�� front�� NULL�̸� ť�� ����ִٰ� �Ǵ�
}
void enqueue(LinkedlistQueue* q, element data)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = data;
	temp->link = NULL;
	if (is_empty(q)) {
		q->front = temp;
		q->rear = temp;
	}
	else
	{
		q->rear->link = temp;
		q->rear = temp;
	}
}

element dequeue(LinkedlistQueue* q)
{
	QueueNode* temp = q->front;
	element data;
	if (is_empty(q))
	{
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else
	{
		data = temp->data;
		q->front = q->front->link;
		if (q->front == NULL)
			q->rear = NULL;
		free(temp);
		return data;
	}
}

void print_queue(LinkedlistQueue* q) {
	printf("= ť ����=\n");
	if (is_empty(q)) {
		printf("NULL <--- Front, Rear \n");
	}
	else {
		for (QueueNode* p = q->front; p != NULL; p = p->link) {
			if (p == q->front && p == q->rear)
			{
				printf("(%d, %d, %d) <--- Front, Rear \n", p->data.x, p->data.y, p->data.z);
			}
			else if (p == q->front)
			{
				printf("(%d, %d, %d) <--- Front \n", p->data.x, p-> data.y, p->data.z);
			}
			else if (p == q->rear)
			{
				printf("(%d, %d, %d) <--- Rear \n", p->data.x, p->data.y, p->data.z);
			}

			else 
			{
				printf("(%d, %d, %d)\n", p->data.x, p->data.y, p->data.z);
			}
		}
		printf("\n");
	}
}

int main()
{
	element item;
	LinkedlistQueue queue;

	init(&queue);

	print_queue(&queue);
	printf("enqueue item \n");
	item.x = 1, item.y = 1, item.z = 1;
	enqueue(&queue, item); 
	print_queue(&queue);

	printf("enqueue item \n");
	item.x = 2, item.y = 2, item.z = 2;
	enqueue(&queue, item); 
	print_queue(&queue);

	printf("enqueue item \n");
	item.x = 3, item.y = 3, item.z = 3;
	enqueue(&queue, item); 
	print_queue(&queue);

	printf("enqueue item \n");
	item.x = 4, item.y = 4, item.z = 4;
	enqueue(&queue, item); 
	print_queue(&queue);

	printf("enqueue item \n");
	item.x = 5, item.y = 5, item.z = 5;
	enqueue(&queue, item); 
	print_queue(&queue);

	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	print_deleted_history();
}





#endif