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
    int last; // 배열의 마지막 요소를 가리키는 인덱스
} SortedList;

// 리스트 초기화
void initList(SortedList* list) {
    list->last = -1;
}

// 리스트가 비었는지 확인
int is_empty(const SortedList* list) {
    return list->last == -1;
}

// 리스트가 꽉 찼는지 확인
int is_full(const SortedList* list) {
    return list->last == MAX_LIST_SIZE - 1;
}

// 리스트의 길이(요소 개수) 반환
int get_length(const SortedList* list) {
    return list->last + 1;
}

// 리스트 출력
void display(const SortedList* list) {
    for (int i = 0; i <= list->last; i++) {
        printf("%d -> ", list->elements[i]);
    }
    printf("\n");
}

// 리스트에서 특정 위치의 요소 가져오기
int get_entry(const SortedList* list, int pos) {
    if (pos < 0 || pos > list->last) {
        return -1; // 잘못된 위치
    }
    return list->elements[pos];
}

// 리스트에 요소 추가
void add(SortedList* list, ElementType item) {
    if (is_full(list)) {
        return; // 리스트가 꽉 찼으면 추가하지 않음
    }
    int i;
    for (i = list->last; (i >= 0 && list->elements[i] > item); i--) {
        list->elements[i + 1] = list->elements[i];
    }
    list->elements[i + 1] = item;
    list->last++;
}

// 리스트에서 요소 삭제 후 인덱스 반환
int delete(SortedList* list, ElementType item) {
    int i, j;
    for (i = 0; i <= list->last; i++) {
        if (list->elements[i] == item) {
            for (j = i; j < list->last; j++) {
                list->elements[j] = list->elements[j + 1];
            }
            list->last--;
            return i; // 삭제된 요소의 인덱스 반환
        }
    }
    return -1; // 요소를 찾지 못한 경우
}

// 리스트에 특정 요소가 있는지 확인하고 인덱스 반환
int is_in_list(const SortedList* list, ElementType item) {
    for (int i = 0; i <= list->last; i++) {
        if (list->elements[i] == item) {
            return i;
        }
    }
    return -1; // 요소를 찾지 못한 경우
}

// 리스트의 모든 요소를 삭제하고 초기화
void clear(SortedList* list) {
    list->last = -1;
}

int main(void) {
    SortedList list;
    int ch;

    printf("배열을 이용하여 정렬 리스트 만들기\n");

    initList(&list);
    srand(100);
    while (!is_full(&list)) {
        int item = rand() % 10000; // 랜덤한 숫자 생성
        add(&list, item);
        display(&list);
        ch = _getch();
        if (ch == 'q' || ch == 'Q') break;
    }

    // 결과 출력
    
    printf("get_length : %d \n", get_length(&list));
    printf("is_empty : %d, is_full : %d \n", is_empty(&list), is_full(&list));
    printf("get_entry : 5 위치의 데이터는 %d\n", get_entry(&list, 5));
    printf("is_in_list : %d 의 위치는 %d \n", 5415, is_in_list(&list, 5415));
    printf("is_in_list : %d 의 위치는 %d \n", 10, is_in_list(&list, 10));
    printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));
    display(&list);
    printf("call clear\n");
    clear(&list);
    display(&list);
    printf("get_length : %d \n", get_length(&list));
 
    printf("대다수 ChatGPT를 이용하여 구현한 코드입니다... 점수를 팍팍 깎으셔도 됩니다.. \n");
    _getch();

    return 0;
}


#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

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

int delete(SortedList** list, int item) { // 삭제함수는 ChatGPT를 이용하였습니다...
    if (*list == NULL) {
        return -1; // 리스트가 비어있다면 -1 반환
    }

    int idx = 0; // 삭제할 요소의 인덱스를 추적
    SortedList* current = *list;
    SortedList* previous = NULL;

    while (current != NULL) {
        if (current->data == item) {
            // 첫 번째 요소를 삭제하는 경우
            if (previous == NULL) {
                *list = current->next;
            }
            else {
                previous->next = current->next;
            }
            free(current);
            return idx; // 삭제된 요소의 인덱스 반환
        }
        previous = current;
        current = current->next;
        idx++;
    }

    return -1; // 요소를 찾지 못한 경우 -1 반환
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

    printf("연결리스트를 이용하여 정렬 리스트 만들기\n");

    srand(100);
    while (1) {
        int item = rand();
        list = add(list, item);
        display(list);
        ch = _getch();
        if (ch == 'q' || ch == 'Q') break;
    }

    // 결과 출력
   
    printf("get_length : %d \n", get_length(list));
    printf("is_empty : %d, is_full : %d \n", is_empty(list), is_full(list));
    printf("get_entry : %d 위치의 데이터는 %d\n", 5, get_entry(list, 5));
    printf("is_in_list : %d 의 위치는 %d \n", 5415, is_in_list(list, 5415));
    printf("is_in_list : %d 의 위치는 %d \n", 10, is_in_list(list, 10));
    printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));
    display(list);
    printf("call clear\n");
    list = clear(list);
    display(list);
    printf("get_length : %d \n", get_length(list));

    printf("대다수 ChatGPT를 이용하여 구현한 코드입니다... 점수를 팍팍 깎으셔도 됩니다.. \n");
    _getch();

    return 0;
}

#endif