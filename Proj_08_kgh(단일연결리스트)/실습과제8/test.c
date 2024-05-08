//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <string.h>
//
//#define MAX_LIST_SIZE 100 
//
//typedef struct SortedList{
//	int data;
//	struct SortedList *next;
//} NODE;
//
//NODE* g_pHead = NULL;
//
//void add(int data)
//{
//	NODE* ADDNODE =	(NODE*)malloc(sizeof(NODE));
//	
//	if (ADDNODE == NULL) {
//		printf("동적메모리 할당이 정상적으로 되지 않았습니다!\n");
//		return;
//	}
//
//	ADDNODE->data = data;  // 데이터 필드 초기화
//	ADDNODE->next = NULL;  // 다음 노드 포인터를 NULL로 초기화
//
//	if (g_pHead == NULL)
//	{
//		g_pHead = ADDNODE;
//	}
//	else
//	{
//		ADDNODE->next = g_pHead;
//		g_pHead = ADDNODE;
//	}
//}
//
//void display()
//{
//	NODE* temp = g_pHead;
//	while (temp != NULL)
//	{
//		printf("%d ->", temp->data);
//		temp = temp->next;
//	}
//}
//
//int main(void) {
//
//	NODE* list = NULL; // 초기화 안 해도 되지만 습관화하게 됐습니다... 만약 지장이가면 꼭 피드백 부탁드립니다!!!
//	srand(100);
//
//	for (int i = 0; i < 10; ++i) { // 여기서 10은 예시로, 실제 사진 속의 숫자 개수에 맞게 조정해야 함
//		add(rand());
//    }
//
//	while (list != NULL) //노드를 출력하고 다음을 가리키는 것
//	{
//		printf("%d -> ", list->data);
//		list = list->next;
//	}
//	
//	display();
//	
//
//	while (list != NULL) {
//		NODE* temp = list;
//		list = list->next;
//		free(temp);
//	}
//	
//
//
//	return 0;
//
//}
//
//
//
//
//	/*NODE* list;
//	//필요한 초기화 코드 추가
//	
//
//		srand(100); // 동일한 패턴을 찾기 위해 seed 값 100 부여함
//	while (1) {
//		item = rand(); //랜덤으로 나오는 수
//		add(&list, item); // 리스트에 요소 추가
//		display(&list); // 리스트의 모든 요소?
//		ch = getch();
//		if (ch == 'q') break; //종료함수
//	}
//	printf("get_length : %d \n", get_length(&list));
//	printf("is_empty : %d, is_full : %d \n",
//		is_empty(&list), is_full(&list)); //비었는지 체크하는 것
//	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5)); // pos -> 몇 번째의 연결리스트
//	printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415)); // 5415가 몇 번째인지 위치 찾기
//	printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));  10의 위치는 -1
//	printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));  위치찾기 및 제거
//	display(&list); // 리스트 출력
//	printf("call clear\n");
//	clear(&list);
//	display(&list);
//	printf("리스트 길이 %d \n", get_length(&list));
//
//	//종료하기 전에 수행해야 할 코드 추가
//	
//		return 0;
//}*/