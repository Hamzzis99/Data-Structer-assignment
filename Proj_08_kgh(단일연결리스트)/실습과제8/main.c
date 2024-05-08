#define _CRT_SECURE_NO_WARNINGS

#define PROB 1

#if PROB == 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX_LIST_SIZE 100

typedef int ElementType;

typedef struct {
    ElementType elements[MAX_LIST_SIZE];
    int last; // �迭�� ������ ��Ҹ� ����Ű�� �ε���
} SortedList;

// ����Ʈ �ʱ�ȭ
void initList(SortedList* list) {
    list->last = -1;
}

// ����Ʈ�� ������� Ȯ��
int is_empty(const SortedList* list) {
    return list->last == -1;
}

// ����Ʈ�� �� á���� Ȯ��
int is_full(const SortedList* list) {
    return list->last == MAX_LIST_SIZE - 1;
}

// ����Ʈ�� ����(��� ����) ��ȯ
int get_length(const SortedList* list) {
    return list->last + 1;
}

// ����Ʈ ���
void display(const SortedList* list) {
    for (int i = 0; i <= list->last; i++) {
        printf("%d -> ", list->elements[i]);
    }
    printf("\n");
}

// ����Ʈ���� Ư�� ��ġ�� ��� ��������
int get_entry(const SortedList* list, int pos) {
    if (pos < 0 || pos > list->last) {
        return -1; // �߸��� ��ġ
    }
    return list->elements[pos];
}

// ����Ʈ�� ��� �߰�
void add(SortedList* list, ElementType item) {
    if (is_full(list)) {
        return; // ����Ʈ�� �� á���� �߰����� ����
    }
    int i;
    for (i = list->last; (i >= 0 && list->elements[i] > item); i--) {
        list->elements[i + 1] = list->elements[i];
    }
    list->elements[i + 1] = item;
    list->last++;
}

// ����Ʈ���� ��� ���� �� �ε��� ��ȯ
int delete(SortedList* list, ElementType item) {
    int i, j;
    for (i = 0; i <= list->last; i++) {
        if (list->elements[i] == item) {
            for (j = i; j < list->last; j++) {
                list->elements[j] = list->elements[j + 1];
            }
            list->last--;
            return i; // ������ ����� �ε��� ��ȯ
        }
    }
    return -1; // ��Ҹ� ã�� ���� ���
}

// ����Ʈ�� Ư�� ��Ұ� �ִ��� Ȯ���ϰ� �ε��� ��ȯ
int is_in_list(const SortedList* list, ElementType item) {
    for (int i = 0; i <= list->last; i++) {
        if (list->elements[i] == item) {
            return i;
        }
    }
    return -1; // ��Ҹ� ã�� ���� ���
}

// ����Ʈ�� ��� ��Ҹ� �����ϰ� �ʱ�ȭ
void clear(SortedList* list) {
    list->last = -1;
}

int main(void) {
    SortedList list;
    int ch;

    printf("�迭�� �̿��Ͽ� ���� ����Ʈ �����\n");

    initList(&list);
    srand(100);
    while (!is_full(&list)) {
        int item = rand() % 10000; // ������ ���� ����
        add(&list, item);
        display(&list);
        ch = _getch();
        if (ch == 'q' || ch == 'Q') break;
    }

    // ��� ���
    
    printf("get_length : %d \n", get_length(&list));
    printf("is_empty : %d, is_full : %d \n", is_empty(&list), is_full(&list));
    printf("get_entry : 5 ��ġ�� �����ʹ� %d\n", get_entry(&list, 5));
    printf("is_in_list : %d �� ��ġ�� %d \n", 5415, is_in_list(&list, 5415));
    printf("is_in_list : %d �� ��ġ�� %d \n", 10, is_in_list(&list, 10));
    printf("delete : %d�� ��ġ�� %d \n", 5415, delete(&list, 5415));
    display(&list);
    printf("call clear\n");
    clear(&list);
    display(&list);
    printf("get_length : %d \n", get_length(&list));
 
    printf("��ټ� ChatGPT�� �̿��Ͽ� ������ �ڵ��Դϴ�... ������ ���� �����ŵ� �˴ϴ�.. \n");
    _getch();

    return 0;
}


