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
//		printf("�����޸� �Ҵ��� ���������� ���� �ʾҽ��ϴ�!\n");
//		return;
//	}
//
//	ADDNODE->data = data;  // ������ �ʵ� �ʱ�ȭ
//	ADDNODE->next = NULL;  // ���� ��� �����͸� NULL�� �ʱ�ȭ
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
//	NODE* list = NULL; // �ʱ�ȭ �� �ص� ������ ����ȭ�ϰ� �ƽ��ϴ�... ���� �����̰��� �� �ǵ�� ��Ź�帳�ϴ�!!!
//	srand(100);
//
//	for (int i = 0; i < 10; ++i) { // ���⼭ 10�� ���÷�, ���� ���� ���� ���� ������ �°� �����ؾ� ��
//		add(rand());
//    }
//
//	while (list != NULL) //��带 ����ϰ� ������ ����Ű�� ��
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
//	//�ʿ��� �ʱ�ȭ �ڵ� �߰�
//	
//
//		srand(100); // ������ ������ ã�� ���� seed �� 100 �ο���
//	while (1) {
//		item = rand(); //�������� ������ ��
//		add(&list, item); // ����Ʈ�� ��� �߰�
//		display(&list); // ����Ʈ�� ��� ���?
//		ch = getch();
//		if (ch == 'q') break; //�����Լ�
//	}
//	printf("get_length : %d \n", get_length(&list));
//	printf("is_empty : %d, is_full : %d \n",
//		is_empty(&list), is_full(&list)); //������� üũ�ϴ� ��
//	printf("get_entry : %d��ġ�� �����ʹ� %d\n", 5, get_entry(&list, 5)); // pos -> �� ��°�� ���Ḯ��Ʈ
//	printf("is_in_list : %d�� ��ġ�� %d \n", 5415, is_in_list(&list, 5415)); // 5415�� �� ��°���� ��ġ ã��
//	printf("is_in_list : %d�� ��ġ�� %d \n", 10, is_in_list(&list, 10));  10�� ��ġ�� -1
//	printf("delete : %d�� ��ġ�� %d \n", 5415, delete(&list, 5415));  ��ġã�� �� ����
//	display(&list); // ����Ʈ ���
//	printf("call clear\n");
//	clear(&list);
//	display(&list);
//	printf("����Ʈ ���� %d \n", get_length(&list));
//
//	//�����ϱ� ���� �����ؾ� �� �ڵ� �߰�
//	
//		return 0;
//}*/