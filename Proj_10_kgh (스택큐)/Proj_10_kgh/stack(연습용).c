//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct WORLD_COORDINATE {
//	int x;
//	int y;
//	int z;
//} element;
//
//typedef struct StackNode {
//	element data;
//	struct StackNode* next;
//} StackNode;
//
//typedef struct {
//	StackNode* top;
//} LinkedStackType;
//
//void init(LinkedStackType* s)
//{
//	s->top = NULL;
//}
//
//int is_empty(LinkedStackType* s)
//{
//	return (s->top == NULL);
//}
//
//int is_full(LinkedStackType* s)
//{
//	return 0;
//}
//
//void push(LinkedStackType* s, element item)
//{
//	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
//
//	temp->data = item;
//	temp->next = s->top;
//	s->top = temp;
//}
//
//void print_stack(LinkedStackType* s)
//{
//	for (StackNode* p = s->top; p != NULL; p = p->next) {
//			printf("%d-> ", p->data.x, p->data.y, p-> data.z);
//	}
//	printf("\n");
//}
//
//element pop(LinkedStackType* s)
//{
//	if (is_empty(s)) {
//		fprintf(stderr, "스택이 비어있음\n");
//		exit(1);
//	}
//	else
//	{
//		StackNode* temp = s->top;
//		//int data = temp->data; 기존 코드에서 변경점 ->
//		element data = temp -> data;
//		//s->top = s->top->next; 변경.
//		s->top = temp->next;
//		free(temp);
//		return data;
//	}
//}
//
//int main()
//{
//	LinkedStackType s;
//	element item;
//
//	init(&s);
//	print_stack(&s);
//
//	item.x = 1; item.y = 1; item.z = 1;
//	printf("Push item\n");
//	push(&s, item); print_stack(&s);
//	item.x = 2; item.y = 2; item.z = 2;
//	printf("Push item\n");
//	push(&s, item); print_stack(&s);
//	item.x = 3; item.y = 3; item.z = 3;
//	printf("Push item\n");
//	push(&s, item); print_stack(&s);
//	item.x = 4; item.y = 4; item.z = 4;
//	printf("Push item\n");
//	push(&s, item); print_stack(&s);
//	printf("PoP item\n");
//	item = pop(&s);
//	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
//	print_stack(&s);
//	printf("PoP item\n");
//	item = pop(&s);
//	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
//	print_stack(&s);
//	printf("PoP item\n");
//	item = pop(&s);
//	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
//	print_stack(&s);
//	printf("PoP item\n");
//	item = pop(&s);
//	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
//	print_stack(&s);
//	printf("PoP item\n");
//	item = pop(&s);
//	printf("PoP data : (%d, %d, %d) \n", item.x, item.y, item.z);
//	print_stack(&s);
//	printf("PoP item\n");
//	item = pop(&s);
//	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
//	print_stack(&s);
//
//}