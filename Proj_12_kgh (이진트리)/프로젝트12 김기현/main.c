#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 학생 정보를 저장하는 구조체 정의
typedef struct ELEMENT {
    int id_num;     // 학번
    char name[10];  // 이름
} element;

// 이진 탐색 트리의 노드 구조체 정의
typedef struct TreeNode {
    element std;        // 학생 정보
    struct TreeNode* left;  // 왼쪽 자식 노드 포인터
    struct TreeNode* right; // 오른쪽 자식 노드 포인터
} TreeNode;

// 새로운 노드를 생성하고 초기화하는 함수
TreeNode* new_node(element item) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode)); // 새 노드 메모리 할당
    temp->std = item; // 노드 초기화
    temp->left = temp->right = NULL; // 자식 노드 포인터 NULL로 초기화
    return temp; // 새로 생성된 노드 반환
}

// 이진 탐색 트리에 새로운 노드를 삽입하는 함수
TreeNode* insert_node(TreeNode* node, element item) {
    if (node == NULL) return new_node(item);
    if (item.id_num < node->std.id_num) {
        node->left = insert_node(node->left, item);
    }
    else if (item.id_num > node->std.id_num) {
        node->right = insert_node(node->right, item);
    }
    return node;
}

// 이진 탐색 트리에서 가장 작은 값을 가진 노드를 찾는 함수
TreeNode* min_value_node(TreeNode* node) {
    TreeNode* current = node;
    // 가장 왼쪽 노드를 찾음(가장 작은 값)
    while (current && current->left != NULL)
        current = current->left;
    return current; // 가장 작은 값을 가진 노드 반환
}

// 이진 탐색 트리에서 노드를 삭제하는 함수
TreeNode* delete_node(TreeNode* root, int id) {
    if (root == NULL) return root; // 삭제할 노드가 없으면 NULL 반환

    // 삭제할 노드를 찾아서 재귀적으로 이동
    if (id < root->std.id_num) { // 삭제할 키가 현재 노드의 키보다 작으면
        root->left = delete_node(root->left, id); // 왼쪽 서브트리에서 삭제
    }
    else if (id > root->std.id_num) { // 삭제할 키가 현재 노드의 키보다 크면
        root->right = delete_node(root->right, id); // 오른쪽 서브트리에서 삭제
    }
    else {
        // 삭제할 노드를 찾았으면 삭제 과정 수행
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root); // 노드 메모리 해제
            return temp; // 오른쪽 자식을 상위 노드에 연결
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root); // 노드 메모리 해제
            return temp; // 왼쪽 자식을 상위 노드에 연결
        }

        // 두 개의 자식을 가지고 있을 경우
        TreeNode* temp = min_value_node(root->right); // 오른쪽 서브트리에서 후계 노드를 찾음
        root->std = temp->std; // 후계 노드의 값을 현재 노드에 복사
        root->right = delete_node(root->right, temp->std.id_num); // 후계 노드 삭제
    }
    return root; // 변경된 루트 노드 반환
}

// 이진 탐색 트리의 높이를 반환하는 함수
int get_height(TreeNode* node) {
    if (node == NULL) return 0; // 빈 트리면 높이는 0
    int leftHeight = get_height(node->left); // 왼쪽 서브트리의 높이
    int rightHeight = get_height(node->right); // 오른쪽 서브트리의 높이
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1; // 더 큰 높이에 1을 더해서 반환
}

// 이진 탐색 트리의 노드 수를 계산하는 함수
int get_node_count(TreeNode* node) {
    if (node == NULL) return 0; // 노드가 없으면 0
    return 1 + get_node_count(node->left) + get_node_count(node->right); // 현재 노드 + 왼쪽 서브트리 + 오른쪽 서브트리
}

// 이진 탐색 트리에서 단말 노드의 수를 계산하는 함수
int get_leaf_count(TreeNode* node) {
    if (node == NULL) return 0; // 노드가 없으면 0
    if (node->left == NULL && node->right == NULL) return 1; // 단말 노드면 1
    return get_leaf_count(node->left) + get_leaf_count(node->right); // 왼쪽 서브트리 + 오른쪽 서브트리
}

// 이진 탐색 트리를 중위 순회하며 노드를 출력하는 함수
void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left); // 왼쪽 서브트리 순회
        printf("[%d] ", root->std.id_num); // 현재 노드 처리
        inorder(root->right); // 오른쪽 서브트리 순회
    }
}

// 주어진 id로 노드를 찾는 함수
TreeNode* search(TreeNode* root, int id) {
    if (root == NULL || root->std.id_num == id) return root; // 노드를 찾거나 끝에 도달했으면 반환
    if (root->std.id_num < id) return search(root->right, id); // 찾는 키가 더 크면 오른쪽으로 이동
    return search(root->left, id); // 찾는 키가 더 작으면 왼쪽으로 이동
}

