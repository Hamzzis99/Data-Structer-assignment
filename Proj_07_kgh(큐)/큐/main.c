

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>


#define PROB 1
#define MAX_QUEUE_SIZE 10

typedef struct ClassTime{
	char day[3]; // 요일
	int period;  // 시간
} ClassTime;

typedef struct Schedule{
	int count;            // 시간표 정보 개수
	ClassTime time[4];    // 최대 4개의 시간표 정보
} Schedule;

typedef struct element {
	char subject[20];     // 과목명
	char professor[20];   // 교수명
	Schedule schedule;    // 강의 시간표
} element;

typedef struct DequeType{ // 데큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;

// 데큐 함수 모음

// 오류 함수
void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 초기화
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 원형데큐 출력 함수
void deque_print(DequeType* q) {
	printf("DEQUE(front=%d rear=%d) : \n", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			// element 구조체의 내용을 출력하는 코드 필요
			printf("교과목명: %s, 교수명: %s, 시간표: ", q->data[i].subject, q->data[i].professor);
			for (int j = 0; j < q->data[i].schedule.count; j++) {
				printf("%s요일, %d교시 ", q->data[i].schedule.time[j].day, q->data[i].schedule.time[j].period);
			}
			printf("\n");
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
	prontf("Test");
}






// 삽입 함수


void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 삭제 함수
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[q->rear];
}

int main(void)
{
	DequeType queue;

	element data1 = { "자료구조","오황석",{4, {"화", 1, "화", 2, "수", 1, "수", 2}} };
	element data2 = { "컴퓨터구조","김경철",{4, {"월", 3, "월", 4, "목", 6, "목", 7}} };
	element data3 = { "선형대수","이용희",{3, {"월", 8, "월", 9, "금", 3}} };

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
//// ===== 원형큐 코드 시작 ======
//#define MAX_QUEUE_SIZE 5
//typedef int element;
//typedef struct { // 큐 타입
//	element data[MAX_QUEUE_SIZE];
//	int front, rear;
//} QueueType;
//
//// 오류 함수
//void error(char* message)
//{
//	fprintf(stderr, "%s\n", message);
//	exit(1);
//}
//// 공백 상태 검출 함수
//void init_queue(QueueType* q)
//{
//	q->front = q->rear = 0;
//}
//// 공백 상태 검출 함수
//int is_empty(QueueType* q)
//{
//	return (q->front == q->rear);
//}
//// 포화 상태 검출 함수
//int is_full(QueueType* q)
//{
//	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
//}
//// 원형큐 출력 함수
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
//// 삽입 함수
//void enqueue(QueueType* q, element item)
//{
//	if (is_full(q))
//		error("큐가 포화상태입니다");
//	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
//	q->data[q->rear] = item;
//}
//// 삭제 함수
//element dequeue(QueueType* q)
//{
//	if (is_empty(q))
//		error("큐가 공백상태입니다");
//	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
//	return q->data[q->front];
//}
//
//# include <stdio.h>
//# include <stdlib.h>
//// 프로그램 5.2에서 다음과 같은 부분을 복사한다.
//// ================ 원형큐 코드 시작 =================
//typedef struct { // 요소 타입
//	int id;
//	int arrival_time;
//	int service_time;
//} element; // 교체!
//// ...
//// ================ 원형큐 코드 종료 =================
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
//		printf("현재시각=%d\n", clock);
//		if ((rand() % 10) < 3) {
//			element customer;
//			customer.id = total_customers++;
//			customer.arrival_time = clock;
//			customer.service_time = rand() % 3 + 1;
//			enqueue(&queue, customer);
//			printf("고객 %d이 %d분에 들어옵니다. 업무처리시간= %d분\n", customer.id, customer.arrival_time, customer.service_time);
//		}
//		if (service_time > 0) {
//			printf("고객 %d 업무처리중입니다. \n", service_customer);
//			service_time--;
//		}
//		else {
//			if (!is_empty(&queue)) {
//				element customer = dequeue(&queue);
//				service_customer = customer.id;
//				service_time = customer.service_time;
//				printf("고객 %d이 %d분에 업무를 시작합니다. 대기시간은 % d분이었습니다.\n", customer.id, clock, clock - customer.arrival_time);
//					total_wait += clock - customer.arrival_time;
//			}
//		}
//	}
//	printf("전체 대기 시간=%d분 \n", total_wait);
//	return 0;
//}