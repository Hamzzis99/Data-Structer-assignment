#define _CRT_SECURE_NO_WARNINGS
#define PROB 1


#if PROB == 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int element;

void swap(element* xp, element* yp) {
    element temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(element arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

void heapify(element arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(element arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main(void) {
    int SIZE = 10;  // or any other value to test
    element* list = malloc(sizeof(element) * SIZE);

    srand(100);
    for (int i = 0; i < SIZE; i++)
        list[i] = rand();

    printf("정수형 데이터 %d개 정렬 \n", SIZE);
    if (SIZE < 100) {
        for (int i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n\n");
    }

    clock_t s_time, e_time;

    s_time = clock();
    heapSort(list, SIZE);
    e_time = clock();
    printf("Heap Sort 걸린 시간 : %d msec\n", (e_time - s_time) * 1000 / CLOCKS_PER_SEC);

    if (SIZE < 100) {
        for (int i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n\n");
    }

    // 재정렬을 위해 다시 랜덤 데이터 생성
    for (int i = 0; i < SIZE; i++)
        list[i] = rand();

    s_time = clock();
    selectionSort(list, SIZE);
    e_time = clock();
    printf("Selection Sort 걸린 시간 : %d msec\n", (e_time - s_time) * 1000 / CLOCKS_PER_SEC);

    if (SIZE < 100) {
        for (int i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n");
    }

    free(list);
    return 0;
}


#elif PROB == 2

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200  // 힙의 최대 요소 수를 정의

// 트리 노드 구조체 정의
typedef struct TreeNode {
    int weight;  // 노드의 가중치
    char ch;  // 문자 (단말 노드일 경우)
    struct TreeNode* left;  // 왼쪽 자식 노드 포인터
    struct TreeNode* right;  // 오른쪽 자식 노드 포인터
} TreeNode;

typedef TreeNode* element;  // element 타입을 TreeNode 포인터로 정의

// 최소 힙을 위한 구조체 정의
typedef struct {
    element heap[MAX_ELEMENT];  // 요소를 저장할 배열
    int heap_size;  // 힙의 현재 크기
} HeapType;

// 힙 생성 함수
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));  // 힙 구조체 메모리 할당
}

// 힙 초기화 함수
void init(HeapType* h) {
    h->heap_size = 0;  // 힙의 크기를 0으로 초기화
}

// 최소 힙에 요소 삽입 함수
void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);  // 힙 크기를 1 증가시키고 새 요소의 위치를 결정
    while ((i != 1) && (item->weight < h->heap[i / 2]->weight)) {
        h->heap[i] = h->heap[i / 2];  // 부모 노드와 비교하여 교환
        i /= 2;
    }
    h->heap[i] = item;  // 새로운 요소를 삽입
}

// 최소 힙에서 요소 삭제 함수
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;
    item = h->heap[1];  // 루트 노드를 반환할 항목
    temp = h->heap[h->heap_size--];  // 힙의 마지막 요소
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        // 두 자식 중 더 작은 자식을 찾는다
        if ((child < h->heap_size) && (h->heap[child]->weight > h->heap[child + 1]->weight)) {
            child++;
        }
        if (temp->weight <= h->heap[child]->weight) break;
        h->heap[parent] = h->heap[child];  // 한 단계 아래로 이동
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 노드가 리프 노드인지 확인하는 함수
int is_leaf(TreeNode* node) {
    return !(node->left) && !(node->right);
}

// 두 개의 서브트리를 합쳐서 새 트리 노드를 만드는 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->weight = left->weight + right->weight;  // 가중치는 자식 노드의 가중치의 합
    node->left = left;
    node->right = right;
    node->ch = 0;  // 리프 노드가 아닐 경우 0으로 설정
    return node;
}

// 트리 제거 함수
void destroy_tree(TreeNode* root) {
    if (root != NULL) {
        destroy_tree(root->left);  // 왼쪽 서브트리 제거
        destroy_tree(root->right);  // 오른쪽 서브트리 제거
        free(root);  // 루트 노드 메모리 해제
    }
}

// 허프만 트리 생성 함수
TreeNode* make_huffman_tree(int freq[], char ch_list[], int n) {
    HeapType* heap = create();
    init(heap);
    for (int i = 0; i < n; i++) {
        TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
        node->ch = ch_list[i];
        node->weight = freq[i];
        node->left = node->right = NULL;
        insert_min_heap(heap, node);
    }

    while (heap->heap_size > 1) {
        TreeNode* left = delete_min_heap(heap);
        TreeNode* right = delete_min_heap(heap);
        printf("%d + %d -> %d\n", left->weight, right->weight, left->weight + right->weight);
        TreeNode* top = make_tree(left, right);
        insert_min_heap(heap, top);
    }

    TreeNode* result = delete_min_heap(heap);
    free(heap);
    return result;
}

// 허프만 코드 출력 함수
void print_codes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1;  // 왼쪽으로 갈 때 1 추가
        print_codes(root->left, codes, top + 1);
    }
    if (root->right) {
        codes[top] = 0;  // 오른쪽으로 갈 때 0 추가
        print_codes(root->right, codes, top + 1);
    }
    if (is_leaf(root)) {
        printf("%c: ", root->ch);  // 리프 노드에서 문자와 코드 출력
        for (int i = 0; i < top; i++) {
            printf("%d", codes[i]);
        }
        printf("\n");
    }
}

// 허프만 디코딩 함수
void huffman_decode(TreeNode* root, const char* str) {
    TreeNode* current = root;
    int index = 0;
    int start_index = 0;

    while (str[index] != '\0') {
        if (is_leaf(current)) {
            for (int i = start_index; i < index; i++) {
                printf("%c", str[i]);  // 디코딩된 비트 시퀀스 출력
            }
            printf(" ==> %c\n", current->ch);  // 해당 문자 출력
            current = root;
            start_index = index;
        }
        current = (str[index] == '1') ? current->left : current->right;
        index++;
    }
    if (is_leaf(current)) {
        for (int i = start_index; i < index; i++) {
            printf("%c", str[i]);
        }
        printf(" ==> %c\n", current->ch);
    }
}

// 메인 함수
int main(void)
{
    char ch_list[] = { 's', 'i', 'n', 't', 'e' };  // 문자 목록
    int freq[] = { 4, 6, 8, 12, 15 };  // 각 문자의 빈도
    TreeNode* head;  // 허프만 트리의 루트 노드
    int codes[100];  // 허프만 코드 저장 배열

    printf("허프만 코드를 위한 트리 생성\n");
    head = make_huffman_tree(freq, ch_list, 5);  // 허프만 트리 생성

    printf("\n문자별 허프만 코드\n");
    print_codes(head, codes, 0);  // 생성된 허프만 코드 출력

    printf("\n허프만 코드를 이용한 디코딩 :\n");
    char* str1 = "1110101010000101";  // 디코딩할 문자열 1
    huffman_decode(head, str1);  // 문자열 1 디코딩
    printf("\n허프만 코드를 이용한 디코딩 :\n");
    char* str2 = "11111111111";  // 디코딩할 문자열 2
    huffman_decode(head, str2);  // 문자열 2 디코딩

    destroy_tree(head);  // 허프만 트리 제거
    return 0;
}

#endif