// 이진 탐색 트리의 모든 노드를 삭제하는 함수
TreeNode* delete_tree(TreeNode* root) {
    if (root) {
        delete_tree(root->left); // 왼쪽 서브트리 삭제
        delete_tree(root->right); // 오른쪽 서브트리 삭제
        free(root); // 현재 노드 메모리 해제
    }
    return NULL; // 트리가 완전히 삭제됐음을 나타냄
}

void level_order(TreeNode* root) {
    if (root == NULL) {
        printf("트리가 비어 있습니다.\n");
        return;
    }

    TreeNode* queue[1000];
    int front = 0, rear = 0;
    
    queue[rear++] = root;  // 큐에 루트 노드 추가
    queue[rear++] = NULL;  // 레벨 구분을 위한 NULL 마커 추가

    int level = 1;

    printf("Level 1: [%d]\n", root->std.id_num);

    // Level 2부터 출력을 시작
    if (root->left || root->right) {
        printf("Level %d: ", level + 1);
    }

    while (front < rear) {
        TreeNode* node = queue[front++]; // 큐에서 노드 추출

        if (node == NULL) {
            if (front < rear && queue[front]) { // NULL 마커 다음에 노드가 더 있으면 새 레벨 시작
                level++;
                // 큐의 다음 요소가 NULL이 아닐 때만 레벨을 출력
          
                printf("\nLevel %d: ", level + 1);
                queue[rear++] = NULL; // 레벨 구분자 추가
            }
        }
        else {
            if (node->left) {
                queue[rear++] = node->left; // 왼쪽 자식 노드를 큐에 추가
            }
            if (node->right) {
                queue[rear++] = node->right; // 오른쪽 자식 노드를 큐에 추가
            }
            if (level > 0) { // LEVEL 1은 루트 노드만 출력하고, 그 후의 레벨에서는 자식 노드 출력
                if (node->left) {
                    printf("<%d> -> [%d] ", node->std.id_num, node->left->std.id_num);
                }
                if (node->right) {
                    printf("<%d> -> [%d] ", node->std.id_num, node->right->std.id_num);
                }
            }
        }
    }

    printf("\n");
}


int main(void)
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	element item;
	item.id_num = 2021006; strcpy(item.name, "name6");
	root = insert_node(root, item);
	item.id_num = 2021001; strcpy(item.name, "name1");
	root = insert_node(root, item);
	item.id_num = 2021009; strcpy(item.name, "name9");
	root = insert_node(root, item);
	item.id_num = 2021007; strcpy(item.name, "name7");
	root = insert_node(root, item);
	item.id_num = 2021003; strcpy(item.name, "name3");
	root = insert_node(root, item);
	item.id_num = 2021002; strcpy(item.name, "name2");
	root = insert_node(root, item);
	item.id_num = 2021005; strcpy(item.name, "name5");
	root = insert_node(root, item);
	item.id_num = 2021004; strcpy(item.name, "name4");
	root = insert_node(root, item);
	item.id_num = 2021008; strcpy(item.name, "name8");
	root = insert_node(root, item);
	item.id_num = 2021010; strcpy(item.name, "name10");
	root = insert_node(root, item);
	printf("이진 탐색 트리의 노드 수, leaf노드 수, 높이 구하기\n");
	printf("노드 수 = %d \nleaf 노드 수 = %d \n높이 = %d \n\n", get_node_count(root), get_leaf_count(root), get_height(root));
	printf("이진 탐색 트리 레벨 탐색 순회 결과\n");
	level_order(root);
	printf("\n\n");
	printf("이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n이진 탐색 트리에서 2021010 검색\n");
	tmp = search(root, 2021010);
	if (tmp != NULL)
		printf("검색 성공 : 학번 %d, 이름 %s \n", tmp->std.id_num, tmp->std.name);
	else
		printf("이진 탐색 트리에서 검색 학생을 발견못함 \n");
	printf("\n이진 탐색 트리에서 2021006 삭제\n");
	delete_node(root, 2021006);
	printf("\n\n이진 탐색 트리에서 2021006 검색\n");
    tmp = search(root, 2021006);
	if (tmp != NULL)
		printf("검색 성공 : 학번 %d, 이름 %s \n", tmp->std.id_num, tmp->std.name);
	else
		printf("이진 탐색 트리에서 검색 학생을 발견못함 \n");
	printf("\n\n이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n");
	printf("\n\n이진 탐색 트리 전체 삭제 \n");
	root = delete_tree(root);
	printf("\n\n이진 탐색 트리 레벨 탐색 순회 결과\n");
	level_order(root);
	printf("\n\n");
	return 0;
}