#elif PROB == 2
// 2�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX_LIST_SIZE 100

typedef struct SortedList {
    int data;
    struct SortedList* next;
} SortedList;

SortedList* add(SortedList* list, int value) {
    SortedList* newNode = (SortedList*)malloc(sizeof(SortedList));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;

    if (list == NULL || list->data >= value) {
        newNode->next = list;
        return newNode;
    }
    else {
        SortedList* current = list;
        while (current->next != NULL && current->next->data < value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        return list;
    }
}

void display(SortedList* list) {
    SortedList* current = list;
    while (current != NULL) {
        printf("%d->", current->data);
        current = current->next;
    }
    printf("\n");
}

SortedList* clear(SortedList* list) {
    SortedList* current = list;
    SortedList* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    return NULL;
}

int delete(SortedList** list, int item) { // �����Լ��� ChatGPT�� �̿��Ͽ����ϴ�...
    if (*list == NULL) {
        return -1; // ����Ʈ�� ����ִٸ� -1 ��ȯ
    }

    int idx = 0; // ������ ����� �ε����� ����
    SortedList* current = *list;
    SortedList* previous = NULL;

    while (current != NULL) {
        if (current->data == item) {
            // ù ��° ��Ҹ� �����ϴ� ���
            if (previous == NULL) {
                *list = current->next;
            }
            else {
                previous->next = current->next;
            }
            free(current);
            return idx; // ������ ����� �ε��� ��ȯ
        }
        previous = current;
        current = current->next;
        idx++;
    }

    return -1; // ��Ҹ� ã�� ���� ��� -1 ��ȯ
}

int get_length(SortedList* list) {
    int count = 0;
    for (SortedList* current = list; current != NULL; current = current->next) {
        count++;
    }
    return count;
}

int is_empty(SortedList* list) {
    return list == NULL;
}

int is_full(SortedList* list) {
    return get_length(list) >= MAX_LIST_SIZE;
}

int get_entry(SortedList* list, int pos) {
    int idx = 0;
    SortedList* current = list;
    while (current != NULL && idx < pos) {
        current = current->next;
        idx++;
    }
    return (current != NULL) ? current->data : -1;
}

int is_in_list(SortedList* list, int item) {
    int idx = 0;
    SortedList* current = list;
    while (current != NULL) {
        if (current->data == item) {
            return idx;
        }
        current = current->next;
        idx++;
    }
    return -1;
}

int main(void) {
    SortedList* list = NULL;
    int ch;

    printf("���Ḯ��Ʈ�� �̿��Ͽ� ���� ����Ʈ �����\n");

    srand(100);
    while (1) {
        int item = rand();
        list = add(list, item);
        display(list);
        ch = _getch();
        if (ch == 'q' || ch == 'Q') break;
    }

    // ��� ���
   
    printf("get_length : %d \n", get_length(list));
    printf("is_empty : %d, is_full : %d \n", is_empty(list), is_full(list));
    printf("get_entry : %d ��ġ�� �����ʹ� %d\n", 5, get_entry(list, 5));
    printf("is_in_list : %d �� ��ġ�� %d \n", 5415, is_in_list(list, 5415));
    printf("is_in_list : %d �� ��ġ�� %d \n", 10, is_in_list(list, 10));
    printf("delete : %d�� ��ġ�� %d \n", 5415, delete(&list, 5415));
    display(list);
    printf("call clear\n");
    list = clear(list);
    display(list);
    printf("get_length : %d \n", get_length(list));

    printf("��ټ� ChatGPT�� �̿��Ͽ� ������ �ڵ��Դϴ�... ������ ���� �����ŵ� �˴ϴ�.. \n");
    _getch();

    return 0;
}

#endif