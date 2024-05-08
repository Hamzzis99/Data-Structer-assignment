#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �л� ������ �����ϴ� ����ü ����
typedef struct ELEMENT {
    int id_num;     // �й�
    char name[10];  // �̸�
} element;

// ���� Ž�� Ʈ���� ��� ����ü ����
typedef struct TreeNode {
    element std;        // �л� ����
    struct TreeNode* left;  // ���� �ڽ� ��� ������
    struct TreeNode* right; // ������ �ڽ� ��� ������
} TreeNode;

// ���ο� ��带 �����ϰ� �ʱ�ȭ�ϴ� �Լ�
TreeNode* new_node(element item) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode)); // �� ��� �޸� �Ҵ�
    temp->std = item; // ��� �ʱ�ȭ
    temp->left = temp->right = NULL; // �ڽ� ��� ������ NULL�� �ʱ�ȭ
    return temp; // ���� ������ ��� ��ȯ
}

// ���� Ž�� Ʈ���� ���ο� ��带 �����ϴ� �Լ�
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

// ���� Ž�� Ʈ������ ���� ���� ���� ���� ��带 ã�� �Լ�
TreeNode* min_value_node(TreeNode* node) {
    TreeNode* current = node;
    // ���� ���� ��带 ã��(���� ���� ��)
    while (current && current->left != NULL)
        current = current->left;
    return current; // ���� ���� ���� ���� ��� ��ȯ
}

// ���� Ž�� Ʈ������ ��带 �����ϴ� �Լ�
TreeNode* delete_node(TreeNode* root, int id) {
    if (root == NULL) return root; // ������ ��尡 ������ NULL ��ȯ

    // ������ ��带 ã�Ƽ� ��������� �̵�
    if (id < root->std.id_num) { // ������ Ű�� ���� ����� Ű���� ������
        root->left = delete_node(root->left, id); // ���� ����Ʈ������ ����
    }
    else if (id > root->std.id_num) { // ������ Ű�� ���� ����� Ű���� ũ��
        root->right = delete_node(root->right, id); // ������ ����Ʈ������ ����
    }
    else {
        // ������ ��带 ã������ ���� ���� ����
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root); // ��� �޸� ����
            return temp; // ������ �ڽ��� ���� ��忡 ����
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root); // ��� �޸� ����
            return temp; // ���� �ڽ��� ���� ��忡 ����
        }

        // �� ���� �ڽ��� ������ ���� ���
        TreeNode* temp = min_value_node(root->right); // ������ ����Ʈ������ �İ� ��带 ã��
        root->std = temp->std; // �İ� ����� ���� ���� ��忡 ����
        root->right = delete_node(root->right, temp->std.id_num); // �İ� ��� ����
    }
    return root; // ����� ��Ʈ ��� ��ȯ
}

// ���� Ž�� Ʈ���� ���̸� ��ȯ�ϴ� �Լ�
int get_height(TreeNode* node) {
    if (node == NULL) return 0; // �� Ʈ���� ���̴� 0
    int leftHeight = get_height(node->left); // ���� ����Ʈ���� ����
    int rightHeight = get_height(node->right); // ������ ����Ʈ���� ����
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1; // �� ū ���̿� 1�� ���ؼ� ��ȯ
}

// ���� Ž�� Ʈ���� ��� ���� ����ϴ� �Լ�
int get_node_count(TreeNode* node) {
    if (node == NULL) return 0; // ��尡 ������ 0
    return 1 + get_node_count(node->left) + get_node_count(node->right); // ���� ��� + ���� ����Ʈ�� + ������ ����Ʈ��
}

// ���� Ž�� Ʈ������ �ܸ� ����� ���� ����ϴ� �Լ�
int get_leaf_count(TreeNode* node) {
    if (node == NULL) return 0; // ��尡 ������ 0
    if (node->left == NULL && node->right == NULL) return 1; // �ܸ� ���� 1
    return get_leaf_count(node->left) + get_leaf_count(node->right); // ���� ����Ʈ�� + ������ ����Ʈ��
}

// ���� Ž�� Ʈ���� ���� ��ȸ�ϸ� ��带 ����ϴ� �Լ�
void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left); // ���� ����Ʈ�� ��ȸ
        printf("[%d] ", root->std.id_num); // ���� ��� ó��
        inorder(root->right); // ������ ����Ʈ�� ��ȸ
    }
}

