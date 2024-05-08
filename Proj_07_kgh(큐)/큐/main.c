

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>


#define PROB 1
#define MAX_QUEUE_SIZE 10

typedef struct ClassTime{
	char day[3]; // ����
	int period;  // �ð�
} ClassTime;

typedef struct Schedule{
	int count;            // �ð�ǥ ���� ����
	ClassTime time[4];    // �ִ� 4���� �ð�ǥ ����
} Schedule;

typedef struct element {
	char subject[20];     // �����
	char professor[20];   // ������
	Schedule schedule;    // ���� �ð�ǥ
} element;

typedef struct DequeType{ // ��ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;

// ��ť �Լ� ����

// ���� �Լ�
void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// �ʱ�ȭ
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// ��ȭ ���� ���� �Լ�
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ������ť ��� �Լ�
void deque_print(DequeType* q) {
	printf("DEQUE(front=%d rear=%d) : \n", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			// element ����ü�� ������ ����ϴ� �ڵ� �ʿ�
			printf("�������: %s, ������: %s, �ð�ǥ: ", q->data[i].subject, q->data[i].professor);
			for (int j = 0; j < q->data[i].schedule.count; j++) {
				printf("%s����, %d���� ", q->data[i].schedule.time[j].day, q->data[i].schedule.time[j].period);
			}
			printf("\n");
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
	prontf("Test");
}






// ���� �Լ�


void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// ���� �Լ�
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// ���� �Լ�
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[q->rear];
}

int main(void)
{
	DequeType queue;

	element data1 = { "�ڷᱸ��","��Ȳ��",{4, {"ȭ", 1, "ȭ", 2, "��", 1, "��", 2}} };
	element data2 = { "��ǻ�ͱ���","���ö",{4, {"��", 3, "��", 4, "��", 6, "��", 7}} };
	element data3 = { "�������","�̿���",{3, {"��", 8, "��", 9, "��", 3}} };

	init_deque(&queue); deque_print(&queue);
	add_front(&queue, data1); deque_print(&queue);
	add_rear(&queue, data2); deque_print(&queue);
	add_front(&queue, data3); deque_print(&queue);
	delete_rear(&queue); deque_print(&queue);
	delete_front(&queue); deque_print(&queue);
	delete_front(&queue); deque_print(&queue);
	delete_rear(&queue); deque_print(&queue);
	return 0;
}


//#include <stdio.h>
//#include <stdlib.h>
//// ===== ����ť �ڵ� ���� ======
//#define MAX_QUEUE_SIZE 5
//typedef int element;
//typedef struct { // ť Ÿ��
//	element data[MAX_QUEUE_SIZE];
//	int front, rear;
//} QueueType;
//
//// ���� �Լ�
//void error(char* message)
//{
//	fprintf(stderr, "%s\n", message);
//	exit(1);
//}
//// ���� ���� ���� �Լ�
//void init_queue(QueueType* q)
//{
//	q->front = q->rear = 0;
//}
//// ���� ���� ���� �Լ�
//int is_empty(QueueType* q)
//{
//	return (q->front == q->rear);
//}
//// ��ȭ ���� ���� �Լ�
//int is_full(QueueType* q)
//{
//	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
//}
//// ����ť ��� �Լ�
//void queue_print(QueueType* q)
//{
//	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
//	if (!is_empty(q)) {
//		int i = q->front;
//		do {
//			i = (i + 1) % (MAX_QUEUE_SIZE);
//			printf("%d | ", q->data[i]);
//			if (i == q->rear)
//				break;
//		} while (i != q->front);
//	}
//	printf("\n");
//}
//// ���� �Լ�
//void enqueue(QueueType* q, element item)
//{
//	if (is_full(q))
//		error("ť�� ��ȭ�����Դϴ�");
//	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
//	q->data[q->rear] = item;
//}
//// ���� �Լ�
//element dequeue(QueueType* q)
//{
//	if (is_empty(q))
//		error("ť�� ��������Դϴ�");
//	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
//	return q->data[q->front];
//}
//
//# include <stdio.h>
//# include <stdlib.h>
//// ���α׷� 5.2���� ������ ���� �κ��� �����Ѵ�.
//// ================ ����ť �ڵ� ���� =================
//typedef struct { // ��� Ÿ��
//	int id;
//	int arrival_time;
//	int service_time;
//} element; // ��ü!
//// ...
//// ================ ����ť �ڵ� ���� =================
//int main(void)
//{
//	int minutes = 60;
//	int total_wait = 0;
//	int total_customers = 0;
//	int service_time = 0;
//	int service_customer;
//	QueueType queue;
//	init_queue(&queue);
//	srand(time(NULL));
//	for (int clock = 0; clock < minutes; clock++) {
//		printf("����ð�=%d\n", clock);
//		if ((rand() % 10) < 3) {
//			element customer;
//			customer.id = total_customers++;
//			customer.arrival_time = clock;
//			customer.service_time = rand() % 3 + 1;
//			enqueue(&queue, customer);
//			printf("�� %d�� %d�п� ���ɴϴ�. ����ó���ð�= %d��\n", customer.id, customer.arrival_time, customer.service_time);
//		}
//		if (service_time > 0) {
//			printf("�� %d ����ó�����Դϴ�. \n", service_customer);
//			service_time--;
//		}
//		else {
//			if (!is_empty(&queue)) {
//				element customer = dequeue(&queue);
//				service_customer = customer.id;
//				service_time = customer.service_time;
//				printf("�� %d�� %d�п� ������ �����մϴ�. ���ð��� % d���̾����ϴ�.\n", customer.id, clock, clock - customer.arrival_time);
//					total_wait += clock - customer.arrival_time;
//			}
//		}
//	}
//	printf("��ü ��� �ð�=%d�� \n", total_wait);
//	return 0;
//}