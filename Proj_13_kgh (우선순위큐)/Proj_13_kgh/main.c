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

    printf("������ ������ %d�� ���� \n", SIZE);
    if (SIZE < 100) {
        for (int i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n\n");
    }

    clock_t s_time, e_time;

    s_time = clock();
    heapSort(list, SIZE);
    e_time = clock();
    printf("Heap Sort �ɸ� �ð� : %d msec\n", (e_time - s_time) * 1000 / CLOCKS_PER_SEC);

    if (SIZE < 100) {
        for (int i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n\n");
    }

    // �������� ���� �ٽ� ���� ������ ����
    for (int i = 0; i < SIZE; i++)
        list[i] = rand();

    s_time = clock();
    selectionSort(list, SIZE);
    e_time = clock();
    printf("Selection Sort �ɸ� �ð� : %d msec\n", (e_time - s_time) * 1000 / CLOCKS_PER_SEC);

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

#define MAX_ELEMENT 200  // ���� �ִ� ��� ���� ����

// Ʈ�� ��� ����ü ����
typedef struct TreeNode {
    int weight;  // ����� ����ġ
    char ch;  // ���� (�ܸ� ����� ���)
    struct TreeNode* left;  // ���� �ڽ� ��� ������
    struct TreeNode* right;  // ������ �ڽ� ��� ������
} TreeNode;

typedef TreeNode* element;  // element Ÿ���� TreeNode �����ͷ� ����

// �ּ� ���� ���� ����ü ����
typedef struct {
    element heap[MAX_ELEMENT];  // ��Ҹ� ������ �迭
    int heap_size;  // ���� ���� ũ��
} HeapType;

// �� ���� �Լ�
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));  // �� ����ü �޸� �Ҵ�
}

// �� �ʱ�ȭ �Լ�
void init(HeapType* h) {
    h->heap_size = 0;  // ���� ũ�⸦ 0���� �ʱ�ȭ
}

// �ּ� ���� ��� ���� �Լ�
void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);  // �� ũ�⸦ 1 ������Ű�� �� ����� ��ġ�� ����
    while ((i != 1) && (item->weight < h->heap[i / 2]->weight)) {
        h->heap[i] = h->heap[i / 2];  // �θ� ���� ���Ͽ� ��ȯ
        i /= 2;
    }
    h->heap[i] = item;  // ���ο� ��Ҹ� ����
}

// �ּ� ������ ��� ���� �Լ�
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;
    item = h->heap[1];  // ��Ʈ ��带 ��ȯ�� �׸�
    temp = h->heap[h->heap_size--];  // ���� ������ ���
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        // �� �ڽ� �� �� ���� �ڽ��� ã�´�
        if ((child < h->heap_size) && (h->heap[child]->weight > h->heap[child + 1]->weight)) {
            child++;
        }
        if (temp->weight <= h->heap[child]->weight) break;
        h->heap[parent] = h->heap[child];  // �� �ܰ� �Ʒ��� �̵�
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// ��尡 ���� ������� Ȯ���ϴ� �Լ�
int is_leaf(TreeNode* node) {
    return !(node->left) && !(node->right);
}

// �� ���� ����Ʈ���� ���ļ� �� Ʈ�� ��带 ����� �Լ�
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->weight = left->weight + right->weight;  // ����ġ�� �ڽ� ����� ����ġ�� ��
    node->left = left;
    node->right = right;
    node->ch = 0;  // ���� ��尡 �ƴ� ��� 0���� ����
    return node;
}

// Ʈ�� ���� �Լ�
void destroy_tree(TreeNode* root) {
    if (root != NULL) {
        destroy_tree(root->left);  // ���� ����Ʈ�� ����
        destroy_tree(root->right);  // ������ ����Ʈ�� ����
        free(root);  // ��Ʈ ��� �޸� ����
    }
}

// ������ Ʈ�� ���� �Լ�
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

// ������ �ڵ� ��� �Լ�
void print_codes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1;  // �������� �� �� 1 �߰�
        print_codes(root->left, codes, top + 1);
    }
    if (root->right) {
        codes[top] = 0;  // ���������� �� �� 0 �߰�
        print_codes(root->right, codes, top + 1);
    }
    if (is_leaf(root)) {
        printf("%c: ", root->ch);  // ���� ��忡�� ���ڿ� �ڵ� ���
        for (int i = 0; i < top; i++) {
            printf("%d", codes[i]);
        }
        printf("\n");
    }
}

// ������ ���ڵ� �Լ�
void huffman_decode(TreeNode* root, const char* str) {
    TreeNode* current = root;
    int index = 0;
    int start_index = 0;

    while (str[index] != '\0') {
        if (is_leaf(current)) {
            for (int i = start_index; i < index; i++) {
                printf("%c", str[i]);  // ���ڵ��� ��Ʈ ������ ���
            }
            printf(" ==> %c\n", current->ch);  // �ش� ���� ���
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

// ���� �Լ�
int main(void)
{
    char ch_list[] = { 's', 'i', 'n', 't', 'e' };  // ���� ���
    int freq[] = { 4, 6, 8, 12, 15 };  // �� ������ ��
    TreeNode* head;  // ������ Ʈ���� ��Ʈ ���
    int codes[100];  // ������ �ڵ� ���� �迭

    printf("������ �ڵ带 ���� Ʈ�� ����\n");
    head = make_huffman_tree(freq, ch_list, 5);  // ������ Ʈ�� ����

    printf("\n���ں� ������ �ڵ�\n");
    print_codes(head, codes, 0);  // ������ ������ �ڵ� ���

    printf("\n������ �ڵ带 �̿��� ���ڵ� :\n");
    char* str1 = "1110101010000101";  // ���ڵ��� ���ڿ� 1
    huffman_decode(head, str1);  // ���ڿ� 1 ���ڵ�
    printf("\n������ �ڵ带 �̿��� ���ڵ� :\n");
    char* str2 = "11111111111";  // ���ڵ��� ���ڿ� 2
    huffman_decode(head, str2);  // ���ڿ� 2 ���ڵ�

    destroy_tree(head);  // ������ Ʈ�� ����
    return 0;
}

#endif