// �־��� id�� ��带 ã�� �Լ�
TreeNode* search(TreeNode* root, int id) {
    if (root == NULL || root->std.id_num == id) return root; // ��带 ã�ų� ���� ���������� ��ȯ
    if (root->std.id_num < id) return search(root->right, id); // ã�� Ű�� �� ũ�� ���������� �̵�
    return search(root->left, id); // ã�� Ű�� �� ������ �������� �̵�
}

// ���� Ž�� Ʈ���� ��� ��带 �����ϴ� �Լ�
TreeNode* delete_tree(TreeNode* root) {
    if (root) {
        delete_tree(root->left); // ���� ����Ʈ�� ����
        delete_tree(root->right); // ������ ����Ʈ�� ����
        free(root); // ���� ��� �޸� ����
    }
    return NULL; // Ʈ���� ������ ���������� ��Ÿ��
}

void level_order(TreeNode* root) {
    if (root == NULL) {
        printf("Ʈ���� ��� �ֽ��ϴ�.\n");
        return;
    }

    TreeNode* queue[1000];
    int front = 0, rear = 0;
    
    queue[rear++] = root;  // ť�� ��Ʈ ��� �߰�
    queue[rear++] = NULL;  // ���� ������ ���� NULL ��Ŀ �߰�

    int level = 1;

    printf("Level 1: [%d]\n", root->std.id_num);

    // Level 2���� ����� ����
    if (root->left || root->right) {
        printf("Level %d: ", level + 1);
    }

    while (front < rear) {
        TreeNode* node = queue[front++]; // ť���� ��� ����

        if (node == NULL) {
            if (front < rear && queue[front]) { // NULL ��Ŀ ������ ��尡 �� ������ �� ���� ����
                level++;
                // ť�� ���� ��Ұ� NULL�� �ƴ� ���� ������ ���
          
                printf("\nLevel %d: ", level + 1);
                queue[rear++] = NULL; // ���� ������ �߰�
            }
        }
        else {
            if (node->left) {
                queue[rear++] = node->left; // ���� �ڽ� ��带 ť�� �߰�
            }
            if (node->right) {
                queue[rear++] = node->right; // ������ �ڽ� ��带 ť�� �߰�
            }
            if (level > 0) { // LEVEL 1�� ��Ʈ ��常 ����ϰ�, �� ���� ���������� �ڽ� ��� ���
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
	printf("���� Ž�� Ʈ���� ��� ��, leaf��� ��, ���� ���ϱ�\n");
	printf("��� �� = %d \nleaf ��� �� = %d \n���� = %d \n\n", get_node_count(root), get_leaf_count(root), get_height(root));
	printf("���� Ž�� Ʈ�� ���� Ž�� ��ȸ ���\n");
	level_order(root);
	printf("\n\n");
	printf("���� Ž�� Ʈ�� ���� ��ȸ ��� \n");
	inorder(root);
	printf("\n\n���� Ž�� Ʈ������ 2021010 �˻�\n");
	tmp = search(root, 2021010);
	if (tmp != NULL)
		printf("�˻� ���� : �й� %d, �̸� %s \n", tmp->std.id_num, tmp->std.name);
	else
		printf("���� Ž�� Ʈ������ �˻� �л��� �߰߸��� \n");
	printf("\n���� Ž�� Ʈ������ 2021006 ����\n");
	delete_node(root, 2021006);
	printf("\n\n���� Ž�� Ʈ������ 2021006 �˻�\n");
    tmp = search(root, 2021006);
	if (tmp != NULL)
		printf("�˻� ���� : �й� %d, �̸� %s \n", tmp->std.id_num, tmp->std.name);
	else
		printf("���� Ž�� Ʈ������ �˻� �л��� �߰߸��� \n");
	printf("\n\n���� Ž�� Ʈ�� ���� ��ȸ ��� \n");
	inorder(root);
	printf("\n\n");
	printf("\n\n���� Ž�� Ʈ�� ��ü ���� \n");
	root = delete_tree(root);
	printf("\n\n���� Ž�� Ʈ�� ���� Ž�� ��ȸ ���\n");
	level_order(root);
	printf("\n\n");
	return 0;
}